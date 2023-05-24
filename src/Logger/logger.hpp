#ifndef _LOGGER_HPP
#define _LOGGER_HPP

#include <vector>
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/rotating_file_sink.h"

namespace Loggers
{
    typedef spdlog::level::level_enum spdlevel;

    extern spdlevel global_level;
    extern spdlevel global_flush_level;

    extern void init();
    extern void drop();

    extern spdlevel getGlobalLevel();
    extern spdlevel getGlobalFlushLevel();

    extern void createFileLogger(const std::string &logger_name);
    extern std::shared_ptr<spdlog::logger> getLogger(const std::string &logger_name);
    // TODO 更改单个 logger 记录等级
    // TODO 更改单个 logger 刷新等级
    // TODO 更改单个 logger 刷新时间
    // TODO 更改单个 logger 输出格式

    // TODO 更改单个 sink 记录等级
    // TODO 更改单个 sink 刷新等级
    // TODO 更改单个 sink 刷新时间
    // TODO 更改单个 sink 输出格式 spdlog::source_loc{__FILE__, __LINE__, SPDLOG_FUNCTION}

    // TODO 更改全局记录等级
    // TODO 更改全局刷新时间
    // TODO 更改全局记录等级
    // TODO 更改全局输出格式 spdlog::set_pattern("[%Y-%m-%d %H:%M:%S.%e][%n][%l][%s,%!]:%v");

    /// @brief 创建一个日志
    /// @param logger_name 要使用的 Logger 的名称
    /// @param lvl 日志等级
    /// @param fmt 要格式化的字符串
    /// @param ...args 向字符串中填充的内容，以字符串中的 {} 为标志
    template <typename... Args>
    inline void Log(const std::string &logger_name, spdlevel lvl, fmt::format_string<Args...> fmt, Args &&...args)
    {
        Loggers::getLogger(logger_name)->log(lvl, fmt, std::forward<Args>(args)...);
    }

    /// @brief 使用默认的 Logger 创建一个 Debug 等级的日志
    /// @param fmt 要格式化的字符串
    /// @param ...args 向字符串中填充的内容，以字符串中的 {} 为标志
    template <typename... Args>
    inline void Debug(fmt::format_string<Args...> fmt, Args &&...args)
    {
        spdlog::log(spdlevel::debug, fmt, std::forward<Args>(args)...);
    }

    /// @brief 使用默认的 Logger 创建一个 Info 等级的日志
    /// @param fmt 要格式化的字符串
    /// @param ...args 向字符串中填充的内容，以字符串中的 {} 为标志
    template <typename... Args>
    inline void Info(fmt::format_string<Args...> fmt, Args &&...args)
    {
        spdlog::log(spdlevel::info, fmt, std::forward<Args>(args)...);
    }

    /// @brief 使用默认的 Logger 创建一个 Warn 等级的日志
    /// @param fmt 要格式化的字符串
    /// @param ...args 向字符串中填充的内容，以字符串中的 {} 为标志
    template <typename... Args>
    inline void Warn(fmt::format_string<Args...> fmt, Args &&...args)
    {
        spdlog::log(spdlevel::warn, fmt, std::forward<Args>(args)...);
    }

    /// @brief 使用默认的 Logger 创建一个 Error 等级的日志
    /// @param fmt 要格式化的字符串
    /// @param ...args 向字符串中填充的内容，以字符串中的 {} 为标志
    template <typename... Args>
    inline void Error(fmt::format_string<Args...> fmt, Args &&...args)
    {
        spdlog::log(spdlevel::err, fmt, std::forward<Args>(args)...);
    }

    /// @brief 使用默认的 Logger 创建一个 Critical 等级的日志，注意：他同时会终止程序进行
    /// @param fmt 要格式化的字符串
    /// @param ...args 向字符串中填充的内容，以字符串中的 {} 为标志
    template <typename... Args>
    inline void Critical(fmt::format_string<Args...> fmt, Args &&...args)
    {
        spdlog::log(spdlevel::critical, fmt, std::forward<Args>(args)...);
        exit(0);
    }

    /// @brief 创建一个 Denug 等级的日志
    /// @param logger_name 要使用的 Logger 的名称
    /// @param fmt 要格式化的字符串
    /// @param ...args 向字符串中填充的内容，以字符串中的 {} 为标志
    template <typename... Args>
    inline void Debug(const std::string &logger_name, fmt::format_string<Args...> fmt, Args &&...args)
    {
        Loggers::getLogger(logger_name)->log(spdlevel::debug, fmt, std::forward<Args>(args)...);
    }

    /// @brief 创建一个 Info 等级的日志
    /// @param logger_name 要使用的 Logger 的名称
    /// @param fmt 要格式化的字符串
    /// @param ...args 向字符串中填充的内容，以字符串中的 {} 为标志
    template <typename... Args>
    inline void Info(const std::string &logger_name, fmt::format_string<Args...> fmt, Args &&...args)
    {
        Loggers::getLogger(logger_name)->log(spdlevel::info, fmt, std::forward<Args>(args)...);
    }

    /// @brief 创建一个 Warn 等级的日志
    /// @param logger_name 要使用的 Logger 的名称
    /// @param fmt 要格式化的字符串
    /// @param ...args 向字符串中填充的内容，以字符串中的 {} 为标志
    template <typename... Args>
    inline void Warn(const std::string &logger_name, fmt::format_string<Args...> fmt, Args &&...args)
    {
        Loggers::getLogger(logger_name)->log(spdlevel::warn, fmt, std::forward<Args>(args)...);
    }

    /// @brief 创建一个 Error 等级的日志
    /// @param logger_name 要使用的 Logger 的名称
    /// @param fmt 要格式化的字符串
    /// @param ...args 向字符串中填充的内容，以字符串中的 {} 为标志
    template <typename... Args>
    inline void Error(const std::string &logger_name, fmt::format_string<Args...> fmt, Args &&...args)
    {
        Loggers::getLogger(logger_name)->log(spdlevel::err, fmt, std::forward<Args>(args)...);
    }

    /// @brief 创建一个 Critical 等级的日志，注意：他同时会终止程序进行
    /// @param logger_name 要使用的 Logger 的名称
    /// @param fmt 要格式化的字符串
    /// @param ...args 向字符串中填充的内容，以字符串中的 {} 为标志
    template <typename... Args>
    inline void Critical(const std::string &logger_name, fmt::format_string<Args...> fmt, Args &&...args)
    {
        Loggers::getLogger(logger_name)->log(spdlevel::critical, fmt, std::forward<Args>(args)...);
        exit(0);
    }

};

#endif