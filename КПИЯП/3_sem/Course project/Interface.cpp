#include "Interface.h"
#include "Truck.h"
#include "Client.cpp"
#include "Worker.h"
#include "Binary_tree.cpp"
#include <fstream>
#include <locale.h>

template<class T>
void Interface<T>::getTicket(T client)
{
	cout << "\t\t\t\t\t\t\t\t\t\t\t\t___________________________" << endl;
	cout << "\t\t\t\t\t\t\t\t\t\t\t\t|         <ТАЛОН>         |" << endl;
	cout << "\t\t\t\t\t\t\t\t\t\t\t\t|=========================|" << endl;
	cout << "\t\t\t\t\t\t\t\t\t\t\t\t| № Места: " << setw(14) << client.getPplace() << " |" << endl;
	cout << "\t\t\t\t\t\t\t\t\t\t\t\t| Номер т/с: " << setw(12) << client.getVehicle().getNumber() << " |" << endl;
	cout << "\t\t\t\t\t\t\t\t\t\t\t\t| Время: " << setw(16) << client.getTime() << " |" << endl;
	cout << "\t\t\t\t\t\t\t\t\t\t\t\t| Цена: " << setw(12) << setprecision(4) << client.getCost() << " руб. |" << endl;
	cout << "\t\t\t\t\t\t\t\t\t\t\t\t| Имя: " << setw(18) << client.getName() << " |" << endl;
	cout << "\t\t\t\t\t\t\t\t\t\t\t\t| Тип: " << setw(18) << client.getVehicle().getType() << " |" << endl;
	cout << "\t\t\t\t\t\t\t\t\t\t\t\t|=========================|" << endl << endl;;
}

template<class T>
void Interface<T>::draw_parking()
{
	cout << endl << endl;
	cout << "\t\t\t\t\t\t\t\t===================================================================================" << endl;
	cout << "\t\t\t\t\t\t\t\t  |#########|     /###\\     |######\\  |##|  /##/ |##|  /###| |##|  |##| |#######|" << endl;
	cout << "\t\t\t\t\t\t\t\t  |#########|    /#####\\    |##|  |#| |##| /##/  |##| /####| |##|  |##| |#######|" << endl;
	cout << "\t\t\t\t\t\t\t\t  |##|   |##|   /##/ \\##\\   |######/  |######|   |##|/#/|##| |########| |##|  " << endl;
	cout << "\t\t\t\t\t\t\t\t  |##|   |##|  /#########\\  |##|      |##| \\##\\  |####/ |##| |##|  |##| |##|   " << endl;
	cout << "\t\t\t\t\t\t\t\t  |##|   |##| /##/     \\##\\ |##|      |##|  \\##\\ |###/  |##| |##|  |##| |##|   " << endl;
	cout << "\t\t\t\t\t\t\t\t===================================================================================" << endl << endl << endl;
}

inline void booking(Binary_tree<Client<Car>>* tree)
{
	Car obj;
	cin >> obj;
	cout << "\t\t\t\t\t\t\t\t\t\t\t\tВведите время:" << endl << endl;
	cout << "\t\t\t\t\t\t\t\t\t\t\t\t>>> ";
	double time = MyExc_Vvod::Check_double(0.99);
	cout << endl;
	int pplace = (*tree).getPlace((*tree).getRoot(), 1);
	Client<Car> client(obj, pplace, time, 0);
	client.countCost();
	cin >> client;
	(*tree).add(client, (*tree).getPlace((*tree).getRoot(), 1));
	system("CLS");
	Interface<Client<Car>>::draw_parking();
	cout << endl;
	Interface<Client<Car>>::getTicket(client);
	
}

inline void booking(Binary_tree<Client<Truck>>* tree)
{
	Truck obj;
	cin >> obj;
	cout << "\t\t\t\t\t\t\t\t\t\t\t\tВведите время:" << endl << endl;
	cout << "\t\t\t\t\t\t\t\t\t\t\t\t>>> ";
	double time = MyExc_Vvod::Check_double(0.99);
	cout << endl;
	int pplace = (*tree).getPlace((*tree).getRoot(), 1);
	Client<Truck> client(obj, pplace, time, 0);
	client.countCost();
	cin >> client;
	(*tree).add(client, (*tree).getPlace((*tree).getRoot(), 1));
	system("CLS");
	Interface<Client<Car>>::draw_parking();
	cout << endl;
	Interface<Client<Truck>>::getTicket(client);
}

