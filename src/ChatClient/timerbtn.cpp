#include "timerbtn.h"
#include <QMouseEvent>
#include <QDebug>

TimerBtn::TimerBtn(QWidget *parent) : QPushButton(parent),_counter(60)
{
    _timer = new QTimer(this);
    connect(_timer,&QTimer::timeout,[this](){
        _counter--;
        if(_counter <= 0){
            _timer->stop();
            _counter = 60;
            this->setText("获取");
            this->setEnabled(true);
            return;
        }
        this->setText(QString::number(_counter));
    });
}

TimerBtn::~TimerBtn()
{
    _timer->stop();
}

void TimerBtn::mouseReleaseEvent(QMouseEvent *e)
{
    //开启定时器
    if(e->button() == Qt::LeftButton){
        qDebug() << "MyButton was released!";
        this->setEnabled(false);
        this->setText(QString::number(_counter));
        _timer->start(1000);
        emit clicked();//因为重写了按钮，所以鼠标释放事件需要触发按钮点击事件
    }
    //调用基类的mouseReleaseEvent以确保事件正常处理
    QPushButton::mouseReleaseEvent(e);//继续执行基类的事件
}

