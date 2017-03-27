#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <cassert>
using namespace std;

namespace my_min
{
	template<class TIter>
	TIter min_element(TIter b, TIter e)
	{
		auto result = b;
		while (b < e)
		{
			// [ ) = [processed)[current)[unprocessed)
			// assert(tmp is min from [processed))
			if (*b < *result)
			{
				result = b
			}
			++b;
			// assert(tmp is min from [processed))
		}
		return result;
	}
}//my_min

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
/*template<class TFunc, class TResult, class TParam1, class TParam2, class TParam3, class TParam4>
void test(TResult expect, TFunc f, TParam1 p1, TParam2 p2, TParam3 p3, TParam4 p4)
{
	auto got = f(p1, p2, p3, p4);
	if (got != expect)
	{
		cerr << "failed: f(" << p1 << ", " << p4 << ") = " << got << "!=" << expect << endl;
	}
	else
	{
		cout << "passed" << endl;
	}
}
*/
int search_0(int v[], size_t size, int key)
{
	for (size_t i = 0; i < size; ++i)
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

int search_2(const vector<int>& v, int key)
{
	for (size_t i = 0; i < v.size(); ++i)
	{
		if (v[i] == key)
		{
			return i;
		}
	}
	return -1;
}

int search_3(vector<int>& v, int key)
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

int binary_search_helper
(
	const  vector<int>& v,
	size_t begin,
	size_t end,
	int key,
	size_t depth = 0
)
{
	assert(depth < 100); //ограничиваем глубину рекурсии
	assert(std::is_sorted(v.begin(), v.end()));
	if (begin < end)
	{
		// [b, e) = [b, m) U [m, e)
		size_t m = (begin + end) / 2;
		assert((m - begin) + (end - m) == (end - begin));
		if (key < v[m])
		{
			return binary_search_helper(v, begin, m, key, depth+1);
		}
		else if (v[m] < key)
		{
			return binary_search_helper(v, m, end, key, depth + 1);
		}
		else {
			return m;
		}
	}
	return -1;
}

int binary_search
(
	const  vector<int>& v,	
	int key
)
{
	assert(std::is_sorted(v.begin(), v.end()));

	size_t b = 0;
	size_t e = v.size();	
	while(b < e)	
	{
		// [b, e) = [b, m) U [m, e)
		size_t m = b + (e - b) / 2;
		//size_t m = b + (e - b) >> 1; // >>K ~ /2 в степени K
		if (key < v[m])
		{
			e = m;
		}
		else if (v[m] < key)
		{
			b = m + 1;
		}
		else
		{
			return m;
		}
	}
	return -1;
}

template<class T, class Tkey>
T my_lower_bound(T b, T e, const Tkey& key)
{	
	while (b < e)
	{
		T m = b + (e - b) / 2;
		if (*m < key)
			b = m + 1;
		else
			e = m;
	}
	return b;
}

template<class T, class Tkey>
T my_upper_bound(T b, T e, const Tkey& key)
{
	while (b < e)
	{
		T m = b + (e - b) / 2;
		if (key < *m) {
			e = m;
		}			
		else {
			b = m + 1;
		}			
	}
	return b;
}

template<class T, class Tkey>
T my_bin_search(T b, T e, const Tkey& key)
{
	assert(std::is_sorted(b, e));
	T result = my_lower_bound(b, e, key);
	if (result == e)
		return e;
	if (!(key < *result))
		return result;
	return e;
}

void test_search()
{
	typedef vector<int> Array;	
	auto search = [](const vector<int>& v, int key)
	{
		auto r = my_bin_search(v.begin(), v.end(), key);
		return r != v.end() ? r - v.begin() : -1;
	};
	auto key = 8;
	//key not exists in array	
	test(-1, search, Array(), key);//degerate	
	test(-1, search, Array({ key - 1}), key);//trivial	
	test(-1, search, Array({ key + 1 }), key);//trivial
	test(-1, search, Array({ key - 1, key + 1 }), key);//trivial-2	
	test(-1, search, Array({ 0, 1, 2, 3, 4, 5, 6, 7 }), key); //general
	test(-1, search, Array({ 9, 10, 11 }), key); //general
	test(-1, search, Array({ 1, 3, 5, 10 }), key); //general
	//key exists
	//degerate	//non appliable		
	test(0, search, Array({ key }), key);//trivial
	test(0, search, Array({ key, key+1 }), key); //trivial-2
	test(1, search, Array({ key - 1, key }), key); //trivial-2
	test(8, search, Array({ 0, 1, 2, 3, 4, 5, 6, 7, key }), key); //general
	test(0, search, Array({ key, 9, 10, 11 }), key); //general
	test(3, search, Array({ 1, 3, 5, key, 10 }), key); //general
	//test(0, search, Array({ key, 3, key, 5, 10 }), key); //general
	//test(2, search, Array({ 1, 3, key, 10, key }), key); //general	
}
/*
void test_binary_search()
{
	typedef vector<int> Array;
	auto search = binary_search_helper;
	auto key = 8;
	auto begin = 0;
	//key not exists in array	
	test(-1, search, Array(), begin, 0, key);//degerate	
	test(-1, search, Array({ key - 1 }), begin, 1, key);//trivial	
	test(-1, search, Array({ key - 1, key + 1 }), begin, 2, key);//trivial-2	
	test(-1, search, Array({ 0, 1, 2, 3, 4, 5, 6, 7 }), begin, 8, key); //general
	test(-1, search, Array({ 9, 10, 11 }), begin, 3, key); //general
	test(-1, search, Array({ 1, 3, 10, 5 }), begin, 4, key); //general
	//key exists
	//degerate	//non appliable		
	test(0, search, Array({ key }), begin, 1, key);//trivial
	test(0, search, Array({ key, key + 1 }), begin, 2, key); //trivial-2
	test(0, search, Array({ key, key - 1 }), begin, 2, key); //trivial-2
	test(8, search, Array({ 0, 1, 2, 3, 4, 5, 6, 7, key }), begin, 9, key); //general
	test(0, search, Array({ key, 9, 10, 11 }), begin, 4, key); //general
	test(2, search, Array({ 1, 3, key, 10, 5 }), begin, 5, key); //general
	test(0, search, Array({ key, 3, key, 10, 5 }), begin, 5, key); //general
	test(2, search, Array({ 1, 3, key, 10, key }), begin, 5, key); //general	
}


void test_search()
{
	typedef vector<int> Array;
	auto search = min;
	auto key = 8;
	//key not exists in array	
	test(-1, search, Array(), key);//degerate	
	test(-1, search, Array({ key - 1 }), key);//trivial	
	test(-1, search, Array({ key - 1, key + 1 }), key);//trivial-2	
	test(-1, search, Array({ 0, 1, 2, 3, 4, 5, 6, 7 }), key); //general
	test(-1, search, Array({ 9, 10, 11 }), key); //general
	test(-1, search, Array({ 1, 3, 5, 10 }), key); //general
												   //key exists
												   //degerate	//non appliable		
	test(0, search, Array({ key }), key);//trivial
	test(0, search, Array({ key, key + 1 }), key); //trivial-2
	test(1, search, Array({ key - 1, key }), key); //trivial-2
	test(8, search, Array({ 0, 1, 2, 3, 4, 5, 6, 7, key }), key); //general
	test(0, search, Array({ key, 9, 10, 11 }), key); //general
	test(3, search, Array({ 1, 3, 5, key, 10 }), key); //general
													   //test(0, search, Array({ key, 3, key, 5, 10 }), key); //general
													   //test(2, search, Array({ 1, 3, key, 10, key }), key); //general	
}

*/
int main()
{
	//test_search();
	//test_binary_search();
	
	return 0;
}