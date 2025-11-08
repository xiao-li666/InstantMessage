#ifndef CLICKEDLABEL_H
#define CLICKEDLABEL_H

#include <QLabel>
#include "global.h"

class ClickedLabel : public QLabel
{
    Q_OBJECT
public:
    ClickedLabel(QWidget *parent=nullptr);
    ~ClickedLabel();

    void enterEvent(QEvent *event) override;
    void leaveEvent(QEvent *event) override;
    void mousePressEvent(QMouseEvent *e) override;
    void mouseReleaseEvent(QMouseEvent *e) override;
    void SetState(QString normal="",QString hover = "", QString press = "",
                  QString select = "", QString select_hover = "",QString select_press="");
    ClickLbState GetCurState();

private:
    QString _normal;
    QString _normalPress;
    QString _normalHover;

    QString _selected;
    QString _selectedHover;
    QString _selectedPress;

    ClickLbState _curState;

signals:
    void clicked(void);
};

#endif // CLICKEDLABEL_H
