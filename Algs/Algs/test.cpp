#include <iostream>
#include <vector>
using namespace std;

template<class T>
ostream& operator<<(ostream& o, const vector<T>& v)
{
	o << "[ ";
	for (auto&x : v)
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
		cerr << "failed: f(" << p1 << ", " << p2 << ") = " << got << "!=" << expect << endl;
	}
	else
	{
		cout << "passed" << endl;
	}
}

int search_0(int v[], size_t size, int key)
{
	for (int i = 0; i < size; ++i)
	{
		if (v[i] == key) { return i; }
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
	for (int i = 0; i < v.size(); ++i)
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
	auto search = search_2;
	auto key = 8;
	//key not exists in array	
	test(-1, search, Array(), key);//degerate	
	test(-1, search, Array({key-1}), key);//trivial	
	test(-1, search, Array({ key - 1, key + 1 }), key);//trivial-2	
	test(-1, search_2, Array({ 0, 1, 2, 3, 4, 5, 6, 7 }), key); //general
	test(-1, search_2, Array({ 9, 10, 11 }), key); //general
	test(-1, search_2, Array({ 1, 3, 10, 5 }), key); //general
	//key exists
	//degerate	//non appliable		
	test(0, search, Array({ key }), key);//trivial
	test(0, search, Array({ key, key+1 }), key); //trivial-2
	test(0, search, Array({ key, key-1 }), key); //trivial-2
	test(8, search_2, Array({ 0, 1, 2, 3, 4, 5, 6, 7, key }), key); //general
	test(0, search_2, Array({ key, 9, 10, 11 }), key); //general
	test(2, search_2, Array({ 1, 3, key, 10, 5 }), key); //general
	test(0, search_2, Array({ key, 3, key, 10, 5 }), key); //general
	test(2, search_2, Array({ 1, 3, key, 10, key }), key); //general	
}

int main()
{
	test_search();
	return 0;
}