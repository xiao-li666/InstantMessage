#include "registerdialog.h"
#include "ui_registerdialog.h"
//#include "global.h"
#include "httpmgr.h"

RegisterDialog::RegisterDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::RegisterDialog),_countdown(5)
{
    ui->setupUi(this);
    ui->passwordEdit->setEchoMode(QLineEdit::Password);
    ui->sureEdit->setEchoMode(QLineEdit::Password);

    ui->errTip->setProperty("state","normal");//设置属性为normal状态,为提示设置状态
    repolish(ui->errTip);//重新刷新它的qss

    //连接http响应信号,用裸指针连接信号
    connect(HttpMgr::GetInstance().get(),&HttpMgr::sig_reg_mod_finish, this, &RegisterDialog::slot_reg_mod_finish);
    InitHttpHandlers();

    ui->errTip->clear();
    connect(ui->userEdit,&QLineEdit::editingFinished,this,[this](){
        checkUserValid();
    });
    connect(ui->emailEdit,&QLineEdit::editingFinished,this,[this](){
        checkEmailValid();
    });
    connect(ui->passwordEdit,&QLineEdit::editingFinished,this,[this](){
        checkPassValid();
    });
    connect(ui->sureEdit,&QLineEdit::editingFinished,this,[this](){
        checkConfirmValid();
    });
    connect(ui->verifyEdit,&QLineEdit::editingFinished,this,[this](){
        checkVarifyValid();
    });
    ui->passLabel->setCursor(Qt::PointingHandCursor);
    ui->confirmLabel->setCursor(Qt::PointingHandCursor);
    ui->passLabel->SetState("unvisible","unvisible_hover","unvisible_selected","visible","visible_hover","visible_selected");
    ui->confirmLabel->SetState("unvisible","unvisible_hover","unvisible_selected","visible","visible_hover","visible_selected");

    connect(ui->passLabel, &ClickedLabel::clicked, this, [this](){
        if(ui->passLabel->GetCurState() == ClickLbState::Normal){
            ui->passwordEdit->setEchoMode(QLineEdit::Normal);
        }
        else{
            ui->passwordEdit->setEchoMode(QLineEdit::Password);
        }
        repolish(ui->passwordEdit);
    });
    connect(ui->confirmLabel, &ClickedLabel::clicked, this, [this](){
        if(ui->confirmLabel->GetCurState() == ClickLbState::Normal){
            ui->sureEdit->setEchoMode(QLineEdit::Normal);
        }
        else{
            ui->sureEdit->setEchoMode(QLineEdit::Password);
        }
        repolish(ui->sureEdit);
    });

    //界面转换
    _countdownTimer = new QTimer(this);
    connect(_countdownTimer, &QTimer::timeout, this, [this](){
        if(_countdown <= 0){
            //发出信号，实现界面转换
            _countdownTimer->stop();
            emit sigSwitchLogin();
            ui->stackedWidget->setCurrentWidget(ui->page);
            return;
        }
        _countdown--;
        auto str = QString("注册成功，%1 s后返回登录").arg(_countdown);
        ui->tipLabel->setText(str);
    });
}

RegisterDialog::~RegisterDialog()
{
    delete ui;
}

void RegisterDialog::InitHttpHandlers(){
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
    _handlers.insert(ReqId::ID_REG_USER,[this](const QJsonObject& jsonObj){
        int error = jsonObj["error"].toInt();
        if(error == ErrorCodes::SUCCESS){
            auto email = jsonObj["email"].toString();
            auto uid = jsonObj["uid"].toInt();
            showTip(tr("注册成功"),true);
            qDebug() << "email is "<< email;
            qDebug() << "user uid is " << uid;
            //转换成第二个页面，倒计时开始
            changeTipPage();
            return;
        }
        if(error == ErrorCodes::VarifyCodeError){
            showTip(tr("验证码错误"),false);
            return;
        }
        if(error == ErrorCodes::VarifyExpire){
            showTip(tr("验证码无效"),false);
            return;
        }
        if(error == ErrorCodes::UserExits){
            showTip(tr("用户以存在"),false);
            return;
        }

        showTip(tr("注册失败"),false);
    });
}

void RegisterDialog::AddTipErr(TipErr te, QString tips)
{
    _tip_errs[te] = tips;
    showTip(tips,false);
}

void RegisterDialog::DelTipErr(TipErr te)
{
    _tip_errs.remove(te);
    if(_tip_errs.empty()){
        ui->errTip->clear();
        return;
    }
    showTip(_tip_errs.first(), false);
}

bool RegisterDialog::checkUserValid()
{
    if(ui->userEdit->text() == ""){
        AddTipErr(TipErr::TIP_USER_ERR,tr("用户名不能为空"));
        return false;
    }
    DelTipErr(TipErr::TIP_USER_ERR);
    return true;
}

bool RegisterDialog::checkEmailValid()
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

bool RegisterDialog::checkPassValid()
{
    QString pass = ui->passwordEdit->text();
    QString confirm = ui->sureEdit->text();
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
    if(pass != confirm){
        AddTipErr(TipErr::TIP_PWD_CONFIRM,tr("密码和确认密码不匹配"));
        //DelTipErr(TipErr::TIP_PWD_CONFIRM);
        return false;
    }
    DelTipErr(TipErr::TIP_PWD_CONFIRM);
    return true;
}

bool RegisterDialog::checkVarifyValid()
{
    auto pass = ui->verifyEdit->text();
    if(pass.isEmpty()){
        AddTipErr(TipErr::TIP_VARIFY_ERR,tr("验证码不能为空"));
        return false;
    }
    DelTipErr(TipErr::TIP_VARIFY_ERR);
    return true;
}

