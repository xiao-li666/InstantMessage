#include "resetdialog.h"
#include "ui_resetdialog.h"

ResetDialog::ResetDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ResetDialog)
{
    ui->setupUi(this);
    InitHandlers();
    ui->errTip->clear();

    connect(HttpMgr::GetInstance().get(),&HttpMgr::sig_reset_mod_finish,this,&ResetDialog::Slot_reset_finish);

    connect(ui->userLineEdit,&QLineEdit::editingFinished,this,[this](){
        checkUserValid();
    });
    connect(ui->emailEdit,&QLineEdit::editingFinished,this,[this](){
        checkEmailValid();
    });
    connect(ui->newPassEdit,&QLineEdit::editingFinished,this,[this](){
        checkPassValid();
    });
    connect(ui->varifyEdit,&QLineEdit::editingFinished,this,[this](){
        checkVarifyValid();
    });
}

ResetDialog::~ResetDialog()
{
    delete ui;
}

void ResetDialog::showTip(QString tip, bool flag)
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

void ResetDialog::on_confirmBtn_clicked()
{
    if(ui->userLineEdit->text() == ""){
        showTip(tr("用户名不能为空"),false);
        return;
    }
    if(ui->emailEdit->text() == ""){
        showTip(tr("邮箱地址为空"),false);
        return;
    }
    if(ui->varifyEdit->text() == ""){
        showTip(tr("验证码为空"),false);
        return;
    }
    if(ui->newPassEdit->text() == ""){
        showTip(tr("密码为空"),false);
        return;
    }
    QJsonObject jsonObj;
    jsonObj["user"] = ui->userLineEdit->text();
    jsonObj["email"] = ui->emailEdit->text();
    jsonObj["varify"] = ui->varifyEdit->text();
    jsonObj["password"] = xorString(ui->newPassEdit->text());
    HttpMgr::GetInstance()->PostHttpReq(QUrl(gateUrlPrefix+"/resetPass"),jsonObj,ReqId::ID_RESET_PASS,Modules::RESETPASSWORD);
}

void ResetDialog::Slot_reset_finish(ReqId id, QString res, ErrorCodes err)
{
    if(err != ErrorCodes::SUCCESS){
        showTip(tr("密码重置失败"),false);
        return;
    }

    QJsonDocument jsonDoc = QJsonDocument::fromJson(res.toUtf8());
    if(jsonDoc.isNull()){
        showTip(tr("JSON解析失败"),false);
        return;
    }
    if(!jsonDoc.isObject()){
        showTip(tr("JSON解析失败"),false);
        return;
    }

    _handlers[id](jsonDoc.object());
}

void ResetDialog::InitHandlers()
{
    _handlers.insert(ReqId::ID_RESET_PASS,[this](const QJsonObject &res){
        int error = res["error"].toInt();
        if(error == ErrorCodes::VarifyCodeError){
            showTip(tr("验证码错误"),false);
            return;
        }
        if(error == ErrorCodes::VarifyExpire){
            showTip(tr("验证码无效"),false);
            return;
        }
        if(error == ErrorCodes::SUCCESS){
            showTip(tr("重置成功，点击返回登录"),true);
            return;
        }
        if(error == ErrorCodes::UserNoExits){
            showTip(tr("用户不存在，请先注册"),false);
            return;
        }
        if(error == ErrorCodes::PasswdUpFailed){
            showTip(tr("修改失败"),false);
            return;
        }
        showTip(tr("修改失败"),false);
        return;
    });
    _handlers.insert(ReqId::ID_GET_VARIFY_CODE, [this](const QJsonObject& jsonObj){
        int error = jsonObj["error"].toInt();
        if(error != ErrorCodes::SUCCESS){
            showTip(tr("参数错误"),false);
            return;
        }

        auto email = jsonObj["email"].toString();
        showTip(tr("验证码已发送到邮箱，注意查收"),true);
        qDebug() << "email is " <<email ;
    });
}

//获取验证码
void ResetDialog::on_varifyBtn_clicked()
{
    //
    if(ui->userLineEdit->text() == ""){
        showTip(tr("用户名不能为空"),false);
        return;
    }
    //检查邮箱格式
    auto email = ui->emailEdit->text();
    static QRegularExpression regex(R"((\w+)(\.|_)?(\w*)@(\w+)(\.(\w+))+)");
    bool match = regex.match(email).hasMatch(); //判断是否匹配
    if(match){
        //发送验证码
        QJsonObject jsonObj;
        jsonObj["user"] = ui->userLineEdit->text();
        jsonObj["email"] = ui->emailEdit->text();
        HttpMgr::GetInstance()->PostHttpReq(QUrl(gateUrlPrefix+"/getVarifycode"),
                                            jsonObj,ReqId::ID_GET_VARIFY_CODE,Modules::RESETPASSWORD);

    }
    else{
        //提示邮箱格式错误
        showTip(tr("邮箱地址不正确"),match);
    }
}
void ResetDialog::AddTipErr(TipErr te, QString tips)
{
    _tip_errs[te] = tips;
    showTip(tips,false);
}

void ResetDialog::DelTipErr(TipErr te)
{
    _tip_errs.remove(te);
    if(_tip_errs.empty()){
        ui->errTip->clear();
        return;
    }
    showTip(_tip_errs.first(), false);
}
bool ResetDialog::checkUserValid()
{
    if(ui->userLineEdit->text() == ""){
        AddTipErr(TipErr::TIP_USER_ERR,tr("用户名不能为空"));
        return false;
    }
    DelTipErr(TipErr::TIP_USER_ERR);
    return true;
}

bool ResetDialog::checkEmailValid()
{
    auto email = ui->emailEdit->text();
    static QRegularExpression regex(R"((\w+)(\.|_)?(\w*)@(\w+)(\.(\w+))+)");
    bool match = regex.match(email).hasMatch(); //判断是否匹配
    if(!match){
        AddTipErr(TipErr::TIP_EMAIL_ERR,tr("邮箱地址不正确"));
        return false;
    }
    DelTipErr(TipErr::TIP_EMAIL_ERR);
    return false;
}

bool ResetDialog::checkPassValid()
{
    QString pass = ui->newPassEdit->text();
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
bool ResetDialog::checkVarifyValid()
{
    auto pass = ui->varifyEdit->text();
    if(pass.isEmpty()){
        AddTipErr(TipErr::TIP_VARIFY_ERR,tr("验证码不能为空"));
        return false;
    }
    DelTipErr(TipErr::TIP_VARIFY_ERR);
    return true;
}


void ResetDialog::on_cancelBtn_clicked()
{
    //发出信号，跳转界面
    emit switchLogin();
}

