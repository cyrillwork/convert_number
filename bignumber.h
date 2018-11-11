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
    BigNumber()
    {
        count_num = 0;
        pNumber = NULL;
    }

    BigNumber(char *str1);

    BigNumber(int numb);


    BigNumber(BigNumber const &v1)
    {
        count_num = v1.count_num;
        pNumber = new int[count_num];
        for(int iii = 0; iii < count_num; iii++)
        {
            pNumber[iii] = v1.pNumber[iii];
        }
    }

    BigNumber(int *b1, int c)
    {
        this->count_num = c;
        pNumber = new int[count_num];
        for(int iii = 0; iii < this->count_num; iii++)
        {
            pNumber[iii] = b1[iii];
        }
    }


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

    friend BigNumber& operator+(BigNumber const &v1, BigNumber const &v2);
    friend BigNumber operator/(BigNumber const &v1, int const &n);
    friend int operator%(BigNumber const &v1, int const &n);

private:
    int count_num;
    int *pNumber;
};



#endif // BIGNUMBER_H
