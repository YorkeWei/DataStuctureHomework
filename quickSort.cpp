//以下区间均为闭区间
#include <iostream>
#include <queue>
template <typename T>
int partition(T* _elem, int lo, int hi)
{
	std::swap(_elem[lo], _elem[lo + rand() % (hi - lo + 1)]);//随机选一个元素与第一个元素交换
	T pivot = _elem[lo];
	while (lo < hi)
	{
		while ((lo < hi) && (pivot <= _elem[hi]))
			hi--;
		_elem[lo] = _elem[hi];
		while ((lo < hi) && (_elem[lo] <= pivot))
			lo++;
		_elem[hi] = _elem[lo];
	}
	_elem[lo] = pivot;
	return lo;
}
//快速排序(递归实现)
template <typename T>
void quickSort(T* _elem, int lo, int hi)
{
	if (hi - lo < 1)
		return;
	int mi = partition(_elem, lo, hi);
	quickSort<T>(_elem, lo, mi - 1);
	quickSort<T>(_elem, mi + 1, hi);
}
//快速排序(非递归实现)
template <typename T> 
void quickSort_non_rec(T* _elem, int lo, int hi)
{
	std::queue<std::pair<int, int>> q;
	q.push(std::make_pair(lo, hi));
	while (!q.empty())
	{
		std::pair<int, int> section = q.front();
		q.pop();
		int _lo = section.first; int _hi = section.second;
		if (_hi - _lo < 1)
			continue;
		int mi = partition(_elem, _lo, _hi);
		q.push(std::make_pair(_lo, mi - 1));
		q.push(std::make_pair(mi + 1, _hi));
	}
}
/*
int main()
{
	int a[15] = {2, 3, 5, 1, 3 ,4 ,6, 4, 10, 11, 15, 0, 11, 12, 18};
	quickSort(a, 0, 14);
	
	for (int i = 0; i < 15; i++)
		std::cout << a[i] << std::endl;
	return 0;
}
*/

