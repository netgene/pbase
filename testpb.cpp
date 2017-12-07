#include "log.h"
#include <iostream>

using namespace pbase;

int main(int argc, char**argv)
{
	char a[10] = "ttest";
	int i = 1;

	pbase::logger::Logger::GetInstance().init(pbase::logger::LOG_LEVEL_DEBUG, pbase::logger::LOG_LEVEL_ERROR, 3, "testpb", "./log/");

	LOG_INFO("info:%d\n", 123);
	LOG_WARN("warn:%d\n", 123);
	LOG_ERROR("error:%d\n", 123);
	LOG_DEBUG("debug:%d\n", 123);
	return 0;
}