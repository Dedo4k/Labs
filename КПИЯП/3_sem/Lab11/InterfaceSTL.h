#pragma once
#include "Interface.h"
#include "Algoritm.h"
#include "AlgoritmSTL.h"
//#include "File_bin.h"
//#include "FIle_txt.h"
#include  "BinaryFile.cpp"
#include "TextFile.cpp"
#include "Iter.h"
#include <algorithm>
#include <list>

template<class TYPE>
class InterfaceSTL
{
private:
	TYPE obj;
public:
	InterfaceSTL();
	~InterfaceSTL();
	void sort_menu(list<TYPE>& list, int i);
	void printlistUp(list<TYPE>& list);
	void printlistDown(list<TYPE>& list);
	void menu(string txtpath,string datpath, int i);
	static void interf();
};

template<class TYPE>
inline InterfaceSTL<TYPE>::InterfaceSTL()
{
	
}

template<class TYPE>
inline InterfaceSTL<TYPE>::~InterfaceSTL()
{
}

template<class TYPE>
inline void InterfaceSTL<TYPE>::sort_menu(list<TYPE>& list, int i)
{
	switch (i)
	{
	case 1:
	{
		cout << "Choose field for sort." << endl;
		cout << "[1] - Brand" << endl;
		cout << "[2] - Processor" << endl;
		cout << "[3] - Prcessor model" << endl;
		cout << "[4] - Voltage" << endl;
		cout << "[5] - Memory capacity" << endl;
		char ch = cin.get();
		switch (ch)
		{
		case '1':
			sort_brand(list, i);
			//if(typeid(TYPE)==typeid(Monoblock))
			//	list.sort([](Computer& a, Computer& b) {return a.getBrand() < b.getBrand(); });
			break;
		case '2':
			//if (typeid(TYPE) == typeid(Monoblock))
			//	list.sort([](Static& a, Static& b) {return a.getProc() < b.getProc(); });
			break;
		default:
			break;
		}
		break;
	}
	case 2:

		break;
	default:
		break;
	}
}

template<class TYPE>
inline void InterfaceSTL<TYPE>::printlistUp(list<TYPE>& list)
{
	for(auto i=list.begin();i!=list.end();++i)
	{
		cout << *i;
	}
}

template<class TYPE>
inline void InterfaceSTL<TYPE>::printlistDown(list<TYPE>& list)
{
	for (auto i = list.rbegin(); i != list.rend(); ++i)
		cout << *i;
}

