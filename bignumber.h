#ifndef BIGNUMBER_H
#define BIGNUMBER_H

#include <iostream>
#include <cstring>
#include <cstdio>

using namespace std;

/**
@brief Класс работы с большими числами
*/
class BigNumber
{
public:
    BigNumber() {}

    BigNumber(char *str1);

    BigNumber(int numb);

    BigNumber(BigNumber const &v1);

    BigNumber(int *b1, int c);


    ~BigNumber();

    void setData(int *ptr, int len);

    void setString(char *str1);

    void print();

    int size() { return count_num; }

    BigNumber& operator*(BigNumber const &v1);

    BigNumber& operator=(BigNumber const &v1);

    BigNumber& operator^(int range);

    int& operator[] (int i)
    {
        return pNumber[i];
    }

    friend BigNumber& operator+(const BigNumber &v1, const BigNumber &v2);

    friend BigNumber operator/(const BigNumber &v1, const int &n);

    friend int operator%(const BigNumber &v1, const int &n);

private:
    int count_num = 0;
    int *pNumber = nullptr;
};



#endif // BIGNUMBER_H
