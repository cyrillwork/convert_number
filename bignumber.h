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
		count = 0;
		pNumber = NULL;
	}

	BigNumber(char *str1);

        BigNumber(int numb);


	BigNumber(BigNumber const &v1)
	{
		count = v1.count;
		pNumber = new int[count];
		for(int iii = 0; iii < count; iii++)
		{
			pNumber[iii] = v1.pNumber[iii];
		}
	}

	BigNumber(int *b1, int c)
	{
		this->count = c;
		pNumber = new int[count];
		for(int iii = 0; iii < this->count; iii++)
		{
			pNumber[iii] = b1[iii];
		}
	}


	~BigNumber();

        void setData(int *b1, int c);

        void setString(char *str1);

	void print();

	int size() { return count; }

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
	int count;
	int *pNumber;
};



#endif // BIGNUMBER_H
