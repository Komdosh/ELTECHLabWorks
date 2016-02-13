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
string inputStr(char);
string strOr(string, string);
string strAnd(string, string);
string genStr();
string delReply(string);
//***********************************************************************
//Основная функция
int main(int argc, char** argv)
{
	srand(time(NULL));
	setlocale(0, ".1251");
	string A,B,C,D,E;
	int pause;
	do
	{
		switch(pause = menu())
		{
			case 1:
				A=delReply("0A23"); B=delReply("23C5"); C=delReply("2389"); D=delReply("2389AB"); 
				cout<<"Константные множества:"<<endl;
				break;
			case 2:
				A=genStr(); B=genStr(); C=genStr(); D=genStr();
				cout<<"Сгенерированные множества:"<<endl;
				break;
			case 3:
				A=delReply(inputStr('A')); B=delReply(inputStr('B')); C=delReply(inputStr('C')); D=delReply(inputStr('D'));
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
			E=delReply(strOr(strAnd(A, B), strAnd(C,D)));
		clock_t timeEnd=clock();
		cout<<"A = {"<<A<<"}"<<endl; cout<<"B = {"<<B<<"}"<<endl; cout<<"C = {"<<C<<"}"<<endl; cout<<"D = {"<<D<<"}"<<endl; cout<<"E = {"<<E<<"}"<<endl;
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
string strOr(string str1, string str2)
{
	return str1+str2;
}
//***********************************************************************
string strAnd(string str1, string str2)
{
	string str;
	for(int i=0; i<str1.length(); ++i)
		for(int j=0; j<str2.length(); ++j)
			if(str1[i]==str2[j])
				str+=str1[i];
	return str;
}
//***********************************************************************
string genStr()
{
	string str;
	string const universum("0123456789ABCDEF");
	for(int i=0; i<u; ++i)
		if(rand()%3)
			str+=universum[i];
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
