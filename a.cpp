#include <iostream>

using namespace std;

class Singleton  
{  
 public:  
    static Singleton& GetInstance()  
    {  
        static Singleton instance_;                   
        return instance_;  
    }  
  
    ~Singleton()  
    {  
        cout << "~Singleton"<<endl;  
    }  
    
private:  
  
    Singleton()  
    {  
        cout << "Singleton "<<endl;  
    }  
    Singleton(Singleton const &other);  
    Singleton & operator=(const Singleton &other);  
};  

int main()  
{  
    Singleton &s1 = Singleton::GetInstance();  
    Singleton &s2 = Singleton::GetInstance(); //s1与s2是同一对象的引用  
  
    return 0;  
}  