inline void add_worker(Binary_tree<Worker>* tree)
{
	Worker worker;
	cin >> worker;
	system("CLS");
	Interface<Client<Car>>::draw_parking();
	(*tree).add(worker, (*tree).getPlace((*tree).getRoot(), 1));
}

inline Node<Worker>* FindSurname(Node<Worker>* tree, string surname)
{
	if (!tree)
	{
		system("CLS");
		return NULL;
	}
	if (tree->data.getSurname() == surname)
		return tree;
	if (tree->left)
		if (FindSurname(tree->left, surname))
			return FindSurname(tree->left, surname);
	if (tree->right)
		if (FindSurname(tree->right, surname))
			return FindSurname(tree->right, surname);
	return NULL;
}

inline void fire_worker(Binary_tree<Worker>* tree)
{
	cout << "\t\t\t\t\t\t\t\t\t\t\t\tВведите фамилию сотрудника:" << endl << endl;
	cout << "\t\t\t\t\t\t\t\t\t\t\t\t>>> ";
	string surname = MyExc_Vvod::Check_string(12);
	int key = 1;
	Node<Worker>* worker = FindSurname((*tree).getRoot(), surname);
	system("CLS");
	Interface<Client<Car>>::draw_parking();
	if (worker)
	{
		(*tree).deleteByKey((*tree).getRoot(), worker->key);
		cout << "\t\t\t\t\t\t\t\t\t\t\t\tВы успешно уволили сотрудника." << endl << endl;
	}
	else cout << "\t\t\t\t\t\t\t\t\t\t\t\tСотрудник с фамилией \"" << surname << "\" не существует." << endl << endl;
}

inline void picking_up(Binary_tree<Client<Car>>* tree)
{
	{
		cout << "\t\t\t\t\t\t\t\t\t\t\t\tВведите парковочное место:" << endl << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t\t\t>>> ";
		int key = MyExc_Vvod::Check_int(0,101);
		if ((*tree).CheckKey((*tree).getRoot(), key))
		{
			(*tree).deleteByKey((*tree).getRoot(), key);
			system("CLS");
			Interface<Client<Car>>::draw_parking();
			cout << "\t\t\t\t\t\t\t\t\t\t\t\tВы успешно забрали т/с." << endl << endl;
		}
		else
		{
			system("CLS");
			Interface<Client<Car>>::draw_parking();
			cout << "\t\t\t\t\t\t\t\t\t\t\t\tЭто место свободно." << endl << endl;;
		}
	}
}

inline void picking_up(Binary_tree<Client<Truck>>* tree)
{
	{
		cout << "\t\t\t\t\t\t\t\t\t\t\t\tВведите парковочное место:" << endl << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t\t\t>>> ";
		int key = MyExc_Vvod::Check_int(0,101);
		if ((*tree).CheckKey((*tree).getRoot(), key))
		{
			(*tree).deleteByKey((*tree).getRoot(), key);
			system("CLS");
			Interface<Client<Car>>::draw_parking();
			cout << "\t\t\t\t\t\t\t\t\t\t\t\tВы успешно забрали т/с." << endl << endl;
		}
		else
		{
			system("CLS");
			Interface<Client<Car>>::draw_parking();
			cout << "\t\t\t\t\t\t\t\t\t\t\t\tЭто место свободно." << endl << endl;;
		}
	}
}

inline void find_menu(Binary_tree<Client<Car>>* tree, Binary_tree<Client<Truck>>* Ttree)
{
	setlocale(LC_ALL, "Russian");
	system("CLS");
	Interface<Client<Car>>::draw_parking();
	cout << "\t\t\t\t\t\t\t\t\t\t\t\tВведите:" << endl << endl;
	cout << "\t\t\t\t\t\t\t\t\t\t\t\t[1] Автомобиль." << endl << endl;
	cout << "\t\t\t\t\t\t\t\t\t\t\t\t[2] Грузовик." << endl << endl;
	cout << "\t\t\t\t\t\t\t\t\t\t\t\t[3] Выход." << endl << endl;
	rewind(stdin);
	cout << "\t\t\t\t\t\t\t\t\t\t\t\t>>> ";
	const char ch = cin.get();
	switch (ch)
	{
	case '1':
	{
		system("CLS");
		Interface<Client<Car>>::draw_parking();
		(*tree).findByKey((*tree).getRoot());
		break;
	}
	case '2':
	{
		system("CLS");
		Interface<Client<Car>>::draw_parking();
		(*Ttree).findByKey((*Ttree).getRoot());
		break;
	}
	case '3':
		break;
	default:
		break;
	}
}

