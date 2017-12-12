g++ -o testpb testpb.cpp log.cpp db.cpp -I./mysqlconn/include -I./mysqlconn/include/cppconn -L./mysqlconn/lib -lmysqlcppconn-static -lpthread -ldl -std=c++11
