#pragma once
//            节点
template<int capacity, class T>                        //capacity 对象元素数, T欲保存数据类型
class node
{
public:
	bool leaf;                                     //叶子节点
	int count;                                     //通过的数目
	node* child[capacity] = {nullptr};                 //儿子节点
	T data;
	node() :leaf(false), count(0) {};
	node(const T& t, bool leaf = false) :leaf(leaf), count(1),data(t) {};
	~node() { }
};




template<int capacity, class T, class K>                       //capacity 对象元素数， K仿函数：将对象映射至唯一的unsigned范围为[0,capacity)
class trie
{
	typedef node<capacity, T>* pointer;
private:
	node<capacity,T> root;
	K index;
	unsigned int data_size;                         //已保存串数目

	template<class Iterator>
	bool erase_node(Iterator first, Iterator last, pointer p);
	void erase_node(pointer p);
public:
	trie();

	template<class Iterator>
	void insert(Iterator first, Iterator last);
	
	template<class Iterator>
	bool contains(Iterator first, Iterator last);

	template<class Iterator>
	void erase(Iterator first, Iterator last);

	unsigned int size() { return data_size; }

	void clear();
};

template<int capacity, class T, class K>
inline trie<capacity, T, K>::trie():data_size(0)                             //构造函数
{
}

template<int capacity, class T, class K>
inline void trie<capacity, T, K>::erase_node(pointer p)          //递归删除节点
{
	if (p == nullptr)
		return;

	for each (pointer& var in p->child)
	{
		if (var != nullptr)
		{
			erase_node(var);
			delete var;
			var = nullptr;
		}
	}

}

template<int capacity, class T, class K>
inline void trie<capacity, T, K>::clear()                    //删除根节点外所有节点
{
	data_size = 0;
	erase_node(&root);
}




template<int capacity, class T, class K>
template<class Iterator>
inline void trie<capacity, T, K>::insert(Iterator first, Iterator last)                  //插入串区间[first,last)
{
	pointer curr = &root;
	while (first != last)
	{
		if (curr->child[index[*first]] == nullptr)   // 不存在       *begin 欲插入对象， index[*begin] 对象的唯一映射，此处作为索引。
		{
			curr->child[index[*first]] = new node<capacity,T>(*first);
		}
		else
			curr->count++;
		curr = curr->child[index[*first]];              //转入下一个
		first++;
	}
	if (curr->leaf == false)
	{
		curr->leaf = true;
		data_size++;
	}                   //若插入已存在的串则不增加
}



template<int capacity, class T, class K>
template<class Iterator>
inline bool trie<capacity, T, K>::contains(Iterator first, Iterator last)               //查询是否包含串[frist,last)
{
	pointer curr = &root;
	while (first != last)
	{
		if (curr->child[index[*first]] == nullptr)             //不可到达last
		{
			return false;
		}
		curr = curr->child[index[*first]];           //转入下一个
		first++;
	}
	return curr->leaf;             //若为叶子节点则包含，否则为某一串的前缀
}


template<int capacity, class T, class K>
template<class Iterator>
inline void trie<capacity, T, K>::erase(Iterator first, Iterator last)                 //删除串[first,last)若存在
{  
	pointer curr = &root;
	if (curr->child[index[*first]] != nullptr)
	{
		if (erase_node(first, last, curr->child[index[*first]]) == true)
			delete curr->child[index[*first]];
	}
}



template<int capacity, class T, class K>
template<class Iterator>
inline bool trie<capacity, T, K>::erase_node(Iterator first, Iterator last, pointer p)        //返回值：是否可以删除本节点
{
	if (first + 1 == last)            //到达串尾
	{
		if (p->leaf == true)
			data_size--;


		if (p->count != 0)            //有后继节点，不能删除
		{
			p->leaf = false;         
			return false;
		}
		else if (p->leaf)             //为叶子节点，无后继节点，可删除
		{
			return true;
		}
	}

	if (p->child[index[*(first+1)]] != nullptr)      //可达下一步
	{
		if (erase_node(first + 1, last, p->child[index[*(first+1)]]) == true)
		{
			delete p->child[index[*(first+1)]];
			if (p->count == 1)                         //可删除本节点
				return true;
		}
	}
	return false;
}
