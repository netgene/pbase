#include <iostream>
#include <mutex>

#ifndef PBASE_SINGLETON_TS_H
#define PBASE_SINGLETON_TS_H

using namespace std;
namespace pbase {

template<class T>
class SingletonTs
{  
public:  
    static T* GetInstance() 
    {
        if(p == NULL) {
            std::lock_guard<std::mutex> guard(m_mutex);
            if(p == NULL) {
                p = new T();
            }
        }
	//std::call_once(coflag, [](){p = new T();});
        return p;
    }
  
protected:
    SingletonTs();
    SingletonTs(const T& other);
    SingletonTs & operator=(const T& other);
    static T* p;
    //static std::once_flag coflag;
    static std::mutex m_mutex;
};

template<class T>
SingletonTs<T>::SingletonTs()
{
}

template<class T>
T* SingletonTs<T>::p = NULL;

template<class T>
std::mutex SingletonTs<T>::m_mutex;
/*
template<class T>
std::once_flag SingletonTs<T>::coflag;
*/

} 

#endif
