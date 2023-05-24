#ifndef _SQL_DATA_H
#define _SQL_DATA_H

#include "mysql/mysql.h"
#include <string>

struct SqlData
{
    SqlData(const char *_data) : data(_data), size(strlen(_data)) {}
    SqlData(const char *_data, const unsigned int _size) : data(_data), size(_size) {}

    SqlData(const int *d) : type(MYSQL_TYPE_LONG), data(reinterpret_cast<const char *>(d)), size(sizeof(int)) {} // 支持插入整型

    enum_field_types type = MYSQL_TYPE_STRING; // 类型
    const char *data = 0;                      // 存放具体数据
    unsigned int size = 0;
};

#endif