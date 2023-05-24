#include "XMySql.h"

#pragma region ClassBasic
/// @brief 构造类并连接数据库（主机名默认为localhost，端口号默认为3306）
/// @param user 用户名
/// @param password 密码
XMySql::XMySql(const std::string &user, const std::string &password, const std::string &database)
{
    XMySql("localhost", user, password, database, 3306);
}
/// @brief 构造类并连接数据库
/// @param host 主机名
/// @param user 用户名
/// @param password 密码
/// @param database 数据库名
/// @param port 端口号
/// @return
XMySql::XMySql(const std::string &host, const std::string &user, const std::string &password, const std::string &database, const unsigned int &port)
{
    Init();
    ConnectSQL(host.c_str(), user.c_str(), password.c_str(), database.c_str(), port);
    //! 在第一次配置时执行(等初次设置的函数完成后)
    // mysql_set_character_set(mysql, "utf8mb3");
}
/// @brief 析构类
XMySql::~XMySql()
{
    disConnect();
}
/// @brief 初始化mysql变量
/// @return true : 成功 false : 失败
bool XMySql::Init()
{
    if (!isInit())
    {
        mysql = mysql_init(0);
        if (isInit())
        {
            Loggers::Info("MySQL is initialized");
            return true;
        }
        else
        {
            Loggers::Error("MySQL initialization failed.");
            return false;
        }
    }
    Loggers::Info("MySQL has been initialized, do not repeat the operation.");
    return false;
}

/// @brief 断开连接
void XMySql::disConnect()
{
    FreeResult();
    // 关闭数据库连接
    if (isConnect())
    {
        mysql_close(mysql);
        mysql = nullptr;
        // 标记断开连接
        _isConnect = false;
    }
}
/// @brief 释放结果集
void XMySql::FreeResult()
{
    // 释放结果集
    if (hasResult())
    {
        mysql_free_result(res);
        res = nullptr;
    }
}
#pragma endregion ClassBasic

/// @brief 连接数据库
/// @param host 主机名
/// @param user 用户名
/// @param password 密码
/// @param database 数据库名
/// @param port 端口号
/// @return true : 已连接   false : 未连接
bool XMySql::ConnectSQL(const std::string &host, const std::string &user, const std::string &password, const std::string &database, const unsigned int &port)
{
    if (isConnect())
    {
        Loggers::Warn("The database is connected.");
        return false;
    }
    if (!isInit())
    {
        Loggers::Warn("Connection failed because MySQL was not initialized, Retry...");
        Init();
        if (!isInit())
        {
            Loggers::Error("Retry failed.");
            return false;
        }
    }
    // 连接数据库（句柄、主机名、用户名、密码、数据库名、端口号、socket指针、标记）
    // 返回 0 连接失败
    if (!mysql_real_connect(mysql, host.c_str(), user.c_str(), password.c_str(), database.c_str(), port, nullptr, 0))
    {
        Loggers::Error("Database connection failed ({0}):{1}, make sure that the hostname, username, etc. are entered correctly.", mysql_errno(mysql), mysql_error(mysql));
        return false;
    }
    _isConnect = true;
    Loggers::Info("The {0} database connection succeeded.", database);
    return true;
}

/// @brief 执行 sql 语句
/// @param sql sql 语句
/// @param sqllen （选填）sql语句长度
/// @return true : 成功   false : 失败
bool XMySql::Query(const std::string &sql, unsigned int sqllen)
{
    if (!isInit())
    {
        Loggers::Warn("Query failed because MySQL was not initialized, Retry...");
        Init();
        if (!isInit())
        {
            Loggers::Error("Retry failed.");
            return false;
        }
    }
    if (sql.empty())
    {
        Loggers::Error("Query failed because the SQL query statement is empty.");
        return false;
    }
    if (sqllen <= 0)
    {
        sqllen = (unsigned int)strlen(sql.c_str());
    }
    if (mysql_real_query(mysql, sql.c_str(), sqllen))
    {
        Loggers::Error("Query failed {0}:{1}.\n", mysql_errno(mysql), mysql_error(mysql));
        return false;
    }
    return true;
}

/// @brief 更改 MySql 设置（通常情况下你应该使用对应字段的特化函数，以避免可能的字段值输入错误）
/// @param option Sql设置字段
/// @param arg 相应字段的值
/// @return true : 成功   false : 失败
bool XMySql::Options(const enum mysql_option &option, const void *arg)
{
    if (!isInit())
    {
        Loggers::Warn("Configure failed because MySQL was not initialized, Retry...");
        Init();
        if (!isInit())
        {
            Loggers::Error("Retry failed.");
            return false;
        }
    }
    if (mysql_options(mysql, option, arg))
    {
        Loggers::Error("Configure failed{0}:{1}.", mysql_errno(mysql), mysql_error(mysql));
        return false;
    }
    // Info("Configuring {0} succeeds", option);
    return true;
}

