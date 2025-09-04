#include "logger.h"
#include <iostream>
#include <chrono>
#include <iomanip>
#include <sstream>

namespace ASCII3D {
    
    Logger::Logger(const std::string& filename, LogLevel level) 
        : currentLevel(level) {
        logFile = std::make_unique<std::ofstream>(filename, std::ios::app);
        if (!logFile->is_open()) {
            std::cerr << "Warning: Could not open log file " << filename << std::endl;
        }
    }
    
    Logger::~Logger() {
        if (logFile && logFile->is_open()) {
            logFile->close();
        }
    }
    
    void Logger::setLevel(LogLevel level) {
        currentLevel = level;
    }
    
    std::string Logger::getCurrentTime() {
        auto now = std::chrono::system_clock::now();
        auto time_t = std::chrono::system_clock::to_time_t(now);
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(
            now.time_since_epoch()) % 1000;
        
        std::stringstream ss;
        ss << std::put_time(std::localtime(&time_t), "%Y-%m-%d %H:%M:%S");
        ss << '.' << std::setfill('0') << std::setw(3) << ms.count();
        return ss.str();
    }
    
    std::string Logger::levelToString(LogLevel level) {
        switch(level) {
            case LogLevel::DEBUG:   return "DEBUG";
            case LogLevel::INFO:    return "INFO";
            case LogLevel::WARNING: return "WARNING";
            case LogLevel::ERROR:   return "ERROR";
            default:                return "UNKNOWN";
        }
    }
    
    std::string Logger::formatMessage(LogLevel level, const std::string& message) {
        return "[" + getCurrentTime() + "] [" + levelToString(level) + "] " + message;
    }
    
    void Logger::log(LogLevel level, const std::string& message) {
        if (level >= currentLevel) {
            std::string formattedMsg = formatMessage(level, message);
            
            // Write to console
            std::cout << formattedMsg << std::endl;
            
            // Write to file
            if (logFile && logFile->is_open()) {
                *logFile << formattedMsg << std::endl;
                logFile->flush();
            }
        }
    }
    
    void Logger::debug(const std::string& message) {
        log(LogLevel::DEBUG, message);
    }
    
    void Logger::info(const std::string& message) {
        log(LogLevel::INFO, message);
    }
    
    void Logger::warning(const std::string& message) {
        log(LogLevel::WARNING, message);
    }
    
    void Logger::error(const std::string& message) {
        log(LogLevel::ERROR, message);
    }
    
    Logger& Logger::getInstance() {
        static Logger instance;
        return instance;
    }
}