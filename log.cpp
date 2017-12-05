#include "log.h"

namespace pbase {
namespace logger {

Logger::Logger() 
{
    file_log_level = LOG_LEVEL_DEBUG;
    terminal_log_level = LOG_LEVEL_ERROR;
}

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

void Logger::init(int file_level, int terminal_level, const std::string &app, const std::string &path)
{
    //m_level = file_level;
    struct timeval tv;
    gettimeofday(&tv, NULL);
    struct tm tm;
    localtime_r(&tv.tv_sec, &tm);
    m_year.store(1900 + tm.tm_year, std::memory_order_relaxed);
    m_month.store(1 + tm.tm_mon, std::memory_order_relaxed); 
    m_day.store(tm.tm_mday, std::memory_order_relaxed);
    system((std::string("mkdir -p ") + path).c_str());
    
    if(path[path.length() - 1] != '/')
    {
        const_cast<std::string&>(path).append("/");
    }
    
    m_file_name = path + app;
    m_file_full_name = path + app + ".log";
    m_file = fopen(m_file_full_name.c_str(), "rb");
    
    if(m_file != NULL)
    {
        int32_t fd = fileno(m_file);
        struct stat st;
        fstat(fd, &st);
        struct tm tm_1;
        localtime_r(&st.st_mtim.tv_sec, &tm_1);
        uint32_t year = 1900 + tm_1.tm_year;
        uint32_t month = 1 + tm_1.tm_mon;
        uint32_t day = tm_1.tm_mday;
        
        if(year != m_year.load(std::memory_order_relaxed) || month != m_month.load(std::memory_order_relaxed) || day != m_day.load(std::memory_order_relaxed))
        {
            char file_name[64];
            sprintf(file_name, "%s_%d-%02d-%02d.log", m_file_name.c_str(), year, month, day);
            fclose(m_file);
            std::rename(m_file_full_name.c_str(), file_name);
        }
        else
        {
            fclose(m_file);
        }
    }
    
    m_file = fopen(m_file_full_name.c_str(), "ab");
    setvbuf(m_file, NULL, _IOLBF, 1024);
}

void Logger::log(uint level, const char *format, ...)
{
    std::lock_guard<std::mutex> guard(m_mutex);
	char str_body[256];
    char str_head[50];

    va_list ap;

    int num_head = snprintf(str_head, 50, "[%s][%s][%ld]", s_level_str[level-1], get_time_str().c_str(), pthread_self());
    va_start(ap, format);
    vsnprintf(str_body, 256, format, ap);

    if(level <= file_log_level) {
        fprintf(m_file, "%s ", str_head);
        va_start(ap, format);
        vfprintf(m_file, format, ap);
    }    
    if(level <= terminal_log_level) {
        printf("%s %s", str_head, str_body);
    }
    va_end(ap);
}

string Logger::get_time_str()
{
	time_t now = {0};
	struct tm *ptime = NULL;
    time(&now);
    ptime = localtime(&now);

    long microsec = 0;
    struct timeval tv = {0};
    gettimeofday(&tv, 0);
    microsec = tv.tv_usec;

    char m_time_str[50] = {0};

    sprintf(m_time_str, "%04d%02d%02d %02d:%02d:%02d.%06ld",
            (1900+ptime->tm_year), (1+ptime->tm_mon), ptime->tm_mday,
            ptime->tm_hour, ptime->tm_min, ptime->tm_sec, microsec);
    string s(m_time_str);
    return s;
}

} //namespace logger
} //namespace pbase