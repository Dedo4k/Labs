#include<ctime>
#include <iostream>
#include <chrono>
#include "Timer.h"
const int m = 16;
const int n = 16;
using namespace std;

int main()
{
    Timer t;
    int a[n][m], b[n][m], c[n][m], i, j;
    cout << "matrica a:\n";
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
        {
            a[i][j] = rand()%100;
            cout << a[i][j] << '\t';
        }
        cout << endl;
    }
    cout << "\nmatrica b:\n";
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
        {
            b[i][j] = rand()%100;
            cout << b[i][j] << '\t';
        }
        cout << endl;
    }
    cout << endl;
    cout << "a-b=\n";
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
        {
            c[i][j] = a[i][j] - b[i][j];
            cout << c[i][j] << '\t';
        }
        cout << endl;
    }
    cout << "time - " << t.elapsed() << endl;
    return 0;
}