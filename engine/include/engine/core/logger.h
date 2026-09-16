#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <functional>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <cassert>
#include <cstdint>
#include <cstring>

namespace engine {

enum class LogLevel {
    Trace = 0,
    Debug,
    Info,
    Warn,
    Error,
    Fatal
};

class Logger {
public:
    static Logger& instance();

    void set_level(LogLevel level);
    void set_output_file(const std::string& path);

    void log(LogLevel level, const char* file, int line, const char* fmt, ...);

private:
    Logger() = default;
    LogLevel m_level = LogLevel::Trace;
    std::ofstream m_file;
};

} // namespace engine

#define LOG_TRACE(fmt, ...) engine::Logger::instance().log(engine::LogLevel::Trace, __FILE__, __LINE__, fmt, ##__VA_ARGS__)
#define LOG_DEBUG(fmt, ...) engine::Logger::instance().log(engine::LogLevel::Debug, __FILE__, __LINE__, fmt, ##__VA_ARGS__)
#define LOG_INFO(fmt, ...)  engine::Logger::instance().log(engine::LogLevel::Info,  __FILE__, __LINE__, fmt, ##__VA_ARGS__)
#define LOG_WARN(fmt, ...)  engine::Logger::instance().log(engine::LogLevel::Warn,  __FILE__, __LINE__, fmt, ##__VA_ARGS__)
#define LOG_ERROR(fmt, ...) engine::Logger::instance().log(engine::LogLevel::Error, __FILE__, __LINE__, fmt, ##__VA_ARGS__)
#define LOG_FATAL(fmt, ...) engine::Logger::instance().log(engine::LogLevel::Fatal, __FILE__, __LINE__, fmt, ##__VA_ARGS__)
