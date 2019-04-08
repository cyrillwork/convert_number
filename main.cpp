#include <iostream>

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

#include "bignumber.h"

using namespace std;

const int MAX_MASS = 256;

//символьные массивы содержащие числа в символьном виде
char numHex[MAX_MASS];
char numDec[MAX_MASS];
char numBin[MAX_MASS];

//тип введеного числа
enum class TypeNumbSystem
{
	TYPE_NONE = 0,
	TYPE_BIN = 1,       // бинарный
	TYPE_DEC,           // дестичный
	TYPE_HEX            // шеснадцатиричный
};

//тип введеного числа
TypeNumbSystem typeInput = TypeNumbSystem::TYPE_NONE;

//Функция вывода на печать числа в двоичной системе счисления
void printBinNumber(long long int num)
{
	printf("bin = ");
	bool first = false;
	for(int i = 31; i >= 0; i--)
	{
		if( num & (1<<i) )
		{
			printf("1");
			first = true;
		}
		else
		{
			if(first) printf("0");
		}
	}
	printf("\n");
}

int checkNumber(char *strNumber)
{
    //cout << "check number: "<< strNumber << endl;
	if((strlen(strNumber) > 1)&&(strNumber[0] == 'b'))
	{
		cout << "You input binary number"<< endl;
		for(unsigned int i=1; i<strlen(strNumber); i++)
		{
			if (!((strNumber[i] == '0')||(strNumber[i] == '1')))
			{
				cout << "!!! Eror format number"<< endl;
				cout << "symbol "<< strNumber[i] <<endl;
				return -1;
			}
		}
		typeInput = TypeNumbSystem::TYPE_BIN;
	}
	else
		if( (strlen(strNumber) > 2) && ((strNumber[0] == '0')&&(strNumber[1] == 'x')) )
		{
		cout << "You input hex number"<< endl;
		for(unsigned int i=2; i<strlen(strNumber); i++)
		{
			if(isxdigit(strNumber[i]) == 0)
			{
				cout << "!!! Eror format number"<< endl;
				cout << "symbol "<< strNumber[i] <<endl;
				return -1;
			}
		}
		typeInput = TypeNumbSystem::TYPE_HEX;
	}
	else
	{
		for(unsigned int i=0; i<strlen(strNumber); i++)
		{
			if(isdigit(strNumber[i]) == 0)
			{
				cout << "!!! Eror format number"<< endl;
				cout << "symbol "<< strNumber[i] <<endl;
				return -1;
			}
		}
		typeInput = TypeNumbSystem::TYPE_DEC;
	}
	return 0;
}

void printNumbers()
{
	printf("bin = %s\n", numBin);
	printf("dec = %s\n", numDec);
	printf("hex = %s\n", numHex);
}

void testBigNumber()
{
    cout << "Test Big number" << endl;

    BigNumber a1    = {226};
    BigNumber aa1   = {226};
    BigNumber b1    = {1000};
    BigNumber bb1    = {255};

    BigNumber c1;

    b1 += 100;
    b1 = b1 + 100;

    cout << b1 << endl;
    c1 = std::move(b1);
    c1 += 1026;

    cout << "a1 =  " << a1 << endl;
    cout << "aa1 = " << aa1 << endl;
    cout << "b1 =  " << b1 << endl;
    cout << "c1 =  " << c1 << endl;

    cout << std::boolalpha;
    cout << "a1<c1 =  " << (a1 < c1) << endl;
    cout << "a1>c1 =  " << (a1 > c1) << endl;
    cout << "a1==c1 =  " << (a1 == c1) << endl;
    cout << "a1==aa1 =  " << (a1 == aa1) << endl;
    cout << "a1!=aa1 =  " << (a1 != aa1) << endl;
    cout << "a1!=c1 =  " << (a1 != c1) << endl;
    cout << "a1>=c1 =  " << (a1 >= c1) << endl;
    cout << "a1<=c1 =  " << (a1 <= c1) << endl;
    cout << "a1<=aa1 =  " << (a1 <= aa1) << endl;

    cout << "++c1 =  " << ++c1 << endl;
    c1++;

    cout << "c1++ =  " << c1 << endl;

    bb1.setPrintFormat(BigNumber::NumbSystem::DEC);
    cout << "DEC bb1 =" << bb1 << endl;
    bb1.setPrintFormat(BigNumber::NumbSystem::BIN);
    cout << "BIN bb1 =" << bb1 << endl;
    bb1.setPrintFormat(BigNumber::NumbSystem::HEX);
    cout << "HEX bb1 =" << bb1 << endl;

    exit(0);
}



int main(int argc, char *argv[])
{
    cout << "Big number convertor" << endl;

    //testBigNumber();
    //return 0;

	if(argc != 2)
	{
		cout << "!!! Error input" << endl;
        cout << "Usage: convertor [number]" << endl;
        cout << "Number format: dec - [1..9], bin [b0..1], hex [0x1..f]" << endl;
        cout << "Max size number 30 symbols" << endl;
    }
	else
	{
		if(strlen(argv[1]) > 30)
		{
			cout << "!!! Error max size 30 chars" << endl;
			return 0;
		}

		if(checkNumber(argv[1]) == -1)
		{
			return 0;
		}

		char *ptr1 = argv[1];

        //cout << "typeInput=" << typeInput << endl;
		switch(typeInput)
		{
			case TypeNumbSystem::TYPE_NONE:
			break;

			case TypeNumbSystem::TYPE_BIN:
			{				
				++ptr1;

				BigNumber num1(ptr1, BigNumber::NumbSystem::BIN);

				string strBin;
				string strHex;
				string strDec;

				num1.getBinString(strBin);
				num1.getHexString(strHex);
				num1.getDecString(strDec);

				strcpy(numBin, strBin.c_str());
				strcpy(numHex, strHex.c_str());
				strcpy(numDec, strDec.c_str());
			}
			break;

			case TypeNumbSystem::TYPE_DEC:
			{
				BigNumber num1(ptr1);
				string strBin;
				string strHex;

				num1.getBinString(strBin);
				num1.getHexString(strHex);

				strcpy(numDec, ptr1);
				strcpy(numBin, strBin.c_str());
				strcpy(numHex, strHex.c_str());

			}
			break;

			case TypeNumbSystem::TYPE_HEX:
			{
				BigNumber num1(ptr1, BigNumber::NumbSystem::HEX);

				string strBin;
				string strDec;

				num1.getBinString(strBin);
				num1.getDecString(strDec);

				strcpy(numHex, ptr1);
				strcpy(numBin, strBin.c_str());
				strcpy(numDec, strDec.c_str());
			}
			break;
		}

		printNumbers();
	}

	return 0;
}
