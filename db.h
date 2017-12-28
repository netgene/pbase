#ifndef GOMSG_DB_H
#define GOMSG_DB_H

#include <mysql_connection.h>  
#include <mysql_driver.h>  
#include <statement.h> 
#include "log.h"

using namespace sql;  
using namespace std;  
using namespace pbase;

namespace gomsg {

class MysqlConn {
public:
    void Connect();
    void DisConnect();
    void Query();

private:
    mysql::MySQL_Driver *driver;  
    Connection *con; 
    Statement *state; 
    ResultSet *result;
};

}//namespace gomsg end

#endif