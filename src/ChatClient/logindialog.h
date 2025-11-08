#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include "global.h"

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = nullptr);
    ~LoginDialog();

private slots:
    void slot_forget_pwd();

    void on_loginBtn_clicked();
    void Slot_login_finish(ReqId id, QString res, ErrorCodes err);
    void slot_tcp_con_finish(bool bSuccess);
    void slot_login_failed(int num);


signals:
    void switchRegister();
    void switchreset();
    void sig_connect_tcp(ServerInfo);

private:
    Ui::LoginDialog *ui;
    void InitHandlers();
    void AddTipErr(TipErr te, QString tips);
    void DelTipErr(TipErr te);
    bool checkEmailValid();
    bool checkPassValid();
    void showTip(QString tip, bool flag);
    void setenable(bool flag);

    QMap<TipErr,QString> _tip_errs;
    QMap<ReqId,std::function<void(const QJsonObject&)>> _handlers;
    int _uid;
    QString _token;
};

#endif // LOGINDIALOG_H
