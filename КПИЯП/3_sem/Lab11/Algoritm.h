#pragma once
#include "Iter.h"

template<class TYPE>
class Algoritm
{
public:
	static void print_iter_up(Iter<TYPE> begin, Iter<TYPE> end);
	static void print_iter_down(Iter<TYPE> begin, Iter<TYPE> end);
	static Iter<TYPE> find_iter_key(Iter<TYPE> begin, Iter<TYPE> end, int key);
	static int find_iter_obj(Iter<TYPE> begin, Iter<TYPE> end, TYPE obj);
};

template<class TYPE>
inline void Algoritm<TYPE>::print_iter_up(Iter<TYPE> begin, Iter<TYPE> end)
{
	Iter<TYPE> it = begin;
	for(it;it!=end;it++)
	{
		cout << *it;
	}
	cout << *it;
}

template<class TYPE>
inline void Algoritm<TYPE>::print_iter_down(Iter<TYPE> begin, Iter<TYPE> end)
{
	Iter<TYPE> it = end;
	for (it; it != begin; it--)
	{
		cout << *it;
	}
	cout << *it;
}

template<class TYPE>
inline Iter<TYPE> Algoritm<TYPE>::find_iter_key(Iter<TYPE> begin, Iter<TYPE> end, int key)
{
	Iter<TYPE> it = begin;
	for (it; it != end; it++)
	{
		if (it.getMem()->key == key)
			return it;
	}
	if (it.getMem()->key == key)
		return it;
	else return nullptr;
}

template<class TYPE>
inline int Algoritm<TYPE>::find_iter_obj(Iter<TYPE> begin, Iter<TYPE> end, TYPE obj)
{
	Iter<TYPE> it = begin;
	for (it; it != end; it++)
	{
		if (it.getMem()->data == obj)
			return it.getMem()->key;
	}
	if (it.getMem()->data == obj)
		return it.getMem()->key;
	else return 0;
}
