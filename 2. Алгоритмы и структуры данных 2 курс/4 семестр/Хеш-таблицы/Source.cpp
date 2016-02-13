#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <time.h>
#include <fstream>
#include "Classes.h"

using namespace std;
//***********************************************************************
//Прототипы функций
int menu();
//***********************************************************************
//Перегрузка операторов MySet
HT& HT::operator & (const HT& rightExp) const
{
	HT* temp = new HT;
	LIST *t, *t1;
	bool b;
	for (int i = 0; i < hPower; ++i) {
		if (hashTable[i])
		{
			t = hashTable[i];
			while (t) {
				b = false;
				t1 = rightExp.hashTable[i];
				while (t1 && !b) {
					if (t->num == t1->num) {
						b = true;
						temp->addHT(t->num);
					}
					t1 = t1->next;
				}
				t = t->next;
			}
		}
	}
	return *temp;
}
//***********************************************************************
HT& HT::operator | (const HT & rightExp) const
{
	HT* temp = new HT;
	LIST *t, *t1;
	bool b;
	for (int i = 0; i < hPower; ++i) {
		if (hashTable[i])
		{
			t = hashTable[i];
			while (t) {
				temp->addHT(t->num);
				t = t->next;
			}
		}
	}
	for (int i = 0; i < hPower; ++i) {
		if (rightExp.hashTable[i]) {
			t = rightExp.hashTable[i];
			if(!temp->hashTable[i])
				while (t) {
					temp->addHT(t->num);
					t = t->next;
				}
			else
				while (t) {
					b = false;
					t1 = temp->hashTable[i];
					while (t1) {
						if (t1->num == t->num)
							b = true;
						t1 = t1->next;
					}
					if (!b)
						temp->addHT(t->num);
					t = t->next;
				}
		}
	}
	return *temp;
}
//***********************************************************************
HT& HT::operator = (const HT & rightExp)
{
	if (this != &rightExp)
	{
		LIST* t;
		power = 0;
		for (int i = 0; i < hPower; ++i) {
			delete hashTable[i];
			hashTable[i] = nullptr;
		}
		for (int i = 0; i < hPower; ++i) {
			if (rightExp.hashTable[i])
			{
				t = rightExp.hashTable[i];
				while (t) {
					addHT(t->num);
					t = t->next;
				}
			}
		}
	}
	return *this;
}
//***********************************************************************
//Функции-члены MySet
void HT::getInf()
{
	LIST* t;
	if (power)
		for (int i = 0; i < hPower; ++i) {
			if (hashTable[i])
			{
				t = hashTable[i];
				cout << name << '[' << i << ']';
				if (t) cout << " => ";
				while (t) {
					cout << t->num << ' ';
					t = t->next;
				}
				cout << endl;
			}
		}
	else
		cout << "Хеш-таблица " << name << " пустая";
	cout << endl;
}
//***********************************************************************
//Функции-члены HT
void HT::genSet()
{
	int t = rand()%(arrPower+1);
	int k = rand() % hPower;
	for (int i = 0; i < t; ++i) {
		addHT(k);
		k += rand() % hPower + 1;
	}
}
//***********************************************************************
void HT::inpSet()
{
	short size, t;
	bool check[100] = { false };
	cout << "Ввод множества " << name << endl;
	cout << "Введите количество элементов от 0 до 16:" << endl;
	do{ 
		cin.clear();
		cin.sync();
		cin >> size; 
		if (size < 0 || size>16 || cin.fail())
			cout << "Число от 0 до 16!\nВведите повторно:";
	} while (size < 0 || size>16 || cin.fail());
	cout << "Введите элементы множества от 0 до 99 без повторов" << endl;
	for (int i = 0; i < size;) {
		cin.clear();
		cin.sync();
		cout << i << "-е число " << name << ":";
		cin >> t;
		if(t<0 || t>99 || cin.fail())
			cout<<"Число от 0 до 99!\nВведите другое значение\n";
		else
			if (check[t])
				cout << "Такое число уже было!\nВведите значение\n";
			else {
				addHT(t);
				check[t] = true;
				++i;
			}
	}
	cout << endl;
}
//***********************************************************************
int HT::fileSet() 
{
	FILE* file;
	int size, t;
	char n[6] = " .txt";
	n[0] = name;
	if (!(file = fopen(n, "r")))
		return 1;         //Файла не существует
	fseek(file, 0, SEEK_END);
	if (!ftell(file))
		return 2;         //Файл пустой
	rewind(file);
	fscanf(file, "%d", &size);
	for (int i = 0; i<size; ++i)
	{
		fgetc(file);
		fscanf(file, "%d", &t);
		addHT(t);
	}
	fclose(file);
}
//***********************************************************************
void HT::addHT(int x)
{
	++power;
	LIST* t = new LIST;
	t->num = x;
	int hv = hashFunc(x);
	if (hashTable[hv])
		t->next = hashTable[hv];
	else
		t->next = nullptr;
	hashTable[hv] = t;
}
//***********************************************************************
//Основная функция
int main(int argc, char** argv)
{
	srand(time(NULL));
	setlocale(0, ".1251");
	int pause;
	
	do
	{
		HT A('A'), B('B'), C('C'), D('D'), E('E');
		switch (pause = menu())
		{
		case 1:
			A.fileSet(); B.fileSet(); C.fileSet(); D.fileSet();
			cout << "Множества прочитанные из файла:" << endl;
			break;
		case 2:
			A.genSet(); B.genSet(); C.genSet(); D.genSet();
			cout << "Сгенерированные множества:" << endl;
			break;
		case 3:
			A.inpSet(); B.inpSet(); C.inpSet(); D.inpSet();
			cout << "Введённые множества:" << endl;
			break;
		case 0:
			cout << "До новых встреч!" << endl;
			break;
		default:
			cout << "Такого пункта не существует, повторите ввод!" << endl;
		}
		if (pause)
		{
			
			E = A&B|C&D;
			A.getInf(); B.getInf(); C.getInf(); D.getInf(); E.getInf();
		}
		cout << "Для выхода в меню введите любое число, для выхода 0: ";
		cin >> pause;
	} while (pause);
	return 0;
}
//***********************************************************************
//Функции
int menu()
{
	int point;
	do {
		cin.clear();
		cin.sync();
		cout << "Выберите пункт меню" << endl;
		cout << "1 - Демо множества" << endl;
		cout << "2 - Сгенерировать множества" << endl;
		cout << "3 - Ввести множества" << endl;
		cout << "0 - Выход" << endl;
		cout << ">";
		cin >> point;
		if (cin.fail())
			cout << "Что-то пошло не так, выберите пункт меню повторно" << endl;
	} while (cin.fail());
	return point;
}
