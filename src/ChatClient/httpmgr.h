#ifndef HTTPMGR_H
#define HTTPMGR_H
#include "singleton.h"

//CRTP
class HttpMgr : public QObject, public Singleton<HttpMgr>,public std::enable_shared_from_this<HttpMgr>
{
    Q_OBJECT
    friend class Singleton<HttpMgr>;
public:
    ~HttpMgr();

        //模块，具体功能的id
    void PostHttpReq(QUrl url, QJsonObject json, ReqId reqId, Modules mod);

private:
    HttpMgr();
    QNetworkAccessManager _manager;

private slots:
    void slot_http_finish(ReqId id, QString res, ErrorCodes err, Modules mod);

signals:
    void sig_http_finish(ReqId id, QString res, ErrorCodes err, Modules mod);
    void sig_reg_mod_finish(ReqId id, QString res, ErrorCodes err);
    void sig_reset_mod_finish(ReqId id, QString res, ErrorCodes err);
    void sig_login_mod_finish(ReqId id, QString res, ErrorCodes err);

};

#endif // HTTPMGR_H
