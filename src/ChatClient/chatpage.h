#ifndef CHATPAGE_H
#define CHATPAGE_H

#include <QWidget>
#include <QPaintEvent>

namespace Ui {
class ChatPage;
}

class ChatPage : public QWidget
{
    Q_OBJECT

public:
    explicit ChatPage(QWidget *parent = nullptr);
    ~ChatPage();

protected:
    void paintEvent(QPaintEvent *event);

private slots:
    void on_sendBtn_clicked();

private:
    Ui::ChatPage *ui;
};

#endif // CHATPAGE_H
