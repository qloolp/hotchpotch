template<class T>
class Queue
{
private:
	struct Node { T item; struct Node* next; };
	Node* front;
	Node* rear;
	int count;
public:
	Queue(Queue&);
	Queue();
	~Queue();
	void clear();
	void enQueue(const T& item);
	T deQueue();
	const T& frontValue()const;
	int size()const;
	bool isEmpty()const;
	bool contains(const T& item)const;
	T* toArray();
	void print();
};


template<class T>
Queue<T>::Queue(Queue& q)
{
	T* temp = q.toArray();
	int num = q.count;
	rear = front = new Node;
	front->next = 0;
	count = 0;
	for(int i=0; i<num; i++)
		enQueue(temp[i]);
}

template<class T>
Queue<T>::Queue()      //具有头节点
{
	rear = front = new Node;
	if(rear == 0)
		throw exception("Failed to allocate memory!");
	front->next = 0;
	count = 0;
}

template<class T>
Queue<T>::~Queue()
{
	clear();
	delete front;
}

template<class T>
void Queue<T>::clear()                           //清除头节点外的所有节点
{
	while(front->next  != 0) 
	{
		Node* temp = front->next;
		delete front;
		front = temp;
	}

	rear = front;
	count = 0;
}

template<class T>
void Queue<T>::enQueue(const T& item)               //入队
{
	rear->next = new Node;
	if(rear->next == 0)
		throw exception("Failed to allocate memory!");
	rear = rear->next;
	rear->item = item;
	rear->next = 0;
	count++;
}

template<class T>
T Queue<T>::deQueue()                              //出队
{
	if(count == 0)
		throw exception("Queue is empty!");
	T item = front->next->item;
	Node* temp = front->next->next;
	delete front->next;
	front->next = temp;
	count--;
	return item;
}

template<class T>
const T& Queue<T>::frontValue()const               //访问队首元素
{
	if(count == 0)
		throw exception("Queue is empty!");
	return front->next->item;
}

template<class T>
int Queue<T>::size()const                        //返回元素数目
{
	return count;
}

template<class T>
bool Queue<T>::isEmpty()const                   //判断队列是否为空
{
	return count == 0;
}


template<class T>
void Queue<T>::print()
{
	if(count == 0)
	{
		cout<<"Queue is empty!";
		return;
	}
	Node* temp = front;
	while(temp->next != 0)
	{
		temp = temp ->next;
		cout<<temp->item<<endl;
	}
	cout<<"The number of element in the queue is:"<<count<<endl;	
}

template<class T>
T* Queue<T>::toArray()
{
	int i=0;
	if(count == 0)
		return 0;
	T* temp = new T[count];
	Node* p = front;
	while (p->next != 0)
	{
		temp[i] = p->next->item;
		p = p->next;
		i++;
	}
	return temp;
}

template<class T>
bool Queue<T>::contains(const T& item)const
{
	Node* temp = front;
	while (temp->next != 0)
	{
		if(temp->next->item == item)
			return true;
		temp = temp->next;
	}
	return false;

}
