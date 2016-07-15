template<class T>
class MinHeap
{
public:
	struct Element
	{
		T item;
		int key;
	};
private:
	enum { defaultSize = 10 };
	int count;                                     //ʵ��Ԫ�ظ���
	int capacity;
	Element* pointer;
	void heapify(int parent,int n);               //ά�ֶ�����
	void set(int index, int key);                 //����index��keyֵ
public:
	MinHeap(Element* p, int size);                    
	MinHeap();
	~MinHeap();
	int size();
	bool isEmpty();
	const T& top();
	T pop();                                     //ɾ���Ѹ��ڵ�Ԫ�أ�������ֵ
	void push(const T& item,int key);           //����Ԫ��
	T* toArray();     
	void setKey(const T& item,int key);         //�ı�keyֵ
	void buildHeap();                           //����
	bool contains(const T& item);
};

template<class T>
MinHeap<T>::MinHeap(Element* p, int size)
{
	if(p==0 || size<=0)
		throw exception("ArgumentInvalid!");
	count = size;
	capacity = 2*count;
	pointer = new Element[capacity];
	for(int i=0; i<count; i++)
		pointer[i] = p[i];
	buildHeap();
}

template<class T>
MinHeap<T>::MinHeap()
{
	count = 0;
	capacity = defaultSize;
	pointer = new Element[capacity];
}

template<class T>
MinHeap<T>::~MinHeap()
{
	if(pointer !=0 )
		delete[] pointer;
}

template<class T>
void MinHeap<T>::heapify(int parent,int n)
{
	Element temp;
	int child = 2*parent+1;                             //���ӽڵ�����Ϊ���ڵ�*2+1
	if(child>n-1)
		return;
	else if(child<n-1)   
		child = pointer[child].key < pointer[child+1].key ? child : child+1;       //ȡ��child�е���Сֵ
	if(pointer[child].key<pointer[parent].key)        //�����ڵ�����ӽڵ����ӽڵ����ƣ����ڵ�����
	{
		temp = pointer[parent];
		pointer[parent] = pointer[child];
		pointer[child] = temp;
		heapify(child,n);
	}
}

template<class T>
void MinHeap<T>::buildHeap()
{
	for(int i=count/2-1; i>=0; i--)
	{
		heapify(i,count);
	}
}

template<class T>
T* MinHeap<T>:: toArray()
{
	Element* temp = new Element[count];
	T* TPointer = new T[count];
	int sz = count;
	for(int i=0; i<count; i++)
		temp[i] = pointer[i];

	for(int i=0; i<sz; i++)
		TPointer[i] = pop();

	count = sz;
	delete[] pointer;
	pointer = temp;
	return TPointer;
}

template<class T>
bool MinHeap<T>::isEmpty()
{
	return count==0;
}

template<class T>
int MinHeap<T>::size()
{
	return count;
}

template<class T>
const T& MinHeap<T>::top()
{
	return pointer[0].item;
}

template<class T>
T MinHeap<T>::pop()
{
	T temp = pointer[0].item;
	if(count==0)
		throw exception("heap underflow");
	pointer[0] = pointer[count-1];
	count--;
	heapify(0,count);
	return temp;
}

template<class T>
void MinHeap<T>::push(const T& item,int key)
{
	Element* temp;
	if(count == capacity)
	{
		capacity = 2*count;
		temp = new Element[capacity];
		for(int i=0; i<count; i++)
			temp[i] = pointer[i];
		pointer = temp;
		delete[] pointer;
	}
	pointer[count].item = item;
	pointer[count].key = key;
	set(count,key);
	count++;
}
template<class T>
void MinHeap<T>::setKey(const T& item, int key)      //�޸�����item��key
{
	for(int i=0; i<count; i++)
		if(item == pointer[i].item)
			set(i,key);
}

template<class T>
void MinHeap<T>::set(int index,int key) 
{
	Element temp;
	if(pointer[index].key<key)                                         //��������
	{
		pointer[index].key=key;
		heapify(index,count);
	}
	else                                                              //��С����
	{
		pointer[index].key=key;
		while(index>=0 && pointer[(index-1)/2].key>pointer[index].key)
		{
			int parent = (index-1)/2;
			temp = pointer[parent];
			pointer[parent] = pointer[index];
			pointer[index] = temp;
			index = parent;
		}
	}
}

template<class T>
bool MinHeap<T>::contains(const T& item)
{
	for(int i=0; i<count; i++)
		if(item == pointer[i].item)
			return true;
	return false;
}






