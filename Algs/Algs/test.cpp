#include <iostream>
#include <vector>
using namespace std;

ostream& operator<<(ostream& o, const vector<T>& v)
{
	
	return o << " ]";
}
template<class TFunc, class TResult, class TParam1>
void test(TResult expect, TFunc f, TParam1 p1)
{
	auto got = f(p1);
	if (got != expect)
	{
		cerr << "failed: " << expect << " != " << got;
	}
}

template<class TFunc, class TResult, class TParam1, class TParam2>
void test(TResult expect, TFunc f, TParam1 p1, TParam2 p2)
{
	auto got = f(p1, p2);
	if (got != expect)
	{
		cerr << "failed: f(" << p1 << ", " << p2 << ") = " expect != got;
	}
}

int search_1(const std::vector<int>& v, int key)
{
	for(int i = 0; i < v.size(); ++i)
	{
		if (v[i] == key)
		{
			return i;
		}					
	}
	return -1;
}

int search(std::vector<int>& v, int key)
{
	v.push_back(key);
	int i = 0;
	while (v[i] != key)
	{
		++i;
	}
	v.pop_back();
	if (i != v.size())
	{
		return i;
	}	
	return -1;
}
 
void test(const std::vector<int>& v)
{
	std::cout << ((search(v, 1) == 0)    ? "passed" : "failed") << std::endl;
	std::cout << ((search(v, 0) == -1)   ? "passed" : "failed") << std::endl;
	std::cout << ((search(v, 'd') == -1) ? "passed" : "failed") << std::endl;
	std::cout << ((search(v, 2) == 1)    ? "passed" : "failed") << std::endl;
	std::cout << ((search(v, 100) == -1) ? "passed" : "failed") << std::endl;
}

void test(std::vector<int>& v)
{
	std::cout << ((search(v, 1) == 0) ? "passed" : "failed") << std::endl;
	std::cout << ((search(v, 0) == -1) ? "passed" : "failed") << std::endl;
	std::cout << ((search(v, 'd') == -1) ? "passed" : "failed") << std::endl;
	std::cout << ((search(v, 2) == 1) ? "passed" : "failed") << std::endl;
	std::cout << ((search(v, 100) == -1) ? "passed" : "failed") << std::endl;
}

void test_search()
{
	typedef vector<int> Array;
	test(8, search, Array({ 0, 1, 2, 3, 4, 5, 6, 7, 8 }), 8);
}

int main()
{
	std::vector<int> v;
	int size = 5;
	for (int i = 0; i < size; i++)
	{
		v.push_back(i+1);
	}
	test(v);
	return 0;
}