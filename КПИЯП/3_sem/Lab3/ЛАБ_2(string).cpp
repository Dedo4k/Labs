#include <iostream>
#include <cstring>
#include "String.h"
using namespace std;

int main()
{
	String s1("Hello");
	s1.Show();
	String s2("World!");
	s2.Show();
	String s3;
	s3 = s1 + s2;
	s3.Show();
	int a = s3 - s1;
	cout << a << endl;
	cout << (s1 == s2) << endl;
	cout << (s1 != s2) << endl;
	if (s1 == s2)
		cout << "true\n";
	else
		cout << "false\n";
	if (s1 != s2)
		cout << "true\n";
	else
		cout << "false\n";
	cout << s1[0] << endl;
	s2[2] = 'Z';
	s2.Show();
	cout << (s1 > s2) << endl;
	if (s1 > s2)
		cout << "true\n";
	else
		cout << "false\n";
	cout << (s1 < s2) << endl;
	if (s1 < s2)
		cout << "true\n";
	else
		cout << "false\n";
	s1 += s2;
	s1.Show();
	s3 = s1(1, 5);
	s3.Show();
	s3 = s1 + "glass"+ s1;
	s3.Show();
	s3 = s3 + s2 + s1 + "_string_" + s1 += s2 + "VladLailo" + s2 += s2;
	s3.Show();
	s3 = "vanya" + s2 + s1;
	s3.Show();
}