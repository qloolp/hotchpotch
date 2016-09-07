#ifndef maxHeap_H
#define maxHeap_H
/*
MAX_maxHeap
*/
template <typename T>
class maxHeap
{
private:
	T* array;
	int heapSize;
	int heapCapacity;
	int parent(int i) { return i%2?i/2:i/2-1; }
	int left(int i) { return 2*i+1; }
	int right(int i) { return 2*i + 2; }
	void maxHeapify(int i);
	void expansion();
public:
	maxHeap();
	maxHeap(T* val, int num);
	~maxHeap();

	void insert(T& t);
	T max();
	const T* data()const;
	int size() { return heapSize; }
	int capacity() { return heapCapacity; }

	void  removeMax();
};

template<typename T>
inline void maxHeap<T>::maxHeapify(int i)
{
	int le = left(i);
	int re = right(i);
	int maxIndex;
	if (le < heapSize && array[le]>array[i])
		maxIndex = le;
	else
		maxIndex = i;
	if (re<heapSize && array[re]>array[maxIndex])
		maxIndex = re;

	if (maxIndex != i)
	{
		T temp = array[maxIndex];
		array[maxIndex] = array[i];
		array[i] = temp;
		maxHeapify(maxIndex);
	}
	
}

template<typename T>
inline void maxHeap<T>::expansion()
{
	heapCapacity = heapCapacity == 0 ? 1 : 2 * heapCapacity;
	T* temp = new T[heapCapacity];
	for (int i = 0; i < heapSize; i++)
	{
		temp[i] = array[i];
	}
	if (array != nullptr)
		delete[] array;
	array = temp;
}

template<typename T>
maxHeap<T>::maxHeap():array(nullptr),heapSize(0),heapCapacity(0)
{
}



template<typename T>
maxHeap<T>::maxHeap(T* val, int num):array(new T[num]),heapSize(num),heapCapacity(num)
{
	for (int i = 0; i < heapSize; i++)
		array[i] = val[i];
	for (int i = heapSize / 2; i>=0; i--)
	{
		maxHeapify(i);
	}
}


template<typename T>
maxHeap<T>::~maxHeap()
{
	if (array != nullptr)
	{
		delete[] array;
	}
}

template<typename T>
inline void maxHeap<T>::insert(T & t)
{
	if (heapSize >= heapCapacity)
		extend();
	array[heapSize++] = t;
	int index = heapSize;
	T temp;
	while (index > 0 && array[index] > parent(index))
	{
		temp = array[index];
		array[index] = array[parent(index)];
		array[parent(index)] = temp;
		index = parent(index);
	}
}
template<typename T>
inline T maxHeap<T>::max()
{
	if (heapSize < 1)
		throw "maxHeap underflow";
	return array[0];
}




template<typename T>
inline const T * maxHeap<T>::data() const
{
	return array;
}
template<typename T>
inline void maxHeap<T>::removeMax()
{
	if (heapSize < 1)
		throw "maxHeap underflow";
	array[0] = array[--heapSize];
	maxHeapify(0);
}
#endif
