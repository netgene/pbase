#include "log.h"

namespace pbase {
namespace logger {

Logger::Logger() 
{
	filename = "a.log";
	logprint("log file:", filename, ":", 123);
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

} //namespace logger
} //namespace pbase