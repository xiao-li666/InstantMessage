#include "chatpage.h"
#include "ui_chatpage.h"
#include <QStyleOption>
#include <QPainter>
#include "global.h"
#include "ChatItemBase.h"
#include "textbubble.h"
#include "picturebubble.h"

ChatPage::ChatPage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ChatPage)
{
    ui->setupUi(this);
    //设置按钮样式
    ui->recvBtn->SetState("normal","hover","press");
    ui->sendBtn->SetState("normal","hover","press");

    //设置图标样式
    ui->emoLabel->SetState("normal","hover","press","normal","hover","press");
    ui->fileLabel->SetState("normal","hover","press","normal","hover","press");
}

ChatPage::~ChatPage()
{
    delete ui;
}

void ChatPage::paintEvent(QPaintEvent *event)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
    QWidget::paintEvent(event);
}

void ChatPage::on_sendBtn_clicked()
{
    auto pTextEdit = ui->chatEdit;
    ChatRole role = ChatRole::Self;
    QString userName = QStringLiteral("鸠魁");
    QString userIcon = ":/res/head_1.jpg";

    const QVector<MsgInfo>& msgList = pTextEdit->getMsgList();
    for(int i = 0; i < msgList.size(); ++i){
        QString type = msgList[i].msgFlag;
        ChatItemBase *pChatItem = new ChatItemBase(role);
        pChatItem->setUserName(userName);
        pChatItem->setUserIcon(QPixmap(userIcon));
        QWidget *pBubble = nullptr;
        if(type == "text"){
            pBubble = new TextBubble(role,msgList[i].context);
        }
        else if(type == "image"){
            pBubble = new PictureBubble(QPixmap(msgList[i].context),role);
        }
        else if(type == "file"){

        }
        if(pBubble != nullptr){
            pChatItem->setWidget(pBubble);
            ui->chatDataList->appendChatItem(pChatItem);
        }
    }
}




















