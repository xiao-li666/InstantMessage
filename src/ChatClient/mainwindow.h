#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "logindialog.h"
#include "registerdialog.h"
#include "resetdialog.h"
#include "chatdialog.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void SlotSwitchReg();
    void SlotSwitchLogin();
    void SlotSwitchLogin2();
    void SlotSwitchResetPass();
    void SlotSwitchChatDlg();

private:
    Ui::MainWindow *ui;
    LoginDialog *_loginDlg;
    RegisterDialog *_registerDlg;
    ResetDialog *_resetDlg;
    ChatDialog *_chatDlg;
};
#endif // MAINWINDOW_H
