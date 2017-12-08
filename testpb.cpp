#include "log.h"
#include <iostream>
#include <thread>

using namespace pbase;

void loginfo()
{
	LOG_INFO("info:%d\n", 123);
	LOG_INFO("info:%d\n", 456);
}

void logwarn()
{
	LOG_WARN("warn:%d\n", 123);
}

void logerror()
{
	LOG_ERROR("error:%d\n", 123);
}

void logdebug()
{
	LOG_DEBUG("debug:%d\n", 123);
}

int main(int argc, char**argv)
{
	char a[10] = "ttest";
	int i = 1;

	pbase::logger::Logger::GetInstance().init(pbase::logger::LOG_LEVEL_DEBUG, pbase::logger::LOG_LEVEL_ERROR, 2, "testpb", "./log/");

	std::thread* t1 = new std::thread(loginfo);
	std::thread* t2 = new std::thread(logwarn);
	std::thread* t3 = new std::thread(logdebug);
	std::thread* t4 = new std::thread(logerror);

	t1->join();
	t2->join();
	t3->join();
	t4->join();

	delete t1;
	delete t2;
	delete t3;
	delete t4;
	return 0;
}
