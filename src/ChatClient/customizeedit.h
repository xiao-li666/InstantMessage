#ifndef CUSTOMIZEEDIT_H
#define CUSTOMIZEEDIT_H

#include <QLineEdit>
#include <QObject>
#include <QFocusEvent>

class CustomizeEdit : public QLineEdit
{
    Q_OBJECT
public:
    CustomizeEdit(QWidget *parent = nullptr);
    ~CustomizeEdit();
    void SetMaxLength(int maxLength);

protected:
    //失去焦点时
    void focusOutEvent(QFocusEvent *) override;

private slots:
    void limitTextLength(QString text);

private:

    int _maxLen;

signals:
    void sig_focus_out();

};

#endif // CUSTOMIZEEDIT_H
