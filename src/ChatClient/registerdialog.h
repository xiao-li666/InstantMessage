#ifndef REGISTERDIALOG_H
#define REGISTERDIALOG_H

#include <QDialog>
#include "global.h"
#include <QMap>


namespace Ui {
class RegisterDialog;
}

class RegisterDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RegisterDialog(QWidget *parent = nullptr);
    ~RegisterDialog();

private slots:
    void on_getCode_clicked();
    void slot_reg_mod_finish(ReqId id, QString res, ErrorCodes err);

    void on_confirmBtn_clicked();

    void on_cancelBtn_clicked();

    void on_returnBtn_clicked();

signals:
    void sigSwitchLogin();

private:
    Ui::RegisterDialog *ui;

    void showTip(QString str,bool flag);
    void InitHttpHandlers();
    void AddTipErr(TipErr te, QString tips);
    void DelTipErr(TipErr te);
    bool checkUserValid();
    bool checkEmailValid();
    bool checkPassValid();
    bool checkVarifyValid();
    bool checkConfirmValid();

    void changeTipPage();

    QMap<ReqId, std::function<void(const QJsonObject&)>> _handlers;
    QMap<TipErr,QString> _tip_errs;

    QTimer *_countdownTimer;
    int _countdown;
};

#endif // REGISTERDIALOG_H
