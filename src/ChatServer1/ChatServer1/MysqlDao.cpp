#include "MysqlDao.h"
#include "ConfigMgr.h"
MysqlDao::MysqlDao()
{
    auto& cfg = ConfigMgr::GetInstance();
    const auto& host = cfg["Mysql"]["Host"];
    const auto& port = cfg["Mysql"]["Port"];
    const auto& pwd = cfg["Mysql"]["Passwd"];
    const auto& schema = cfg["Mysql"]["Schema"];
    const auto& user = cfg["Mysql"]["User"];
    pool_.reset(new MySqlPool(host + ":" + port, user, pwd, schema, 5));
}
MysqlDao::~MysqlDao() {
    pool_->Close();
}
int MysqlDao::RegUser(const std::string& name, const std::string& email, const std::string& pwd)
{
    auto con = pool_->getConnection();
    Defer defer([this, &con]() {
        pool_->returnConnection(std::move(con));
        });
    try {
        if (con == nullptr) {
            //pool_->returnConnection(std::move(con));
            return false;
        }
        // 准备调用存储过程
        std::unique_ptr < sql::PreparedStatement > stmt(con->_conn->prepareStatement("CALL reg_user(?,?,?,@result)"));
        // 设置输入参数
        stmt->setString(1, name);
        stmt->setString(2, email);
        stmt->setString(3, pwd);
        // 由于PreparedStatement不直接支持注册输出参数，我们需要使用会话变量或其他方法来获取输出参数的值
          // 执行存储过程
        stmt->execute();
        // 如果存储过程设置了会话变量或有其他方式获取输出参数的值，你可以在这里执行SELECT查询来获取它们
       // 例如，如果存储过程设置了一个会话变量@result来存储输出结果，可以这样获取：
        std::unique_ptr<sql::Statement> stmtResult(con->_conn->createStatement());
        std::unique_ptr<sql::ResultSet> res(stmtResult->executeQuery("SELECT @result AS result"));
        if (res->next()) {
            int result = res->getInt("result");
            std::cout << "Result: " << result << std::endl;
            return result;
        }
        return -1;
    }
    catch (sql::SQLException& e) {
        std::cerr << "SQLException: " << e.what();
        std::cerr << " (MySQL error code: " << e.getErrorCode();
        std::cerr << ", SQLState: " << e.getSQLState() << " )" << std::endl;
        return -1;
    }
}

bool MysqlDao::checkEmail(const std::string& name, const std::string& email)
{
    auto con = pool_->getConnection();
    Defer defer([this, &con]() {
        pool_->returnConnection(std::move(con));
        });
    try {
        if (con == nullptr) {
            return false;
        }
        std::unique_ptr<sql::PreparedStatement> stmt(con->_conn->prepareStatement("SELECT EXISTS(SELECT 1 FROM user WHERE email = ? AND name = ? ) as user_exists"));
        stmt->setString(1, email);
        stmt->setString(2, name);
        std::unique_ptr<sql::ResultSet> res(stmt->executeQuery());
        if (res->next()) {
            bool exists = res->getBoolean("user_exists");
            return exists;
        }
        return false;
    }
    catch (sql::SQLException& e) {
        std::cerr << "SQLException: " << e.what();
        std::cerr << " (MySQL error code: " << e.getErrorCode();
        std::cerr << ", SQLState: " << e.getSQLState() << " )" << std::endl;
        return false;
    }
}

bool MysqlDao::updatePwd(const std::string& email, const std::string& newPwd)
{
    auto con = pool_->getConnection();
    Defer defer([this, &con]() {
        pool_->returnConnection(std::move(con));
        });
    try {
        if (con == nullptr) {
            return false;
        }
        std::unique_ptr<sql::PreparedStatement> stmt(con->_conn->prepareStatement("UPDATE user SET pwd = ? WHERE email = ?"));
        stmt->setString(1, newPwd);
        stmt->setString(2, email);
        int updateCount = stmt->executeUpdate();
        std::cout << "update rows is " << updateCount << std::endl;
        return true;
    }
    catch (sql::SQLException& e) {
        std::cerr << "SQLException: " << e.what();
        std::cerr << " (MySQL error code: " << e.getErrorCode();
        std::cerr << ", SQLState: " << e.getSQLState() << " )" << std::endl;
        return false;
    }
}