inline void info_menu(Binary_tree<Client<Car>>* tree, Binary_tree<Client<Truck>>* Ttree, int size)
{
	setlocale(LC_ALL, "Russian");
	while (true)
	{
		system("CLS");
		Interface<Client<Car>>::draw_parking();
		cout << "\t\t\t\t\t\t\t\t\t\t\t\tВведите:" << endl << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t\t\t[1] Информация о парковке." << endl << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t\t\t[2] Информация о клиентах." << endl << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t\t\t[3] Информация о клиенте." << endl << endl;
		//cout << "\t\t\t\t\t\t\t\t\t\t\t\t[4] История." << endl << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t\t\t[4] Выход." << endl << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t\t\t>>> ";
		rewind(stdin);
		const char ch = cin.get();
		cout << endl;
		switch (ch)
		{
		case '1':
		{
			system("CLS");
			Interface<Client<Car>>::draw_parking();
			cout << "\t\t\t\t\t\t\t\t\t\t\t\tСтоянка автомобилей:" << endl << endl;
			cout << "\t\t\t\t\t\t\t\t\t\t\t\tКоличество мест: " << size << endl;
			cout << "\t\t\t\t\t\t\t\t\t\t\t\tСвободных мест: " << size - (*tree).numberNode((*tree).getRoot()) << endl;
			cout << "\t\t\t\t\t\t\t\t\t\t\t\tЗанятых мест: " << (*tree).numberNode((*tree).getRoot()) << endl << endl << endl;
			cout << "\t\t\t\t\t\t\t\t\t\t\t\tСтоянка грузовиков:" << endl << endl;
			cout << "\t\t\t\t\t\t\t\t\t\t\t\tКоличество мест: " << size << endl;
			cout << "\t\t\t\t\t\t\t\t\t\t\t\tСвободных мест: " << size - (*Ttree).numberNode((*Ttree).getRoot()) << endl;
			cout << "\t\t\t\t\t\t\t\t\t\t\t\tЗанятых мест: " << (*Ttree).numberNode((*Ttree).getRoot()) << endl << endl << endl;
			cout << "\t\t\t\t\t\t\t\t\t\t\t\t";
			system("pause");
			break;
		}
		case '2':
		{
			system("CLS");
			Interface<Client<Car>>::draw_parking();
			cout << "\t\t\t\t\t\t\t\t  _______________________________________________________________________________" << endl;
			cout << "\t\t\t\t\t\t\t\t  |                           <<<СТОЯНКА АВТОМОБИЛЕЙ>>>                         |" << endl;
			cout << "\t\t\t\t\t\t\t\t  |_____________________________________________________________________________|" << endl;
			(*tree).getRoot()->data.shapka();
			cout << "\t\t\t\t\t\t\t\t  |____________|____________|____________|____________|____________|____________|" << endl;
			if ((*tree).getRoot())
			{
				(*tree).printIterUp();
				cout << "\t\t\t\t\t\t\t\t  |=============================================================================|" << endl;
			}
			else
			{
				cout << "\t\t\t\t\t\t\t\t  |                            У вас пока нет клиентов.                         |" << endl;
				cout << "\t\t\t\t\t\t\t\t  |=============================================================================|" << endl;
			}
			cout << "\t\t\t\t\t\t\t\t  _______________________________________________________________________________" << endl;
			cout << "\t\t\t\t\t\t\t\t  |                            <<<СТОЯНКА ГРУЗОВИКОВ>>>                         |" << endl;
			cout << "\t\t\t\t\t\t\t\t  |_____________________________________________________________________________|" << endl;
			(*Ttree).getRoot()->data.shapka();
			cout << "\t\t\t\t\t\t\t\t  |____________|____________|____________|____________|____________|____________|" << endl;
			if((*Ttree).getRoot())
			{
				(*Ttree).printIterUp();
				cout << "\t\t\t\t\t\t\t\t  |=============================================================================|" << endl;
			}
			else
			{
				cout << "\t\t\t\t\t\t\t\t  |                            У вас пока нет клиентов.                         |" << endl;
				cout << "\t\t\t\t\t\t\t\t  |=============================================================================|" << endl;
			}
			cout << endl << "\t\t\t\t\t\t\t\t\t\t\t";
			system("pause");
			break;
		}
		case '3':
		{
			system("CLS");
			find_menu(tree, Ttree);
			cout << endl << "\t\t\t\t\t\t\t\t\t\t\t";
			system("pause");
			break;
		}
		case '4':
			return;
		default:
			break;
		}
	}
}

