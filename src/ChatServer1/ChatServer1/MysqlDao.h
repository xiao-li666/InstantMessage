#pragma once
#include "const.h"
#include "data.h"

//超时断开连接
class SqlConnection {
public:
    SqlConnection(sql::Connection* conn, int64_t lasttime) : _conn(conn), _last_oper_time(lasttime)
    {
    }

    int64_t _last_oper_time;
    std::unique_ptr<sql::Connection> _conn;
};

class MySqlPool {
public:
    MySqlPool(const std::string& url, const std::string& user, const std::string& pass, const std::string& schema, int poolSize)
        : url_(url), user_(user), pass_(pass), schema_(schema), poolSize_(poolSize), b_stop_(false) {
        try {
            for (int i = 0; i < poolSize_; ++i) {
                sql::mysql::MySQL_Driver* driver = sql::mysql::get_mysql_driver_instance();
                auto *con = driver->connect(url_, user_, pass_);
                con->setSchema(schema_);
                //获取当前时间
                auto currenttime = std::chrono::system_clock::now().time_since_epoch();
                //将时间转换为秒
                long long timestamp = std::chrono::duration_cast<std::chrono::seconds>(currenttime).count();
                pool_.push(std::make_unique<SqlConnection>(con,timestamp));
            }

            _checkThread = std::thread([this]() {
                while (!b_stop_) {
                    checkConnection();
                    std::this_thread::sleep_for(std::chrono::seconds(60));//每隔1分钟检查一次
                }
                });
            _checkThread.detach();
        }
        catch (sql::SQLException& e) {
            // 处理异常
            std::cout << "mysql pool init failed" << e.what() << std::endl;
        }
    }
    void checkConnection() {
        std::lock_guard<std::mutex> guard(mutex_);
        std::size_t poolSize = pool_.size();
        auto currenttime = std::chrono::system_clock::now().time_since_epoch();
        auto timestamp = std::chrono::duration_cast<std::chrono::seconds>(currenttime).count();
        for (int i = 0; i < poolSize; i++) {
            std::unique_ptr<SqlConnection> con(std::move(pool_.front()));
            pool_.pop();

            Defer defer([this, &con]() {
                pool_.push(std::move(con));
                });

            if (timestamp - con->_last_oper_time < 5) {
                continue;
            }
            try {
                std::unique_ptr<sql::Statement> stmt(con->_conn->createStatement());
                stmt->executeQuery("SELECT 1");
                con->_last_oper_time = timestamp;
                //std::cout << "execute timer alive query, cur is " << timestamp << std::endl;
            }
            catch (sql::SQLException& ec) {
                std::cout << "Error keeping connection alive" << ec.what() << std::endl;
                //重新创建连接并替换旧的连接
                sql::mysql::MySQL_Driver* driver = sql::mysql::get_mysql_driver_instance();
                auto* newcon = driver->connect(url_, user_, pass_);
                newcon->setSchema(schema_);
                con->_conn.reset(newcon);
                con->_last_oper_time = timestamp;
            }
        }
    }
    std::unique_ptr<SqlConnection> getConnection() {
        std::unique_lock<std::mutex> lock(mutex_);
        cond_.wait(lock, [this] {
            if (b_stop_) {
                return true;
            }
            return !pool_.empty(); });
        if (b_stop_) {
            return nullptr;
        }
        std::unique_ptr<SqlConnection> con(std::move(pool_.front()));
        pool_.pop();
        return con;
    }
    void returnConnection(std::unique_ptr<SqlConnection> con) {
        std::unique_lock<std::mutex> lock(mutex_);
        if (b_stop_) {
            return;
        }
        pool_.push(std::move(con));
        cond_.notify_one();
    }
    void Close() {
        b_stop_ = true;
        cond_.notify_all();
    }
    ~MySqlPool() {
        std::unique_lock<std::mutex> lock(mutex_);
        while (!pool_.empty()) {
            pool_.pop();
        }
    }
private:
    std::string url_;
    std::string user_;
    std::string pass_;
    std::string schema_;
    int poolSize_;
    std::queue<std::unique_ptr<SqlConnection>> pool_;
    std::mutex mutex_;
    std::condition_variable cond_;
    std::atomic<bool> b_stop_;
    std::thread _checkThread;//检测线程，检测是否超过一定时间，超时断开连接
};

//struct UserInfo {
//    std::string name;
//    std::string pwd;
//    int uid;
//    std::string email;
//};

class MysqlDao
{
public:
    MysqlDao();
    ~MysqlDao();
    int RegUser(const std::string& name, const std::string& email, const std::string& pwd);
    bool checkEmail(const std::string& name, const std::string& email);
    bool updatePwd(const std::string& email, const std::string& newPwd);
    bool selectPwd(const std::string& email,UserInfo& userInfo);
    bool AddFriendApply(const int& from, const int& to);
    bool GetApplyList(int touid, std::vector<std::shared_ptr<ApplyInfo>>& applyList, int begin, int limit = 10);
    bool AuthFriendApply(const int& from, const int& to);
    bool AddFriend(const int& from, const int& to, const std::string& back);
    std::shared_ptr<UserInfo> GetUser(int uid);
    std::shared_ptr<UserInfo> GetUser(const std::string &name);

private:
    std::unique_ptr<MySqlPool> pool_;
};

