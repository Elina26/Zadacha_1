#pragma once
class DynamicIntArray {
private:
    int* numbers;    //массив
    int SIZE;        //длина массива

public:
    
    DynamicIntArray();

    DynamicIntArray(int SIZE);

    DynamicIntArray(int SIZE, int n);

    DynamicIntArray(DynamicIntArray& arr);

    DynamicIntArray& operator=(DynamicIntArray& arr);

    DynamicIntArray(DynamicIntArray&& arr) noexcept;

    DynamicIntArray& operator=(DynamicIntArray&& arr) noexcept;

    ~DynamicIntArray();

    int& operator[] (int i);

    int length();

    void resize(int newSIZE);

    friend bool operator== (DynamicIntArray& arr1, DynamicIntArray& arr2);
    friend bool operator!= (DynamicIntArray& arr1, DynamicIntArray& arr2);
    friend bool operator< (DynamicIntArray& arr1, DynamicIntArray& arr2);
    friend bool operator> (DynamicIntArray& arr1, DynamicIntArray& arr2);
    friend bool operator<= (DynamicIntArray& arr1, DynamicIntArray& arr2);
    friend bool operator>= (DynamicIntArray& arr1, DynamicIntArray& arr2);



    friend DynamicIntArray operator+ (DynamicIntArray& m1, DynamicIntArray& m2);

    friend std::istream& operator>> (std::istream& in, DynamicIntArray& arr);
    friend std::ostream& operator<< (std::ostream& out, const DynamicIntArray& arr);
};