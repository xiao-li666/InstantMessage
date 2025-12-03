#include "chatdialog.h"
#include "ui_chatdialog.h"
#include <QAction>
#include "chatuserwid.h"
#include <QRandomGenerator>
#include "loadingdlg.h"
#include <QPixmap>
#include <vector>
#include "global.h"
#include "tcpmgr.h"
#include "usermgr.h"
#include "conuseritem.h"

ChatDialog::ChatDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ChatDialog), _mode(ChatUIMode::ChatMode),_state(ChatUIMode::ChatMode),_b_loading(false)
{
    ui->setupUi(this);
    ui->addBtn->SetState("normal","hover","press");
    ui->searchEdit->SetMaxLength(25);

    QAction *searchAction = new QAction(ui->searchEdit);
    searchAction->setIcon(QIcon(":/res/search.png"));
    ui->searchEdit->addAction(searchAction, QLineEdit::LeadingPosition);
    ui->searchEdit->setPlaceholderText(QStringLiteral("搜索"));

    QAction *clearAction = new QAction(ui->searchEdit);
    clearAction->setIcon(QIcon(":/res/close_transparent.png"));
    ui->searchEdit->addAction(clearAction, QLineEdit::TrailingPosition);
    //当需要显示图标时更改为实际的清除图标
    connect(ui->searchEdit, &QLineEdit::textChanged, this, [clearAction](const QString &text){
        if(!text.isEmpty()){
            clearAction->setIcon(QIcon(":/res/close_search.png"));
        }
        else{
            clearAction->setIcon(QIcon(":/res/close_transparent.png"));
        }
    });
    //点击左侧清除按钮，清除搜索框中的文本
    connect(clearAction, &QAction::triggered, this, [this, clearAction](){
        ui->searchEdit->clear();
        clearAction->setIcon(QIcon(":/res/close_transparent.png"));
        ui->searchEdit->clearFocus();
        //清除按钮被按下则不显示搜索框
        showSearch(false);
    });
    //默认情况下隐藏搜索框
    showSearch(false);

    connect(ui->chatUserList, &ChatUserList::sig_loading_chat_user, this, &ChatDialog::slot_uploading_chatUser);
    addChatUserList();
    QString head_icon = UserMgr::GetInstance()->GetIcon();
    QPixmap pixmap(head_icon); // 加载图片
    ui->sideHeadLabel->setPixmap(pixmap);
    QPixmap scaledPixmap = pixmap.scaled(ui->sideHeadLabel->size(),Qt::KeepAspectRatio);
    ui->sideHeadLabel->setPixmap(scaledPixmap);
    ui->sideHeadLabel->setScaledContents(true); //图片自适应大小

    ui->sideChatLabel->setProperty("state","normal");
    ui->sideChatLabel->SetState("normal","hover","pressed","selected_normal","selected_hover","selected_pressed");
    ui->sideContactLabel->SetState("normal","hover","pressed","selected_normal","selected_hover","selected_pressed");
    //ui->sideHeadLabel->SetState("normal","hover","pressed","selected","selected_hover","selected_pressed");

    AddLBGroup(ui->sideChatLabel);
    AddLBGroup(ui->sideContactLabel);

    connect(ui->sideChatLabel,&StateWidget::clicked, this, &ChatDialog::slot_side_chat);
    connect(ui->sideContactLabel,&StateWidget::clicked, this, &ChatDialog::slot_side_contact);

    //链接搜索框输入变化
    connect(ui->searchEdit, &QLineEdit::textChanged, this, &ChatDialog::slot_text_changed);

    showSearch(false);
    //检测鼠标点击的位置判断是否要清空搜索框
    this->installEventFilter(this); //安装事件过滤器

    ui->sideChatLabel->SetSelected(true);

    //为searchlist设置searchedit
    ui->searchUserList->SetSearchEdit(ui->searchEdit);

    //连接申请添加好友的请求
    connect(TcpMgr::GetInstance().get(),&TcpMgr::sig_friend_apply,this,&ChatDialog::slot_friend_apply);

    //连接认证添加好友信号
    connect(TcpMgr::GetInstance().get(), &TcpMgr::sig_add_auth_friend, this, &ChatDialog::slot_add_auth_friend);
    connect(TcpMgr::GetInstance().get(), &TcpMgr::sig_auth_rsp, this, &ChatDialog::slot_auth_rsp);

    //连接searchlist跳转聊天信号
    connect(ui->searchUserList, &SearchList::sig_jump_chat_item, this, &ChatDialog::slot_jump_chat_item);
    //连接加载联系人的信号和槽函数
    connect(ui->conUserList, &ContactUserList::sig_loading_contact_user,
            this, &ChatDialog::slot_loading_contact_user);
}

