#ifndef _XMYSQL_H
#define _XMYSQL_H

#include <map>
#include <string>
#include <vector>
#include <iostream>
#include "SqlData.h"
#include "logger.hpp"

/// @brief 对Mysql数据库的操作
class XMySql
{
public:
private:
    bool _isConnect = false;
    // 创建数据库句柄
    MYSQL *mysql = nullptr;
    // 创建数据库查询结果集
    MYSQL_RES *res = nullptr;
    // 一个行数据的类型安全(type-safe)的表示
    MYSQL_ROW row;
    // 查询语句
    char query[300];

public:
    ~XMySql();
    XMySql() = delete;
    XMySql(const std::string &user, const std::string &password, const std::string &database);
    XMySql(const std::string &host, const std::string &user, const std::string &password, const std::string &database, const unsigned int &port);

    bool Init(); // 初始化mysql
    bool ConnectSQL(const std::string &host, const std::string &user, const std::string &password, const std::string &database, const unsigned int &port);
    void disConnect();
    void FreeResult();

    // 通用
    bool Query(const std::string &sql, unsigned int sqllen = -1);
    bool UseResult();
    bool StoreResult();
    std::vector<SqlData> FetchRow();

    // 操作
    bool Insert(const std::string &keys, const std::string &vals, const std::string &table);
    bool Insert(const std::map<std::string, std::string> &kv, const std::string &table);
    int Update(const std::string &keys, const std::string &vals, const std::string &table, const std::string &where);
    int Update(const std::map<std::string, std::string> &kv, const std::string &table, const std::string &where);
    int UpdateBin(const std::string &keys, const std::string &vals, const std::string &table, const std::string &where);
    int UpdateBin(const std::map<std::string, std::string> &kv, const std::string &table, const std::string &where);

    // 配置
    bool SetConnectTimeout(const int &sec);
    bool SetReconnect(const bool &isre = true);
    bool Options(const enum mysql_option &option, const void *arg);
    bool StartTransaction();
    bool StopTransactiom();
    bool Commit();
    bool Rollback();

    // template <typename T>
    // T QueryField(std::string table_name);

    // 状态
    inline bool isConnect() const;
    inline bool hasResult() const;
    inline bool isInit() const;

protected:
    std::string GetInsertSql(const std::string &keys, const std::string &vals, const std::string &table);
    std::string GetInsertSql(const std::map<std::string, std::string> &kv, const std::string &table);
    std::string GetUpdateSql(const std::string &keys, const std::string &vals, const std::string &table, const std::string &where);
    std::string GetUpdateSql(const std::map<std::string, std::string> &kv, const std::string &table, const std::string &where);

    // int GetTableField(std::string table_name);
};

#endif // _XMYSQL_H