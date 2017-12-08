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
    LOG_LEVEL_MAX       = 5,
};

static const char* s_level_str[] = {"ERRO", "WARN", "INFO", "DBUG"};

#define LOG_DEBUG(format, ...)      pbase::logger::Logger::GetInstance().log(pbase::logger::LOG_LEVEL_DEBUG, format, ## __VA_ARGS__)
#define LOG_INFO(format, ...)       pbase::logger::Logger::GetInstance().log(pbase::logger::LOG_LEVEL_INFO, format, ## __VA_ARGS__)
#define LOG_WARN(format, ...)       pbase::logger::Logger::GetInstance().log(pbase::logger::LOG_LEVEL_WARNING, format, ## __VA_ARGS__)
#define LOG_ERROR(format, ...)      pbase::logger::Logger::GetInstance().log(pbase::logger::LOG_LEVEL_ERROR, format, ## __VA_ARGS__)

class Logger : public Singleton<Logger> {
public:
	Logger();
	~ Logger();

	void init(int file_level, int terminal_level, int maxline, const std::string &app, const std::string &path);

	void log(uint level, const char *format, ...);
	void flush();
	void close();
	void open();
	bool is_log_goto_nextday();
private:
	string get_time_str();
	
private:
	int m_file_log_level;
	int m_terminal_log_level;
    std::string m_app;
    std::string m_path;	
    std::string m_file_name_end;
    std::string m_file_name_logging;
    FILE *m_file;
    int32_t m_maxline;
    int32_t m_countline;
    uint32_t m_year;
    uint32_t m_month;
    uint32_t m_day;
    std::mutex m_mutex;

};

} //namespace logger
} //namespace pbase
