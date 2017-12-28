#include <iostream>
#include <pthread.h> 

#ifndef PBASE_SINGLETON_TS_H
#define PBASE_SINGLETON_TS_H

using namespace std;
namespace pbase {

template<typename T>
class SingletonTs
{  
public:  
    static T* GetInstance();
  
protected:
    SingletonTs();
    SingletonTs(const T& other);
    SingletonTs & operator=(const T& other);
    static std::mutex m_mutex;
    static T* p;
};

template<typename T>
T* SingletonTs<T>::GetInstance()
{
    if(p == NULL) {
        std::lock_guard<std::mutex> guard(m_mutex);
        if(p == NULL) {
            p = new SingletonTs();
        }
    }
}


} //namespace pbase

#endif