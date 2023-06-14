#include "JsonUtils.h"

/// @brief Read Json from a file
/// @param filename The file name to open
/// @param doc Save the type of Json library
/// @return true : success, false : failure
bool LoadJson(const char *filename, rapidjson::Document &doc)
{
    std::ifstream ifs(filename);
    if (!ifs.is_open())
    {
        Loggers::Error("Loading Json from path {0} failed. Check that the path is valid", filename);
        return false;
    }

    std::string content((std::istreambuf_iterator<char>(ifs)),
                        (std::istreambuf_iterator<char>()));
    doc.Parse(content.c_str());
    ifs.close();

    Loggers::Info("Loading Json from path {0} successfully. ", filename);
    return true;
}

/// @brief Convert Json to string and output to a file
/// @param filename The file name to write
/// @param doc Save the type of Json library
/// @return true : success, false : failure
bool SaveJson(const char *filename, const rapidjson::Document &doc)
{
    std::ofstream ofs(filename);
    if (!ofs.is_open())
    {
        Loggers::Error("Loading Json from path {0} failed. Check that the path is legitimate.", filename);
        return false;
    }

    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    doc.Accept(writer);
    ofs << buffer.GetString();
    ofs.close();

    Loggers::Info("Saving Json from path {0} successfully.", filename);
    return true;
}

/// @brief Modify the key-value pair in Json
/// @tparam T The type of the value
/// @param doc Save the type of Json library
/// @param key The key to modify
/// @param value The value to modify
/// @return true : success, false : failure
template <typename T>
bool SetJsonValue(rapidjson::Document &doc, const char *key, T value)
{
    if (!hasJsonMember(doc, key))
    {
        Loggers::Warn("JSON files {0} do not contain {1}.", doc, key);
        return false;
    }
    rapidjson::Value &v = doc[key];
    if (v.IsInt())
        v.SetInt(value);
    else if (v.IsString())
        v.SetString(value, doc.GetAllocator());
    else if (v.IsBool())
        v.SetBool(value);
    else if (v.IsDouble())
        v.SetDouble(value);
    else
    {
        Loggers::Error("An unsupported data type was used when storing {0} to {2}, Check the data type of {1}.", key, value, "nowJsonfileName");
        return false;
    }

    Loggers::Info("Set the key {0} from {1} successfully.", key, "nowJsonfileName");
    return true;
}

/// @brief Add a new key-value pair
/// @tparam T The type of the value
/// @param doc Save the type of Json library
/// @param key The key to add
/// @param value The value to add
template <typename T>
void AddJsonMember(rapidjson::Document &doc, const char *key, T value)
{
    rapidjson::Value v;
    v.Set(value, doc.GetAllocator());
    doc.AddMember(rapidjson::StringRef(key), v, doc.GetAllocator());
    Loggers::Info("Create a new key {0} in {1} successfully.", key, "nowJsonfileName");
}

/// @brief Query whether a key exists in Json
/// @param doc Save the type of Json library
/// @param key The key to query
/// @return true : success, false : failure
inline bool hasJsonMember(const rapidjson::Document &doc, const char *key)
{
    return doc.HasMember(key);
}