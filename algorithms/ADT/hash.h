#pragma once
/*
链接法解决冲突

关键字为int类型

*/
#include <ctime>
#include <cstdio>

namespace li {

	template<typename VALUE>
	struct node
	{
		bool filled;
		int key;
		VALUE value;
		node* next;
		node() :filled(false), next(nullptr) {}
		node(node& n)
		{
			filled = n.filled;
			key = n.key;
			value = n.value;
			next = n.next;
		}
		node(int key, VALUE val, node* p) :filled(true), key(key), vlaue(val), next(p) {}
		node(int key, VALUE val) :filled(true), key(key), value(val), next(nullptr) {}
	};


	template<typename VALUE>
	class hash
	{
	private:
		node<VALUE>* entry;
		float factor;
		int storage;
		int count;
		static const int prime = 64709;
		int index(int x);
		void expansion();
	public:
		hash();
		~hash();
		void insert(node<VALUE>& n);
		void insert(int key, VALUE val);
		const node<VALUE> find(int key);
		int capacity() { return storage; }
		int size() { return count; }
	};

	template<typename VALUE>
	inline hash<VALUE>::hash() :entry(new node<VALUE>[16]), factor(0), storage(16), count(0)
	{
		//初始值设定为16
	}

	template<typename VALUE>
	inline int hash<VALUE>::index(int x)
	{
		//vs2015中为算术右移
		x += ~(x << 9);
		x ^= (x >> 14);
		x += (x << 4);
		x ^= (x >> 10);
		return x & (storage - 1);
	}

	template<typename VALUE>
	inline void hash<VALUE>::expansion()
	{
		node<VALUE>* temp = new node<VALUE>[storage * 2];
		for (int i = 0; i < storage; i++)
		{

			node<VALUE>* p = &entry[i];
			if (p->filled == true)
			{
				while (p != nullptr)
				{

					insert(*p);
					p = p->next;
				}
			}
		}
		storage *= 2;
	}



	template<typename VALUE>
	inline hash<VALUE>::~hash()
	{
		if (entry != nullptr)
			delete[] entry;
	}

	template<typename VALUE>
	inline void hash<VALUE>::insert(node<VALUE> & n)
	{
		if (count / storage >= 0.75)
			expansion();
		int Index = index(n.key);
		if (entry[Index].filled == false)
		{
			entry[Index] = n;
			count++;
		}
		else
		{
			node<VALUE>* p = &entry[Index];
			while (p->next != nullptr)
			{
				if (p->key == n.key)       //已存在相同key值得数据，仅改变value即可
				{
					p->value = n.value;
					count++;
					return;
				}
				else
					p = p->next;
			}
			p->next = new node<VALUE>(n);
		}

	}

	template<typename VALUE>
	inline void hash<VALUE>::insert(int key, VALUE val)
	{
		put(node(key, val));
	}

	template<typename VALUE>
	inline const node<VALUE> hash<VALUE>::find(int key)
	{
		int Index = index(key);
		if (entry[Index].filled == false)  //没有数据
			return node<VALUE>();
		node<VALUE>* p = &entry[Index];
		while (p != nullptr)
		{
			if (p->key == key)
				return *p;
			else
				p = p->next;
		}
		return node<VALUE>();
	}



}