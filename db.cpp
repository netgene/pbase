#include "db.h"

namespace gomsg {

void MysqlConn::Connect()   
{  
    driver = sql::mysql::get_mysql_driver_instance();  
    // 建立链接  
    con = driver->connect("tcp://127.0.0.1:3306", "root", "0709");  
    state = con->createStatement();  
    state->execute("use shudang");
}

void MysqlConn::Query()
{
    // 查询  
    result = state->executeQuery("select * from user");  
    // 输出查询  
    while(result->next())  
    {  
        int id = result->getInt("ID");  
        string name = result->getString("name");  
        //cout << id << " : " << name << endl;  
        LOG_INFO("id:%d name:%s\n", id, name);
    }  
}

void MysqlConn::DisConnect()
{
    delete state;  
    delete con;
}

}//namespace gomsg end