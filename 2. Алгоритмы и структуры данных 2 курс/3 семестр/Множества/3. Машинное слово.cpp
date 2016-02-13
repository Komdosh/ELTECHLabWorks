#include <iostream>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <time.h>

using namespace std;

enum{u=16, timer=1000000};

//***********************************************************************
//Прототипы
int menu();
unsigned short int inputStr(char);
string delReply(string);
void outputByUniversum(unsigned short int, char);
unsigned short int myRand();
//***********************************************************************
//Основная функция
int main(int argc, char** argv)
{
	srand(time(NULL));
	setlocale(0, ".1251");
	unsigned short int A,B,C,D,E;
	int pause;
	do
	{
		switch(pause = menu())
		{
			case 1:
				A=1036; B=12532; C=2352134; D=2331; //23A 24567CD 12ADEF 01348B
				cout<<"Константные множества:"<<endl;
				break;
			case 2:
				A=myRand(); B=myRand(); C=myRand(); D=myRand();
				cout<<"Сгенерированные множества:"<<endl;
				break;
			case 3:
				A=inputStr('A'); B=inputStr('B'); C=inputStr('C'); D=inputStr('D');
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
			E=A&B|C&D;
		clock_t timeEnd=clock();
		outputByUniversum(A, 'A');
		outputByUniversum(B, 'B');
		outputByUniversum(C, 'C');
		outputByUniversum(D, 'D');
		outputByUniversum(E, 'E');
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
unsigned short int inputStr(char name)
{
	string str;
	string const universum("0123456789ABCDEF");
	int mBool, j;
	unsigned short int twoBytes=0;
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
	str = delReply(str);
	
	for(int i=0; i<str.length(); ++i)
		for(int j=0; j<u; ++j)
			if(str[i]==universum[j])
				twoBytes+=1<<j;
	return twoBytes;
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
//***********************************************************************
void outputByUniversum(unsigned short int num, char name)
{
	cout << name << "={";
  	string const universum("0123456789ABCDEF");
  	for (int i=0; i<u; ++i)
	  if (num >> i & 0x1)
	    cout << universum[i];
	cout<<"}"<<endl;
}
//***********************************************************************
unsigned short int myRand()
{
	if(RAND_MAX<32768)
		return (rand()*3)%65536;
	else
		return rand()%65536;
}
