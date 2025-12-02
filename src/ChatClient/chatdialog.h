#ifndef CHATDIALOG_H
#define CHATDIALOG_H

#include <QDialog>
#include "global.h"
#include "statewidget.h"
#include "userdata.h"
#include <QListWidgetItem>

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
    void ClearLabelState(StateWidget *lb);

protected:
    bool eventFilter(QObject *watched, QEvent* event) override;
    void handleGlobalMousePress(QMouseEvent* event);
private:
    Ui::ChatDialog *ui;

    void showSearch(bool bSearch = false);

    void AddLBGroup(StateWidget* lb);

    ChatUIMode _mode;
    ChatUIMode _state;
    bool _b_loading;
    QList<StateWidget*> _lb_list;

    QMap<int, QListWidgetItem*> _chat_items_added;

private slots:
    void slot_uploading_chatUser();
    void slot_side_chat();
    void slot_side_contact();
    void slot_text_changed(const QString &str);
public slots:
    void slot_friend_apply(std::shared_ptr<AddFriendApply>);
    void slot_add_auth_friend(std::shared_ptr<AuthInfo>);
    void slot_auth_rsp(std::shared_ptr<AuthRsp>);
};

#endif // CHATDIALOG_H
