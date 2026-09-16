#include "engine/core/logger.h"
#include <cstdarg>
#include <cstdio>
#include <ctime>

namespace engine {

Logger& Logger::instance() {
    static Logger s_instance;
    return s_instance;
}

void Logger::set_level(LogLevel level) {
    m_level = level;
}

void Logger::set_output_file(const std::string& path) {
    m_file.open(path, std::ios::out | std::ios::trunc);
}

void Logger::log(LogLevel level, const char* file, int line, const char* fmt, ...) {
    if (level < m_level) return;

    const char* level_str[] = {"TRACE", "DEBUG", "INFO", "WARN", "ERROR", "FATAL"};
    int idx = static_cast<int>(level);

    time_t now = time(nullptr);
    struct tm* t = localtime(&now);

    char buffer[4096];
    va_list args;
    va_start(args, fmt);
    vsnprintf(buffer, sizeof(buffer), fmt, args);
    va_end(args);

    char output[4200];
    snprintf(output, sizeof(output), "[%02d:%02d:%02d] [%s] %s:%d: %s",
             t->tm_hour, t->tm_min, t->tm_sec, level_str[idx], file, line, buffer);

    if (level >= LogLevel::Warn) {
        fprintf(stderr, "%s\n", output);
    } else {
        printf("%s\n", output);
    }

    if (m_file.is_open()) {
        m_file << output << "\n";
        m_file.flush();
    }
}

} // namespace engine
