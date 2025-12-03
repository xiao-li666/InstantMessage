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

bool MysqlDao::AddFriendApply(const int& from, const int& to)
{
	auto con = pool_->getConnection();
    if (con == nullptr) {
        return false;
    }
	Defer defer([this, &con]() {
		pool_->returnConnection(std::move(con));
		});
    try {
        std::unique_ptr<sql::PreparedStatement> pstmt(con->_conn->prepareStatement("INSERT INTO friend_apply (from_uid,to_uid) VALUES (?,?) "
            "ON DUPLICATE KEY UPDATE from_uid = from_uid, to_uid = to_uid"));
		pstmt->setInt(1, from);
		pstmt->setInt(2, to);
		int updateCount = pstmt->executeUpdate();
		std::cout << "insert friend apply rows is " << updateCount << std::endl;
        if (updateCount < 0) {
			return false;
        }
        return true;
    }
    catch(sql::SQLException &e){
        std::cerr << "SQLException: " << e.what();
        std::cerr << " (MySQL error code: " << e.getErrorCode();
        std::cerr << ", SQLState: " << e.getSQLState() << " )" << std::endl;
        return false;
    }
    return false;
}

bool MysqlDao::GetApplyList(int touid, std::vector<std::shared_ptr<ApplyInfo>>& applyList, int begin, int limit)
{
    auto con = pool_->getConnection();
	if (con == nullptr) {
		return false;
	}
    Defer defer([this,&con]() {
        pool_->returnConnection(std::move(con));
        });
    try {
        std::unique_ptr<sql::PreparedStatement> pstmt(con->_conn->prepareStatement("SELECT apply.from_uid, apply.status, user.name, "
        "user.nick, user.sex, user.icon FROM friend_apply as apply join user ON apply.from_uid=user.uid WHERE apply.to_uid = ?"
        " AND apply.id > ? ORDER BY apply.id ASC LIMIT ? "));
		pstmt->setInt(1, touid);
		pstmt->setInt(2, begin);
		pstmt->setInt(3, limit);

		std::unique_ptr<sql::ResultSet> res(pstmt->executeQuery());
        while (res->next()) {
			auto name = res->getString("name");
            auto uid = res->getInt("from_uid");
            auto status = res->getInt("status");
            auto nick = res->getString("nick");
            auto sex = res->getInt("sex");
            auto icon = res->getString("icon");
			auto apply_ptr = std::make_shared<ApplyInfo>(uid, name, "", icon, nick, sex, status);
            applyList.push_back(apply_ptr);
        }
        return true;
    }
    catch (sql::SQLException& e) {
        std::cerr << "SQLException: " << e.what();
        std::cerr << " (MySQL error code: " << e.getErrorCode();
        std::cerr << ", SQLState: " << e.getSQLState() << " )" << std::endl;
        return false;
    }
    return false;
}

bool MysqlDao::GetFriendList(int self_uid, std::vector<std::shared_ptr<UserInfo>>& friendList)
{
	auto con = pool_->getConnection();
    if (con == nullptr) {
		return false;
    }
	Defer defer([this, &con]() {
		pool_->returnConnection(std::move(con));
		});
    try {
        std::unique_ptr<sql::PreparedStatement> pstmt(con->_conn->prepareStatement("SELECT * FROM friend WHERE self_id = ?"));
		pstmt->setInt(1, self_uid);
		std::unique_ptr<sql::ResultSet> res(pstmt->executeQuery());
        while (res->next()) {
			auto friend_id = res->getInt("friend_id");
			auto back = res->getString("back");
			auto user_info = GetUser(friend_id);
            if (user_info == nullptr) {
                continue;
            }
			user_info->back = back;
			friendList.push_back(user_info);
        }
		return true;
    }
	catch (sql::SQLException& e) {
		std::cerr << "SQLException: " << e.what();
		std::cerr << " (MySQL error code: " << e.getErrorCode();
		std::cerr << ", SQLState: " << e.getSQLState() << " )" << std::endl;
		return false;
	}
    return false;
}

bool MysqlDao::AuthFriendApply(const int& from, const int& to)
{
	auto con = pool_->getConnection();
	if (con == nullptr) {
		return false;
	}
    Defer defer([this, &con]() {
        pool_->returnConnection(std::move(con));
        });

    try {
        std::unique_ptr<sql::PreparedStatement> pstmt(con->_conn->prepareStatement("UPDATE friend_apply SET status = 1 "
        "WHERE from_uid = ? AND to_uid = ?"));
		pstmt->setInt(1, to);
		pstmt->setInt(2, from);

        int updateCount = pstmt->executeUpdate();
        if (updateCount < 0) {
            return false;
        }
        return true;
    }
    catch (sql::SQLException &e) {
        std::cerr << "SQLException: " << e.what();
        std::cerr << " (MySQL error code: " << e.getErrorCode();
        std::cerr << ", SQLState: " << e.getSQLState() << " )" << std::endl;
    }
    return false;
}

bool MysqlDao::AddFriend(const int& from, const int& to, const std::string& back)
{
    auto con = pool_->getConnection();
    if (con == nullptr) {
        return false;
    }

    Defer defer([this, &con]() {
        pool_->returnConnection(std::move(con));
        });

    try {

        //开始事务
        con->_conn->setAutoCommit(false);

        // 准备第一个SQL语句, 插入认证方好友数据
        std::unique_ptr<sql::PreparedStatement> pstmt(con->_conn->prepareStatement("INSERT IGNORE INTO friend(self_id, friend_id, back) "
            "VALUES (?, ?, ?) "
        ));
        //反过来的申请时from，验证时to
        pstmt->setInt(1, from); // from id
        pstmt->setInt(2, to);
        pstmt->setString(3, back);
        // 执行更新
        int rowAffected = pstmt->executeUpdate();
        if (rowAffected < 0) {
            con->_conn->rollback();
            return false;
        }

        //准备第二个SQL语句，插入申请方好友数据
        std::unique_ptr<sql::PreparedStatement> pstmt2(con->_conn->prepareStatement("INSERT IGNORE INTO friend(self_id, friend_id, back) "
            "VALUES (?, ?, ?) "
        ));
        //反过来的申请时from，验证时to
        pstmt2->setInt(1, to); // from id
        pstmt2->setInt(2, from);
        pstmt2->setString(3, "");
        // 执行更新
        int rowAffected2 = pstmt2->executeUpdate();
        if (rowAffected2 < 0) {
            con->_conn->rollback();
            return false;
        }

        // 提交事务
        con->_conn->commit();
        std::cout << "addfriend insert friends success" << std::endl;

        return true;
    }
    catch (sql::SQLException& e) {
        // 如果发生错误，回滚事务
        if (con) {
            con->_conn->rollback();
        }
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
            std::cout << "uid is not exits in database, uid = " << uid << std::endl;
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
