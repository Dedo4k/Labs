#pragma once
#include "MyExc.h"

class MyExc_Vvod : public MyExc
{
private:
	int code;
public:
	MyExc_Vvod(int code);
	~MyExc_Vvod();
	int getCode();
	static string Check_string(int length);
	static int Check_int();
	string what() override;
};