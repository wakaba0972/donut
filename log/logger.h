#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <fstream>
#include <memory>

namespace ASCII3D {
    
    enum class LogLevel {
        DEBUG = 0,
        INFO = 1,
        WARNING = 2,
        ERROR = 3
    };
    
    class Logger {
    private:
        std::unique_ptr<std::ofstream> logFile;
        LogLevel currentLevel;
        std::string formatMessage(LogLevel level, const std::string& message);
        std::string levelToString(LogLevel level);
        std::string getCurrentTime();
        
    public:
        Logger(const std::string& filename = "log/app.log", LogLevel level = LogLevel::INFO);
        ~Logger();
        
        void setLevel(LogLevel level);
        void log(LogLevel level, const std::string& message);
        void debug(const std::string& message);
        void info(const std::string& message);
        void warning(const std::string& message);
        void error(const std::string& message);
        
        static Logger& getInstance();
    };
    
    // Convenience macros
    #define LOG_DEBUG(msg) ASCII3D::Logger::getInstance().debug(msg)
    #define LOG_INFO(msg) ASCII3D::Logger::getInstance().info(msg)
    #define LOG_WARNING(msg) ASCII3D::Logger::getInstance().warning(msg)
    #define LOG_ERROR(msg) ASCII3D::Logger::getInstance().error(msg)
}

#endif