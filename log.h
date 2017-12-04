#include "singleton.h"
#include <iostream>
#include <string>

using namespace std;

namespace pbase {
namespace logger {

class Logger : public Singleton<Logger> {
public:
	Logger();

	template<typename T>
	void print_args(T t);

	template<typename T, typename... Rest>
	void print_args(T t, Rest... rest);

	template<typename T, typename... Rest>
	void logprint(T t, Rest... rest);
	
private:
	string filename;
};

} //namespace logger
} //namespace pbase
