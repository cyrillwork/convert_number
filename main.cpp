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
    BigNumber a1 = {226};
    BigNumber aa1 = {226};
    BigNumber b1 = {1000};
    BigNumber c1;

    b1 += 100;
    b1 = b1 + 100;

    cout << b1 << endl;
    c1 = std::move(b1);
    c1 += 1026;

    cout << "a1 =  " << a1 << endl;
    cout << "aa1 =  " << aa1 << endl;
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

    exit(0);
}



int main(int argc, char *argv[])
{
    cout << "Big number convertor" << endl;

    //testBigNumber();

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

        //cout << "typeInput=" << typeInput << endl;
		switch(typeInput)
		{
			case TypeNumbSystem::TYPE_NONE:
			break;

			case TypeNumbSystem::TYPE_BIN:
			{
				char *ptr1 = argv[1]  + 1;
				strcpy(numBin, ptr1);
				int countHex = strlen(ptr1)/4;
				int addHex = strlen(ptr1) - countHex*4;
				int indexHex = 2;

                memset(numHex, 0, sizeof(numHex));
				numHex[0] = '0';
				numHex[1] = 'x';

				if(addHex > 0)
				{
					addHex = 4 - addHex;
					char *ptr2 = (char*)malloc(countHex*4 + addHex + 1);
					memset(ptr2, 0, countHex*4 + addHex + 1);
					for(int iii = 0; iii<addHex; iii++)
					{
						ptr2[iii] = '0';
					}
					strcpy(ptr2 + addHex, ptr1);
					ptr1 = ptr2;
					countHex++;
				}

				for(int iii = 0; iii < countHex; iii++)
				{
					int index = 4*iii;
                    char str1[16];
					memset(str1, 0, 5);
					//printf("index=%d\n", index);
					strncpy(str1, ptr1 + index, 4);
					//printf("str1=%s\n", str1);

					{

						if(strcmp(str1, "0000") == 0)
						{
							numHex[indexHex] = '0';
						}
						else
							if(strcmp(str1, "0001") == 0)
							{
							numHex[indexHex] = '1';
						}
						else
							if(strcmp(str1, "0010") == 0)
							{
							numHex[indexHex] = '2';
						}
						else
							if(strcmp(str1, "0011") == 0)
							{
							numHex[indexHex] = '3';
						}
						else
							if(strcmp(str1, "0100") == 0)
							{
							numHex[indexHex] = '4';
						}
						else
							if(strcmp(str1, "0101") == 0)
							{
							numHex[indexHex] = '5';
						}
						else
							if(strcmp(str1, "0110") == 0)
							{
							numHex[indexHex] = '6';
						}
						else
							if(strcmp(str1, "0111") == 0)
							{
							numHex[indexHex] = '7';
						}
						else
							if(strcmp(str1, "1000") == 0)
							{
							numHex[indexHex] = '8';
						}
						else
							if(strcmp(str1, "1001") == 0)
							{
							numHex[indexHex] = '9';
						}
						else
							if(strcmp(str1, "1010") == 0)
							{
							numHex[indexHex] = 'a';
						}
						else
							if(strcmp(str1, "1011") == 0)
							{
							numHex[indexHex] = 'b';
						}
						else
							if(strcmp(str1, "1100") == 0)
							{
							numHex[indexHex] = 'c';
						}
						else
							if(strcmp(str1, "1101") == 0)
							{
							numHex[indexHex] = 'd';
						}
						else
							if(strcmp(str1, "1110") == 0)
							{
							numHex[indexHex] = 'e';
						}
						else
							if(strcmp(str1, "1111") == 0)
							{
							numHex[indexHex] = 'f';
						}
						indexHex++;
					}

				}
				if(addHex > 0)
				{
					free(ptr1);
				}

				BigNumber num_res;
				BigNumber num_res1;

				int off1 = 0;

				for(int iii=(strlen(numBin)-1); iii>=0; iii--)
				{
					int ddd = 0;
					//fprintf(stdout, "iii=%d\n", iii);
					ddd = numBin[iii] - 48;
					//fprintf(stdout, "iii=%d ddd=%d off1=%d\n", iii, ddd, off1);
					if(ddd == 1)
					{
						BigNumber num_2((char*)"2");
						num_res1 = num_2^off1;
						//num_res1.print();
						num_res = num_res + num_res1;

					}
					off1++;
				}
				//num_res.print();
				num_res.setString(numDec);
				//num_res.print();

			}
			break;

			case TypeNumbSystem::TYPE_DEC:
			{
				int ost = 0;
				char *ptr1 = argv[1];

				strcpy(numDec, ptr1);

				{ //set bin number
                    BigNumber num1(numDec);
					BigNumber num2;

					int currBin = 0;
					numBin[currBin] = 0;
					currBin++;

                    for(;;)
					{
                        //cout << "num1 = ";
                        //num1.print();

						num2 = num1/2;
						ost = num1%2;

						if(ost)
						{
							strcat(numBin, "1");
						}
						else
						{
							strcat(numBin, "0");
						}

						currBin++;
                        //cout << "currBin=" << currBin  << endl;
                        //cout << "numBin=" << numBin  << endl;
                        //cout << "num2size=" << num2.size()  << endl;
                        if(num2.size() == 0)
						{
							break;
						}
						num1 = num2;
					}

					char numBin1[MAX_MASS];

					unsigned int iii;
					for(iii = 0; iii<strlen(numBin); iii++)
					{
						numBin1[iii] = numBin[strlen(numBin) - iii - 1];
					}
					numBin1[iii] = 0;
					strcpy(numBin, numBin1);
				}

				{ //set hex number
					BigNumber num1(ptr1);
					BigNumber num2;

					numHex[0] = 0;

					for(;;)			//for(int iii = strlen(ptr1)-1; iii >= 2; iii--)
					{
						char str2[8];
						num2 = num1/16;
						ost = num1%16;
                        if(ost > 9)
						{
							char str1[] = {'a', 'b', 'c', 'd', 'e', 'f'};
							sprintf(str2, "%c", str1[ost - 10]);
						}
						else
						{
							sprintf(str2, "%d", ost);
						}
						strcat(numHex, str2);

						if(num2.size() == 0)
						{
							break;
						}
						num1 = num2;
					}
                    std::reverse(numHex, numHex + strlen(numHex));
				}

			}
			break;

			case TypeNumbSystem::TYPE_HEX:
			{
				char *ptr1 = argv[1];
				strcpy(numHex, ptr1);
				int currBin = 0;
				for(int iii = strlen(ptr1)-1; iii >= 2; iii--)
				{
					//printf("ptr1 %c\n", ptr1[iii]);
					switch (ptr1[iii])
					{
					case '0':
						strcpy(numBin+currBin, "0000");
						break;
					case '1':
						strcpy(numBin+currBin, "0001");
						break;
					case '2':
						strcpy(numBin+currBin, "0010");
						break;
					case '3':
						strcpy(numBin+currBin, "0011");
						break;
					case '4':
						strcpy(numBin+currBin, "0100");
						break;
					case '5':
						strcpy(numBin+currBin, "0101");
						break;
					case '6':
						strcpy(numBin+currBin, "0110");
						break;
					case '7':
						strcpy(numBin+currBin, "0111");
						break;
					case '8':
						strcpy(numBin+currBin, "1000");
						break;
					case '9':
						strcpy(numBin+currBin, "1001");
						break;
					case 'a':
						strcpy(numBin+currBin, "1010");
						break;
					case 'b':
						strcpy(numBin+currBin, "1011");
						break;
					case 'c':
						strcpy(numBin+currBin, "1100");
						break;
					case 'd':
						strcpy(numBin+currBin, "1101");
						break;
					case 'e':
						strcpy(numBin+currBin, "1110");
						break;
					case 'f':
						strcpy(numBin+currBin, "1111");
						break;

					}
					currBin += 4;
				}

				BigNumber num_res;
				BigNumber num_res1;

				int off1 = 0;

				for(int iii= strlen(ptr1) - 1; iii>=2; iii--)
				{
					char ch1 = ptr1[iii];
					int ddd = 0;
					//fprintf(stdout, "iii=%d\n", iii);
					if (('a' <= ch1) && (ch1 <= 'f'))
					{
						ddd = 10 + ptr1[iii] - 97;
					}
					else
					{
						ddd = ptr1[iii] - 48;
					}
					//fprintf(stdout, "iii=%d %c %d\n", iii, ptr1[iii], ddd);
					//fprintf(stdout, "iii=%d ddd=%d off1=%d\n", iii, ddd, off1);
					if(ddd > 0)
					{
						BigNumber num_res3;
						BigNumber num_res2(ddd);
						BigNumber num_16((char *)"16");
						num_res1 = num_16^off1;
						num_res3 = num_res2*num_res1;
						num_res = num_res + num_res3;

					}
					off1++;
				}
				num_res.setString(numDec);
			}
			break;
		}

		printNumbers();
	}

	return 0;
}
