#include <iostream>
#include "DynamicIntArray.h"
using namespace std;

//КОНСТРУКТОРЫ:
// 
//по умолчанию (создает массив некоторой длины по умолчанию)

DynamicIntArray::DynamicIntArray() {
    SIZE = NULL;
    numbers = nullptr;
}
//по размеру (элементы инициализируются 0)
DynamicIntArray::DynamicIntArray(int SIZE) {
    this->SIZE = SIZE;
    this->numbers = new int[this->SIZE];
    for (int i = 0; i < SIZE; i++) {
        numbers[i] = 0;
    }
}

//по размеру и числу n (элементы инициализируются числом n)
DynamicIntArray::DynamicIntArray(int SIZE, int n) {
    this->SIZE = SIZE;
    this->numbers = new int[this->SIZE];
    for (int i = 0; i < SIZE; i++) {
        numbers[i] = n;
    }
}

//копирования
DynamicIntArray::DynamicIntArray(DynamicIntArray& arr) {
    SIZE = arr.SIZE;
    numbers = new int[SIZE];

    for (int i = 0; i < SIZE; i++)
        numbers[i] = arr.numbers[i];
}

//оператор копирования 
DynamicIntArray& DynamicIntArray::operator=(DynamicIntArray& arr)
{
    if (&arr == this) return *this; // проверка, нет ли присваивания самому себе

    if (SIZE > 0) {
        delete[] numbers; // освобождение памяти под массив numbers
        SIZE = 0;
    }

    SIZE = arr.SIZE;
    numbers = new int[SIZE];

    for (int i = 0; i < SIZE; i++)
        numbers[i] = arr.numbers[i];
    return *this;
}

//перемещения
DynamicIntArray::DynamicIntArray(DynamicIntArray&& arr) noexcept {
    numbers = arr.numbers; //перенаправляем numbers на arr.numbers и меняем SIZE
    SIZE = arr.SIZE;
    arr.SIZE = 0; // Занулить кол-во элементов в исходном массиве, чтобы избежать лишнего 
                  // освобождения памяти в деструкторе
}

//оператор перемещения
DynamicIntArray& DynamicIntArray::operator=(DynamicIntArray&& arr) noexcept {
    if (&arr == this) return *this; // проверка, нет ли присваивания самому себе

    if (SIZE > 0) {
        delete[] numbers; // освобождение памяти под массив numbers
        SIZE = 0;
    }

    SIZE = arr.SIZE; // присваиваем другое кол-во эл-тов
    numbers = arr.numbers; // перенаправляем указатель numbers на arr.numbers

    arr.SIZE = 0; // зануляем arr.SIZE чтобы избежать двойного освобождения 
                  // одного и того же участка памяти

    return *this;
}

//ДЕСТРУКТОР
DynamicIntArray::~DynamicIntArray()
{
    if (SIZE > 0) {
        delete[] numbers;
        SIZE = 0;
    }
}

//доступ к элементу (оператор [])
int& DynamicIntArray::operator[](int i)
{
    return numbers[i];
}

//длина массива
int DynamicIntArray::length()
{
    return SIZE;
}

/*изменение размера (массив пересоздается, элементы копируются на новое место,
старый массив разрушается; если новый размер меньше старого, не поместившаяся часть
элементов теряется, если новый размер больше – добавляются элементы 0)*/
void DynamicIntArray::resize(int newSIZE) {
    //сохраняем предыдущий массив в copy
    int* copy = new int[SIZE];
    for (int i = 0; i < SIZE; i++) {
        copy[i] = numbers[i];
    }
    int copySIZE = SIZE;

    //удаляем старый массив
    if (SIZE > 0) {
        delete[] numbers;
        SIZE = 0;
    }

    SIZE = newSIZE;
    numbers = new int[SIZE];

    if (newSIZE <= copySIZE) {
        for (int i = 0; i < newSIZE; i++) {
            numbers[i] = copy[i];
        }
    }
    else {
        for (int i = 0; i < copySIZE; i++) {
            numbers[i] = copy[i];
        }
        for (int i = copySIZE; i < newSIZE; i++) {
            numbers[i] = 0;
        }
    }

    delete[] copy;
}

bool operator==(DynamicIntArray& arr1, DynamicIntArray& arr2)
{
    int c = 0;
    if (arr1.SIZE == arr2.SIZE) {
        for (int i = 0; i < arr1.SIZE; i++) {
            if (arr1.numbers[i] == arr2.numbers[i]) c++;
        }
        if (c == arr1.SIZE) return true;
        else return false;
    }
    else throw "\nSizes are not the same!\n";
}
bool operator!=(DynamicIntArray& arr1, DynamicIntArray& arr2)
{
    return (!(arr1 == arr2));
}
bool operator<(DynamicIntArray& arr1, DynamicIntArray& arr2)
{
    int k;
    int flag = 0;
    if (arr1.SIZE <= arr2.SIZE) k = arr1.SIZE;
    else k = arr2.SIZE;

    for (int i = 0; i < k; i++) {
        if (arr1.numbers[i] < arr2.numbers[i]) {}
        else flag++;
    }

    if (flag == 0) return true;
    else return false;
}
bool operator>(DynamicIntArray& arr1, DynamicIntArray& arr2)
{
    int k;
    int flag = 0;
    if (arr1.SIZE <= arr2.SIZE) k = arr1.SIZE;
    else k = arr2.SIZE;

    for (int i = 0; i < k; i++) {
        if (arr1.numbers[i] > arr2.numbers[i]) {}
        else flag++;
    }

    if (flag == 0) return true;
    else return false;
}
bool operator<=(DynamicIntArray& arr1, DynamicIntArray& arr2)
{
    return (!(arr1 > arr2));
}
bool operator>=(DynamicIntArray& arr1, DynamicIntArray& arr2)
{
    return (!(arr1 < arr2));
}

/*- оператор + (конкатенация массивов, m1 + m2 – это новый массив,
в котором сперва идут элементы m1, а затем – m2)*/
DynamicIntArray operator+(DynamicIntArray& m1, DynamicIntArray& m2)
{
    int newSIZE = m1.length() + m2.length();

    DynamicIntArray arr(newSIZE);

    for (int i = 0; i < m1.length(); i++) {
        arr.numbers[i] = m1.numbers[i];
    }
    for (int i = 0; i < m2.length(); i++) {
        arr.numbers[m1.length() + i] = m2.numbers[i];
    }
    return arr;
}

std::istream& operator>>(std::istream& in, DynamicIntArray& arr)
{
    for (int i = 0; i < arr.SIZE; i++) {
        in >> arr.numbers[i];
    }

    return in;
}
std::ostream& operator<<(std::ostream& out, const DynamicIntArray& arr)
{
    for (int i = 0; i < arr.SIZE; i++) {
        out << arr.numbers[i] << "  ";
    }
    return out;
}
