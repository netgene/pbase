#include "singleton.h"
#include <iostream>
#include <string>
#include <stdarg.h>
#include <time.h>
#include <sys/time.h>
#include <stdint.h>
#include <sys/syscall.h>
#include <pthread.h>
#include <sys/types.h> 

#include <cstdio>
#include <atomic>
#include <mutex>
#include <sys/stat.h>
#include <unistd.h>

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

static const char* s_level_str[] = {"ERRO", "WARN", "INFO", "DBUG"};

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

	void init(int file_level, int terminal_level, const std::string &app, const std::string &path);

	void log(uint level, const char *format, ...);
private:
	string get_time_str();
	
private:
	string logtime;
	int file_log_level;
	int terminal_log_level;

    //LOG_LEVEL m_level;
    std::string m_file_name;
    std::string m_file_full_name;
    FILE *m_file;
    std::atomic<uint32_t> m_year;
    std::atomic<uint32_t> m_month;
    std::atomic<uint32_t> m_day;
    std::atomic<uint32_t> m_enter_num {0};
    std::mutex m_mutex;

};

} //namespace logger
} //namespace pbase
