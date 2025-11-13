#include "friendlabel.h"
#include "ui_friendlabel.h"
#include <QDebug>

FriendLabel::FriendLabel(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::FriendLabel)
{
    ui->setupUi(this);
    ui->closeLb->SetState("normal","hover","pressed",
                           "selected_normal","selected_hover","selected_pressed");
    connect(ui->closeLb, &ClickedLabel::clicked, this, &FriendLabel::slot_close);
}
FriendLabel::~FriendLabel()
{
    delete ui;
}

void FriendLabel::SetText(QString text)
{
    _text = text;
    ui->tipLb->setText(_text);
    ui->tipLb->adjustSize();

    QFontMetrics fontMetrics(ui->tipLb->font()); // 获取QLabel控件的字体信息
    auto textWidth = fontMetrics.width(ui->tipLb->text()); // 获取文本的宽度
    auto textHeight = fontMetrics.height(); // 获取文本的高度

    qDebug()<< " ui->tip_lb.width() is " << ui->tipLb->width();
    qDebug()<< " ui->close_lb->width() is " << ui->closeLb->width();
    qDebug()<< " textWidth is " << textWidth;
    this->setFixedWidth(ui->tipLb->width()+ui->closeLb->width()+5);
    this->setFixedHeight(textHeight+2);
    qDebug()<< "  this->setFixedHeight " << this->height();
    _width = this->width();
    _height = this->height();
}

int FriendLabel::Width()
{
    return _width;
}

int FriendLabel::Height()
{
    return _height;
}

QString FriendLabel::Text()
{
    return _text;
}

void FriendLabel::slot_close()
{
    emit sig_close(_text);
}
