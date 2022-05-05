#include <iostream>
using namespace std;

class DynamicIntArray {
private:
    int* numbers;    //массив
    int SIZE;        //длина массива

public:
    //КОНСТРУКТОРЫ:
    // 
    //по умолчанию (создает массив некоторой длины по умолчанию)
    DynamicIntArray() {
        SIZE = NULL;
        numbers = nullptr;
    }

    //по размеру (элементы инициализируются 0)
    DynamicIntArray(int SIZE) {
        this->SIZE = SIZE;
        this->numbers = new int[this->SIZE];
        for (int i = 0; i < SIZE; i++) {
            numbers[i] = 0;
        }
    }

    //по размеру и числу n (элементы инициализируются числом n)
    DynamicIntArray(int SIZE, int n) {
        this->SIZE = SIZE;
        this->numbers = new int[this->SIZE];
        for (int i = 0; i < SIZE; i++) {
            numbers[i] = n;
        }
    }

    //копирования
    DynamicIntArray(DynamicIntArray& arr) {
        SIZE = arr.SIZE;
        numbers = new int[SIZE];

        for (int i = 0; i < SIZE; i++)
            numbers[i] = arr.numbers[i];
    }

    //оператор копирования 
    DynamicIntArray& operator=(DynamicIntArray& arr)
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
    DynamicIntArray(DynamicIntArray&& arr) noexcept {
        numbers = arr.numbers; //перенаправляем numbers на arr.numbers и меняем SIZE
        SIZE = arr.SIZE;
        arr.SIZE = 0; // Занулить кол-во элементов в исходном массиве, чтобы избежать лишнего 
                      // освобождения памяти в деструкторе
    }