inline void booking_menu(Binary_tree<Client<Car>>* tree, Binary_tree<Client<Truck>>* Ttree)
{
	setlocale(LC_ALL, "Russian");
	cout << "\t\t\t\t\t\t\t\t\t\t\t\tВведите:" << endl << endl;
	cout << "\t\t\t\t\t\t\t\t\t\t\t\t[1] Автомобиль." << endl << endl;
	cout << "\t\t\t\t\t\t\t\t\t\t\t\t[2] Грузовик." << endl << endl;
	cout << "\t\t\t\t\t\t\t\t\t\t\t\t[3] Выход." << endl << endl;
	rewind(stdin);
	cout << "\t\t\t\t\t\t\t\t\t\t\t\t>>> ";
	const char ch = cin.get();
	switch (ch)
	{
	case '1':
	{
		system("CLS");
		Interface<Client<Car>>::draw_parking();
		booking(tree);
		cout << "\t\t\t\t\t\t\t\t\t\t\t\tВы успешно забронировали место." << endl << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t\t\t";
		system("pause");
		break;
	}
	case '2':
	{
		system("CLS");
		Interface<Client<Car>>::draw_parking();
		booking(Ttree);
		cout << "\t\t\t\t\t\t\t\t\t\t\t\tВы успешно забронировали место." << endl << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t\t\t";
		system("pause");
		break;
	}
	case '3':
		break;
	default:
		break;
	}
}

inline void picking_up_menu(Binary_tree<Client<Car>>* tree, Binary_tree<Client<Truck>>* Ttree)
{
	setlocale(LC_ALL, "Russian");
	cout << "\t\t\t\t\t\t\t\t\t\t\t\tВведите:" << endl << endl;
	cout << "\t\t\t\t\t\t\t\t\t\t\t\t[1] Автомобиль." << endl << endl;
	cout << "\t\t\t\t\t\t\t\t\t\t\t\t[2] Грузовик." << endl << endl;
	cout << "\t\t\t\t\t\t\t\t\t\t\t\t[3] Выход." << endl <<endl;
	rewind(stdin);
	cout << "\t\t\t\t\t\t\t\t\t\t\t\t>>> ";
	const char ch = cin.get();
	switch (ch)
	{
	case '1':
	{
		system("CLS");
		Interface<Client<Car>>::draw_parking();
		picking_up(tree);
		cout << "\t\t\t\t\t\t\t\t\t\t\t\t";
		system("pause");
		break;
	}
	case '2':
	{
		system("CLS");
		Interface<Client<Car>>::draw_parking();
		picking_up(Ttree);
		cout << "\t\t\t\t\t\t\t\t\t\t\t\t";
		system("pause");
		break;
	}
	case '3':
		break;
	default:
		break;
	}
}

inline void show_workers(Binary_tree<Worker>* tree)
{
	cout << "\t\t\t\t\t\t\t\t\t\t_____________________________________________________" << endl;
	cout << "\t\t\t\t\t\t\t\t\t\t|               <<<СПИСОК СОТРУДНИКОВ>>>            |" << endl;
	cout << "\t\t\t\t\t\t\t\t\t\t|___________________________________________________|" << endl;
	(*tree).getRoot()->data.shapka();
	cout << "\t\t\t\t\t\t\t\t\t\t|____________|____________|____________|____________|" << endl;
	if ((*tree).getRoot())
	{
		(*tree).printIterUp();
		cout << "\t\t\t\t\t\t\t\t\t\t|===================================================|" << endl;
	}
	else
	{
		cout << "\t\t\t\t\t\t\t\t\t\t|              У вас пока нет сотрудников.          |" << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t|===================================================|" << endl;
	}
}

