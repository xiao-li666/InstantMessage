#include "chatuserlist.h"
#include <QEvent>
#include <QWheelEvent>
#include <QScrollBar>
#include "usermgr.h"
#include <QTimer>
#include <QCoreApplication>

ChatUserList::ChatUserList(QWidget *parent)
    :QListWidget(parent),_load_pending(false)
{
    Q_UNUSED(parent);
    //关闭横，纵滚动条
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //安装事件过滤器
    this->viewport()->installEventFilter(this);
}
//当基类事件无法满足需求时，使用eventFilter
bool ChatUserList::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == this->viewport()){
        //判断事件类型
        if(event->type() == QEvent::Enter){
            //鼠标进入事件打开纵向滚动条
            this->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        }
        else if(event->type() == QEvent::Leave){
            //鼠标离开关闭混动条
            this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        }
    }

    //检查事件是否滚轮事件
    if(watched == this->viewport() && event->type() == QEvent::Wheel){
        QWheelEvent *wheelEvent = static_cast<QWheelEvent*>(event);
        int numDegrees = wheelEvent->angleDelta().y()/8;
        int numSteps = numDegrees / 15;//计算滚轮步数

        //设置滚动幅度
        this->verticalScrollBar()->setValue(this->verticalScrollBar()->value() - numSteps);
        //检查是否滚动到底部
        QScrollBar *scrollBar = this->verticalScrollBar();
        int maxScrollValue = scrollBar->maximum();
        int currentValue = scrollBar->value();
        if(maxScrollValue - currentValue <= 0){
            auto b_loaded = UserMgr::GetInstance()->IsLoadChatFin();
            if(b_loaded){
                return true;
            }

            if(_load_pending){
                return true;
            }
            // 滚动到底部，加载新的联系人
            qDebug()<<"load more chat user";
            _load_pending = true;

            QTimer::singleShot(100, [this](){
                _load_pending = false;
                QCoreApplication::quit(); // 完成后退出应用程序
            });
            //发送信号通知聊天界面加载更多聊天内容
            emit sig_loading_chat_user();
        }
        return true;
    }
    return QListWidget::eventFilter(watched,event);
}




























