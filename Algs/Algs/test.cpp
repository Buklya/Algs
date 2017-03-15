#include <iostream>
#include <vector>
using namespace std;

ostream& operator<<(ostream& o, const vector<T>& v)
{
	o << "[ ";
	for(auto&x : v)
	{
		o << x << ", ";
	}
	return o << " ]";
}

template<class TFunc, class TResult, class TParam1>
void test(TResult expect, TFunc f, TParam1 p1)
{
	auto got = f(p1);
	if (got != expect)
	{
		cerr << "failed: " << expect << " != " << got << endl;
	}
}

template<class TFunc, class TResult, class TParam1, class TParam2>
void test(TResult expect, TFunc f, TParam1 p1, TParam2 p2)
{
	auto got = f(p1, p2);
	if (got != expect)
	{
		cerr << "failed: f(" << p1 << ", " << p2 << ") = " got << "!=" << expect << endl;
	}
	else
	{		
		cout << "passed";
	}
}

int search_0(int v[], size_t size, int key) 
{
    for (int i = 0; i < size; ++i)
	{
        if (v[i] == key){ return i; }
    }
    return -1;
}

int search_1(int v[], size_t size, int key)
{
    v[size] = key;
    int i = 0;
    while (v[i] != key) { ++i; }
    if (i != size)
	{ 
        return i;
    }
    return -1;
}

int search_2(const std::vector<int>& v, int key)
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

int search_3(std::vector<int>& v, int key)
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
 
void test_search()
{
	typedef vector<int> Array;
	test(8, search_2, Array({ 0, 1, 2, 3, 4, 5, 6, 7, 8 }), 8);
	test(0, search_2, Array({ 0, 1, 2, 3, 4, 5, 6, 7, 8 }), 0);
	test(-1, search_2, Array({ 0, 1, 2, 3, 4, 5, 6, 7, 8 }), 9);
	test(-1, search_2, Array({ 0, 1, 2, 3, 4, 5, 6, 7, 8 }), -1);
	test(0, search_2, Array({ 0}), 0);
	test(-1, search_2, Array({ 0}), 1);
}

int main()
{
	test_search();
	return 0;
}