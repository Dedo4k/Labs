#include "Client.h"
#include "Car.h"
#include "Truck.h"

template<class T>
Client<T>::Client()
{
	this->pplace = 0;
	this->vehicle = T();
	this->cost = 0;
	this->time = 0;
}

template<class T>
Client<T>::Client(T obj, int pplace, double time , double cost)
{
	this->pplace = pplace;
	this->vehicle = obj;
	this->cost = cost;
	this->time = time;
}

template<class T>
Client<T>::~Client()
{
	//cout << "Client destructor" << endl;
}

template<class T>
void Client<T>::countCost()
{
	if (this->getVehicle().getType() == "car")
	{
		if (time <= 2.0)
			cost = 2.0;
		else cost = 2 + (time - 2) * 0.5;
	}
	else
	{
		if (time <= 2.0)
			cost = 5.0;
		else cost = 5 + (time - 2) * 1.5;
	}
}

template<class T>
void Client<T>::shapka()
{
	cout << "\t\t\t\t\t\t\t\t  |" << setw(12) << "№ Места  " << "|" << setw(12) << "Номер т/с " << "|" << setw(12) << "Тип    " << "|" << setw(12) << "Имя    " << "|" << setw(12) << "Время   " << "|" << setw(12) << "Цена    " << "|" << endl;
}

template<class T>
int Client<T>::getPplace()
{
	return pplace;
}

template<class T>
double Client<T>::getTime()
{
	return time;
}

template<class T>
double Client<T>::getCost()
{
	return cost;
}

template<class T>
T Client<T>::getVehicle()
{
	return vehicle;
}

template<class T>
void Client<T>::setPplace(int pplace)
{
	this->pplace = pplace;
}

template<class T>
void Client<T>::setTime(double time)
{
	this->time = time;
}

template<class T>
void Client<T>::setCost(double cost)
{
	this->cost = cost;
}

template<class T>
void Client<T>::setVehicle(T vehicle)
{
	this->vehicle = vehicle;
}

template<class T>
class Client;

//template<class T>
//istream& operator>>(istream& in, Client<T>& client)
//{
//	//in >> *(dynamic_cast<Person*>(client));
//	client.pplace = MyExc_Vvod::Check_int();
//	return in;
//}

template<class T>
ostream& operator<<(ostream& out, Client<T>& client)
{
	cout << "\t\t\t\t\t\t\t\t  |" << setw(12) << client.pplace << client.vehicle << "|" << setw(12) << client.getName() << "|" << setw(12) << client.time << "|" << setw(12) << setprecision(4) << client.cost << "|" << endl;
	return out;
}
