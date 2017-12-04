#include "log.h"
#include <iostream>

using namespace pbase;

int main()
{
	char a[10] = "ttest";
	int i = 1;
	//logger::Logger::GetInstance().logprint(i);
	//logger::Logger::GetInstance().logprint("log2:", 456);
	LOG_INFO("123:%d", 123);
	LOG_INFO("123:%d", 123);
	LOG_INFO("123:%d", 123);
	LOG_INFO("123:%d", 123);
	return 0;
}