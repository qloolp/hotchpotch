#include <iostream>
#include <string>
#include <vector>
#include "trie.h"
using namespace std;

template<int capacity>
class IndexChar              //字符串类型
{
public:
	unsigned int operator[](const char ch)
	{
		return ch % capacity;           //ASII capacity=128
	}
};


template<int capacity>
class IndexInt             //整型
{
public:
	unsigned int operator[](const int n)
	{
		return n%capacity;              //[0,10) capacity = 10;
	}
};


int main()
{

	

	trie<128, char, IndexChar<128>> t;

	string str;
	string str1 = "123";
	string str2 = "1234";
	string str3 = "23";
	string str4 = "345";
	string str5 = "abc";
	string str6 = "efg";
	string str7 = "ab";
	string str8 = "a";
	

	t.insert(str1.begin(), str1.end());
	t.insert(str2.begin(), str2.end());
	t.insert(str3.begin(), str3.end());
	t.insert(str4.begin(), str4.end());
	t.insert(str5.begin(), str5.end());
	t.insert(str6.begin(), str6.end());
	t.insert(str7.begin(), str7.end());
	t.insert(str8.begin(), str8.end());

	cout << "size:" << t.size() << endl;

	t.erase(str4.begin(), str4.end());
	t.erase(str3.begin(), str3.end());
	t.insert(str7.begin(), str7.end());

	cout << "size:" << t.size() << endl;

//	t.clear();

//	cout << "size:" << t.size() << endl;
	
	while (cin >> str)
	{
		if (t.contains(str.begin(), str.end()))
		{
			cout << "contains" << endl;
		}
		else
			cout << "not contains" << endl;
	}

/*
    typedef vector<int> vec;
	trie<10, int, IndexInt<10>> t;
	vec v1 = { 1,2,3 };
	vec v2 = { 2,3 };
	vec v3 = { 0,1,4 };
	vec v4 = { 0 };
	t.insert(v1.begin(), v1.end());
	t.insert(v2.begin(), v2.end());
	t.insert(v3.begin(), v3.end());
*/

	std::cin.get();
}