#include <iostream>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <time.h>

using namespace std;

enum{u=16, timer=1000000};

struct sLIST
  {
  	char x;
  	sLIST *next;
  	~sLIST(){if(next)delete next;}
  };
typedef sLIST* LIST;
//***********************************************************************
//Прототипы
int menu();
string inputStr(char);
string genStr();
string delReply(string);
LIST delReplyInList(LIST);
LIST initialEl(LIST, string);
LIST process(LIST, LIST, LIST);
void output(LIST, const char);
LIST del(LIST el);
LIST inverseList(LIST list) ;
//***********************************************************************
//Основная функция
int main(int argc, char** argv)
{
	srand(time(NULL));
	setlocale(0, ".1251");
	LIST A=NULL,B=NULL,C=NULL,D=NULL,E=NULL;
	int pause;
	do
	{
		switch(pause = menu())
		{
			case 1:
				A = initialEl(A, delReply("0A23")); B = initialEl(B, delReply("23C5")); C = initialEl(C, delReply("2389")); D = initialEl(D, delReply("2389AB"));
				cout<<"Константные множества:"<<endl;
				break;
			case 2:
				A = initialEl(A, genStr()); B = initialEl(B, genStr()); C = initialEl(C, genStr()); D = initialEl(D, genStr());
				cout<<"Сгенерированные множества:"<<endl;
				break;
			case 3:
				A = initialEl(A, delReply(inputStr('A'))); B = initialEl(B, delReply(inputStr('B'))); C = initialEl(C, delReply(inputStr('C'))); D = initialEl(D, delReply(inputStr('D')));
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
		{
			E = process(A, B, E);
			E = process(C, D, E);
			E = delReplyInList(E);
		}
		clock_t timeEnd=clock();
		output(A, 'A'); output(B, 'B'); output(C, 'C'); output(D, 'D'); output(E, 'E');
		A=del(A); B=del(B); C=del(C); D=del(D); E=del(E);
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
//***********************************************************************
LIST delReplyInList(LIST list)
{
	LIST result;
    string const universum("0123456789ABCDEF");
    string str;
	int bits[u]={0};
	for(; list; list=list->next)
		for(int j=0; j<u; ++j)
			if(list->x==universum[j] && !bits[j])
				bits[j]=1;
	for(int i=0; i<u; ++i)
		if(bits[i])
			str+=universum[i];
    return initialEl(result, str);
}
//***********************************************************************
void output(LIST el, const char c)
{
	if(el)
	{
	cout << c << " = {";
	for(;el; el=el->next)
		cout << el->x;
	cout << "}" << endl;
	}

}
//***********************************************************************
LIST initialEl(LIST el, string M)
  {
	el = new sLIST;
	LIST startList = el;
	if(M[0])
	{
  	el->x = M[0];
  	for(int i=1; M[i]; ++i)
  	  {
  	  	LIST B = new sLIST;
  	  	B->x = M[i];
  	  	el->next = B;
  	  	el = el->next;
  	  }
  	el->next = NULL;
	}
  	return startList;
  }
//***********************************************************************
LIST del(LIST el)
{
	LIST t;
	while(!el)
	{
		t = el;
		el = el->next;
		delete t;
	}
	return NULL;
}
//***********************************************************************
LIST process(LIST oSource, LIST sSource, LIST E)
{
	LIST sTemp=sSource;
	for(; oSource; oSource = oSource->next)
		for(sSource=sTemp; sSource; sSource=sSource->next)
			if((oSource->x)==(sSource->x))
				{
					LIST el = new sLIST;
					el->x = oSource->x;
					el->next=E;
					E=el;
				}
	return E;
}
//***********************************************************************
LIST inverseList(LIST list)
{
  LIST ptr=NULL, tmp;
  while (list)
  {
    tmp=list->next;
    list->next=ptr;
    ptr=list;
    list=tmp;
  }
  return ptr;
}
