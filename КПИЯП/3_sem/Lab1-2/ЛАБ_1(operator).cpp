#include <iostream>
#include "Array.h"
using namespace std;

int main()
{
    int size;
    cout << "enter size of the first array: ";
    cin >> size;
    Array A(size);
    A.add();
    cout << endl << "first array:" << endl;
    A.show();
    cout << endl << endl << "enter size of the second array: ";
    cin >> size;
    Array B(size);
    B.add();
    cout << endl << "second array:" << endl;
    B.show();
    Array C;
    C = A & B & A & B & A & B;
    C.show();
    C = A.crossing(B);
    cout << endl << endl << "array after crossing:" << endl;
    C.show();
}
