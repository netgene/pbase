#include "log.h"
#include <iostream>

using namespace pbase;

int main()
{
	char a[10] = "ttest";
	int i = 1;
	//logger::Logger::GetInstance().logprint(i);
	//logger::Logger::GetInstance().logprint("log2:", 456);
	LOG_INFO("info:%d", 123);
	LOG_WARN("warn:%d", 123);
	LOG_ERROR("error:%d", 123);
	LOG_DEBUG("debug:%d", 123);
	return 0;
}