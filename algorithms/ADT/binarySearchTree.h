#pragma once

template<typename T>   //节点
class bstNode
{
public:
	bstNode<T>* parent;
	bstNode<T>* left;
	bstNode<T>* right;

	T data;

	node() :parent(nullptr), left(nullptr), right(nullptr), data(x) {}
	node(const T& x):parent(nullptr),left(nullptr),right(nullptr),data(x){}
	
};




template <typename T>
class binarySearchTree
{
	typedef binarySearchTree<T> self;
	typedef bstNode<T> node;

protected:
	node* root;
	int number;
public:
	binarySearchTree();
	~binarySearchTree();

	template<typename Functor>
	void PreorderTraversal();    //先序遍历
	template<typename Functor>
	void inorderTraversal();     //中序遍历
	template<typename Functor>
	void postorderTraversal();   //后序遍历


	const node<T>* max(const node<T>* p=root)const;
	const node<T>* min(const node<T>* p=root)const;


	void insert(T& x);
	void remove(T& x);
};

template<typename T>
inline binarySearchTree<T>::binarySearchTree():root(nullptr),number(0)
{
}

template<typename T>
inline binarySearchTree<T>::~binarySearchTree()
{
}

template<typename T>
inline const node<T> * binarySearchTree<T>::max(const node<T> * p) const
{
	if (p == nullptr)
		return nullptr;
	while (true)
	{
		if (p->right == nullptr)
			return p;
		else
			p = p->right;
	}
}

template<typename T>
inline const node<T> * binarySearchTree<T>::min(const node<T> * p) const
{
	if (p == nullptr)
		return nullptr;
	while (true)
	{
		if (p->left == nullptr)
			return p;
		else
			p = p->left;
	}
}

template<typename T>
inline void binarySearchTree<T>::insert(T & x)
{
	node* pointer = root;
	node* parent = nullptr;
	while (pointer != nullptr)
	{
		parent = pointer;
		if (pointer->data < x)
			pointer = pointer->left;
		else
			pointer = pointer->right;
	}
	pointer = new node(x);
	pointer->parent = parent;
}

template<typename T>
inline void binarySearchTree<T>::remove(T & x)
{
}

template<typename T>
template<typename Functor>
inline void binarySearchTree<T>::PreorderTraversal()
{
}

template<typename T>
template<typename Functor>
inline void binarySearchTree<T>::inorderTraversal()
{
}

template<typename T>
template<typename Functor>
inline void binarySearchTree<T>::postorderTraversal()
{
}
