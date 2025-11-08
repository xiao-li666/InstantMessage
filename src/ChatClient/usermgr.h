#ifndef USERMGR_H
#define USERMGR_H
#include <QObject>
#include <memory>
#include <singleton.h>

class UserMgr : public QObject ,public Singleton<UserMgr>
{
    Q_OBJECT
public:
    friend class Singleton<UserMgr>;
    ~UserMgr();
    void SetName(QString name);
    void SetUid(int uid);
    void SetToken(QString token);
private:
    UserMgr();
    QString _name;
    QString _token;
    int _uid;
};

#endif // USERMGR_H
