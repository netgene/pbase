#include <iostream>

using namespace std;
namespace pbase {

template<typename T>
class Singleton  
{  
public:  
 	// static 静态函数 全局访问接口
    static T& GetInstance()
	{  
    	static T instance_; //static 只构造一次, 生命周期同类
    	return instance_;  
	}
  
protected:
	//私有化构造函数、拷贝构造函数和赋值运算符
    Singleton();

    Singleton(const T& other);

    Singleton & operator=(const T& other);  
};

template<typename T>
Singleton<T>::Singleton()
{
	//cout << __FUNCTION__ << endl;
}

} //namespace pbase