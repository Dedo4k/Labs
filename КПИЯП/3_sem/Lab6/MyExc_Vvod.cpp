#include "MyExc_Vvod.h"

MyExc_Vvod::MyExc_Vvod(int code)
{
	this->code = code;
	switch (code)
	{
	case 1:
		MyExc::setMessage("wrong length");
		break;
	case 2:
		MyExc::setMessage("not integer input");
		break;
	case 3:
		MyExc::setMessage("not string input");
		break;
	case 4:
		MyExc::setMessage("empty string");
	default:
		break;
	}
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
				if (str[i] < 'A' || str[i]>'z')
					throw MyExc_Vvod(3);
			}		
		}
		catch (MyExc_Vvod& ex)
		{
			cin.clear();
			rewind stdin;
			cout << endl << "#" << ex.getCode() << " | " << ex.what() << endl << endl;
			fl = 1;
		}
		catch (...)
		{
			cin.clear();
			rewind stdin;
			cout << endl << "Unknown Error" << endl << endl;
			fl = 1;
		}
	} while (fl);

	return str;
}

int MyExc_Vvod::Check_int()
{
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
		}
		catch (MyExc_Vvod& ex)
		{
			cin.clear();
			rewind stdin;
			cout << endl << "#" << ex.getCode() << " | " << ex.what() << endl << endl;
			fl = 1;
		}
		catch (...)
		{
			cin.clear();
			rewind stdin;
			cout << endl << "Unknown Error" << endl << endl;
			fl = 1;
		}
	} while (fl);
	return input;
}

string MyExc_Vvod::what()
{
	return getMessage();
}
