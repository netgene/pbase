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
    static pthread_mutex_t mutex;
    static T* p;
};

template<typename T>
T* SingletonTs<T>::GetInstance()
{
    if(p == NULL) {
        pthread_mutex_lock(&mutex);
        if(p == NULL) {
            p = new SingletonTs();
        }
        pthread_mutex_unlock(&mutex);
    }
}


} //namespace pbase

#endif