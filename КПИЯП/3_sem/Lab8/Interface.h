#pragma once
#include <iostream>
#include "Binary_tree.h"
#include "Binary_tree.cpp"
#include "Monoblock.h"
#include "MPhone.h"
#include "Notebook.h"
#include "Server.h"
#include "Binary_tree.h"

template <class TYPE> class Interface
{
private:
	TYPE obj;
public:
	Interface();
	~Interface();
	void menu();
	static void interf();
};