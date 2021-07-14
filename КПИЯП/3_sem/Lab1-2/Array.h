#pragma once
class Array
{
private:
	int* ms;
	int size;
public:
	Array();								//конструктор
	Array(int size);						//конструктор с параметрами
	Array(const Array& other);				//конструктор копированимя
	~Array();								//диструктор
	void add();								//функция добавления значения в массив
	void show();							//функция вывода элементов массива
	//int getSize();						//функция получения рахмера массива
	//int getMs(int i);						//функция получения элемента массива
	Array operator&(const Array& b);		//функция пересечения
	Array &operator=(const Array& b);		//Функция присваивания
	Array crossing(Array& b);
};

