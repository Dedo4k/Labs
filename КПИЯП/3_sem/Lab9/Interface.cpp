#include "Interface.h"
#include "Algoritm.h"

template<class TYPE> Interface<TYPE>::Interface()
{
	//cout << endl << "Interface constructor" << endl;
}

template<class TYPE> Interface<TYPE>::~Interface()
{
	//cout << endl << "Interface destructor" << endl;
}

template<class TYPE> void Interface<TYPE>::menu()
{
	Binary_tree<TYPE> b;
	TYPE obj;
	do
	{
		system("CLS");
		cout << "Enter [1] to add\n      [2] to print\n      [3] to print keys\n      [4] to find by key\n      [5] to delete by key\n      [6] to print Up by iter\n      [7] to print Down by iter\n      [8] to find by Iter obj\n      [9] to find by Iter key\n      [10] to exit" << endl;
		int choose = MyExc_Vvod::Check_int();
		switch (choose)
		{
		case 1:
		{
			cin >> obj;
			system("CLS");
			b.printKey(b.getRoot(), 0);
			b.add(obj);
			break;
		}
		case 2:
		{
			system("CLS");
			obj.shapka();
			b.print(b.getRoot());
			cout << endl;
			system("pause");
			break;
		}
		case 3:
		{
			system("CLS");
			b.printKey(b.getRoot(), 0);
			cout << endl;
			system("pause");
			break;
		}
		case 4:
		{
			system("CLS");
			b.printKey(b.getRoot(), 0);
			cout << endl;
			b.findByKey(b.getRoot());
			cout << endl;
			system("pause");
			break;
		}
		case 5:
		{
			system("CLS");
			b.printKey(b.getRoot(), 0);
			cout << endl;
			b.deleteByKey(b.getRoot());
			break;
		}
		case 6:
		{
			system("CLS");
			b.printKey(b.getRoot(), 0);
			cout << endl;
			b.getRoot()->data.shapka();
			Algoritm<TYPE>::print_iter_up(b.Begin(), b.End());
			//b.printIterUp();
			cout << endl;
			system("pause");
			break;
		}
		case 7:
		{
			system("CLS");
			b.printKey(b.getRoot(), 0);
			cout << endl;
			b.getRoot()->data.shapka();
			Algoritm<TYPE>::print_iter_down(b.Begin(), b.End());
			//b.printIterDown();
			cout << endl;
			system("pause");
			break;
		}
		case 8:
		{
			system("CLS");
			b.printKey(b.getRoot(), 0);
			cout << endl;
			cout << "Enter key: ";
			int key = MyExc_Vvod::Check_int();
			b.getRoot()->data.shapka();
			cout << (Algoritm<TYPE>::find_iter_key(b.Begin(), b.End(), key)).getMem()->data;
			//b.printIterDown();
			cout << endl;
			system("pause");
			break;
		}
		case 9:
		{
			system("CLS");
			TYPE obj;
			cin >> obj;
			cout << Algoritm<TYPE>::find_iter_obj(b.Begin(), b.End(), obj);
			cout << endl;
			system("pause");
			break;
		}
		case 10:
			return;
			break;
		default:
			system("CLS");
			cout << "Wrong input" << endl;
			break;
		}
	} while (true);
}

template<class TYPE> void Interface<TYPE>::interf()
{
	do 
	{
		system("CLS");
		cout << "Enter [1] to use Monoblock\n      [2] to use Server\n      [3] to use MPhone\n      [4] to use Notebook\n      [5] to exit" << endl;
		char choose = cin.get();
		switch (choose)
		{
		case '1':
		{Interface<Monoblock> t1;
		t1.menu();
		break; }
		case '2':
		{Interface<Server> t2;
		t2.menu();
		break; }
		case '3':
		{Interface<MPhone> t3;
		t3.menu();
		break; }
		case '4':
		{Interface<Notebook> t4;
		t4.menu();
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
