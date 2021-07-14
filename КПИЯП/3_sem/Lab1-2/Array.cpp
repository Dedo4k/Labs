#include "Array.h"
#include <iostream>
#include<iomanip>
using namespace std;

Array::Array()
{
	this->size = 0;
	ms = new int[0];
}

Array::Array(int size)
{
	this->size = size;
	ms = new int[size];
}

Array::~Array()
{
	delete[]ms;
}


Array::Array(const Array& b)
{
	this->size = b.size;
	this->ms = new int[this->size];
	for (int i = 0; i < this->size; i++)
		this->ms[i] = b.ms[i];
}

Array &Array::operator=(const Array& other)
{
	if (&other != this)
	{
		if (ms)delete[]ms;
		this->size = other.size;

		ms = new int[this->size];
		for (int i = 0; i < other.size; i++)
			this->ms[i] = other.ms[i];
	}
	return *this;
}

Array Array::operator&(const Array& b)
{
	int small, k=0;
	if (b.size >= this->size)
		small = this->size;
	else
		small = b.size;
	Array result(small);
	for (int i = 0; i < b.size; i++)
		for (int j = 0; j < this->size; j++)
			if (this->ms[i] == b.ms[j])
			{
				result.ms[k] = this->ms[i];
				k++;
				break;
			}
	result.size = k;
	return result;
}

Array Array::crossing(Array& b)
{
	int small, k = 0;
	if (b.size >= this->size)
		small = this->size;
	else
		small = b.size;
	Array result(small);
	for (int i = 0; i < b.size; i++)
		for (int j = 0; j < this->size; j++)
			if (this->ms[i] == b.ms[j])
			{
				result.ms[k] = this->ms[i];
				k++;
				break;
			}
	result.size = k;
	return result;
}

void Array::add()
{
	for (int i = 0; i < size; i++)
	{
		cout << "[" << i << "]- ";
		cin >> ms[i];
	}
}

void Array::show()
{
	for (int i = 0; i < size; i++)
		cout << setw(4) << ms[i];
	cout << endl;
}
