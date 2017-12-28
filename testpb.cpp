#include "log.h"
#include "db.h"
#include <iostream>
#include <thread>
#include <csignal>

using namespace pbase;
using namespace pbase::logger;
using namespace gomsg;

static bool bexit = false;

void quit(int)
{
	LOG_INFO("SIGINT\n");
	bexit = true;
}
void flush(int)
{
	LOG_INFO("SIGUSR2\n");
	Logger::GetInstance()->flush();
}

int main(int argc, char**argv)
{
	signal(SIGUSR2, flush);
	signal(SIGINT, quit);

	Logger::GetInstance()->init(pbase::logger::LOG_LEVEL_DEBUG, pbase::logger::LOG_LEVEL_INFO, 10000, "testpb", "./log/");

	gomsg::MysqlConn msql;
	msql.Connect();
	while(!bexit) {
		msql.Query();
		sleep(60);
	}
	
	msql.DisConnect();

	return 0;
}
