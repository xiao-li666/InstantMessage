#include "chatdialog.h"
#include "ui_chatdialog.h"
#include <QAction>
#include "chatuserwid.h"
#include <QRandomGenerator>
#include "loadingdlg.h"

ChatDialog::ChatDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ChatDialog), _mode(ChatUIMode::ChatMode),_state(ChatUIMode::ChatMode),_b_loading(false)
{
    ui->setupUi(this);
    ui->addBtn->SetState("normal","hover","press");
    ui->searchEdit->SetMaxLength(15);

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
}

ChatDialog::~ChatDialog()
{
    delete ui;
}
std::vector<QString>  strs ={"hello world !",
                             "nice to meet u",
                             "New year，new life",
                             "You have to love yourself",
                             "My love is written in the wind ever since the whole world is you"};
std::vector<QString> heads = {
    ":/res/head_1.jpg",
    ":/res/head_2.jpg",
    ":/res/head_3.jpg",
    ":/res/head_4.jpg",
    ":/res/head_5.jpg"
};
std::vector<QString> names = {
    "llfc",
    "zack",
    "golang",
    "cpp",
    "java",
    "nodejs",
    "python",
    "rust"
};
void ChatDialog::addChatUserList()
{
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

void ChatDialog::slot_uploading_chatUser()
{
    if(_b_loading){
        return;
    }
    _b_loading = true;
    LoadingDlg *loadingDialog = new LoadingDlg(this);
    loadingDialog->setModal(true);
    loadingDialog->show();
    addChatUserList();

    //加载完成后关闭对话框
    loadingDialog->deleteLater();
    _b_loading = false;
}


























