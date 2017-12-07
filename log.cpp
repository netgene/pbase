#include "log.h"

namespace pbase {
namespace logger {

Logger::Logger() 
{

}

/*
template<typename T>
void Logger::print_args(T t)
{	
	cout << t << endl;
}

template<typename T, typename... Rest>
void Logger::print_args(T t, Rest... rest)
{	
	cout << t ;
	print_args(rest...);
}

template<typename T, typename... Rest>
void Logger::logprint(T t, Rest... rest)
{	
	cout << __FUNCTION__ << ":" ;
	print_args(t, rest...);
}
*/

void Logger::init(int file_level, int terminal_level, int maxline, const std::string &app, const std::string &path)
{
    m_file_log_level = file_level;
    m_terminal_log_level = terminal_level;
    m_maxline = maxline;
    m_path = path;
    m_app = app;

    system((std::string("mkdir -p ") + path).c_str());
    if(path[path.length() - 1] != '/')
    {
        const_cast<std::string&>(path).append("/");
    }
    
    open();
}

void Logger::open()
{
    std::lock_guard<std::mutex> guard(m_mutex);

    struct timeval tv;
    gettimeofday(&tv, NULL);
    struct tm tm;
    localtime_r(&tv.tv_sec, &tm);

    char m_time_str[50] = {0};
    sprintf(m_time_str, "%04d%02d%02d%02d%02d%02d_%06ld",
            (1900+tm.tm_year), (1+tm.tm_mon), tm.tm_mday,
            tm.tm_hour, tm.tm_min, tm.tm_sec, static_cast<long>(tv.tv_usec));
    string time_str(m_time_str);
    m_file_name_end = m_path + m_app + "_" + to_string(getpid()) + "_" + time_str + ".log";

    m_file_name_logging = m_file_name_end + ".tmp";
    m_countline = 0;
    m_year = 1900+tm.tm_year;
    m_month = 1+tm.tm_mon;
    m_day = tm.tm_mday;

    m_file = fopen(m_file_name_logging.c_str(), "ab+");
    setvbuf(m_file, NULL, _IOLBF, 1024);
}

void Logger::log(uint level, const char *format, ...)
{
    //switch log
    if(m_countline >= m_maxline || is_log_goto_nextday()) {
        close();
        open();
    }

    std::lock_guard<std::mutex> guard(m_mutex);
	char str_body[256];
    char str_head[50];

    va_list ap;

    //writelog
    int num_head = snprintf(str_head, 50, "[%s][%s]", s_level_str[level-1], get_time_str().c_str());
    va_start(ap, format);
    vsnprintf(str_body, 256, format, ap);

    if(level <= m_file_log_level) {
        fprintf(m_file, "%s ", str_head);
        va_start(ap, format);
        vfprintf(m_file, format, ap);
    }    
    if(level <= m_terminal_log_level) {
        printf("%s %s", str_head, str_body);
    }
    va_end(ap);

    m_countline++;
}

bool Logger::is_log_goto_nextday()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    struct tm tm;
    localtime_r(&tv.tv_sec, &tm);
    uint32_t year = 1900 + tm.tm_year;
    uint32_t month = 1 +tm.tm_mon;
    uint32_t day = tm.tm_mday;
        
    if(year != m_year || month != m_month || day != m_day)
    {
        return true;
    } else {
        return false;
    }
}

string Logger::get_time_str()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    struct tm tm;
    localtime_r(&tv.tv_sec, &tm);

    char m_time_str[50] = {0};

    sprintf(m_time_str, "%04d%02d%02d %02d:%02d:%02d.%06ld",
        (1900+tm.tm_year), (1+tm.tm_mon), tm.tm_mday,
        tm.tm_hour, tm.tm_min, tm.tm_sec, static_cast<long>(tv.tv_usec));
    
    string s(m_time_str);
    return s;
}

void Logger::flush()
{
    fflush(m_file);
}

void Logger::close()
{
    std::lock_guard<std::mutex> guard(m_mutex);
    flush();
    fclose(m_file);
    std::rename(m_file_name_logging.c_str(), m_file_name_end.c_str());
}

Logger::~Logger()
{
    close();
}

} //namespace logger
} //namespace pbase