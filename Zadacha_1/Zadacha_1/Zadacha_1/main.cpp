#include <iostream>
#include "DynamicIntArray.h"
#include <vector>
using namespace std;

int main()
{
    setlocale(LC_ALL, "Russian");

    DynamicIntArray arr(5);
    cin >> arr;
    cout << arr << endl << endl;

    arr.resize(3);
    cout << arr << endl << endl;

    arr.resize(8);
    cout << arr << endl << endl;

    DynamicIntArray m1(5, 5); //{5,5,5,5,5}
    cout << "m1: " << m1 << endl << endl;
    DynamicIntArray m2(3, 3); //{3,3,3}
    cout << "m2: " << m2 << endl << endl;
    cout << "m1 + m2: " << m1 + m2 << endl << endl;

    cout << "КОНСТРУКТОР И ОПЕРАТОР КОПИРОВАНИЯ: " << endl;
    DynamicIntArray copy = arr; // срабатывает конструктор копирования
    cout << "arr: " << arr << endl << endl;
    cout << "copy(конструктор копирования от arr): " << copy << endl << endl;
    copy = m1 + m2; // срабатывает оператор копирования
    cout << "copy(оператор копирования от m1 + m2): " << copy << endl << endl;
    arr[1] = 8;
    cout << "arr: " << arr << endl << endl;
    cout << "copy(изменили arr, copy не меняли): " << copy << endl << endl;

    
    cout << "КОНСТРУКТОР И ОПЕРАТОР ПЕРЕМЕЩЕНИЯ: " << endl;
    cout << "arr: " << arr << endl << endl;
    DynamicIntArray move0 = std::move(arr); // срабатывает конструктор перемещения
    cout << "move0(конструктор перемещения на arr): " << move0 << endl << endl;
    cout << "arr: " << arr << endl << endl;
    arr = m1 + m2;
    cout << "arr = m1 + m2: " << arr << endl << endl;
    cout << "move0(изменили arr): " << move0 << endl << endl;
    move0 = std::move(arr);
    cout << "move0(оператор перемещения на arr): " << move0 << endl << endl;


    if (m1 < m2) cout << "\nm1<m2\n";
    else if (m1 > m2) cout << "\nm1>m2\n";


    if (m1 <= m2) cout << "\nm1<=m2\n";
    else if (m1 >= m2) cout << "\nm1>=m2\n";


    try { if (m1 == m2) cout << "\nm1==m2\n"; }
    catch (const char* msg) { cout << msg << endl; }


    try { if (m1 != m2) cout << "\nm1!=m2\n"; }
    catch (const char* msg) { cout << msg << endl; }
}