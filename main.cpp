#include "bignumber.h"

#include <cctype>
#include <memory>

using namespace std;

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

int checkNumber(string strNumber)
{
    unsigned int length = strNumber.length();
    //cout << "check number: "<< strNumber << endl;

	if((length > 1) && (strNumber[0] == 'b'))
	{
		cout << "You input binary number"<< endl;
		for(unsigned int i=1; i<length; i++)
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
		if( (length > 2) && ((strNumber[0] == '0') && (strNumber[1] == 'x')) )
		{
		cout << "You input hex number"<< endl;

		for(unsigned int i = 2; i < length; i++)
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
		for(unsigned int i=0; i<length; i++)
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
	//cout << "typeInput = "<< (int)typeInput << endl;

	return 0;
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
    auto gNumber = make_shared<BigNumber>();

    cout << "Big number convertor" << endl;

    //testBigNumber();
    //return 0;

	if(argc != 2)
	{
		cout << "!!! Error input" << endl;
        cout << "Usage: convertor [number]" << endl;
        cout << "Number format: dec - [1..9], bin [b0..1], hex [0x1..f]" << endl;
        cout << "Max size number 255 symbols" << endl;
    }
	else
	{
		if(string(argv[1]).length() > 255)
		{
			cout << "!!! Error max size 255 chars" << endl;
			return 0;
		}

		if(checkNumber(argv[1]) == -1)
		{
			return 0;
		}

		char *ptr1 = argv[1];

		switch(typeInput)
		{
			case TypeNumbSystem::TYPE_NONE:
			break;

			case TypeNumbSystem::TYPE_BIN:
			{				
				++ptr1;

				gNumber = make_shared<BigNumber>(ptr1, BigNumber::NumbSystem::BIN);
			}
			break;

			case TypeNumbSystem::TYPE_DEC:
			{
				gNumber = make_shared<BigNumber>(ptr1, BigNumber::NumbSystem::DEC);
			}
			break;

			case TypeNumbSystem::TYPE_HEX:
			{
				gNumber = make_shared<BigNumber>(ptr1, BigNumber::NumbSystem::HEX);

			}
			break;
		}

		if(gNumber)
		{
			gNumber->setPrintFormat(BigNumber::NumbSystem::BIN);
			cout << "binary      = " << *gNumber << endl;
			gNumber->setPrintFormat(BigNumber::NumbSystem::DEC);
			cout << "decimal     = " << *gNumber << endl;
			gNumber->setPrintFormat(BigNumber::NumbSystem::HEX);
			cout << "hexadecimal = " << *gNumber << endl;
		}
	}

	return 0;
}
