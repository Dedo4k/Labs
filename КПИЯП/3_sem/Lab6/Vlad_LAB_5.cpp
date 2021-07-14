#include "Monoblock.h"
#include "Server.h"
#include "MPhone.h"
#include "Notebook.h"
#include "MyExc.h"

int main()
{
	Monoblock m1;
	cin >> m1;
	m1.shapka();
	cout << m1;

	Server s1;
	cin >> s1;
	s1.shapka();
	cout << s1;

	MPhone p1;
	cin >> p1;
	p1.shapka();
	cout << p1;

	Notebook n1;
	cin >> n1;
	n1.shapka();
	cout << n1;
}