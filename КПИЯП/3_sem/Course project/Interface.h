#pragma once
#include <iomanip>
#include "Binary_tree.h"
#include "Client.h"
#include "Car.h"
using namespace std;

template<class T>
class Interface
{
public:
	static void menu();
	static void getTicket(T client);
	static void draw_parking();
};