#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "tcpmgr.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    /*-------------------------------------------------------------------------------*/
    // _chatDlg = new ChatDialog(this);
    // _chatDlg->setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
    // setCentralWidget(_chatDlg);
    // _chatDlg->show();
    // this->setMinimumSize(QSize(1300,900));
    // this->setMaximumSize(QWIDGETSIZE_MAX,QWIDGETSIZE_MAX);
    /*-------------------------------------------------------------------------------*/
    _loginDlg = new LoginDialog(this);
    _loginDlg->setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
    setCentralWidget(_loginDlg);
    _loginDlg->show();
    //创建注册消息链接，跳转界面
    connect(_loginDlg, &LoginDialog::switchRegister, this, &MainWindow::SlotSwitchReg);
    connect(_loginDlg, &LoginDialog::switchreset,this,&MainWindow::SlotSwitchResetPass);
    //登录成功
    connect(TcpMgr::GetInstance().get(), &TcpMgr::sig_switch_chatdlg, this, &MainWindow::SlotSwitchChatDlg);
    //connect(_registerDlg,&RegisterDialog::sigSwitchLogin,this,&MainWindow::SlotSwitchLogin);
}

MainWindow::~MainWindow()
{
    delete ui;
    // if(_loginDlg){
    //     delete _loginDlg;
    //     _loginDlg = nullptr;
    // }
    // if(_registerDlg){
    //     delete _registerDlg;
    //     _registerDlg = nullptr;
    // }
}

void MainWindow::SlotSwitchReg(){

    _registerDlg = new RegisterDialog(this);

    //将其设置为无边框，此时就会嵌入主窗口中
    _registerDlg->setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
    connect(_registerDlg,&RegisterDialog::sigSwitchLogin,this,&MainWindow::SlotSwitchLogin);
    //界面显示注册界面
    setCentralWidget(_registerDlg);
    _loginDlg->hide();
    _registerDlg->show();

}
void MainWindow::SlotSwitchLogin(){
    _loginDlg = new LoginDialog(this);
    _loginDlg->setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
    setCentralWidget(_loginDlg);
    _registerDlg->hide();
    _loginDlg->show();
    connect(_loginDlg, &LoginDialog::switchRegister, this, &MainWindow::SlotSwitchReg);
    connect(_loginDlg, &LoginDialog::switchreset,this,&MainWindow::SlotSwitchResetPass);
}

void MainWindow::SlotSwitchLogin2()
{
    _loginDlg = new LoginDialog(this);
    _loginDlg->setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
    setCentralWidget(_loginDlg);
    _resetDlg->hide();
    _loginDlg->show();
    connect(_loginDlg, &LoginDialog::switchRegister, this, &MainWindow::SlotSwitchReg);
    connect(_loginDlg, &LoginDialog::switchreset,this,&MainWindow::SlotSwitchResetPass);
}

void MainWindow::SlotSwitchResetPass()
{
    _resetDlg = new ResetDialog(this);
    _resetDlg->setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
    connect(_resetDlg,&ResetDialog::switchLogin,this,&MainWindow::SlotSwitchLogin2);
    setCentralWidget(_resetDlg);
    _loginDlg->hide();
    _resetDlg->show();
}

void MainWindow::SlotSwitchChatDlg()
{
    _chatDlg = new ChatDialog();
    _chatDlg->setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
    setCentralWidget(_chatDlg);
    _chatDlg->show();
    _loginDlg->hide();
    this->setMinimumSize(QSize(1300,900));
    this->setMaximumSize(QWIDGETSIZE_MAX,QWIDGETSIZE_MAX);
}





















