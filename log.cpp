#include "log.h"

namespace pbase {
namespace logger {

Logger::Logger() 
{
	//filename = "a.log";
	//LOG_INFO("log file:%s %d", filename.c_str(), 123);
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

void Logger::log(uint level, const char *format, ...)
{
	char str[1000];
	int l = snprintf(str, 1000, "[%s][%s][%ld] ", s_level_str[level-1], get_time_str().c_str(), pthread_self());
	//fprintf(str, "[%s-%d][%s]", get_time_str(true));
    va_list ap;
    va_start(ap, format);
    int n = vsnprintf(str+l, 1000, format, ap);
    printf("%s\n", str);
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