#include "bignumber.h"

BigNumber::BigNumber(const string&str1)
{
    if(str1.size() == 0) return;

    int len = str1.size();

    count_num = 0;

    if(len > 0)
    {
        count_num = len;

        pNumber = new int[count_num];

        for(int iii = 0; iii<count_num; iii++)
        {
            pNumber[iii] = str1[count_num - iii - 1] - 48;
        }

    }

}

BigNumber::BigNumber(int numb)
{
    char str1[256];
    str1[0] = 0;
    sprintf(str1, "%d", numb);

    count_num = static_cast<int>(strlen(str1));
    pNumber = new int[count_num];

    for(int iii = 0; iii<count_num; iii++)
    {
        char ch1 = str1[count_num - iii - 1] - 48;
        pNumber[iii] = ch1;
    }
}

BigNumber::BigNumber(const BigNumber&v1)
{
    count_num = v1.count_num;
    pNumber = new int[count_num];
    for(int iii = 0; iii < count_num; iii++)
    {
        pNumber[iii] = v1.pNumber[iii];
    }
}

BigNumber::BigNumber(int*b1, int c)
{
    this->count_num = c;
    pNumber = new int[count_num];
    for(int iii = 0; iii < this->count_num; iii++)
    {
        pNumber[iii] = b1[iii];
    }
}

BigNumber::~BigNumber()
{
    delete []pNumber;
}


void BigNumber::setData(int *ptr, int len)
{
    this->count_num = len;

    if(pNumber)
    {
        delete []pNumber;
    }

    pNumber = nullptr;

    if(len > 0)
    {
        pNumber = new int[count_num];
        for(int iii = 0; iii < this->count_num; iii++)
        {
            pNumber[iii] = ptr[iii];
        }
    }
}

void BigNumber::setString(char *str1)
{
    //printf("string this=%p count=%d\n", this, count);
    int iii;
    if(!str1) return;

    //printf("count=%d\n", this->count);
    for(iii = 0; iii<this->count_num; iii++)
    {
        char ch1 = static_cast<char>(pNumber[this->count_num - iii - 1] + 48);
        //printf("ch1=%c \n", ch1);
        *(str1 + iii) = ch1;
    }

    *(str1 + iii) = 0;
}

//Перегрузка операции вывода в поток
ostream& operator << (ostream &s, const BigNumber &b)
{
    int len = b.count_num;

    for(int iii = 0; iii<len; iii++)
    {
        s << b.pNumber[len - iii - 1];
    }

    return s;
}

void BigNumber::print() const
{
    //printf("print this=%p count=%d\n", this, count);

    for(int iii = 0; iii<count_num; iii++)
    {
        printf("%d", pNumber[count_num - iii - 1]);
    }
    printf("\n");
}

BigNumber& BigNumber::operator*(BigNumber const &v1)
{
    int len;
    int *arr1;

    len = v1.count_num + this->count_num + 1;
    arr1 = new int[len];

    for(int iii=0; iii<len; iii++)
    {
        arr1[iii] = 0;
    }


    for(int ix=0; ix < this->count_num; ix++)
    {
        for(int jx=0; jx < v1.count_num; jx++)
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

BigNumber& BigNumber::operator = (BigNumber const &v1)
{
	if(this != &v1)
	{
		this->count_num = v1.count_num;
		
		if(this->pNumber)
		{
			delete []this->pNumber;
		}
		
		this->pNumber = new int[this->count_num];
		
		for(int iii = 0; iii < count_num; iii++)
		{
			this->pNumber[iii] = v1.pNumber[iii];
		}
	}
	return *this;
}

BigNumber operator / (BigNumber const &v1, int const &n)
{
    int len;
    int *arr1;
    int osn = 10;
    int ost =0;

    BigNumber result;
    len = v1.count_num;
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

    if(len < 0)
    {
        len = 0;
    }

    //cout << "delenie len=" << len<< endl;
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
    len = v1.count_num;
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

BigNumber  operator + (BigNumber const &v1, BigNumber const &v2)
{
    BigNumber temp = v1;
    return temp += v2;
}

BigNumber& BigNumber::operator^(int range)
{
    BigNumber *aaa = nullptr;
    BigNumber *bbb = nullptr;

    if(range == 0)
    {
        aaa = new BigNumber("1");
        this->setData(aaa->pNumber, aaa->count_num);
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
                if(aaa)
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
            this->setData(aaa->pNumber, aaa->count_num);
        }

    return *this;
}

const BigNumber& BigNumber::operator += (const BigNumber&v1)
{
    BigNumber &v2 = *this;

    int len = 0;
    int *arr1;
    int *arr2;

    if(v2.count_num > v1.count_num)
    {
        len = v2.count_num + 1;
    }
    else
    {
        len = v1.count_num + 1;
    }

    arr1 = new int[len];
    arr2 = new int[len];

    for(int iii=0; iii<len; ++iii)
    {
        arr1[iii] = 0;
        arr2[iii] = 0;
    }

    for(int iii=0; iii<v2.count_num; ++iii)
    {
        arr1[iii] = v2.pNumber[iii];
    }
    for(int iii=0; iii<v1.count_num; ++iii)
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
        --len;
    }

    setData(arr1, len);

    delete []arr1;
    delete []arr2;

    return *this;
}

