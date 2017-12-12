#include "log.h"
#include "db.h"
#include <iostream>
#include <thread>

using namespace pbase;

int main(int argc, char**argv)
{
	char a[10] = "ttest";
	int i = 1;

	pbase::logger::Logger::GetInstance().init(pbase::logger::LOG_LEVEL_DEBUG, pbase::logger::LOG_LEVEL_ERROR, 2, "testpb", "./log/");

	MysqlConn msql;
	msql.Connect();
	msql.Query();
	msql.DisConnect();

	return 0;
}
