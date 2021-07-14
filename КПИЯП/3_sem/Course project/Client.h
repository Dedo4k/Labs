#pragma once
#include "Person.h"

template<class T>
class Client :  public Person
{
private:
	T vehicle;
	int pplace;
	double time;
	double cost;
public:
	Client();
	Client(T obj, int pplace, double time, double cost);
	~Client();
	void countCost();
	void shapka();
	int getPplace();
	double getTime();
	double getCost();
	T getVehicle();
	void setPplace(int pplace);
	void setTime(double time);
	void setCost(double cost);
	void setVehicle(T vehicle);
	//friend istream& operator>><T>(istream& in, Client<T>& client);
	friend ostream& operator<<<T>(ostream& out, Client<T>& client);
};