ChatDialog::~ChatDialog()
{
    delete ui;
}

void ChatDialog::addChatUserList()
{
    //先按照好友列表加载聊天记录，等以后客户端实现聊天记录数据库之后再按照最后信息排序
    auto friend_list = UserMgr::GetInstance()->GetChatListPerPage();
    if (friend_list.empty() == false) {
        for(auto & friend_ele : friend_list){
            auto find_iter = _chat_items_added.find(friend_ele->_uid);
            if(find_iter != _chat_items_added.end()){
                continue;
            }
            auto *chat_user_wid = new ChatUserWid();
            auto user_info = std::make_shared<UserInfo>(friend_ele);
            chat_user_wid->SetInfo(user_info);
            QListWidgetItem *item = new QListWidgetItem;
            //qDebug()<<"chat_user_wid sizeHint is " << chat_user_wid->sizeHint();
            item->setSizeHint(chat_user_wid->sizeHint());
            ui->chatUserList->addItem(item);
            ui->chatUserList->setItemWidget(item, chat_user_wid);
            _chat_items_added.insert(friend_ele->_uid, item);
        }

        //更新已加载条目
        UserMgr::GetInstance()->UpdateChatLoadedCount();
    }

    for(int i = 0; i < 13; i++){
        int randomValue = QRandomGenerator::global()->bounded(100);
        int str_i = randomValue%strs.size();
        int head_i = randomValue%heads.size();
        int name_i = randomValue%names.size();

        auto *chat_user_wid = new ChatUserWid();
        chat_user_wid->SetInfo(names[name_i],heads[head_i],strs[str_i]);
        QListWidgetItem *item = new QListWidgetItem;
        item->setSizeHint(chat_user_wid->sizeHint());//设置item的尺寸
        ui->chatUserList->addItem(item);//添加item
        ui->chatUserList->setItemWidget(item,chat_user_wid);//将一个自定义的QWidget设置为QListWidgetItem的显示内容
    }
}

void ChatDialog::ClearLabelState(StateWidget *lb)
{
    for(auto &ele: _lb_list){
        if(ele == lb){
            continue;
        }
        ele->ClearState();
    }
}

bool ChatDialog::eventFilter(QObject *watched, QEvent *event)
{
    if(event->type() == QEvent::MouseButtonPress){
        QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
        handleGlobalMousePress(mouseEvent);
    }
    return QDialog::eventFilter(watched, event);
}

void ChatDialog::handleGlobalMousePress(QMouseEvent *event)
{
    // 实现点击位置的判断和处理逻辑
    // 先判断是否处于搜索模式，如果不处于搜索模式则直接返回
    if( _mode != ChatUIMode::SearchMode){
        return;
    }

    // 将鼠标点击位置转换为搜索列表坐标系中的位置
    QPoint posInSearchList = ui->searchUserList->mapFromGlobal(event->globalPos());
    // 判断点击位置是否在聊天列表的范围内
    if (!ui->searchUserList->rect().contains(posInSearchList)) {
        // 如果不在聊天列表内，清空输入框
        ui->searchEdit->clear();
        showSearch(false);
    }
}

void ChatDialog::showSearch(bool bSearch)
{
    if(bSearch){
        ui->searchUserList->show();
        ui->chatUserList->hide();
        ui->conUserList->hide();
        _mode = ChatUIMode::SearchMode;
    }
    else if(_state == ChatUIMode::ChatMode){
        ui->searchUserList->hide();
        ui->chatUserList->show();
        ui->conUserList->hide();
        _mode = ChatUIMode::ChatMode;
    }
    else if(_state == ChatUIMode::ContactMode){
        ui->searchUserList->hide();
        ui->chatUserList->hide();
        ui->conUserList->show();
        _mode = ChatUIMode::ContactMode;
    }

}

void ChatDialog::AddLBGroup(StateWidget *lb)
{
    _lb_list.push_back(lb);
}

void ChatDialog::SetSelectChatItem(int uid)
{
    if(ui->chatUserList->count() <= 0){
        return;
    }

    if(uid == 0){
        ui->chatUserList->setCurrentRow(0);
        QListWidgetItem *firstItem = ui->chatUserList->item(0);
        if(!firstItem){
            return;
        }

        //转为widget
        QWidget *widget = ui->chatUserList->itemWidget(firstItem);
        if(!widget){
            return;
        }

        auto con_item = qobject_cast<ChatUserWid*>(widget);
        if(!con_item){
            return;
        }

        _cur_chat_uid = con_item->GetUserInfo()->_uid;

        return;
    }

    auto find_iter = _chat_items_added.find(uid);
    if(find_iter == _chat_items_added.end()){
        qDebug() << "uid " <<uid<< " not found, set curent row 0";
        ui->chatUserList->setCurrentRow(0);
        return;
    }

    ui->chatUserList->setCurrentItem(find_iter.value());

    _cur_chat_uid = uid;
}