/// @brief 设置连接超时时间
/// @param sec 单位：s
/// @return true : 成功   false : 失败
bool XMySql::SetConnectTimeout(const int &sec)
{
    return Options(MYSQL_OPT_CONNECT_TIMEOUT, &sec);
}

/// @brief 设置自动重连，默认不开启
/// @param isre true : 自动重连
/// @return true : 成功   false : 失败
bool XMySql::SetReconnect(const bool &isre)
{
    return Options(MYSQL_OPT_RECONNECT, &isre);
}

/// @brief 开始事务
/// @return true : 成功   false : 失败
bool XMySql::StartTransaction()
{
    return Query("SET AUTOCOMMIT = 0");
}

/// @brief 结束事务
/// @return true : 成功   false : 失败
bool XMySql::StopTransactiom()
{
    return Query("SET AUTOCOMMIT = 1");
}

/// @brief 事务提交
/// @return true : 成功   false : 失败
bool XMySql::Commit()
{
    return Query("COMMIT");
}

/// @brief 回滚事务
/// @return true : 成功   false : 失败
bool XMySql::Rollback()
{
    return Query("ROLLBACK");
}

/// @brief 自动生成 insert SQL 语句
/// @param keys 要插入的字段名
/// @param vals 要插入的值
/// @param table 表名称
/// @return 对应的sql语句
std::string XMySql::GetInsertSql(const std::string &keys, const std::string &vals, const std::string &table)
{
    if (keys.empty() || vals.empty() || table.empty())
    {
        Loggers::Warn("Insufficient parameters.");
        return "";
    }

    // inser into table (name,size) values('name1','1024')
    return "insert into `" + table + "` (`" + keys + "`) values ('" + vals + "')";
}

/// @brief 自动生成 insert SQL 语句
/// @param kv 插入数据的字段名和值
/// @param table 表名称
/// @return 对应的sql语句
std::string XMySql::GetInsertSql(const std::map<std::string, std::string> &kv, const std::string &table)
{
    if (kv.empty() || table.empty())
    {
        Loggers::Warn("Insufficient parameters.");
        return "";
    }

    std::string keys = "";
    std::string vals = "";
    // inser into table (name,size) values('Jack','1024')
    for (auto iter = kv.begin(); iter != kv.end(); iter++)
    {
        keys += "`";
        keys += iter->first;
        keys += "`,";

        vals += "'";
        vals += iter->second;
        vals += "',";
    }
    keys.erase(keys.size() - 1);
    vals.erase(vals.size() - 1);

    return "insert into `" + table + "` (" + keys + ") values (" + vals + ")";
}

/// @brief 自动生成 Update sql 语句
/// @param keys 要修改的字段名
/// @param vals 要修改的值
/// @param table 表名称
/// @param where 修改条件（用于指定哪些数据要修改）
/// @return 对应的sql语句
std::string XMySql::GetUpdateSql(const std::string &keys, const std::string &vals, const std::string &table, const std::string &where)
{
    if (keys.empty() || vals.empty() || table.empty())
    {
        Loggers::Warn("Insufficient parameters.");
        return "";
    }

    return "update `" + table + "` set `" + keys + "`='" + vals + "' where " + where;
}

/// @brief 自动生成 Update sql 语句
/// @param kv 要修改的数据的字段名和值
/// @param table 表名称
/// @param where 修改条件（用于指定哪些数据要修改）
/// @return 对应的sql语句
std::string XMySql::GetUpdateSql(const std::map<std::string, std::string> &kv, const std::string &table, const std::string &where)
{
    if (kv.empty() || table.empty())
    {
        Loggers::Warn("Insufficient parameters.");
        return "";
    }

    std::string sql = "";
    // update `table` set `name` = 'test_001' where `id`=`id`
    for (auto iter = kv.begin(); iter != kv.end(); iter++)
    {
        sql += "`";
        sql += iter->first;
        sql += "`=";

        sql += "'";
        sql += iter->second;
        sql += "',";
    }
    sql.erase(sql.length() - 1);

    return "update `" + table + "` set " + sql + " where " + where;
}

