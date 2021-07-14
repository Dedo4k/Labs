#pragma once
#include <list>
#include <iostream>
using namespace std;
template<class TYPE>
class AlgoritmSTL
{
public:
	static void print_up(list<TYPE> begin, list<TYPE> end);
	
};

template<class TYPE>
inline void AlgoritmSTL<TYPE>::print_up(list<TYPE> begin, list<TYPE> end)
{
	for (auto i = begin; i != end; ++i)
		cout << *i;
}