inline void manage_menu(Binary_tree<Worker>* tree)
{
	while(true)
	{
		setlocale(LC_ALL, "Russian");
		system("CLS");
		Interface<Client<Car>>::draw_parking();
		cout << "\t\t\t\t\t\t\t\t\t\t\t\tВведите:" << endl << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t\t\t[1] Добавить сотрудниака." << endl << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t\t\t[2] Уволить сотрудника." << endl << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t\t\t[3] Информация о сотрудниках." << endl << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t\t\t[4] Информация о сотруднике." << endl << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t\t\t[5] Редактировать." << endl << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t\t\t[6] Выход." << endl << endl;
		rewind(stdin);
		cout << "\t\t\t\t\t\t\t\t\t\t\t\t>>> ";
		const char ch = cin.get();
		switch (ch)
		{
		case '1':
		{
			system("CLS");
			Interface<Client<Car>>::draw_parking();
			add_worker(tree);
			cout << "\t\t\t\t\t\t\t\t\t\t\t\tВы успешно добавили нового сотрудника." << endl << endl;
			cout << "\t\t\t\t\t\t\t\t\t\t\t\t";
			system("pause");
			break;
		}
		case '2':
		{
			system("CLS");
			Interface<Client<Car>>::draw_parking();
			fire_worker(tree);
			cout << "\t\t\t\t\t\t\t\t\t\t\t\t";
			system("pause");
			break;
		}
		case '3':
		{
			system("CLS");
			Interface<Client<Car>>::draw_parking();			
			show_workers(tree);
			//cout << "\t\t\t\t\t\t\t\t\t\t_____________________________________________________" << endl;
			//cout << "\t\t\t\t\t\t\t\t\t\t|               <<<СПИСОК СОТРУДНИКОВ>>>            |" << endl;
			//cout << "\t\t\t\t\t\t\t\t\t\t|___________________________________________________|" << endl;
			//(*tree).getRoot()->data.shapka();
			//cout << "\t\t\t\t\t\t\t\t\t\t|____________|____________|____________|____________|" << endl;
			//if ((*tree).getRoot())
			//{
			//	(*tree).printIterUp();
			//	cout << "\t\t\t\t\t\t\t\t\t\t|===================================================|" << endl;
			//}
			//else
			//{
			//	cout << "\t\t\t\t\t\t\t\t\t\t|              У вас пока нет сотрудников.          |" << endl;
			//	cout << "\t\t\t\t\t\t\t\t\t\t|===================================================|" << endl;
			//}
			cout << endl << "\t\t\t\t\t\t\t\t\t\t\t";
			system("pause");
			break;
		}
		case  '4':
		{
			system("CLS");
			Interface<Client<Car>>::draw_parking();
			cout << "\t\t\t\t\t\t\t\t\t\t\t\tВведите фамилию сотрудника:" << endl << endl;
			cout << "\t\t\t\t\t\t\t\t\t\t\t\t>>> ";
			string surname = MyExc_Vvod::Check_string(12);
			Node<Worker>* worker = FindSurname((*tree).getRoot(), surname);
			if (worker)
			{
				system("CLS");
				Interface<Client<Car>>::draw_parking();
				cout << "\t\t\t\t\t\t\t\t\t\t_____________________________________________________" << endl;
				cout << "\t\t\t\t\t\t\t\t\t\t|             <<<ИНФОРМАЦИЯ О СОТРУДНИКЕ>>>         |" << endl;
				cout << "\t\t\t\t\t\t\t\t\t\t|___________________________________________________|" << endl;
				worker->data.shapka();
				cout << "\t\t\t\t\t\t\t\t\t\t|____________|____________|____________|____________|" << endl;
				cout << worker->data;
				cout << "\t\t\t\t\t\t\t\t\t\t|===================================================|" << endl;
				cout << endl << "\t\t\t\t\t\t\t\t\t\t\t";
				system("pause");
			}
			else
			{
				system("CLS");
				Interface<Client<Car>>::draw_parking();
				cout << "\t\t\t\t\t\t\t\t\t\t\t\tСотрудник с фамилией \"" << surname << "\" не существует." << endl << endl;
				cout << "\t\t\t\t\t\t\t\t\t\t\t\t";
				system("pause");
			}
			break;
		}
		case '5':
		{
			system("CLS"); int k = 1;
			Binary_tree<Worker> stack;
			Interface<Client<Car>>::draw_parking();
			show_workers(tree);
			cout << endl << "\t\t\t\t\t\t\t\t\t\t\t\tВведите фамилию сотрудника: " << endl << endl;
			cout << "\t\t\t\t\t\t\t\t\t\t\t\t>>> ";
			string surname = MyExc_Vvod::Check_string(12);
			Node<Worker>* worker = FindSurname((*tree).getRoot(), surname);
			int temp = worker->key;
			//stack.add(worker->data, worker->key);
			if (worker)
			{
				while (k)
				{
					system("CLS");
					Interface<Client<Car>>::draw_parking();
					show_workers(tree);
					cout << endl << "\t\t\t\t\t\t\t\t\t\t\t\tВведите:" << endl << endl;
					cout << "\t\t\t\t\t\t\t\t\t\t\t\t[1] Изменить имя." << endl << endl;
					cout << "\t\t\t\t\t\t\t\t\t\t\t\t[2] Изменить фамилию." << endl << endl;
					cout << "\t\t\t\t\t\t\t\t\t\t\t\t[3] Изменить должность." << endl << endl;
					cout << "\t\t\t\t\t\t\t\t\t\t\t\t[4] Изменить зарплату." << endl << endl;
					cout << "\t\t\t\t\t\t\t\t\t\t\t\t[5] Отменить последнее действие." << endl << endl;
					cout << "\t\t\t\t\t\t\t\t\t\t\t\t[6] Выход." << endl << endl;
					rewind(stdin);
					cout << "\t\t\t\t\t\t\t\t\t\t\t\t>>> ";
					const char ch = cin.get();
					switch (ch)
					{
					case '1':
					{
						system("CLS");
						stack.add(worker->data, stack.getPlace(stack.getRoot(),1));
						Interface<Client<Car>>::draw_parking();
						show_workers(tree);
						cout << endl << "\t\t\t\t\t\t\t\t\t\t\t\tВведите имя: " << endl << endl;
						cout << "\t\t\t\t\t\t\t\t\t\t\t\t>>> ";
						string name = MyExc_Vvod::Check_string(12);
						worker->data.setName(name);
						system("CLS");
						Interface<Client<Car>>::draw_parking();
						show_workers(tree);
						cout << endl << "\t\t\t\t\t\t\t\t\t\t\t\tВы успешно отредактировали." << endl << endl;
						cout << "\t\t\t\t\t\t\t\t\t\t\t\t";
						system("pause");
						break;
					}
					case '2':
					{
						system("CLS");
						stack.add(worker->data, stack.getPlace(stack.getRoot(), 1));
						Interface<Client<Car>>::draw_parking();
						show_workers(tree);
						cout << endl << "\t\t\t\t\t\t\t\t\t\t\t\tВведите фамилию: " << endl << endl;
						cout << "\t\t\t\t\t\t\t\t\t\t\t\t>>> ";
						string surname = MyExc_Vvod::Check_string(12);
						worker->data.setSurname(surname);
						system("CLS");
						Interface<Client<Car>>::draw_parking();
						show_workers(tree);
						cout << endl << "\t\t\t\t\t\t\t\t\t\t\t\tВы успешно отредактировали." << endl << endl;
						cout << "\t\t\t\t\t\t\t\t\t\t\t\t";
						system("pause");
						break;
					}
					case '3':
					{
						system("CLS");
						stack.add(worker->data, stack.getPlace(stack.getRoot(), 1));
						Interface<Client<Car>>::draw_parking();
						show_workers(tree);
						cout << endl << "\t\t\t\t\t\t\t\t\t\t\t\tВведите должность:" << endl << endl;
						cout << "\t\t\t\t\t\t\t\t\t\t\t\t>>> ";
						string position = MyExc_Vvod::Check_string(12);
						worker->data.setPosition(position);
						system("CLS");
						Interface<Client<Car>>::draw_parking();
						show_workers(tree);
						cout << endl << "\t\t\t\t\t\t\t\t\t\t\t\tВы успешно отредактировали." << endl << endl;
						cout << "\t\t\t\t\t\t\t\t\t\t\t\t";
						system("pause");
						break;
					}
					case '4':
					{
						system("CLS");
						stack.add(worker->data, stack.getPlace(stack.getRoot(), 1));
						Interface<Client<Car>>::draw_parking();
						show_workers(tree);
						cout << endl << "\t\t\t\t\t\t\t\t\t\t\t\tВведите зарплату:" << endl << endl;
						cout << "\t\t\t\t\t\t\t\t\t\t\t\t>>> ";
						double salary = MyExc_Vvod::Check_double(0.99);
						worker->data.setSalary(salary);
						system("CLS");
						Interface<Client<Car>>::draw_parking();
						show_workers(tree);
						cout << endl <<"\t\t\t\t\t\t\t\t\t\t\t\tВы успешно отредактировали." << endl << endl;
						cout << "\t\t\t\t\t\t\t\t\t\t\t\t";
						system("pause");
						break;
					}
					case '5':
					{
						Binary_tree<Worker>::TreeIterator it;
						it = stack.End();
						if (!it.mem)
						{
							system("CLS");
							Interface<Client<Car>>::draw_parking();
							show_workers(tree);
							cout << endl << "\t\t\t\t\t\t\t\t\t\t\t\tВы пока ничего не изменили." << endl << endl;
							cout << "\t\t\t\t\t\t\t\t\t\t\t\t";
							system("pause");
							break;
						}
						(*tree).deleteByKey((*tree).getRoot(), temp);
						(*tree).add(it.mem->data, temp);
						stack.deleteByKey(stack.getRoot(), it.mem->key);
						system("ClS");
						Interface<Client<Car>>::draw_parking();
						show_workers(tree);
						cout << endl << "\t\t\t\t\t\t\t\t\t\t\t\tПоследнее действие успешно отменено." << endl << endl;
						cout << "\t\t\t\t\t\t\t\t\t\t\t\t";
						system("pause");
						break;
					}
					case '6':
						k = 0;
						break;
					default:
						break;
					}
				}
			}
			else
			{
				system("CLS");
				Interface<Client<Car>>::draw_parking();
				cout << "\t\t\t\t\t\t\t\t\t\t\t\tСотрудник с фамилией \"" << surname << "\" не существует." << endl << endl;
				cout << "\t\t\t\t\t\t\t\t\t\t\t\t";
				system("pause");
			}
			break;
		}
		case '6':
			return;
		}
	}
}

