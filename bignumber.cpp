#include "bignumber.h"

BigNumber::BigNumber(char *str1)
{
	if(!str1) return;
	int len = strlen(str1);
	count = 0;
	if(len > 0)
	{
		count  = len;
		pNumber = new int[count];
		for(int iii = 0; iii<count; iii++)
		{
			pNumber[iii] = str1[count - iii - 1] - 48;
		}
	}
}

BigNumber::BigNumber(int numb)
{
	char str1[256];
	str1[0] = 0;
	sprintf(str1, "%d", numb);

	count = strlen(str1);
	pNumber = new int[count];

	for(int iii = 0; iii<count; iii++)
	{
		char ch1 = str1[count - iii - 1] - 48;
		pNumber[iii] = ch1;
	}
}

BigNumber::~BigNumber()
{
	delete []pNumber;
}


void BigNumber::setData(int *b1, int c)
{
	this->count = c;

	if(pNumber)
	{
		delete []pNumber;
	}

	pNumber = new int[count];
	for(int iii = 0; iii < this->count; iii++)
	{
		pNumber[iii] = b1[iii];
	}
}

void BigNumber::setString(char *str1)
{
	//printf("string this=%p count=%d\n", this, count);
	int iii;
	if(!str1) return;

	//printf("count=%d\n", this->count);
	for(iii = 0; iii<this->count; iii++)
	{
		char ch1 = pNumber[this->count - iii - 1] + 48;
		//printf("ch1=%c \n", ch1);
		*(str1 + iii) = ch1;
	}

	*(str1 + iii) = 0;
}

void BigNumber::print()
{
	//printf("print this=%p count=%d\n", this, count);

	for(int iii = 0; iii<count; iii++)
	{
		printf("%d", pNumber[count - iii - 1]);
	}
	printf("\n");
}

BigNumber& BigNumber::operator*(BigNumber const &v1)
{
	int len;
	int *arr1;

	len = v1.count + this->count + 1;
	arr1 = new int[len];

	for(int iii=0; iii<len; iii++)
	{
		arr1[iii] = 0;
	}


	for(int ix=0; ix < this->count; ix++)
	{
		for(int jx=0; jx < v1.count; jx++)
		{
			arr1[ix + jx] += this->pNumber[ix]*v1.pNumber[jx];
		}
	}

	for(int iii=0; iii<len; iii++)
	{
		arr1[iii + 1] += arr1[iii]/10;
		arr1[iii] %= 10;
	}

	//printf("len=%d arr1[len-1]=%d\n", len, arr1[len]);
	while(arr1[len-1] == 0)
	{
		len--;
		//printf("len=%d arr1[len]=%d\n", len, arr1[len]);
	}

	this->setData(arr1, len);
	delete []arr1;

	return *this;
}

BigNumber& BigNumber::operator=(BigNumber const &v1)
							   {
	this->count = v1.count;
	if(this->pNumber)
	{
		delete []this->pNumber;
	}
	this->pNumber = new int[this->count];
	for(int iii = 0; iii < count; iii++)
	{
		this->pNumber[iii] = v1.pNumber[iii];
	}

	return *this;
}

BigNumber operator/(BigNumber const &v1, int const &n)
{
	int len;
	int *arr1;
	int osn = 10;
	int ost =0;

	BigNumber result;
	len = v1.count;
	arr1 = new int[len];

	for(int iii=0; iii<len; iii++)
	{
		arr1[iii] = 0;
	}	
	for(int iii = len - 1; iii >= 0; iii--)
	{
		int cur = ost*osn + v1.pNumber[iii];
		arr1[iii] = cur/n;
		ost = cur % n;
	}
	while(arr1[len-1] == 0)
	{
		len--;
	}
	result.setData(arr1, len);
	delete []arr1;
	return result;
}

int operator%(BigNumber const &v1, int const &n)
{
	int len;
	int *arr1;
	int osn = 10;
	int ost =0;

	BigNumber result;
	len = v1.count;
	arr1 = new int[len];

	for(int iii=0; iii<len; iii++)
	{
		arr1[iii] = 0;
	}
	for(int iii = len - 1; iii >= 0; iii--)
	{
		int cur = ost*osn + v1.pNumber[iii];
		arr1[iii] = cur/n;
		ost = cur % n;
	}
	while(arr1[len-1] == 0)
	{
		len--;
	}
	result.setData(arr1, len);
	delete []arr1;

	return ost;
}

BigNumber& operator+(BigNumber const &v1, BigNumber const &v2)
{
	BigNumber *res = new BigNumber();

	int len = 0;
	int *arr1;
	int *arr2;

	if(v2.count > v1.count)
	{
		len = v2.count + 1;
	}
	else
	{
		len = v1.count + 1;
	}

	arr1 = new int[len];
	arr2 = new int[len];

	for(int iii=0; iii<len; iii++)
	{
		arr1[iii] = 0;
		arr2[iii] = 0;
	}

	for(int iii=0; iii<v2.count; iii++)
	{
		arr1[iii] = v2.pNumber[iii];
	}
	for(int iii=0; iii<v1.count; iii++)
	{
		arr2[iii] = v1.pNumber[iii];
	}
	for(int ix=0; ix<len; ix++)
	{
		arr1[ix] += arr2[ix];
		arr1[ix + 1] += (arr1[ix]/10);
		arr1[ix] %= 10;
	}

	if(arr1[len - 1] == 0)
	{
		len--;
	}


	res->setData(arr1, len);

	delete []arr1;
	delete []arr2;


	return *res;
}

BigNumber& BigNumber::operator^(int range)
{
	BigNumber *aaa = NULL;
	BigNumber *bbb = NULL;

	if(range == 0)
	{
		aaa = new BigNumber("1");
		this->setData(aaa->pNumber, aaa->count);
	}
	else
		if(range == 1)
		{
	}
	else
	{
		//printf("range=%d\n", range);
		for(int iii=0; iii<(range-1); iii++)
		{
			if(aaa != NULL)
			{
				delete aaa;
			}
			else
			{
				bbb = new BigNumber(*this);
			}

			aaa = new BigNumber((*bbb) * (*this));
			delete bbb;
			bbb = new BigNumber(*aaa);
			//bbb->print();
		}
		//printf("end loop\n");
		this->setData(aaa->pNumber, aaa->count);
	}

	return *this;
}
