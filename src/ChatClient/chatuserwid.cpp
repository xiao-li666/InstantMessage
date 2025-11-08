#include "chatuserwid.h"
#include "ui_chatuserwid.h"

ChatUserWid::ChatUserWid(QWidget *parent)
    : ListItemBase(parent)
    , ui(new Ui::ChatUserWid)
{
    ui->setupUi(this);
    SetItemType(ListItemType::CHAT_USER_ITEM);
}

ChatUserWid::~ChatUserWid()
{
    delete ui;
}

void ChatUserWid::SetInfo(QString name, QString head, QString msg)
{
    _name = name;
    _head = head;
    _msg = msg;

    //加载图片
    QPixmap pixmap(_head);

    //设置图片自动缩放
    ui->iconLabel->setPixmap(pixmap.scaled(ui->iconLabel->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation));
    ui->iconLabel->setScaledContents(true);

    ui->userChatLabel->setText(_msg);
    ui->userNameLabel->setText(_name);
}
