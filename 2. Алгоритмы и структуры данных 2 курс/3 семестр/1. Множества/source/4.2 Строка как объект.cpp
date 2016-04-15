#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <time.h>
#include <string>

using namespace std;

enum{u=16, timer=1000};

class MySet
{
	private:
		int bits[u], power;
		string str;
		char name;
	public:
		MySet(char iName = 'T'):name(iName),power(0){}

		//перегружаем операторы
		MySet operator | (const MySet &) const;
    	MySet operator & (const MySet &) const;
    	MySet operator = (const MySet &);
		//геттеры
		void getInf();
		string getMas(){return str;};
		char getName(){return name;}
		int getPower(){return power;}
		//сеттеры
		void setName(char iName){name=iName;}
		void setBits(int* iBits){for(int i=0; i<u; ++i) bits[i]=iBits[i];}
		void setStr(string st){str=st; power=str.length();}
		//доп. функции
		void strToBits(string);
		void genSet();
		~MySet(){}
};

MySet MySet::operator & (const MySet & rightExp) const
{
	MySet temp;
	for(int i=0; i<rightExp.str.length(); ++i)
		for(int j=0; j<str.length(); ++j)
			if(rightExp.str[i]==str[j])
				temp.str+=str[j];
    return temp;
}
//***********************************************************************
MySet MySet::operator | (const MySet & rightExp) const
{
    MySet temp;
		temp.setStr(str+rightExp.str);
    return temp;
}
//***********************************************************************
MySet MySet::operator = (const MySet & rightExp)
{
    if (this != &rightExp)
    {
    	power=0;
		str=rightExp.str;
    }
    return *this;
}
//***********************************************************************
//Функции-члены MySet
void MySet::getInf()
{
	cout << name << "={";
  	cout<<str;
	cout<<"}"<<endl;
}
//***********************************************************************
void MySet::genSet()
{
	power=0;
	string const universum("0123456789ABCDEF");
	for(int i=0; i<u; ++i)
		if(rand()%3)
			{str+=universum[i]; power++;}
}
/*//***********************************************************************
//Перегрузка операторов MySet
MySet MySet::operator & (const MySet & rightExp) const
{
    MySet temp;
    for (int i = 0; i < u; ++i)
        temp.bits[i] = (bits[i] && rightExp.bits[i]) ;
    return temp;
}
//***********************************************************************
MySet MySet::operator | (const MySet & rightExp) const
{
    MySet temp;
    for(int i = 0; i<u; ++i)
		if(bits[i] || rightExp.bits[i]) temp.bits[i] = 1;
    return temp;
}
//***********************************************************************
MySet MySet::operator = (const MySet & rightExp)
{
    if (this != &rightExp)
    {
    	power=0;
		for(int i=0; i<u; ++i)
		{
			bits[i]=rightExp.bits[i];
			if(bits[i]) ++power;
		}
        
    }
    return *this;
}
//***********************************************************************
//Функции-члены MySet
void MySet::getInf()
{
	cout << name << "={";
  	string const universum("0123456789ABCDEF");
  	for (int i=0; i<u; ++i)
	  if (bits[i])
	    cout << universum[i];
	  else
		cout<<".";
	cout<<"}"<<endl;
}
//***********************************************************************
void MySet::genSet()
{
	power=0;
	for (int i = 0; i < u; ++i) {bits[i]=0;}
	for (int i = 0; i < u; ++i)
		if (rand () % 3)
		{
			bits[i]=1;
			++power;
		}
}
//***********************************************************************
void MySet::strToBits(string str)
{
	power=0;
	for (int i = 0; i < u; ++i) bits[i]=0;
	string const universum("0123456789ABCDEF");
	for(unsigned int i=0; i<str.length(); ++i)
		for(int j=0; j<u; ++j)
			if(str[i]==universum[j] && !bits[j])
			{
				bits[j]=1;
				++power;
			}
				
}*/
//***********************************************************************
//Прототипы функций
int menu();
string inputStr(char);
string delReply(string str);
//***********************************************************************
//Основная функция
int main(int argc, char* argv[])
{
	
	srand(time(NULL));
	setlocale(0, ".1251");
	int pause;
	MySet A('A'), B('B'), C('C'), D('D'), E('E');
	do
	{
		switch(pause = menu())
		{
			case 1:
				A.setStr("0A23"); B.setStr("23C5"); C.setStr("2389"); D.setStr("2389AB");
				cout<<"Константные множества:"<<endl;
				break;
			case 2:
				A.genSet(); B.genSet(); C.genSet(); D.genSet();
				cout<<"Сгенерированные множества:"<<endl;
				break;
			case 3:
				A.setStr(inputStr(A.getName())); B.setStr(inputStr(B.getName())); C.setStr(inputStr(C.getName())); D.setStr(inputStr(D.getName()));
				cout<<"Введённые множества:"<<endl;
				break;
			case 0:
				cout<<"До новых встреч!"<<endl;
				break;
			default:
				cout<<"Такого пункта не существует, повторите ввод!"<<endl;
		}
		if(pause)
		{
  		clock_t timeStart=clock();
		for(int i=0; i< timer; ++i)
			E=(A&B)|(C&D);
		clock_t timeEnd=clock();
		E.setStr(delReply(E.getMas()));
		A.getInf(); B.getInf(); C.getInf(); D.getInf(); E.getInf();
		cout<<"Средняя мошность множеств: "<<(A.getPower()+B.getPower()+C.getPower()+D.getPower()+E.getPower())/5<<endl;
		cout<<"Время затраченное на "<<timer<<" итераций операции E=A&B|C&D:"<<(timeEnd-timeStart)<<endl;
		}
	}
	while(pause);
	return 0;
}
//***********************************************************************
//Функции
int menu()
{
	int point;
	do{
	cin.clear();
	cin.sync();
	cout << "Выберите пункт меню" << endl;
	cout << "1 - Демо множества" << endl;
	cout << "2 - Сгенерировать множества" << endl;
	cout << "3 - Ввести множества" << endl;
	cout << "0 - Выход" << endl;
	cout << ">";
	cin >> point;
	if(cin.fail())
		cout<<"Что-то пошло не так, выберите пункт меню повторно"<<endl;
	}
	while(cin.fail());
	return point;
}
//***********************************************************************
string inputStr(char name)
{
	string str;
	string const universum("0123456789ABCDEF");
	int mBool, j;
	do
	{
	mBool=1;
	cout<<name<<" = ";
	cin>>str;
	transform(str.begin(), str.end(), str.begin(), ::toupper);
	for(int i=0; i<str.length() && mBool; ++i)
		for(j=0, mBool=0; j<u && !mBool; ++j)
			if(str[i]==universum[j])
				mBool=1;
	if(!mBool)
	cout<<"Вы ввели недопустимое множество, повторите ввод!"<<endl;
	}while(!mBool);
	return str;
}
//***********************************************************************
string delReply(string str)
{
    string result;
    string const universum("0123456789ABCDEF");
	int bits[u]={0};
	for(int i=0; i<str.length(); ++i)
		for(int j=0; j<u; ++j)
			if(str[i]==universum[j] && !bits[j])
				bits[j]=1;
	for(int i=0; i<u; ++i)
		if(bits[i])
			result+=universum[i];
    return result;
}
