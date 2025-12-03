#ifndef CHATVIEW_H
#define CHATVIEW_H
#include <QScrollArea>
#include <QVBoxLayout>
#include <QTimer>
#include <QWidget>

class ChatView : public QWidget
{
    Q_OBJECT
public:
    ChatView(QWidget *parent = nullptr);
    void appendChatItem(QWidget *item); //尾插
    void prependChatItem(QWidget *item); //头插
    void insertChatItem(QWidget *before, QWidget *item); //中间插
    void removeAllItem();

protected:

    virtual bool eventFilter(QObject *watched, QEvent *event);
    virtual void paintEvent(QPaintEvent *event);
private slots:
    void onVScrollBarMoved(int min, int max);
private:
    void initStyleSheet();
private:
    QVBoxLayout *m_pVl;
    QScrollArea *m_pScrollArea;
    bool isAppended;
};

#endif // CHATVIEW_H