    //оператор перемещения
    DynamicIntArray& operator=(DynamicIntArray&& arr) noexcept{
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
    ~DynamicIntArray() {
        if (SIZE > 0) {
            delete[] numbers;
            SIZE = 0;
        }
    }

    //доступ к элементу (оператор [])
    int& operator[] (int i) {
        return numbers[i];
    }

    //длина массива
    int getSizeOfArray() {
        return SIZE;
    }

    /*изменение размера (массив пересоздается, элементы копируются на новое место, 
    старый массив разрушается; если новый размер меньше старого, не поместившаяся часть 
    элементов теряется, если новый размер больше – добавляются элементы 0)*/
    void resize(int newSIZE) {

        int oldSIZE = SIZE;
        DynamicIntArray oldArr(newSIZE);
        for (int i = 0; i < newSIZE; i++) {
            oldArr[i] = numbers[i];
        }
        

        if (SIZE > 0) { // удаляем старый массив numbers
            delete[] numbers;
            SIZE = oldSIZE;
        }

        if (newSIZE <= oldSIZE) {
            for (int i = 0; i < SIZE; i++) {
                numbers[i] = oldArr[i];
            }
            
        }
        delete[] oldArr;

        /*DynamicIntArray oldArr(newSIZE);    //запоминаем старый массив в oldArr по новому размеру
        for (int i = 0; i < newSIZE; i++) {
            oldArr[i] = numbers[i];
        }
        int oldSIZE = SIZE;                  //запоминаем старый размер

        if (SIZE > 0) { // удаляем старый массив numbers
            delete[] numbers;
            SIZE = oldSIZE;
        }

        if (SIZE <= oldSIZE) {
            for (int i = 0; i < oldSIZE; i++) {
                numbers[i] = oldArr[i];
            }
        }
        else {
            for (int i = 0; i < oldSIZE; i++) {
                numbers[i] = oldArr[i];
            }
            for (int i = oldSIZE; i < SIZE; i++) {
                numbers[i] = 0;
            }
        }*/
    }

    //оператор ==
    friend bool operator== (DynamicIntArray& arr1, DynamicIntArray& arr2) {
        int c = 0;
        if (arr1.SIZE == arr2.SIZE) {
            for (int i = 0; i < arr1.SIZE; i++) {
                if (arr1.numbers[i] == arr2.numbers[i]) c++;
            }
            if (c == arr1.SIZE) return true;
            else return false;
        }
        else throw "Sizes are not the same!";
    }

    //оператор !=
    friend bool operator!= (DynamicIntArray& arr1, DynamicIntArray& arr2) {
        /*int c = 0;
        if (arr1.SIZE == arr2.SIZE) {
            for (int i = 0; i < arr1.SIZE; i++) {
                if (arr1.numbers[i] == arr2.numbers[i]) c++;
            }
            if (c == arr1.SIZE) return false;
            else return true;
        }
        else throw "Sizes are not the same!";*/

        return (!(arr1 == arr2));
    }

    //оператор <
    friend bool operator< (DynamicIntArray& arr1, DynamicIntArray& arr2) {
        int k; 
        int flag=0;
        if (arr1.SIZE <= arr2.SIZE) k = arr1.SIZE;
        else k = arr2.SIZE;

        for (int i = 0; i < k; i++) {
            if (arr1.numbers[i] < arr2.numbers[i]) {}
            else flag++;
        }
        
        if (flag == 0) return true;
        else return false;
    }

    //оператор <=
    friend bool operator<= (DynamicIntArray& arr1, DynamicIntArray& arr2) {
        int k;
        int flag = 0;
        if (arr1.SIZE <= arr2.SIZE) k = arr1.SIZE;
        else k = arr2.SIZE;

        for (int i = 0; i < k; i++) {
            if (arr1.numbers[i] <= arr2.numbers[i]) {}
            else flag++;
        }

        if (flag == 0) return true;
        else return false;
    }

    //оператор =>
    friend bool operator>= (DynamicIntArray& arr1, DynamicIntArray& arr2) {
        int k;
        int flag = 0;
        if (arr1.SIZE <= arr2.SIZE) k = arr1.SIZE;
        else k = arr2.SIZE;
         
        for (int i = 0; i < k; i++) {
            if (arr1.numbers[i] >= arr2.numbers[i]) {}
            else flag++;
        }

        if (flag == 0) return true;
        else return false;
    }

    //оператор >
    friend bool operator> (DynamicIntArray& arr1, DynamicIntArray& arr2) {
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

    /*- оператор + (конкатенация массивов, m1 + m2 – это новый массив, 
    в котором сперва идут элементы m1, а затем – m2)*/
    friend DynamicIntArray operator+ (DynamicIntArray& m1, DynamicIntArray& m2) {
        int newSIZE = m1.getSizeOfArray() + m2.getSizeOfArray();

        DynamicIntArray arr(newSIZE);

        for (int i = 0; i < m1.getSizeOfArray(); i++) {
            arr.numbers[i] = m1.numbers[i];
        }
        for (int i = 0; i < m2.getSizeOfArray(); i++) {
            arr.numbers[m1.getSizeOfArray()+i] = m2.numbers[i];
        }
        return arr;
    }

    //оператор ввода
    friend std::istream& operator>> (std::istream& in, DynamicIntArray& arr) {
        for (int i = 0; i < arr.SIZE; i++) {
            in >> arr.numbers[i];
        }

        return in;
    }

    //оператор вывода
    friend std::ostream& operator<< (std::ostream& out, const DynamicIntArray& arr) {
        for (int i = 0; i < arr.SIZE; i++) {
            out << arr.numbers[i] << "  ";
        }
        return out;
    }
};


int main()
{
    DynamicIntArray arr(5);
    cin >> arr;
    cout << arr << endl << endl;

    arr.resize(3);
    cout << arr << endl << endl;

    arr.resize(8);
    cout << arr << endl << endl;

    DynamicIntArray m1(5, 5); //{5,5,5,5,5}
    DynamicIntArray m2(3, 3); //{3,3,3}
    arr = m1 + m2; // {5,5,5,5,5,3,3,3}
    cout << "arr: " << arr << "(copy = arr)" << endl << endl;

    DynamicIntArray copy;
    copy = arr;
    arr.resize(1); // {5}
    cout << "arr: " << arr << endl << endl;
    cout << "copy: " << copy << endl << endl;



    if (m1 < m2) cout << "\nm1<m2\n";
    else if (m1 > m2) cout << "\nm1>m2\n";


    if (m1 <= m2) cout << "\nm1<=m2\n";
    else if (m1 >= m2) cout << "\nm1>=m2\n";

    
    try {if (m1 == m2) cout << "\nm1==m2\n";}
    catch (const char* msg) {cout << msg << endl;}


    try {if (m1 != m2) cout << "\nm1!=m2\n";}
    catch (const char* msg) {cout << msg << endl;}
}