void ChatDialog::SetSelectChatPage(int uid)
{
    if( ui->chatUserList->count() <= 0){
        return;
    }

    if (uid == 0) {
        auto item = ui->chatUserList->item(0);
        //转为widget
        QWidget* widget = ui->chatUserList->itemWidget(item);
        if (!widget) {
            return;
        }

        auto con_item = qobject_cast<ChatUserWid*>(widget);
        if (!con_item) {
            return;
        }

        //设置信息
        auto user_info = con_item->GetUserInfo();
        ui->chatPage->SetUserInfo(user_info);
        return;
    }

    auto find_iter = _chat_items_added.find(uid);
    if(find_iter == _chat_items_added.end()){
        return;
    }

    //转为widget
    QWidget *widget = ui->chatUserList->itemWidget(find_iter.value());
    if(!widget){
        return;
    }

    //判断转化为自定义的widget
    // 对自定义widget进行操作， 将item 转化为基类ListItemBase
    ListItemBase *customItem = qobject_cast<ListItemBase*>(widget);
    if(!customItem){
        qDebug()<< "qobject_cast<ListItemBase*>(widget) is nullptr";
        return;
    }

    auto itemType = customItem->GetItemType();
    if(itemType == CHAT_USER_ITEM){
        auto con_item = qobject_cast<ChatUserWid*>(customItem);
        if(!con_item){
            return;
        }

        //设置信息
        auto user_info = con_item->GetUserInfo();
        ui->chatPage->SetUserInfo(user_info);

        return;
    }

}

void ChatDialog::loadMoreChatUser()
{
    auto friend_list = UserMgr::GetInstance()->GetChatListPerPage();
    if (friend_list.empty() == false) {
        for(auto & friend_ele : friend_list){
            auto find_iter = _chat_items_added.find(friend_ele->_uid);
            if(find_iter != _chat_items_added.end()){
                continue;
            }
            auto *chat_user_wid = new ChatUserWid();
            auto user_info = std::make_shared<UserInfo>(friend_ele);
            chat_user_wid->SetInfo(user_info);
            QListWidgetItem *item = new QListWidgetItem;
            //qDebug()<<"chat_user_wid sizeHint is " << chat_user_wid->sizeHint();
            item->setSizeHint(chat_user_wid->sizeHint());
            ui->chatUserList->addItem(item);
            ui->chatUserList->setItemWidget(item, chat_user_wid);
            _chat_items_added.insert(friend_ele->_uid, item);
        }

        //更新已加载条目
        UserMgr::GetInstance()->UpdateChatLoadedCount();
    }
}

void ChatDialog::loadMoreConUser()
{
    auto friend_list = UserMgr::GetInstance()->GetConListPerPage();
    if (friend_list.empty() == false) {
        for(auto & friend_ele : friend_list){
            auto *chat_user_wid = new ConUserItem();
            chat_user_wid->SetInfo(friend_ele->_uid,friend_ele->_name,
                                   friend_ele->_icon);
            QListWidgetItem *item = new QListWidgetItem;
            //qDebug()<<"chat_user_wid sizeHint is " << chat_user_wid->sizeHint();
            item->setSizeHint(chat_user_wid->sizeHint());
            ui->conUserList->addItem(item);
            ui->conUserList->setItemWidget(item, chat_user_wid);
        }

        //更新已加载条目
        UserMgr::GetInstance()->UpdateContactLoadedCount();
    }
}

void ChatDialog::slot_uploading_chatUser()
{
    if(_b_loading){
        return;
    }
    _b_loading = true;
    LoadingDlg *loadingDialog = new LoadingDlg(this);
    loadingDialog->setModal(true);
    loadingDialog->show();
    loadMoreChatUser();

    //加载完成后关闭对话框
    loadingDialog->deleteLater();
    _b_loading = false;
}

void ChatDialog::slot_side_chat()
{
    ClearLabelState(ui->sideChatLabel);
    ui->stackedWidget->setCurrentWidget(ui->chatPage);
    _state = ChatUIMode::ChatMode;
    showSearch(false);
}

void ChatDialog::slot_side_contact()
{
    ClearLabelState(ui->sideContactLabel);
    ui->stackedWidget->setCurrentWidget(ui->friendApplyPage);
    _state = ChatUIMode::ContactMode;
    showSearch(false);
    ui->sideContactLabel->ShowRedPoint(false);
    ui->conUserList->ShowRedPoint(false);
}

void ChatDialog::slot_text_changed(const QString &str)
{
    if(!str.isEmpty()){
        showSearch(true);
    }
}