template<class TYPE>
inline void InterfaceSTL<TYPE>::menu(string txtpath,string datpath, int i)
{
	list<TYPE> b;
	TYPE obj;
	do
	{
		system("CLS");
		cout << "[1]  to add back" << endl;
		cout << "[2]  to add front" << endl;
		cout << "[3]  to print Up" << endl;
		cout << "[4]  to print Down" << endl;
		cout << "[5]  to find by index" << endl;
		cout << "[6]  to find by object" << endl;
		cout << "[7]  to find by brand" << endl;
		cout << "[8]  to delete by index" << endl;
		cout << "[9]  to delete by object" << endl;
		cout << "[10] to delete range of elements" << endl;
		cout << "[11] to sort" << endl;
		cout << "[12] to insert by index" << endl;
		cout << "[13] Exit." << endl;
		int choose = MyExc_Vvod::Check_int();
		switch (choose)
		{
		case 1:		//добавить в конец
		{
			cin >> obj;
			system("CLS");
			b.push_back(obj);
			break;
		}
		case 2:		//добавить в начало
		{
			cin >> obj;
			system("CLS");
			b.push_front(obj);
			break;
			break;
		}
		case 3:		//печать в прямод обходе
		{
			system("CLS");
			obj.shapka();
			printlistUp(b);
			cout << endl;
			system("pause");
 			break;
		}
		case 4:		//печать в обратном обходе
		{
			system("CLS");
			obj.shapka();
			printlistDown(b);
			cout << endl;
			system("pause");
			break;
		}
		case 5:		//поиск объекта по индексу
		{
			system("CLS");
			cout << "Enter index: ";
			int index = MyExc_Vvod::Check_int();
			if (index >= b.size())
			{
				cout << "Wrong index." << endl;
				system("pause");
				break;
			}
			auto it = b.begin();
			advance(it, index);
			cout << endl;
			obj.shapka();
			cout << *it;
			cout << endl;
			system("pause");
			break;
		}
		case 6:		//поиск индекса по объекту
		{
			system("CLS");
			cin >> obj;
			int index = 0;
			for(auto i = b.begin();i!=b.end();++i)
			{
				if (*i == obj)
				{
					cout << index << endl;
					system("pause");
					break;
				}
				index++;
			}
			break;
		}
		case 7:		//поиск объекта по бренду
		{
			system("CLS");
			cout << "Enter brand: ";
			string str = MyExc_Vvod::Check_string(12);
			auto i = find_if(b.begin(), b.end(), [str](TYPE& a) {if (a.getBrand() == str)return true; });
			if (i == b.end())
				cout << "This object doesn't exists." << endl;
			else
			{
				obj.shapka();
				cout << *i << endl;
			}
			system("pause");
			break;
		}
		case 8:		//удаление по индексу
		{
			system("CLS");
			cout << "Enter index: ";
			int index = MyExc_Vvod::Check_int();
			if (index >= b.size())
			{
				cout << "Wrong index." << endl;
				system("pause");
				break;
			}
			auto it = b.begin();
			advance(it, index);
			b.erase(it);
			break;
		}
		case 9:		//удаление по объекту
		{
			system("CLS");
			cout << "Enter object:" << endl;
			cin >> obj;
			b.erase(remove_if(b.begin(), b.end(), [obj](TYPE& el) {if (el == obj)return true; }),b.end());
			break;
			}
		case 10:	//удаление диапозона значений по индексам
		{
			system("CLS");
			cout << "Enter start index: ";
			int start = MyExc_Vvod::Check_int();
			if(start>b.size())
			{
				cout << "Wrong index." << endl;
				system("pause");
				break;
			}
			cout << endl << "Enter end index: ";
			int end = b.size()-MyExc_Vvod::Check_int();
			if (end > b.size())
			{
				cout << "Wrong index." << endl;
				system("pause");
				break;
			}
			if(start>end)
			{
				cout << "Start index must be less than end index." << endl;
				system("pause");
				break;
			}
			auto s = b.begin();
			auto e = b.end();
			advance(s, start);
			advance(e, -end);
			b.erase(s,e);
			break;
		}
		case 11:	//сортировка по бренду
		{
			system("CLS");
			b.sort([]( TYPE&a,  TYPE&b) {return a.getBrand() < b.getBrand(); });
			break;
		}
		case 12:	//вставка по индексу
		{
			system("CLS");
			cout << "Enter object: " << endl;
			cin >> obj;
			cout << "Enter index: ";
			int index = MyExc_Vvod::Check_int();
			if(index>b.size())
			{
				cout << "Wrong index." << endl;
				system("pause");
				break;
			}
			auto i = b.begin();
			advance(i, index);
			b.insert(i, obj);
			break;
		}
		case 13:	//выход
			return;
			break;
		default:
			system("CLS");
			cout << "Wrong input" << endl;
			break;
		}
	} while (true);
}

template<class TYPE>
inline void InterfaceSTL<TYPE>::interf()
{
	string txtpathMonoblock = "txtMon.txt";
	string txtpathServer = "txtSer.txt";
	string txtpathMPhone = "txtMP.txt";
	string txtpathNotebook = "txtNot.txt";
	string datpathMonoblock = "datMon.dat";
	string datpathServer = "datSer.dat";
	string datpathMPhone = "datMP.dat";
	string datpathNotebook = "datNot.dat";
	do
	{
		system("CLS");
		cout << "Enter [1] to use Monoblock\n      [2] to use Server\n      [3] to use MPhone\n      [4] to use Notebook\n      [5] to exit" << endl;
		char choose = cin.get();
		switch (choose)
		{
		case '1':
		{InterfaceSTL<Monoblock> t1;
		t1.menu(txtpathMonoblock,datpathMonoblock,1);
		break; }
		case '2':
		{InterfaceSTL<Server> t2;
		t2.menu(txtpathServer,datpathServer,2);
		break; }
		case '3':
		{InterfaceSTL<MPhone> t3;
		t3.menu(txtpathMPhone,datpathMPhone,3);
		break; }
		case '4':
		{InterfaceSTL<Notebook> t4;
		t4.menu(txtpathNotebook,datpathNotebook,4);
		break; }
		case '5':
			return;
			break;
		default:
			system("CLS");
			cout << "Wrong input" << endl;
			break;
		}
	} while (true);
}
