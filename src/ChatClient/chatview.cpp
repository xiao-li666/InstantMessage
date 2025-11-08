#include "chatview.h"
#include <QScrollBar>
#include <QDebug>
#include <QEvent>
#include <QStyleOption>
#include <QPainter>
ChatView::ChatView(QWidget *parent)
    :QWidget(parent),isAppended(false)
{
    //创建整体垂直布局
    QVBoxLayout *pMainLayout = new QVBoxLayout();
    this->setLayout(pMainLayout);
    pMainLayout->setMargin(0);
    //给垂直布局中添加滚动区域
    m_pScrollArea = new QScrollArea();
    m_pScrollArea->setObjectName("chat_area");
    pMainLayout->addWidget(m_pScrollArea);
    //显示消息的窗口
    QWidget *w = new QWidget(this);
    w->setObjectName("chat_bg");
    w->setAutoFillBackground(true);//消息越多窗口越大,允许小部件自动填充背景颜色
    //消息采用垂直布局
    QVBoxLayout *pHLayout_1 = new QVBoxLayout();
    pHLayout_1->addWidget(new QWidget(), 100000);//100000是伸缩因子
    w->setLayout(pHLayout_1);
    m_pScrollArea->setWidget(w);

    //设置滚动区域的滑动条
    m_pScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    QScrollBar *pVScrollbar = m_pScrollArea->verticalScrollBar();

    //当消息占满滚动区域时，新来的消息显示在最下面，所以上面的消息应该滑动上去，此时会触发这个信号
    connect(pVScrollbar, &QScrollBar::rangeChanged, this, &ChatView::onVScrollBarMoved);

    //调整滑动条的位置
    QHBoxLayout *pHLayout_2 = new QHBoxLayout();
    pHLayout_2->addWidget(pVScrollbar, 0, Qt::AlignRight);
    pHLayout_2->setMargin(0);
    m_pScrollArea->setLayout(pHLayout_2);
    pVScrollbar->setHidden(true);
    m_pScrollArea->setWidgetResizable(true);
    m_pScrollArea->installEventFilter(this);
    initStyleSheet();
}

void ChatView::appendChatItem(QWidget *item)
{
    QVBoxLayout *vl = qobject_cast<QVBoxLayout *>(m_pScrollArea->widget()->layout());
    qDebug() << "vl->count() is " << vl->count();
    vl->insertWidget(vl->count()-1, item);
    isAppended = true;
}

bool ChatView::eventFilter(QObject *o, QEvent *e)
{
    /*if(e->type() == QEvent::Resize && o == )
    {

    }
    else */if(e->type() == QEvent::Enter && o == m_pScrollArea)
    {
        m_pScrollArea->verticalScrollBar()->setHidden(m_pScrollArea->verticalScrollBar()->maximum() == 0);
    }
    else if(e->type() == QEvent::Leave && o == m_pScrollArea)
    {
        m_pScrollArea->verticalScrollBar()->setHidden(true);
    }
    return QWidget::eventFilter(o, e);
}

void ChatView::paintEvent(QPaintEvent *event)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}


void ChatView::onVScrollBarMoved(int min, int max)
{
    if(isAppended){//添加item可能调用多次
        QScrollBar *pVScrollBar = m_pScrollArea->verticalScrollBar();
        pVScrollBar->setSliderPosition(pVScrollBar->maximum());
        //500毫秒内可能多次调用
        QTimer::singleShot(500, [this](){
            isAppended = false;
        });
    }
}

void ChatView::initStyleSheet()
{

}
