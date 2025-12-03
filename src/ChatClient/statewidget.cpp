#include "statewidget.h"
#include <QVBoxLayout>
#include <QPaintEvent>
#include <QStyleOption>
#include <QPainter>

StateWidget::StateWidget(QWidget *parent)
    :QWidget(parent),_curState(ClickLbState::Normal)
{
    setCursor(Qt::PointingHandCursor);
    //添加红点
    AddRedPoint();
}

void StateWidget::SetState(QString normal, QString hover, QString press, QString select, QString select_hover, QString select_press)
{
    _normal = normal;
    _normalHover = hover;
    _normalPress = press;
    _selected = select;
    _selectedHover = select_hover;
    _selectedPress = select_press;
    setProperty("state", normal);
    repolish(this);
}

void StateWidget::paintEvent(QPaintEvent *event)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
    return;

}

// 处理鼠标点击事件
void StateWidget::mousePressEvent(QMouseEvent* event)  {
    if (event->button() == Qt::LeftButton) {
        if(_curState == ClickLbState::Selected){
            qDebug()<<"PressEvent , already to selected press: "<< _selectedPress;
            //emit clicked();
            // 调用基类的mousePressEvent以保证正常的事件处理
            QWidget::mousePressEvent(event);
            return;
        }

        if(_curState == ClickLbState::Normal){
            qDebug()<<"PressEvent , change to selected press: "<< _selectedPress;
            _curState = ClickLbState::Selected;
            setProperty("state",_selectedPress);
            repolish(this);
            update();
        }

        return;
    }
    // 调用基类的mousePressEvent以保证正常的事件处理
    QWidget::mousePressEvent(event);
}

void StateWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        if(_curState == ClickLbState::Normal){
            //qDebug()<<"ReleaseEvent , change to normal hover: "<< _normal_hover;
            setProperty("state",_normalHover);
            repolish(this);
            update();

        }else{
            //qDebug()<<"ReleaseEvent , change to select hover: "<< _selected_hover;
            setProperty("state",_selectedHover);
            repolish(this);
            update();
        }
        emit clicked();
        return;
    }
    // 调用基类的mousePressEvent以保证正常的事件处理
    QWidget::mousePressEvent(event);
}

// 处理鼠标悬停进入事件
void StateWidget::enterEvent(QEvent* event) {
    // 在这里处理鼠标悬停进入的逻辑
    if(_curState == ClickLbState::Normal){
        //qDebug()<<"enter , change to normal hover: "<< _normal_hover;
        setProperty("state",_normalHover);
        repolish(this);
        update();

    }else{
        //qDebug()<<"enter , change to selected hover: "<< _selected_hover;
        setProperty("state",_selectedHover);
        repolish(this);
        update();
    }

    QWidget::enterEvent(event);
}

// 处理鼠标悬停离开事件
void StateWidget::leaveEvent(QEvent* event){
    // 在这里处理鼠标悬停离开的逻辑
    if(_curState == ClickLbState::Normal){
        // qDebug()<<"leave , change to normal : "<< _normal;
        setProperty("state",_normal);
        repolish(this);
        update();

    }else{
        // qDebug()<<"leave , change to select normal : "<< _selected;
        setProperty("state",_selected);
        repolish(this);
        update();
    }
    QWidget::leaveEvent(event);
}

ClickLbState StateWidget::GetCurState(){
    return _curState;
}

void StateWidget::ClearState()
{
    _curState = ClickLbState::Normal;
    setProperty("state",_normal);
    repolish(this);
    update();
}

void StateWidget::SetSelected(bool bselected)
{
    if(bselected){
        _curState = ClickLbState::Selected;
        setProperty("state",_selected);
        repolish(this);
        update();
        return;
    }

    _curState = ClickLbState::Normal;
    setProperty("state",_normal);
    repolish(this);
    update();
    return;

}

void StateWidget::AddRedPoint()
{
    _redPoint = new QLabel();
    _redPoint->setObjectName("redPoint");
    QVBoxLayout* layout2 = new QVBoxLayout();
    _redPoint->setAlignment(Qt::AlignCenter);
    layout2->addWidget(_redPoint);
    layout2->setMargin(0);
    this->setLayout(layout2);
    _redPoint->setVisible(false);
}

void StateWidget::ShowRedPoint(bool show)
{
    _redPoint->setVisible(show);
}
