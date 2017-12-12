//#include "stdafx.h"  
#include <mysql_connection.h>  
#include <mysql_driver.h>  
#include <statement.h>  
using namespace sql;  
using namespace std;  
void RunConnectMySQL()   
{  
    mysql::MySQL_Driver *driver;  
    Connection *con;  
    Statement *state;  
    ResultSet *result;  
    // 初始化驱动  
    driver = sql::mysql::get_mysql_driver_instance();  
    // 建立链接  
    con = driver->connect("tcp://127.0.0.1:3306", "root", "0709");  
    state = con->createStatement();  
    state->execute("use shudang");  
    // 查询  
    result = state->executeQuery("select * from user");  
    // 输出查询  
    while(result->next())  
    {  
        int id = result->getInt("ID");  
        string name = result->getString("name");  
        cout << id << " : " << name << endl;  
    }  
    delete state;  
    delete con;  
}  
int main()  
{  
    RunConnectMySQL();    
    return 0;  
}  