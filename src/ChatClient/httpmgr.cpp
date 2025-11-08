#include "httpmgr.h"

HttpMgr::HttpMgr() {

    connect(this,&HttpMgr::sig_http_finish, this, &HttpMgr::slot_http_finish);
}

HttpMgr::~HttpMgr(){

}

void HttpMgr::PostHttpReq(QUrl url, QJsonObject json, ReqId reqId, Modules mod){
    QByteArray data = QJsonDocument(json).toJson();
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/json");
    request.setHeader(QNetworkRequest::ContentLengthHeader, QByteArray::number(data.length()));
    //使用伪闭包方法延长生命周期
    auto self = shared_from_this();

    QNetworkReply *reply = _manager.post(request,data);
    //收到对面挥包后replay会发送 一个信号
    QObject::connect(reply, &QNetworkReply::finished,this,[self, reply, reqId, mod](){
        //处理错误情况
        if(reply->error() != QNetworkReply::NoError){
            qDebug() << reply->errorString();
            //发送信号通知完成
            emit self->sig_http_finish(reqId,"",ErrorCodes::ERR_NETWORK,mod);
            reply->deleteLater();//告诉Qt reply不用的时候回收掉
            return;
        }
        //无错误
        QString res = reply->readAll();
        //发送信号通知完成
        emit self->sig_http_finish(reqId,res,ErrorCodes::SUCCESS, mod);
        reply->deleteLater();
        return;
    });
}

void HttpMgr::slot_http_finish(ReqId id, QString res, ErrorCodes err, Modules mod){
    if(mod == Modules::REGISTERMOD){
        //发送信号通知指定模块http的响应结束了
        emit sig_reg_mod_finish(id,res,err);
    }
    if(mod == Modules::RESETPASSWORD){
        //重置密码响应
        emit sig_reset_mod_finish(id, res, err);
    }
    if(mod == Modules::LOGIN){
        //登录响应
        emit sig_login_mod_finish(id, res, err);
    }
}
