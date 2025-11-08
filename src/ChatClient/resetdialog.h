#ifndef RESETDIALOG_H
#define RESETDIALOG_H

#include <QDialog>
#include "global.h"
#include "httpmgr.h"

namespace Ui {
class ResetDialog;
}

class ResetDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ResetDialog(QWidget *parent = nullptr);
    ~ResetDialog();

private:
    void showTip(QString tip, bool flag);

private slots:
    void on_confirmBtn_clicked();
    void Slot_reset_finish(ReqId id, QString res, ErrorCodes err);

    void on_varifyBtn_clicked();

    void on_cancelBtn_clicked();

private:
    Ui::ResetDialog *ui;
    void InitHandlers();
    void AddTipErr(TipErr te, QString tips);
    void DelTipErr(TipErr te);
    bool checkUserValid();
    bool checkEmailValid();
    bool checkPassValid();
    bool checkVarifyValid();

    QMap<ReqId,std::function<void(const QJsonObject&)>> _handlers;
    QMap<TipErr,QString> _tip_errs;

signals:
    void switchLogin();
};

#endif // RESETDIALOG_H
