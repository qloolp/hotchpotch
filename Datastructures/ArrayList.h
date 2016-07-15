template<class T>
class ArrayList
{
private:
	enum {defaultSize = 5};
	T* pointer;
	int capacity;
	int count;
	void expend();
public:
	ArrayList();
	ArrayList(const int n);
	ArrayList(const ArrayList& list);
	~ArrayList();
	void clear();
	void append(const T& item);
	void insertAt(int index,const T& item);
	void insertRange(int index,const T* begin, const int n);
	void remove();
	void removeAt(const T& item);
    void removeRange(int index, int n);
	int size()const;
	int maxSize()const;
	T* toArray()const;
	bool contains(const T& item);
	bool isEmpty();
	ArrayList& operator=(const ArrayList& list);
	const T& operator[](int index)const;
	T& operator[](int index);
	ArrayList operator+(const ArrayList& list);
	ArrayList subArrayList(int index,int n);
	void reverse();
	void print();
	int indexOf(const T& item);
};


template<class T>
ArrayList<T>::ArrayList()
{
	capacity = defaultSize;
	pointer = new T[capacity];
	count = 0;
}

template<class T>
ArrayList<T>::ArrayList(const int n)
{
	if(n<0)
		throw exception("ArgumentOutOfRange");
	else
	{
		capacity = n;
		count = 0;
		pointer = new T [capacity];
	}
}

template<class T>
ArrayList<T>::ArrayList(const ArrayList& list)
{
	capacity = list.capacity;
	count = list.count;
	pointer = new T[capacity];
	for(int i=0; i<count; i++)
		pointer[i] = list.pointer[i];
}

template<class T>
ArrayList<T>::~ArrayList()
{
	if(pointer != 0)
		delete[] pointer;
}

template<class T>
void ArrayList<T>::clear()
{
	capacity = defaultSize;
	count = 0;
}

template<class T>
void ArrayList<T>::append(const T& item)
{
	if(count == capacity)
	{
		capacity *= 2;
		T* temp = new T[capacity];
		for(int i=0; i<count; i++)
			temp[i] = pointer[i];
		pointer = temp;
	}
	pointer[count] = item;
	count++;
}

template<class T>
void ArrayList<T>::expend()
{
	capacity *= 2;
	T* temp = new T [capacity];
	for(int i=0; i<count; i++)
		temp[i] = pointer[i];
	delete[] pointer;
	pointer = temp;
}

template<class T>
void ArrayList<T>::insertAt(int index, const T& item)
{
	if(index<0||index>count)
		throw exception("ArumentOutOfRange");
	if(count = capacity)
		expend();
	for(int i=count-1; i>=index; i--)
		pointer[i+1] = pointer[i];
	pointer[index]=item;
	count++;
}

template<class T>
void ArrayList<T>::insertRange(int index,const T* begin, const int n)
{
	if(index<0 || index>count || n<0)
		throw exception("ArgumentOutOfRange");
	if((count+n) > capacity)
	{
		capacity = (count + n);
		expend();
	}
	for(int i=count-1; i>=index; i--)
		pointer[i+n] = pointer[i];
	for(int i=0; i<n; i++)
		pointer[i+index] = begin[i];
	count += n;
}

template<class T>
void ArrayList<T>::remove()
{
	count = count>0?count-1:0;
}

template<class T>
void ArrayList<T>::removeAt(const T& item)
{
	int i=0;
	for(i=0; i<count; i++)
		if(pointer[i] == item)
		{
			count--;
			break;
		}
	for(i; i<count; i++)
		pointer[i] = pointer[i+1];
}

template<class T>
void ArrayList<T>::removeRange(int index,int n)
{
	if(index<0 || index>=count || n<0 || n>count)
		throw exception("ArgumentOutOfRange");
	if(index+n>count)
		throw exception("ArgumentException");
	for(int i=index; i<count; i++)
		pointer[i] = pointer[i+n];
	count -= n;
}

template<class T>
int ArrayList<T>::size()const
{
	return count;
}

template<class T>
int ArrayList<T>::maxSize()const
{
	return capacity;
}


template<class T>
T* ArrayList<T>::toArray()const
{
	T* temp = new T [count];
	for(int i=0; i<count; i++)
		temp[i] = pointer[i];
	return temp;
}

template<class T>
bool ArrayList<T>::contains(const T& item)
{
	for(int i=0; i<count; i++)
		if(pointer[i] == item)
			return true;
	return false;
}

template<class T>
bool ArrayList<T>::isEmpty()
{
	if(count == 0)
		return true;
	else
		return false;
}

template<class T>
ArrayList<T>& ArrayList<T>::operator=(const ArrayList& list)
{
	if(this == &list)
		return *this;

	capacity = list.capacity;
	count = list.count;
	delete[] pointer;
	pointer = new T [capacity];
	for(int i=0; i<count; i++)
		pointer[i] = list.pointer[i];
	return *this;
}

template<class T>
const T& ArrayList<T>:: operator[](int index)const
{
	if(index<0 || index>=count)
		throw exception("ArgumentOutOfRange");
	else
		return pointer[index];
}

template<class T>
T& ArrayList<T>:: operator[](int index)
{
	if(index<0 || index>=count)
		throw exception("ArgumentOutOfRange");
	else
		return pointer[index];
}

template<class T>
ArrayList<T> ArrayList<T>::subArrayList(int index,int n)
{
	if(index<0 || index>count || n<0 || n>count)
		throw exception("ArgumentOutOfRange");
	ArrayList<T> temp(n);
	temp.insertRange(index,pointer+index,n);
	return temp;
}

template<class T>
void ArrayList<T>:: reverse()
{
	T temp;
	T* front = pointer;
	T* rear = pointer + count-1;
	while (front<rear)
	{
		temp = *front;
		*front = *rear;
		*rear = temp;
		front++;
		rear--;
	}
}


template<class T>
ArrayList<T> ArrayList<T>::operator+(const ArrayList& list)
{
	int n = coutn + list.count;
	ArrayList temp(n);
	for(int i=0; i<count; i++)
		pointer[i] = pointer[i];
	for(int i=0; i<list.count; i++)
		pointer[i+count-1] = list.pointer[i];
}

template<class T>
void ArrayList<T>::print()
{
	for(int i=0; i<count; i++)
		cout<<"index= "<<i<<"\t"<<pointer[i]<<endl;
	cout<<"count= "<<count<<"\t"<<"capacity= "<<capacity<<endl;
}

template<class T>
int ArrayList<T>::indexOf(const T& item)
{
	for(int i=0; i<count; i++)
		if(pointer[i] == item)
			return i;
	return -1;
}

