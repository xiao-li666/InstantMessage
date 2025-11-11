#ifndef STATEWIDGET_H
#define STATEWIDGET_H
#include <QWidget>
#include "global.h"
#include <QLabel>

class StateWidget : public QWidget
{
    Q_OBJECT
public:
    explicit StateWidget(QWidget *parent = nullptr);

    void SetState(QString normal="",QString hover="",QString press="",
                  QString select="",QString select_hover="",QString select_press="");

    ClickLbState GetCurState();
    void ClearState();

    void SetSelected(bool bselected);
    void AddRedPoint();
    void ShowRedPoint(bool show = true);

protected:
    void paintEvent(QPaintEvent *event);
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
    virtual void enterEvent(QEvent *event);
    virtual void leaveEvent(QEvent *event);

private:
    QString _normal;
    QString _normalHover;
    QString _normalPress;

    QString _selected;
    QString _selectedHover;
    QString _selectedPress;

    ClickLbState _curState;
    QLabel *_redPoint;

private slots:

signals:
    void clicked(void);

};

#endif // STATEWIDGET_H
