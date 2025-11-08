#ifndef CLICKBTN_H
#define CLICKBTN_H
#include <QPushButton>

class ClickBtn : public QPushButton
{
    Q_OBJECT
public:
    ClickBtn(QWidget *parent = nullptr);
    ~ClickBtn();
    void SetState(QString normal, QString hover, QString press);

protected:
    virtual void enterEvent(QEvent *event) override;
    virtual void leaveEvent(QEvent *event) override;
    void mousePressEvent(QMouseEvent *e) override;
    void mouseReleaseEvent(QMouseEvent *e) override;

private:
    QString _normal;
    QString _hover;
    QString _press;
};

#endif // CLICKBTN_H