bool RegisterDialog::checkConfirmValid()
{
    QString pass = ui->passwordEdit->text();
    QString confirm = ui->sureEdit->text();
    if(confirm.length() < 6 || confirm.length() > 15){
        AddTipErr(TipErr::TIP_CONFIRM_ERR,tr("密码长度应为6-15"));
        return false;
    }

    static QRegularExpression regExp("^[a-zA-Z0-9!@#$%^&*]{6,15}$");
    bool match = regExp.match(confirm).hasMatch();
    if(!match){
        AddTipErr(TipErr::TIP_CONFIRM_ERR,tr("不能包含非法字符"));
        return false;
    }
    DelTipErr(TipErr::TIP_CONFIRM_ERR);
    if(pass != confirm){
        AddTipErr(TipErr::TIP_CONFIRM_ERR,tr("密码和确认密码不匹配"));
        return false;
    }
    DelTipErr(TipErr::TIP_CONFIRM_ERR);
    checkPassValid();
    return true;
}

void RegisterDialog::changeTipPage()
{
    _countdownTimer->stop();
    ui->stackedWidget->setCurrentWidget(ui->page_2);
    _countdownTimer->start(1000);
}



void RegisterDialog::showTip(QString str,bool flag){
    if(flag)
    {
        ui->errTip->setProperty("state","normal");//修改状态
    }
    else{
        ui->errTip->setProperty("state","err");//修改状态
    }
    ui->errTip->setText(str);//提示
    repolish(ui->errTip);//刷新qss
}

void RegisterDialog::on_getCode_clicked()
{
    if(ui->userEdit->text() == ""){
        showTip(tr("用户名不能为空"),false);
        return;
    }
    if(ui->passwordEdit->text() == ""){
        showTip(tr("密码不能为空"),false);
        return;
    }
    if(ui->sureEdit->text() == ""){
        showTip(tr("确认密码不能为空"),false);
        return;
    }
    if(ui->passwordEdit->text() != ui->sureEdit->text()){
        showTip(tr("密码不一致"),false);
        return;
    }
    auto email = ui->emailEdit->text();
    static QRegularExpression regex(R"((\w+)(\.|_)?(\w*)@(\w+)(\.(\w+))+)");
    bool match = regex.match(email).hasMatch(); //判断是否匹配
    if(match){
        //发送验证码
        QJsonObject jsonObj;
        jsonObj["user"] = ui->userEdit->text();
        jsonObj["email"] = ui->emailEdit->text();
        jsonObj["passwd"] = ui->passwordEdit->text();
        jsonObj["confirm"] = ui->sureEdit->text();
        HttpMgr::GetInstance()->PostHttpReq(QUrl(gateUrlPrefix+"/getVarifycode"),
                                            jsonObj,ReqId::ID_GET_VARIFY_CODE,Modules::REGISTERMOD);
    }
    else{
        //提示邮箱格式错误
        showTip(tr("邮箱地址不正确"),match);
    }
}

void RegisterDialog::slot_reg_mod_finish(ReqId id, QString res, ErrorCodes err){
    if(err != ErrorCodes::SUCCESS){
        //注册失败,显示提示信息
        showTip(tr("注册失败"),false);
        return;
    }

    //解析JSON,res转换为QByteArray,res.toUtf8()将字符串转换为QByteArray，然后fromJson将其生成json文件
    QJsonDocument jsonDoc = QJsonDocument::fromJson(res.toUtf8());
    if(jsonDoc.isNull()){
        //解析失败
        showTip(tr("json解析失败"),false);
        return;
    }
    //json解析错误
    if(!jsonDoc.isObject()){
        //不为空但没有解析成一个json对象
        showTip(tr("json解析失败"),false);
        return;
    }
    //json文档转json对象
    _handlers[id](jsonDoc.object());

    return;
}

//发送注册请求
void RegisterDialog::on_confirmBtn_clicked()
{
    if(ui->userEdit->text() == ""){
        showTip(tr("用户名不能为空"),false);
        return;
    }
    if(ui->emailEdit->text() == ""){
        showTip(tr("邮箱不能为空"),false);
        return;
    }
    if(ui->passwordEdit->text() == ""){
        showTip(tr("密码不能为空"),false);
        return;
    }
    if(ui->sureEdit->text() == ""){
        showTip(tr("确认密码不能为空"),false);
        return;
    }
    if(ui->passwordEdit->text() != ui->sureEdit->text()){
        showTip(tr("密码不一致"),false);
        return;
    }
    if(ui->verifyEdit->text() == ""){
        showTip(tr("验证码不能为空"),false);
        return;
    }
    //发送http注册请求
    QJsonObject jsonObj;
    jsonObj["user"] = ui->userEdit->text();
    jsonObj["email"] = ui->emailEdit->text();
    jsonObj["passwd"] = xorString(ui->passwordEdit->text());
    jsonObj["confirm"] = xorString(ui->sureEdit->text());//加密
    jsonObj["varify"] = ui->verifyEdit->text();
    HttpMgr::GetInstance()->PostHttpReq(QUrl(gateUrlPrefix+"/userRegister"),jsonObj,ReqId::ID_REG_USER,Modules::REGISTERMOD);
}


void RegisterDialog::on_cancelBtn_clicked()
{
    emit sigSwitchLogin();
    return;
}


void RegisterDialog::on_returnBtn_clicked()
{
    _countdownTimer->stop();
    emit sigSwitchLogin();
    ui->stackedWidget->setCurrentWidget(ui->page);
    return;
}

