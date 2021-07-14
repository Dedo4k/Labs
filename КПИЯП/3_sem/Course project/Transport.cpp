#include "Transport.h"
#include "Interface.h"

Transport::Transport()
{
	number = 0;
	//cout << endl << "Transport constructor" << endl;
}

Transport::~Transport()
{
	//cout << endl << "Transport destructor" << endl;
}

void Transport::setNumber(int number)
{
	this->number = number;
}

int Transport::getNumber()
{
	return number;
}

istream& operator>>(istream& in, Transport& transport)
{
	system("CLS");
	Interface<Client<Car>>::draw_parking();
	cout << "\t\t\t\t\t\t\t\t\t\t\t\t¬ведите номер т/с:" << endl << endl;
	cout << "\t\t\t\t\t\t\t\t\t\t\t\t>>> ";
	transport.number = MyExc_Vvod::Check_int(1000,9999);
	cout << endl;
	return in;
}

ostream& operator<<(ostream& out, const Transport& transport)
{
	out << "|" << setw(12) << transport.number;
	return out;
}
