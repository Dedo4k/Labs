#pragma once
#include "MyExc.h"

class MyExc_Vvod : public MyExc
{
private:
	int code;
public:
	MyExc_Vvod(int code);
	MyExc_Vvod(int min, int max);
	~MyExc_Vvod();
	int getCode();
	static string Check_string(int length);
	static int Check_int(int min, int max);
	static double Check_double(const double length);
	string what() override;
};