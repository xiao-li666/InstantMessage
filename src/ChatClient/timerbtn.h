#ifndef TIMERBTN_H
#define TIMERBTN_H
#include <QPushButton>
#include <QTimer>

class TimerBtn : public QPushButton
{
public:
    TimerBtn(QWidget *parent = nullptr);
    ~TimerBtn();

    void mouseReleaseEvent(QMouseEvent *e) override;

    QTimer *_timer;
private:
    int _counter;
};

#endif // TIMERBTN_H
