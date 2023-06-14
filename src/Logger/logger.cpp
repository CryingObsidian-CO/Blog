#include "logger.hpp"

// using namespace Loggers;

Loggers::spdlevel Loggers::global_level = spdlog::level::debug;       // TODO 从配置文件获取等级
Loggers::spdlevel Loggers::global_flush_level = spdlog::level::debug; // TODO 从配置文件获取等级

void Loggers::drop()
{
    spdlog::drop_all();
}

/// @brief 初始化 Logger
void Loggers::init()
{
    spdlog::flush_every(std::chrono::seconds(5));
    spdlog::flush_on(global_flush_level);
    createFileLogger("default_Logger");
    spdlog::set_default_logger(getLogger("default_Logger"));
    std::atexit(drop);
}

/// @brief 创建一个新的文件 Logger
/// @param logger_name Logger 的名字
void Loggers::createFileLogger(const std::string &logger_name)
{
    std::string log_file_name = ".\\Logs\\" + logger_name + ".log";
    auto logger = spdlog::rotating_logger_mt(logger_name, log_file_name, 1024 * 1024 * 5, 3, false);
    logger->set_level(global_level);
    // spdlog::register_logger(logger);
}

/// @brief 获取一个以创建的 Logger
/// @param logger_name Logger 的名字
/// @return 一个指向 Logger 的指针
std::shared_ptr<spdlog::logger> Loggers::getLogger(const std::string &logger_name)
{
    auto logger = spdlog::get(logger_name);
    if (!logger)
    {
        spdlog::warn("can't 'find the logger named: {0} , use the default logger", logger_name);
        return getLogger("default_Logger");
    }
    return logger;
}

/// @brief 获取 spdlog 的全局Level
/// @return spdlog::level::level_enum
Loggers::spdlevel Loggers::getGlobalLevel()
{
    return global_level;
}

/// @brief 获取 spdlog 的全局FlushLevel
/// @return spdlog::level::level_enum
Loggers::spdlevel Loggers::getGlobalFlushLevel()
{
    return global_flush_level;
}