#include "log.h"
#include "db.h"
#include <iostream>
#include <thread>

using namespace pbase;
using namespace gomsg;

int main(int argc, char**argv)
{
	char a[10] = "ttest";
	int i = 1;

	pbase::logger::Logger::GetInstance().init(pbase::logger::LOG_LEVEL_DEBUG, pbase::logger::LOG_LEVEL_ERROR, 2, "testpb", "./log/");

	gomsg::ysqlConn msql;
	msql.Connect();
	msql.Query();
	msql.DisConnect();

	return 0;
}
