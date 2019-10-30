#ifndef UNION_SET_HPP
#define UNION_SET_HPP
#include <map>
#include <set>
template <typename T>
class union_set 
{
private:
	std::map<T, T> fa;
public:
	union_set(const std::set<T>& ele)
	{
		typename std::set<T>::iterator it;
		for (it = ele.begin(); it != ele.end(); it++)
			fa[*it] = *it;
	}
	T find(T e)
	{
		T k, j, r;
		r = e;
		while (r != fa[r])
			r = fa[r];
		//Â·¾¶Ñ¹Ëõ
		k = e;
		while (k != r)
		{
			j = fa[k];
			fa[k] = r;
			k = j;
		}
		return r;
	}
	bool merge(T ex, T ey)
	{
		T ex_a = find(ex);
		T ey_a = find(ey);
		if (ex_a != ey_a)
		{
			fa[ey_a] = ex_a;
			return true;
		}
		else
			return false;
	}
	~union_set() {}
};
#endif