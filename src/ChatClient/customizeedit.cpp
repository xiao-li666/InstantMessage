#include "customizeedit.h"
#include <QByteArray>

CustomizeEdit::CustomizeEdit(QWidget *parent)
    :QLineEdit(parent),_maxLen(0)
{
    connect(this, &QLineEdit::textChanged, this, &CustomizeEdit::limitTextLength);
}

CustomizeEdit::~CustomizeEdit()
{

}

void CustomizeEdit::SetMaxLength(int maxLength)
{
    _maxLen = maxLength;
}

void CustomizeEdit::focusOutEvent(QFocusEvent *e)
{
    QLineEdit::focusOutEvent(e);
    emit sig_focus_out();
}

void CustomizeEdit::limitTextLength(QString text)
{
    if(_maxLen <= 0){
        return;
    }
    QByteArray byteArray = text.toUtf8();
    if(byteArray.size() > _maxLen){
        byteArray = byteArray.left(_maxLen);
        this->setText(QString::fromUtf8(byteArray));
    }
}



