#include "clickbtn.h"
#include "global.h"
#include <QMouseEvent>

ClickBtn::ClickBtn(QWidget *parent)
    :QPushButton(parent)
{
    setCursor(Qt::PointingHandCursor);
}

ClickBtn::~ClickBtn()
{

}

void ClickBtn::SetState(QString normal, QString hover, QString press)
{
    _normal = normal;
    _hover = hover;
    _press = press;

    setProperty("state",normal);
    repolish(this);
    update();
}

void ClickBtn::enterEvent(QEvent *event)
{
    setProperty("state",_hover);
    repolish(this);
    update();
    QPushButton::enterEvent(event);
}

void ClickBtn::leaveEvent(QEvent *event)
{
    setProperty("state",_normal);
    repolish(this);
    update();
    QPushButton::leaveEvent(event);
}

void ClickBtn::mousePressEvent(QMouseEvent *e)
{
    setProperty("state",_press);
    repolish(this);
    update();
    QPushButton::mousePressEvent(e);
}

void ClickBtn::mouseReleaseEvent(QMouseEvent *e)
{
    setProperty("state",_normal);
    repolish(this);
    update();
    QPushButton::mouseReleaseEvent(e);
}
