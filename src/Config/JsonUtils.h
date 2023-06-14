#ifndef _JSON_UTILS_H
#define _JSON_UTILS_H

#include <fstream>
#include "logger.hpp"
#include "rapidjson/writer.h"
#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"

bool LoadJson(const char *filename, rapidjson::Document &doc);
bool SaveJson(const char *filename, const rapidjson::Document &doc);
inline bool hasJsonMember(const rapidjson::Document &doc, const char *key);

template <typename T>
bool SetJsonValue(rapidjson::Document &doc, const char *key, T value);
template <typename T>
void AddJsonMember(rapidjson::Document &doc, const char *key, T value);

#endif // _JSON_UTILS_H