void ChatDialog::slot_loading_contact_user()
{
    qDebug() << "slot loading contact user";
    if(_b_loading){
        return;
    }

    _b_loading = true;
    LoadingDlg *loadingDialog = new LoadingDlg(this);
    loadingDialog->setModal(true);
    loadingDialog->show();
    qDebug() << "add new data to list.....";
    loadMoreConUser();
    // 加载完成后关闭对话框
    loadingDialog->deleteLater();

    _b_loading = false;
}

void ChatDialog::slot_friend_apply(std::shared_ptr<AddFriendApply> apply)
{
    qDebug() << "recv apply friend request, applyuid is" << apply->_from_uid << " name is "<<apply->_name;
    //判断是否重复申请
    if(UserMgr::GetInstance()->AlreadyApply(apply->_from_uid)){
        return;
    }
    //添加到申请列表中
    UserMgr::GetInstance()->SetApply(std::make_shared<ApplyInfo>(apply));
    ui->sideContactLabel->ShowRedPoint(true);
    ui->conUserList->ShowRedPoint(true);
    ui->friendApplyPage->AddNewApply(apply);
}

void ChatDialog::slot_add_auth_friend(std::shared_ptr<AuthInfo> auth_info)
{
    qDebug() << "receive slot_add_auth__friend uid is " << auth_info->_uid
             << " name is " << auth_info->_name << " nick is " << auth_info->_nick;

    //判断如果已经是好友则跳过
    auto bfriend = UserMgr::GetInstance()->CheckFriendById(auth_info->_uid);
    if(bfriend){
        return;
    }

    UserMgr::GetInstance()->AddFriend(auth_info);

    auto* chat_user_wid = new ChatUserWid();
    auto user_info = std::make_shared<UserInfo>(auth_info);
    chat_user_wid->SetInfo(user_info);
    QListWidgetItem* item = new QListWidgetItem;
    //qDebug()<<"chat_user_wid sizeHint is " << chat_user_wid->sizeHint();
    item->setSizeHint(chat_user_wid->sizeHint());
    ui->chatUserList->insertItem(0, item);
    ui->chatUserList->setItemWidget(item, chat_user_wid);
    _chat_items_added.insert(auth_info->_uid, item);
}

void ChatDialog::slot_auth_rsp(std::shared_ptr<AuthRsp> auth_rsp)
{
    qDebug() << "receive slot_auth_rsp uid is " << auth_rsp->_uid
             << " name is " << auth_rsp->_name << " nick is " << auth_rsp->_nick;

    //判断如果已经是好友则跳过
    auto bfriend = UserMgr::GetInstance()->CheckFriendById(auth_rsp->_uid);
    if(bfriend){
        return;
    }

    UserMgr::GetInstance()->AddFriend(auth_rsp);

    auto* chat_user_wid = new ChatUserWid();
    auto user_info = std::make_shared<UserInfo>(auth_rsp);
    chat_user_wid->SetInfo(user_info);
    QListWidgetItem* item = new QListWidgetItem;
    //qDebug()<<"chat_user_wid sizeHint is " << chat_user_wid->sizeHint();
    item->setSizeHint(chat_user_wid->sizeHint());
    ui->chatUserList->insertItem(0, item);
    ui->chatUserList->setItemWidget(item, chat_user_wid);
    _chat_items_added.insert(auth_rsp->_uid, item);
}

void ChatDialog::slot_jump_chat_item(std::shared_ptr<SearchInfo> si)
{
    qDebug() << "slot jump chat item " << endl;
    auto find_iter = _chat_items_added.find(si->_uid);
    if(find_iter != _chat_items_added.end()){
        qDebug() << "jump to chat item , uid is " << si->_uid;
        ui->chatUserList->scrollToItem(find_iter.value());
        ui->sideChatLabel->SetSelected(true);
        SetSelectChatItem(si->_uid);
        //更新聊天界面信息
        SetSelectChatPage(si->_uid);
        slot_side_chat();
        return;
    }

    //如果没找到，则创建新的插入listwidget

    auto* chat_user_wid = new ChatUserWid();
    auto user_info = std::make_shared<UserInfo>(si);
    chat_user_wid->SetInfo(user_info);
    QListWidgetItem* item = new QListWidgetItem;
    //qDebug()<<"chat_user_wid sizeHint is " << chat_user_wid->sizeHint();
    item->setSizeHint(chat_user_wid->sizeHint());
    ui->chatUserList->insertItem(0, item);
    ui->chatUserList->setItemWidget(item, chat_user_wid);

    _chat_items_added.insert(si->_uid, item);

    ui->sideChatLabel->SetSelected(true);
    SetSelectChatItem(si->_uid);
    //更新聊天界面信息
    SetSelectChatPage(si->_uid);
    slot_side_chat();
}


























