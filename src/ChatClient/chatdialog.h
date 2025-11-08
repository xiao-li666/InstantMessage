#ifndef CHATDIALOG_H
#define CHATDIALOG_H

#include <QDialog>
#include "global.h"

namespace Ui {
class ChatDialog;
}

class ChatDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ChatDialog(QWidget *parent = nullptr);
    ~ChatDialog();

    void addChatUserList();
private:
    Ui::ChatDialog *ui;

    void showSearch(bool bSearch = false);

    ChatUIMode _mode;
    ChatUIMode _state;
    bool _b_loading;

private slots:
    void slot_uploading_chatUser();
};

#endif // CHATDIALOG_H
