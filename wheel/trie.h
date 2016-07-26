#pragma once
//            �ڵ�
template<int capacity, class T>                        //capacity ����Ԫ����, T��������������
class node
{
public:
	bool leaf;                                     //Ҷ�ӽڵ�
	int count;                                     //ͨ������Ŀ
	node* child[capacity] = {nullptr};                 //���ӽڵ�
	T data;
	node() :leaf(false), count(0) {};
	node(const T& t, bool leaf = false) :leaf(leaf), count(1),data(t) {};
	~node() { }
};




template<int capacity, class T, class K>                       //capacity ����Ԫ������ K�º�����������ӳ����Ψһ��unsigned��ΧΪ[0,capacity)
class trie
{
	typedef node<capacity, T>* pointer;
private:
	node<capacity,T> root;
	K index;
	unsigned int data_size;                         //�ѱ��洮��Ŀ

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
inline trie<capacity, T, K>::trie():data_size(0)                             //���캯��
{
}

template<int capacity, class T, class K>
inline void trie<capacity, T, K>::erase_node(pointer p)          //�ݹ�ɾ���ڵ�
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
inline void trie<capacity, T, K>::clear()                    //ɾ�����ڵ������нڵ�
{
	data_size = 0;
	erase_node(&root);
}




template<int capacity, class T, class K>
template<class Iterator>
inline void trie<capacity, T, K>::insert(Iterator first, Iterator last)                  //���봮����[first,last)
{
	pointer curr = &root;
	while (first != last)
	{
		if (curr->child[index[*first]] == nullptr)   // ������       *begin ��������� index[*begin] �����Ψһӳ�䣬�˴���Ϊ������
		{
			curr->child[index[*first]] = new node<capacity,T>(*first);
		}
		else
			curr->count++;
		curr = curr->child[index[*first]];              //ת����һ��
		first++;
	}
	if (curr->leaf == false)
	{
		curr->leaf = true;
		data_size++;
	}                   //�������Ѵ��ڵĴ�������
}



template<int capacity, class T, class K>
template<class Iterator>
inline bool trie<capacity, T, K>::contains(Iterator first, Iterator last)               //��ѯ�Ƿ������[frist,last)
{
	pointer curr = &root;
	while (first != last)
	{
		if (curr->child[index[*first]] == nullptr)             //���ɵ���last
		{
			return false;
		}
		curr = curr->child[index[*first]];           //ת����һ��
		first++;
	}
	return curr->leaf;             //��ΪҶ�ӽڵ������������Ϊĳһ����ǰ׺
}


template<int capacity, class T, class K>
template<class Iterator>
inline void trie<capacity, T, K>::erase(Iterator first, Iterator last)                 //ɾ����[first,last)������
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
inline bool trie<capacity, T, K>::erase_node(Iterator first, Iterator last, pointer p)        //����ֵ���Ƿ����ɾ�����ڵ�
{
	if (first + 1 == last)            //���ﴮβ
	{
		if (p->leaf == true)
			data_size--;


		if (p->count != 0)            //�к�̽ڵ㣬����ɾ��
		{
			p->leaf = false;         
			return false;
		}
		else if (p->leaf)             //ΪҶ�ӽڵ㣬�޺�̽ڵ㣬��ɾ��
		{
			return true;
		}
	}

	if (p->child[index[*(first+1)]] != nullptr)      //�ɴ���һ��
	{
		if (erase_node(first + 1, last, p->child[index[*(first+1)]]) == true)
		{
			delete p->child[index[*(first+1)]];
			if (p->count == 1)                         //��ɾ�����ڵ�
				return true;
		}
	}
	return false;
}
