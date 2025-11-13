#include "clickedlabel.h"
#include <QMouseEvent>
#include <QEvent>

ClickedLabel::ClickedLabel(QWidget *parentr)
    : QLabel(parentr),_curState(ClickLbState::Normal)
{
    setProperty("state",_normal);
    repolish(this);
    update();
    this->setCursor(Qt::PointingHandCursor);
}

ClickedLabel::~ClickedLabel()
{

}

void ClickedLabel::enterEvent(QEvent *event)
{
    if(_curState == ClickLbState::Normal){
        setProperty("state",_normalHover);
    }
    else{
        setProperty("state",_selectedHover);
    }
    repolish(this);
    update();
    QLabel::enterEvent(event);
}

void ClickedLabel::leaveEvent(QEvent *event)
{
    if(_curState == ClickLbState::Normal){
        setProperty("state",_normal);
    }
    else{
        setProperty("state",_selected);
    }
    repolish(this);
    update();
    QLabel::leaveEvent(event);
}

void ClickedLabel::mousePressEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton){
        //发出点击信号,告诉外部,标签被点击
        //emit clicked();
        //修改状态
        if(_curState == ClickLbState::Normal){
            _curState = ClickLbState::Selected;
            setProperty("state",_selectedPress);
            repolish(this);
            update();
        }
        else{
            _curState = ClickLbState::Normal;
            setProperty("state",_normalPress);
            repolish(this);
            update();
        }
        return;
    }

    QLabel::mousePressEvent(e);
}

void ClickedLabel::mouseReleaseEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton){
        //发出点击信号,告诉外部,标签被点击
        //emit clicked();
        //修改状态
        if(_curState == ClickLbState::Normal){
            setProperty("state",_normalHover);
            repolish(this);
            update();
        }
        else{
            _curState = ClickLbState::Normal;
            setProperty("state",_selectedHover);
            repolish(this);
            update();
        }
        emit clicked(this->text(),_curState);
        return;
    }

    QLabel::mouseReleaseEvent(e);
}

void ClickedLabel::SetState(QString normal, QString hover, QString press,
                            QString select, QString select_hover, QString select_press)
{
    _normal = normal;
    _normalHover = hover;
    _normalPress = press;
    _selected = select;
    _selectedHover = select_hover;
    _selectedPress = select_press;

    setProperty("state",normal);
    repolish(this);
}

ClickLbState ClickedLabel::GetCurState()
{
    return _curState;
}

bool ClickedLabel::SetCurState(ClickLbState state)
{
    _curState = state;
    if (_curState == ClickLbState::Normal) {
        setProperty("state", _normal);
        repolish(this);
    }
    else if (_curState == ClickLbState::Selected) {
        setProperty("state", _selected);
        repolish(this);
    }

    return true;
}

void ClickedLabel::ResetNormalState()
{
    _curState = ClickLbState::Normal;
    setProperty("state", _normal);
    repolish(this);
}
