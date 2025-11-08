#include "logindialog.h"
#include "ui_logindialog.h"
#include <QDebug>
#include "httpmgr.h"
#include "tcpmgr.h"

LoginDialog::LoginDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    ui->passwordEdit->setEchoMode(QLineEdit::Password);
    InitHandlers();

    //连接点击事件，点击之后发送信号
    connect(ui->registerBtn, &QPushButton::clicked, this, &LoginDialog::switchRegister);

    ui->forgetLabel->SetState("normal","normal_hover","","selected","selected_hover","");
    connect(ui->forgetLabel,&ClickedLabel::clicked,this,&LoginDialog::slot_forget_pwd);

    connect(ui->emailEdit,&QLineEdit::editingFinished,this,[this](){
        checkEmailValid();
    });
    connect(ui->passwordEdit,&QLineEdit::editingFinished,this,[this](){
        checkPassValid();
    });

    connect(HttpMgr::GetInstance().get(), &HttpMgr::sig_login_mod_finish, this, &LoginDialog::Slot_login_finish);
    //连接tcp连接请求的信号和槽函数
    connect(this, &LoginDialog::sig_connect_tcp, TcpMgr::GetInstance().get(), &TcpMgr::slot_tcp_connect);
    //连接tcp管理者发出的连接成功信号
    connect(TcpMgr::GetInstance().get(), &TcpMgr::sig_con_success, this, &LoginDialog::slot_tcp_con_finish);
    //登录失败
    connect(TcpMgr::GetInstance().get(), &TcpMgr::sig_login_failed, this, &LoginDialog::slot_login_failed);

}

LoginDialog::~LoginDialog()
{
    delete ui;
}
void LoginDialog::InitHandlers()
{
    _handlers.insert(ID_LOGIN,[this](const QJsonObject& res){
        int error = res["error"].toInt();
        if(error == ErrorCodes::UserNoExits){
            showTip(tr("用户不存在"),false);
            setenable(true);
            return;
        }
        if(error == ErrorCodes::PassWdErr){
            showTip(tr("密码错误"),false);
            setenable(true);
            return;
        }
        if(error == ErrorCodes::SUCCESS){
            auto email = res["email"].toString();

            //发送信号通知TCPMgr发送长连接
            ServerInfo si;
            si.Uid = res["uid"].toInt();
            si.Host = res["host"].toString();
            si.Port = res["port"].toString();
            si.Token = res["token"].toString();

            _uid = si.Uid;
            _token = si.Token;

            qDebug()<< "email is " << email << " uid is " << si.Uid <<" host is "
                     << si.Host << " Port is " << si.Port << " Token is " << si.Token;

            emit sig_connect_tcp(si);
            return;
        }
        showTip(tr("参数错误"),false);
        setenable(true);
        return;
    });
}

void LoginDialog::slot_forget_pwd()
{
    qDebug() << "slot forget pwd";
    emit switchreset();
}

void LoginDialog::on_loginBtn_clicked()
{
    if(!checkEmailValid()){
        return;
    }
    if(!checkPassValid()){
        return;
    }
    setenable(false);
    //发送登录请求
    auto email = ui->emailEdit->text();
    auto pwd = ui->passwordEdit->text();
    QJsonObject jsonObj;
    jsonObj["email"] = email;
    jsonObj["pwd"] = xorString(pwd);

    HttpMgr::GetInstance()->PostHttpReq(QUrl(gateUrlPrefix+"/login"), jsonObj ,ReqId::ID_LOGIN, Modules::LOGIN);
}

void LoginDialog::Slot_login_finish(ReqId id, QString res, ErrorCodes err)
{
    if(err != ErrorCodes::SUCCESS){
        showTip(tr("网络请求错误"),false);
        return;
    }

    // 解析 JSON 字符串,res需转化为QByteArray
    QJsonDocument jsonDoc = QJsonDocument::fromJson(res.toUtf8());
    //json解析错误
    if(jsonDoc.isNull()){
        showTip(tr("json解析错误"),false);
        return;
    }

    //json解析错误
    if(!jsonDoc.isObject()){
        showTip(tr("json解析错误"),false);
        return;
    }


    //调用对应的逻辑,根据id回调。
    _handlers[id](jsonDoc.object());

    return;
}

void LoginDialog::slot_tcp_con_finish(bool bSuccess)
{
    if(bSuccess){
        showTip(tr("正在登录..."),true);
        QJsonObject jsonObj;
        jsonObj["token"] = _token;
        jsonObj["uid"] = _uid;

        QJsonDocument doc(jsonObj);
        QString jsonString = doc.toJson(QJsonDocument::Indented);

        emit TcpMgr::GetInstance()->sig_send_data(ReqId::ID_CHAT_LOGIN,jsonString);
    }
    else{
        showTip(tr("网络异常"),false);
        setenable(true);
    }
}

void LoginDialog::slot_login_failed(int num)
{
    showTip(tr("登录失败"),false);
    setenable(true);
    qDebug() << "err is" << num;
    return;
}

void LoginDialog::AddTipErr(TipErr te, QString tips)
{
    _tip_errs[te] = tips;
    showTip(tips,false);
}

void LoginDialog::DelTipErr(TipErr te)
{
    _tip_errs.remove(te);
    if(_tip_errs.empty()){
        ui->errTip->clear();
        return;
    }
    showTip(_tip_errs.first(), false);
}

bool LoginDialog::checkEmailValid()
{
    auto email = ui->emailEdit->text();
    static QRegularExpression regex(R"((\w+)(\.|_)?(\w*)@(\w+)(\.(\w+))+)");
    bool match = regex.match(email).hasMatch(); //判断是否匹配
    if(!match){
        AddTipErr(TipErr::TIP_EMAIL_ERR,tr("邮箱地址不正确"));
        return false;
    }
    DelTipErr(TipErr::TIP_EMAIL_ERR);
    return true;
}

bool LoginDialog::checkPassValid()
{
    QString pass = ui->passwordEdit->text();
    if(pass.length() < 6 || pass.length() > 15){
        AddTipErr(TipErr::TIP_PWD_ERR,tr("密码长度应为6-15"));
        return false;
    }

    static QRegularExpression regExp("^[a-zA-Z0-9!@#$%^&*]{6,15}$");
    bool match = regExp.match(pass).hasMatch();
    if(!match){
        AddTipErr(TipErr::TIP_PWD_ERR,tr("不能包含非法字符"));
        return false;
    }
    DelTipErr(TipErr::TIP_PWD_ERR);
    return true;
}

void LoginDialog::showTip(QString tip, bool flag)
{
    if(flag)
    {
        ui->errTip->setProperty("state","normal");//修改状态
    }
    else{
        ui->errTip->setProperty("state","err");//修改状态
    }
    ui->errTip->setText(tip);//提示
    repolish(ui->errTip);//刷新qss
}

void LoginDialog::setenable(bool flag)
{
    ui->loginBtn->setEnabled(flag);
    ui->registerBtn->setEnabled(flag);
}

