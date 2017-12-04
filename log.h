#include "singleton.h"
#include <iostream>
#include <string>
#include <stdarg.h>
#include <time.h>
#include <sys/time.h>
#include <stdint.h>

using namespace std;

namespace pbase {
namespace logger {

enum _log_level
{
    LOG_LEVEL_ERROR     = 1,  //错误
    LOG_LEVEL_WARNING   = 2,  //警告
    LOG_LEVEL_INFO      = 3,  //普通
    LOG_LEVEL_DEBUG     = 4,  //调试
    LOG_LEVEL_MAX
};

static const char* s_level_str[] = {"ERROR", "WARNING", "INFO", "DEBUG"};

#define LOG_DEBUG(format, ...)      pbase::logger::Logger::GetInstance().log(pbase::logger::LOG_LEVEL_DEBUG, format, ## __VA_ARGS__)
#define LOG_INFO(format, ...)       pbase::logger::Logger::GetInstance().log(pbase::logger::LOG_LEVEL_INFO, format, ## __VA_ARGS__)
#define LOG_WARN(format, ...)       pbase::logger::Logger::GetInstance().log(pbase::logger::LOG_LEVEL_WARNING, format, ## __VA_ARGS__)
#define LOG_ERROR(format, ...)      pbase::logger::Logger::GetInstance().log(pbase::logger::LOG_LEVEL_ERROR, format, ## __VA_ARGS__)

class Logger : public Singleton<Logger> {
public:
	Logger();

	template<typename T>
	void print_args(T t);

	template<typename T, typename... Rest>
	void print_args(T t, Rest... rest);

	template<typename T, typename... Rest>
	void logprint(T t, Rest... rest);

	void log(uint level, const char *format, ...);
private:
	string get_time_str();
	
private:
	string filename;
	string logtime;
};

} //namespace logger
} //namespace pbase
