#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <memory>
#include <sstream>
#include <iomanip>
#include "algorithm"

// 定义日志级别枚举
enum class LogLevel {
		Warning,
		Error,
		Success
};


class Logger {
public:
		Logger(const std::string& logDirectory) {
			// 使用 std::ctime
			std::time_t now = std::time(nullptr);
			std::tm* localTime = std::localtime(&now);
			char timestamp[11]; // 用于存储格式化后的日期，格式为 "YYYY-MM-DD"
			std::strftime(timestamp, sizeof(timestamp), "%Y-%m-%d", localTime);
			std::string timestampStr(timestamp);

			timestampStr.erase(std::remove(timestampStr.begin(), timestampStr.end(), '\n'), timestampStr.end());
			for (char& c : timestampStr) {
				if (!std::isalnum(c)) {
					c = '_';
				}
			}
			logFilePath = logDirectory + "/log_" + timestampStr + ".txt";

			logFile.open(logFilePath, std::ios::app);
			if (!logFile.is_open()) {
				std::cerr << "Failed to open log file: " << logFilePath << std::endl;
			}
		}

		~Logger() {
			if (logFile.is_open()) {
				logFile.close();
			}
		}

		void log(LogLevel level, const std::string& message) {
			if (logFile.is_open()) {
				std::time_t now = std::time(nullptr);
				std::tm* localTime = std::localtime(&now);
				std::ostringstream oss;
				oss << std::put_time(localTime, "%Y-%m-%d %H:%M:%S");
				std::string timestampStr = oss.str();
				std::string levelStr;
				switch (level) {
					case LogLevel::Warning:
						levelStr = "Warning";
						break;
					case LogLevel::Error:
						levelStr = "Error";
						break;
					case LogLevel::Success:
						levelStr = "Success";
						break;
				}
				std::string logMessage = "[" + timestampStr + "] [" + levelStr + "] " + message;
				logFile << logMessage << std::endl;
				logFile.flush();
				std::cout << logMessage << std::endl;
			}
		}

private:
		std::string logFilePath;
		std::ofstream logFile;
};

int main() {
	std::string logDirectory = "/home/liwei/books/oj/suanfa_1000/duckdb/logs";
	// 使用 std::make_shared 创建 Logger 的共享指针
	std::shared_ptr<Logger> logger = std::make_shared<Logger>(logDirectory);
	if (logger) {
		// 记录不同级别的日志信息
		logger->log(LogLevel::Warning, "This is a warning log message.");
		logger->log(LogLevel::Error, "This is an error log message.");
		logger->log(LogLevel::Success, "This is a success log message.");
	}

	return 0;
}