bool MysqlDao::selectPwd(const std::string& email, UserInfo& userInfo)
{
    auto con = pool_->getConnection();
    if (con == nullptr) {
        return false;
    }
    Defer defer([this,&con]() {
        pool_->returnConnection(std::move(con));
        });
    try {
        std::unique_ptr<sql::PreparedStatement> stmt(con->_conn->prepareStatement("SELECT * FROM user WHERE email=?"));
        stmt->setString(1, email);
        std::unique_ptr<sql::ResultSet> res(stmt->executeQuery());
        if (res->next()) {
            userInfo.pwd = res->getString("pwd");
            userInfo.email = res->getString("email");
            userInfo.name = res->getString("name");
            userInfo.uid = res->getInt("uid");
            userInfo.nick = res->getString("nick");
            //userInfo.back = res->getString("back");
            userInfo.desc = res->getString("desc");
            userInfo.icon = res->getString("icon");
            userInfo.sex = res->getInt("sex");
            std::cout << "select pwd is " << userInfo.pwd << std::endl;
        }
        else {
            std::cout << "email is not exits in database" << std::endl;
            return false;
        }
    }
    catch (sql::SQLException& e) {
        std::cerr << "SQLException: " << e.what();
        std::cerr << " (MySQL error code: " << e.getErrorCode();
        std::cerr << ", SQLState: " << e.getSQLState() << " )" << std::endl;
        return false;
    }
    return true;
}

std::shared_ptr<UserInfo> MysqlDao::GetUser(int uid)
{
    auto con = pool_->getConnection();
    if (con == nullptr) {
        return nullptr;
    }
    Defer defer([this, &con]() {
        pool_->returnConnection(std::move(con));
        });
    std::shared_ptr<UserInfo> userInfo = std::make_shared<UserInfo>();
    try {
        std::unique_ptr<sql::PreparedStatement> stmt(con->_conn->prepareStatement("SELECT * FROM user WHERE uid=?"));
        stmt->setInt(1, uid);
        std::unique_ptr<sql::ResultSet> res(stmt->executeQuery());
        if (res->next()) {
            userInfo->pwd = res->getString("pwd");
            userInfo->email = res->getString("email");
            userInfo->name = res->getString("name");
            userInfo->uid = res->getInt("uid");
            userInfo->nick = res->getString("nick");
            //userInfo.back = res->getString("back");
            userInfo->desc = res->getString("desc");
            userInfo->icon = res->getString("icon");
            userInfo->sex = res->getInt("sex");
            std::cout << "select pwd is " << userInfo->pwd << std::endl;
            return userInfo;
        }
        else {
            std::cout << "email is not exits in database" << std::endl;
            return nullptr;
        }
    }
    catch (sql::SQLException& e) {
        std::cerr << "SQLException: " << e.what();
        std::cerr << " (MySQL error code: " << e.getErrorCode();
        std::cerr << ", SQLState: " << e.getSQLState() << " )" << std::endl;
        return nullptr;
    }
    return nullptr;
}

std::shared_ptr<UserInfo> MysqlDao::GetUser(const std::string& email)
{
    auto con = pool_->getConnection();
    if (con == nullptr) {
        return nullptr;
    }
    Defer defer([this, &con]() {
        pool_->returnConnection(std::move(con));
        });

    std::shared_ptr<UserInfo> userInfo = std::make_shared<UserInfo>();
    try {
        std::unique_ptr<sql::PreparedStatement> stmt(con->_conn->prepareStatement("SELECT * FROM user WHERE email=?"));
        stmt->setString(1, email);
        std::unique_ptr<sql::ResultSet> res(stmt->executeQuery());
        if (res->next()) {
            userInfo->name = res->getString("name");
            userInfo->uid = res->getInt("uid");
            userInfo->nick = res->getString("nick");
            userInfo->desc = res->getString("desc");
            userInfo->icon = res->getString("icon");
            userInfo->sex = res->getInt("sex");
        }
        return userInfo;
    }
    catch (sql::SQLException& e) {
        std::cerr << "SQLException: " << e.what();
        std::cerr << " (MySQL error code: " << e.getErrorCode();
        std::cerr << ", SQLState: " << e.getSQLState() << " )" << std::endl;
        return nullptr;
    }
    return nullptr;
}
