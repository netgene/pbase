#include <iostream>
#include <vector>

using namespace	 std;

void PrintVector(const vector<int>& v)
{
    vector<int>::const_iterator it = v.begin();
    while (it!=v.end())
    {
        cout << *it << " ";
        it++;
    }
    cout << endl;
}
void TestIterator()
{
    //迭代器失效
	vector<int> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(2);
	v.push_back(4);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);
	v.push_back(5);
	v.push_back(4);
	v.push_back(4);
	v.push_back(6);
    vector<int>::iterator it = v.begin();
    while (it != v.end())
    {
        if (*it % 2 == 0)
        {
            it = v.erase(it);
            ++it;
        }
        
    }
    PrintVector(v);
}

int main()
{
    TestIterator();
    return 0;
}
