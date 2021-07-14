#include "MyExc_Vvod.h"
#include <locale.h>
#include <windows.h>
#include <cstdlib>
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable : 4996)

MyExc_Vvod::MyExc_Vvod(int code)
{
	setlocale(LC_ALL, "Russian");
	this->code = code;
	switch (code)
	{
	case 1:
		MyExc::setMessage("�� ����� ������� ������� �����, ���������� ����� 12 ��������.");
		break;
	case 2:
		MyExc::setMessage("�� ����� ������������ ������, ��������� ������� ������ ����� 0-9.");
		break;
	case 3:
		MyExc::setMessage("�� ����� ������������ ������, ��������� ������� ������ ����� �-�.");
		break;
	case 4:
		MyExc::setMessage("�� ����� ������ ������.");
	case 5:
		MyExc::setMessage("�� ����� ������������ ������ �����, ��������� ������� 2 ����� ����� �����.");
	case 6:
		MyExc::setMessage("�� ����� ������������ ������, ��������� ������� ������ \".\" � ����� 0-9.");
		break;
	default:
		break;
	}
}

MyExc_Vvod::MyExc_Vvod(int min, int max)
{
	this->code = 5;
	char strMin[5] = "";
	itoa(min,strMin,10);
	char strMax[10];
	itoa(max, strMax, 10);
	string text = "�� ����� ������������ ������ �����, ����� ������ ���� " + string(strMin) +"<=N<="+string(strMax)+".";
	MyExc::setMessage(text);
}

MyExc_Vvod::~MyExc_Vvod()
{
	//cout << "MyEc_Vvod" << endl;
}

int MyExc_Vvod::getCode()
{
	return code;
}

string MyExc_Vvod::Check_string(int length)
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	bool fl;
	string str;
	do
	{
		fl = 0;
		try
		{
			cin >> str;
			if (str.empty())
				throw MyExc_Vvod(4);

			if (str.length() > length)
				throw MyExc_Vvod(1);

			for (int i = 0; i < str.length(); i++)
			{
				if (str[i] < '�' || str[i]>'�')
					throw MyExc_Vvod(3);
			}		
		}
		catch (MyExc_Vvod& ex)
		{
			cin.clear();
			rewind stdin;
			cout << endl << "\t\t\t\t\t\t\t\t\t\t\t\t#" << ex.getCode() << " | " << ex.what() << endl << endl;
			fl = 1;
			cout << "\t\t\t\t\t\t\t\t\t\t\t\t>>> ";
		}
		catch (...)
		{
			cin.clear();
			rewind stdin;
			cout << endl << "\t\t\t\t\t\t\t\t\t\t\tUnknown Error" << endl << endl;
			fl = 1;
		}
	} while (fl);

	return str;
}

int MyExc_Vvod::Check_int(int min, int max)
{
	setlocale(LC_ALL, "Russian");
	bool fl;
	int input;
	do
	{
		fl = 0;
		try
		{
			cin >> input;
			if (cin.fail() || cin.get()!='\n')
				throw MyExc_Vvod(2);
			if (input < min || input > max)
				throw MyExc_Vvod(min, max);
		}
		catch (MyExc_Vvod& ex)
		{
			cin.clear();
			rewind stdin;
			cout << endl << "\t\t\t\t\t\t\t\t\t\t\t\t#" << ex.getCode() << " | " << ex.what() << endl << endl;
			fl = 1;
			cout << "\t\t\t\t\t\t\t\t\t\t\t\t>>> ";
		}
		catch (...)
		{
			cin.clear();
			rewind stdin;
			cout << endl << "\t\t\t\t\t\t\t\t\t\t\t\tUnknown Error" << endl << endl;
			fl = 1;
		}
	} while (fl);
	return input;
}

double MyExc_Vvod::Check_double(const double length)
{
	setlocale(LC_ALL, "Russian");
	bool fl;
	double input;
	do
	{
		fl = 0;
		try
		{
			cin >> input;
			if (cin.fail() || cin.get() != '\n')
				throw MyExc_Vvod(6);
			if ((input - (int)input) > length)
				throw MyExc_Vvod(5);
		}
		catch (MyExc_Vvod& ex)
		{
			cin.clear();
			rewind stdin;
			cout << endl << "\t\t\t\t\t\t\t\t\t\t\t\t#" << ex.getCode() << " | " << ex.what() << endl << endl;
			fl = 1;
			cout << "\t\t\t\t\t\t\t\t\t\t\t\t>>> ";
		}
		catch (...)
		{
			cin.clear();
			rewind stdin;
			cout << endl << "\t\t\t\t\t\t\t\t\t\t\t\tUnknown Error" << endl << endl;
			fl = 1;
		}
	} while (fl);
	return input;
}

string MyExc_Vvod::what()
{
	return getMessage();
}