inline Client<Car> get_client(Binary_tree<Client<Car>>* tree)
{
	Client<Car> client = (*tree).getRoot()->data;
	(*tree).deleteByKey((*tree).getRoot(), (*tree).getRoot()->key);
	return client;
}

inline Client<Truck> get_client(Binary_tree<Client<Truck>>* tree)
{
	Client<Truck> client = (*tree).getRoot()->data;
	(*tree).deleteByKey((*tree).getRoot(), (*tree).getRoot()->key);
	return client;
}

inline Worker get_worker(Binary_tree<Worker>* tree)
{
	Worker worker = (*tree).getRoot()->data;
	(*tree).deleteByKey((*tree).getRoot(), (*tree).getRoot()->key);
	return worker;
}

inline Binary_tree<Client<Car>> read_client(string path)
{
	Binary_tree <Client<Car>> tree;
	ifstream fin;
	fin.open(path);
	Client<Car> client;

	if (!fin.is_open())
	{
		cout << "Error open" << endl;
	}
	else
	{
		cout << "Open" << endl;
		while (fin.read((char*)&client, sizeof(Client<Car>)))
		{
			tree.add(client, client.getPplace());
		}
		//delete &client;
	}
	fin.close();
	return tree;
}

template<class T>
void Interface<T>::menu()
{
	setlocale(LC_ALL, "Russian");
	string path_Cclient = "CClient.dat";
	string path_Tclient = "TClient.dat";
	string path_worker = "Worker.dat";

	Binary_tree<Client<Truck>> tree_Tclient;
	Binary_tree<Client<Car>> tree_client;// = read_client(path_client);;
	Binary_tree<Worker> tree_worker;

	ifstream fin;
	fin.open(path_Cclient);
	Client<Car> client;
	if (!fin.is_open())
	{
		cout << "Error open" << endl;
	}
	else
	{
		while (fin.read((char*)&client, sizeof(Client<Car>)))
		{
			tree_client.add(client, client.getPplace());
		}
	}
	fin.close();
	fstream clear_file(path_Cclient, ios::out);
	clear_file.close();

	fin.open(path_worker);
	Worker worker;
	if (!fin.is_open())
	{
		cout << "Error open" << endl;
	}
	else
	{
		while (fin.read((char*)&worker, sizeof(Worker)))
		{
			tree_worker.add(worker, tree_worker.getPlace(tree_worker.getRoot(), 1));
		}
	}
	fin.close();
	fstream clear_file1(path_worker, ios::out);
	clear_file1.close();

	fin.open(path_Tclient);
	Client<Truck> Tclient;
	if (!fin.is_open())
	{
		cout << "Error open" << endl;
	}
	else
	{
		while (fin.read((char*)&Tclient, sizeof(Client<Truck>)))
		{
			tree_Tclient.add(Tclient, Tclient.getPplace());
		}
	}
	fin.close();
	fstream clear_file2(path_Tclient, ios::out);
	clear_file2.close();

	int size = 100, k = 1;
	while (k)
	{
		system("CLS");
		draw_parking();
		cout << "\t\t\t\t\t\t\t\t\t\t\t\tВведите:" << endl << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t\t\t[1] Забронировать." << endl << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t\t\t[2] Забрать т/с." << endl << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t\t\t[3] Информация." << endl << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t\t\t[4] Управление сотрудниками." << endl << endl;
		cout << "\t\t\t\t\t\t\t\t\t\t\t\t[5] Выход." << endl << endl;
		rewind(stdin);
		cout << "\t\t\t\t\t\t\t\t\t\t\t\t>>> ";
		const char ch = cin.get();
		switch (ch)
		{
		case '1':
		{
			system("CLS");
			Interface<Client<Car>>::draw_parking();
			booking_menu(&tree_client, &tree_Tclient);
			break;
		}
		case '2':
		{
			system("CLS");
			Interface<Client<Car>>::draw_parking();
			picking_up_menu(&tree_client, &tree_Tclient);
			break;
		}
		case '3':
		{
			info_menu(&tree_client, &tree_Tclient, size);
			break;
		}
		case '4':
		{
			manage_menu(&tree_worker);
			break;
		}
		case '5':
			system("CLS");
			k = 0;
			break;
		default:
			break;
		}
	}

	ofstream fout;
	fout.open(path_Cclient, ofstream::app);
	if (!fout.is_open())
	{
		cout << "Error open" << endl;
	}
	else
	{
		while (tree_client.numberNode(tree_client.getRoot()))
		{
			client = get_client(&tree_client);
			fout.write((char*)&client, sizeof(Client<Car>));
		}
	}
	fout.close();

	fout.open(path_worker, ofstream::app);
	if (!fout.is_open())
	{
		cout << "Error open" << endl;
	}
	else
	{
		Binary_tree<Worker>::TreeIterator it;
		for (it = tree_worker.Begin(); it != tree_worker.End(); it++)
		{
			worker = *it;
			fout.write((char*)&worker, sizeof(Worker));
		}
		worker = *it;
		fout.write((char*)&worker, sizeof(Worker));
		//while (tree_worker.numberNode(tree_worker.getRoot()))
		//{
		//	worker = get_worker(&tree_worker);
		//	fout.write((char*)&worker, sizeof(Worker));
		//}
	}
	fout.close();

	fout.open(path_Tclient, ofstream::app);
	if (!fout.is_open())
	{
		cout << "Error open" << endl;
	}
	else
	{
		while (tree_Tclient.numberNode(tree_Tclient.getRoot()))
		{
			Tclient = get_client(&tree_Tclient);
			fout.write((char*)&Tclient, sizeof(Client<Truck>));
		}
	}
	fout.close();

	while (true)
	{
		system("CLS");
		draw_parking();
		cout << endl << endl << endl << endl << endl << endl << endl <<"\t\t\t\t\t\t\t\t\t\t\tНажмите крестик [X] чтобы закрыть программу." << endl << endl;
		cout << endl << "\t\t\t\t\t\t\t\t\t\t\t";
		system("pause");
	}
}
