#define Parent(i) ((i - 1) >> 1) //i的父亲
#define LChild(i) (1 + (( i ) << 1))//i的左儿子
#define RChild(i) ((1 + ( i )) << 1)//i的右儿子
#define InHeap(n, i) (((-1) < ( i )) &&(( i ) < ( n )))
#define LChildValid(n, i) InHeap(n, LChild( i ))//i是否有左儿子
#define RChildValid(n, i) InHeap(n, RChild( i ))//i是否有右儿子
#define Smaller(HC, i, j) ((HC[i] > HC[j]) ? j : i)
#define ProperParent(HC, n, i)\
			(RChildValid(n, i) ? Smaller(HC, Smaller(HC, i, LChild(i)), RChild(i)) : \
			(LChildValid(n, i) ? Smaller(HC, i, LChild(i)) : i)\
			)
#define DEFAULT_CAPACITY 100
#include <iostream>
template <typename T>
class heap
{
protected:
	T* heapChain;
	int _size;
	int _capacity;
public:
	heap()
	{
		_capacity = DEFAULT_CAPACITY;
		heapChain = new T[_capacity];
		_size = 0;
	}
	heap(T* e, int lo, int hi)
	{
		_capacity = DEFAULT_CAPACITY;
		heapChain = new T[_capacity];
		_size = 0;
		for (int i = lo; i < hi; i++)
			insert(e[i]);
	}
	void insert(T e)
	{
		expand();
		int i = _size;
		heapChain[_size++] = e;
		while ((i > 0) && (heapChain[Parent(i)] > heapChain[i]))
		{
			std::swap(heapChain[Parent(i)], heapChain[i]);
			i = Parent(i);
		}
	}
	void expand()
	{
		//空间不足时，将容量扩为原来的2倍
		if (_size < _capacity)
			return;
		T* oldHeapChain = heapChain;
		heapChain = new T[_capacity << 1];
		for (int i = 0; i < _size; i++) 
			heapChain[i] = oldHeapChain[i];
		delete[] oldHeapChain;
	}
	T delMin()//删除堆顶元素
	{
		if (_size <= 0) 
			return NULL;
		T e = heapChain[0];
		heapChain[0] = heapChain[--_size];
		int n = _size;
		int i = 0, j;
		while (i != (j = ProperParent(heapChain, n, i))) 
		{
			std::swap(heapChain[i], heapChain[j]);
			i = j;
		}
		shrink();
		return e;
	}
	T del(int rank)
	{
		if (rank < 0 || rank >= _size)
			return NULL;
		T e = heapChain[rank];
		heapChain[rank] = heapChain[--_size];
		int n = _size;
		int i = rank, j;
		if (i == ProperParent(heapChain, n, i))
		{
			while ((i > 0) && (heapChain[Parent(i)] > heapChain[i]))
			{
				std::swap(heapChain[Parent(i)], heapChain[i]);
				i = Parent(i);
			}
		}
		else {
			while (i != (j = ProperParent(heapChain, n, i)))
			{
				std::swap(heapChain[i], heapChain[j]);
				i = j;
			}
		}
		shrink();
		return e;

	}
	void shrink()
	{
		//有效空间不足25%时，将容量缩小为原来的50%
		if (_size << 2 >= _capacity)
			return;
		T* oldHeapChain = heapChain;
		heapChain = new T[_capacity >> 1];
		for (int i = 0; i < _size; i++)
			heapChain[i] = oldHeapChain[i];
		delete[] oldHeapChain;
	}
	T getMin()
	{
		if (_size <= 0)
			return NULL;
		return heapChain[0];
	}
};
template <typename T>
void heapSort(T* _elem, int lo, int hi) 
{
	heap<T> h(_elem, lo, hi);
	for (int i = lo; i < hi; i++)
		_elem[i] = h.delMin();
}
/*
int main()
{
	int a[13] = { 3, 3, 1, 6, 10, 2, 42, 51, -1, -10, 100, -53, -7};
	heapSort(a, 0, 13);
	for (int i = 0; i < 10; i++) {
		std::cout << a[i] << " ";
	}
	return 0;
}
*/