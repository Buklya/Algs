#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <string>
#include <bitset>
#include <cstdio>
#include <limits>
#include <vector>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <unordered_map>

using namespace std;

long int sum(const vector<long int>& v)
{
	long int sum = 0;
	for (size_t i = 0; i < v.size(); i++)
	{
		sum += v[i];
	}
	return sum;
}

long int min(const vector<long int>& v)
{
	if (v.empty()) { return -1; }
	long int min = v[0];
	for (size_t i = 1; i < v.size(); i++)
	{
		if (min > v[i])
			min = v[i];
	}
	return min;
}

long int max(const vector<long int>& v)
{
	if (v.empty()) { return -1; }
	long int max = v[0];
	for (size_t i = 1; i < v.size(); i++)
	{
		if (max < v[i])
			max = v[i];
	}
	return max;
}

vector<long int> calculate_sum(const vector<long int>& v, long int sum)
{
	vector<long int> calculate_sum;
	for (size_t i = 0; i < v.size(); i++)
	{
		calculate_sum.push_back(sum - v[i]);
	}
	return calculate_sum;
}

void test(const vector<long int>& v)
{

}
/*
int main() {
	long int a;
	long int b;
	long int c;
	long int d;
	long int e;
	cin >> a >> b >> c >> d >> e;
	vector<long int> v;
	v.push_back(a);
	v.push_back(b);
	v.push_back(c);
	v.push_back(d);
	v.push_back(e);
	vector<long int> sums = calculate_sum(v, sum(v));
	cout << min(sums) << " " << max(sums);
	return 0;
}*/