/// @brief 修改非二进制数据
/// @param keys 要修改的字段名
/// @param vals 要修改的值
/// @param table 表名称
/// @param where 修改条件（用于指定哪些数据要修改）
/// @return 返回 Update 影响的记录数，如果失败返回-1
int XMySql::Update(const std::string &keys, const std::string &vals, const std::string &table, const std::string &where)
{
    std::string sql = GetUpdateSql(keys, vals, table, where);
    if (!Query(sql.c_str()))
    {
        Loggers::Error("Modification failed, make sure the SQL statement is correct. ↑");
        return -1;
    }

    return mysql_affected_rows(mysql);
}

/// @brief 修改非二进制数据
/// @param kv 要修改的数据的字段名和值
/// @param table 表名称
/// @param where 修改条件（用于指定哪些数据要修改）
/// @return 返回 Update 影响的记录数，如果失败返回-1
int XMySql::Update(const std::map<std::string, std::string> &kv, const std::string &table, const std::string &where)
{
    std::string sql = GetUpdateSql(kv, table, where);
    if (!Query(sql.c_str()))
    {
        Loggers::Error("Modification failed, make sure the SQL statement is correct. ↑");
        return -1;
    }

    return mysql_affected_rows(mysql);
}

/// @brief 插入非二进制数据
/// @param keys 要插入的字段名
/// @param vals 要插入的值
/// @param table 表名称
/// @return
bool XMySql::Insert(const std::string &keys, const std::string &vals, const std::string &table)
{
    std::string sql = GetInsertSql(keys, vals, table);

    if (sql.empty())
    {
        Loggers::Error("Failed to generate MySQL insert statement.");
        return false;
    }
    if (Query(sql.c_str()) || mysql_affected_rows(mysql) <= 0)
    {
        Loggers::Error("Insert failed, make sure that the SQL statement is correct. ↑");
        return false;
    }

    return true;
}

/// @brief 插入非二进制数据
/// @param kv 插入数据的字段名和值
/// @param table 表名称
/// @return
bool XMySql::Insert(const std::map<std::string, std::string> &kv, const std::string &table)
{
    std::string sql = GetInsertSql(kv, table);

    if (sql.empty())
    {
        Loggers::Error("Failed to generate MySQL insert statement.");
        return false;
    }
    if (Query(sql.c_str()) || mysql_affected_rows(mysql) <= 0)
    {
        Loggers::Error("Insert failed, make sure that the SQL statement is correct. ↑");
        return false;
    }

    return true;
}

/// @brief 获取结果集
/// @return true : 成功   false : 失败
bool XMySql::StoreResult()
{
    if (!isInit())
    {
        Loggers::Warn("StoreResult failed because MySQL was not initialized, Retry...");
        Init();
        if (!isInit())
        {
            Loggers::Error("Retry failed.");
            return false;
        }
    }
    FreeResult();

    res = mysql_store_result(mysql);
    if (!hasResult())
    {
        Loggers::Error("Failed to get result set ({0}):{1}.", mysql_errno(mysql), mysql_error(mysql));
        return false;
    }

    return true;
}

/// @brief 接受结果
/// @return true : 成功   false : 失败
bool XMySql::UseResult()
{
    if (!isInit())
    {
        Loggers::Warn("UseResult failed because MySQL was not initialized, Retry...");
        Init();
        if (!isInit())
        {
            Loggers::Error("Retry failed.");
            return false;
        }
    }
    FreeResult();

    res = mysql_use_result(mysql);
    if (!hasResult())
    {
        Loggers::Error("Failed to get result set ({0}):{1}.", mysql_errno(mysql), mysql_error(mysql));
        return false;
    }

    return true;
}

/// @brief 获取一行数据
/// @return 返回结果数组
std::vector<SqlData> XMySql::FetchRow()
{
    std::vector<SqlData> re;
    if (!hasResult())
    {
        return re;
    }
    MYSQL_ROW row = mysql_fetch_row(res); // 获取一行
    if (!row)
    {
        return re;
    }

    // 获取列数
    unsigned long *lens = mysql_fetch_lengths(res); // 获取每个字段内容的大小
    for (int i = 0; i < mysql_num_fields(res); i++) // 挨个将一行中的每个字段插入到vector
    {
        re.push_back((SqlData){row[i], lens[i]}); // 插入形成一行
    }
    return re;
}

#pragma region State
/// @brief 数据库连接状态
/// @return true : 已连接   false : 未连接
inline bool XMySql::isConnect() const
{
    return _isConnect;
}
/// @brief 是否获得结果集
/// @return true : 已获得 false : 未获得
inline bool XMySql::hasResult() const
{
    return res == nullptr ? false : true;
}
/// @brief mysql是否初始化
/// @return true : 已初始化 false : 未初始化
inline bool XMySql::isInit() const
{
    return mysql == nullptr ? false : true;
}
#pragma endregion State