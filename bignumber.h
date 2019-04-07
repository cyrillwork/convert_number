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
    BigNumber() = default;

    BigNumber(const string& str1);

    BigNumber(int numb);

    BigNumber(BigNumber const &v1);

    BigNumber(int *b1, int c);

    BigNumber(BigNumber && b) { swap(b); }

    ~BigNumber();

    void setData(int *ptr, int len);

    void setString(char *str1);

    void print() const;

    int size() const { return count_num; }

    BigNumber& operator*(BigNumber const &v1);

    BigNumber& operator=(BigNumber const &v1);

    BigNumber& operator=(BigNumber && b)
    {
        swap(b);
        return *this;
    }

    BigNumber& operator^(int range);

    int& operator[] (int i)
    {
        return pNumber[i];
    }

    const int& operator[] (int i) const
    {
        return pNumber[i];
    }

    void swap(BigNumber &b)
    {
        std::swap(count_num, b.count_num);
        std::swap(pNumber, b.pNumber);
    }

    const BigNumber & operator ++ ();
    const BigNumber operator ++ (int);

    const BigNumber& operator += (const BigNumber &v1);

    friend bool operator < (const BigNumber &v1, const BigNumber &v2);
    friend bool operator > (const BigNumber &v1, const BigNumber &v2);
    friend bool operator == (const BigNumber &v1, const BigNumber &v2);
    friend bool operator != (const BigNumber &v1, const BigNumber &v2);
    friend bool operator >= (const BigNumber &v1, const BigNumber &v2);
    friend bool operator <= (const BigNumber &v1, const BigNumber &v2);

    friend BigNumber operator+(const BigNumber &v1, const BigNumber &v2);

    friend BigNumber operator/(const BigNumber &v1, const int &n);

    friend ostream& operator << (ostream &s, const BigNumber &b);

    friend int operator%(const BigNumber &v1, const int &n);

private:
    int count_num = 0;
    int *pNumber = nullptr;
};



#endif // BIGNUMBER_H
