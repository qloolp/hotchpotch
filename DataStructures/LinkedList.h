template<class T>
class LinkedList
{
private:
	struct Node
	{
		T item;
		Node* prev;
		Node* next;
	};
	Node* head;
	int count;
public:
	LinkedList();
	LinkedList(const LinkedList& list);
	~LinkedList();
	void clear();
	void push_back(const T& item);
	T pop_back();
	void push_front(const T& item);
	T pop_front();
	void insertAt(int index,const T& item);
	T removeAt(int index);
	int size()const;
	T* toArray()const;
	bool contains(const T& item);
	bool isEmpty();
	const T& operator[](int index)const;
	T& operator[](int index);
	int indexOf(const T& item);
	void reverse();
	void print();

};

template<class T>
LinkedList<T>::LinkedList()
{
	count = 0;
	head = new Node;
	head->prev = head->next = head;
}

template<class T>
LinkedList<T>::LinkedList(const LinkedList& list)
{


}

template<class T>
LinkedList<T>::~LinkedList()
{
	clear();
	delete head;
}

template<class T>
void LinkedList<T>::clear()
{
	Node* temp = head->next;
	Node* temp1;
	while (temp != head)
	{
		temp1 = temp-next;
		delete temp;
		temp = temp1;
	}
}

template<class T>
void LinkedList<T>::push_back(const T& item)
{
	Node* temp = new Node;
	temp->item = item;

	temp->prev = head->prev;
	temp->next = head;

	head->prev->next = temp;
	head->prev = temp;

	count++;
}

template<class T>
void LinkedList<T>::insertAt(int index,const T& item)
{
	int i=0;
	Node* temp;
	Node* p = new Node;
	p->item = item;

	if(index<count/2)
	{
		temp = head->next;
		while (i != index)
		{
			temp = temp->next;
			i++;
		}
	}
	else
	{

		temp = head->prev;
		index = count-index-1;
		while (i != index)
		{
			temp = temp->prev;
			i++;
		}
	}

	temp = temp->prev;

	p->next = temp->next;
	p->prev = temp;

	temp->next = p;
	p->next->prev = p;

	count++;
}

template<class T>
T LinkedList<T>::pop_back()
{
	Node* temp = head->prev;
	T item = temp->item;
	temp->prev->next = head;
	head->prev = temp->prev;
	count--;
	delete temp;
	return item;
}

template<class T>
void LinkedList<T>::push_front(const T& item)
{
	Node* temp = new Node;
	temp->item = item;

	temp->next = head->next;
	temp->prev = head;
	temp->next->prev = temp;
	head->next = temp;
	count++;
}

template<class T>
T LinkedList<T>::pop_front()
{
	Node* temp = head->next;
	T item = temp->item;
	head->next = temp->next;
	temp->next->prev = temp->prev;
	count--;
	delete temp;
	return item;
}

template<class T>
T LinkedList<T>::removeAt(int index)
{
	int i=0;
	Node* temp;
	
	if(index<count/2)
	{
		temp = head->next;
		while (i != index)
		{
			temp = temp->next;
			i++;
		}
	}
	else
	{

		temp = head->prev;
		index = count-index-1;
		while (i != index)
		{
			temp = temp->prev;
			i++;
		}
	}


	temp->prev->next = temp->next;
	temp->next->prev = temp->prev;

	T item = temp->item;
	delete temp;
	count--;
	return item;
}

template<class T>
int LinkedList<T>::size()const
{
	return count;
}

template<class T>
T* LinkedList<T>::toArray()const
{
	int i=0;
	T* p = new T[count];
	Node* temp = head;
	while (temp->next != heaed)
	{
		p[i] = temp->next->item;
		temp = temp->next;
	}
	return p;
}

template<class T>
bool LinkedList<T>::contains(const T& item)
{
	Node* temp = head;
	while (temp->next != head)
	{
		if(temp->next->item == item)
			return true;
		temp = temp->next;
	}
	return false;
}

template<class T>
bool LinkedList<T>::isEmpty()
{
	return !count;
}

template<class T>
const T& LinkedList<T>::operator[](int index)const
{
	int i=0;
	Node* temp;

	if(index<count/2)
	{
		temp = head->next;
	}
	else
	{

		temp = head;
		index = count - index;
	}

	while (i != index)
	{
		temp = temp->next;
		i++;
	}
	return temp->item;
}

template<class T>
T& LinkedList<T>::operator[](int index)
{
	int i=0;
	Node* temp;

	if(index<count/2)
	{
		temp = head->next;
	}
	else
	{

		temp = head;
		index = count - index;
	}

	while (i != index)
	{
		temp = temp->next;
		i++;
	}
	return temp->item;
}

template<class T>
int LinkedList<T>::indexOf(const T& item)
{
	int i=0;
	Node* temp = head;
	while (temp->next != head)
	{
		if(temp->next->item == item)
			return i;
		temp = temp->next;
		i++;
	}
	return -1;
}

template<class T>
void LinkedList<T>::reverse()
{
	if(count<=1)
		return;
	push_front(pop_back());
	for(int i=1; i<count-1; i++)
		insertAt(i,pop_back());
}


template <class T>
void LinkedList<T>::print()
{
	Node* temp = head;
	while (temp->next != head)
	{
		cout<<temp->next->item<<endl;
		temp = temp->next;
	}
}















