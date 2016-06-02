#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <time.h>
#include <fstream>
#include "Classes.h"

using namespace std;
//***********************************************************************
//Прототипы функций
int menu(int);
//***********************************************************************
//Конструктор копий
HT::HT(const HT& rightExp)
{
	LIST* t;
	power = 0;
	int pos = 0;
	for (int i = 0; i < hPower; ++i) {
		delete hashTable[i];
		hashTable[i] = nullptr;
	}
	for (int i = 0; i < hPower; ++i) {
		if (rightExp.hashTable[i])
		{
			t = rightExp.hashTable[i];
			while (t) {
				addHT(t->key, pos++);
				t = t->next;
			}
		}
	}

}
//***********************************************************************
//Перегрузка операторов HT
HT& HT::operator & (const HT& rightExp) const
{
	HT* temp = new HT;
	LIST *t, *t1;
	bool b;
	int pos = 0;
	for (int i = 0; i < hPower; ++i) {
		if (hashTable[i])
		{
			t = hashTable[i];
			while (t) {
				b = false;
				t1 = rightExp.hashTable[i];
				while (t1 && !b) {
					if (t->key == t1->key) {
						b = true;
						temp->addHT(t->key, pos++);
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
	int pos = 0;
	for (int i = 0; i < hPower; ++i) {
		if (hashTable[i])
		{
			t = hashTable[i];
			while (t) {
				temp->addHT(t->key, pos++);
				t = t->next;
			}
		}
	}
	for (int i = 0; i < hPower; ++i) {
		if (rightExp.hashTable[i]) {
			t = rightExp.hashTable[i];
			if (!temp->hashTable[i])
				while (t) {
					temp->addHT(t->key, pos++);
					t = t->next;
				}
			else
				while (t) {
					b = false;
					t1 = temp->hashTable[i];
					while (t1) {
						if (t1->key == t->key)
							b = true;
						t1 = t1->next;
					}
					if (!b)
						temp->addHT(t->key, pos++);
					t = t->next;
				}
		}
	}
	return *temp;
}
//***********************************************************************
HT& HT::operator = (const HT& rightExp)
{
	if (this != &rightExp)
	{
		LIST* t;
		power = 0;
		for (int i = 0; i < hPower; ++i) {
			delete hashTable[i];
			hashTable[i] = nullptr;
		}
		int pos = 0;
		for (int i = 0; i < hPower; ++i) {
			if (rightExp.hashTable[i])
			{
				t = rightExp.hashTable[i];
				while (t) {
					addHT(t->key, pos++);
					t = t->next;
				}
			}
		}
	}
	return *this;
}
//***********************************************************************
//Функции-члены HT
void HT::getInf()
{
	if (power) {
		LIST* t;
		for (int i = 0; i < hPower; ++i) {
			if (hashTable[i])
			{
				t = hashTable[i];
				cout << name << '[' << i << ']';
				if (t) cout << " => ";
				while (t) {
					cout << t->key << ' ';
					t = t->next;
				}
				cout << endl;
			}
		}
	}
	else
		cout << "Хеш-таблица " << name << " пустая";
	cout << endl;
}
//***********************************************************************
void HT::getInfSeq()
{
	if (power) {
		LIST *t;
		cout << name << " = <";
		for (int i = 0; i < power; i++)
		{
			cout << ((t = findPos(i)) ? t->key : 99) << " ";
		}
		cout << "\b>" << endl;
	}
	else
		cout << name << " - Пустая последовательность!"<<endl;
}
//***********************************************************************
void HT::genSet()
{
	int t = rand() % (arrPower + 1);
	for (int i = 0; i < t; ++i) {
		addHT((rand() % hPower + 1), i);
	}
}
//***********************************************************************
void HT::inpSet()
{
	short size, t;
	cout << "Ввод множества " << name << endl;
	cout << "Введите количество элементов от 0 до 16:" << endl;
	do {
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
		if (t<0 || t>99 || cin.fail())
			cout << "Число от 0 до 99!\nВведите другое значение\n";
		else
			addHT(t,i);
			++i;
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
		addHT(t, i);
	}
	fclose(file);
	return 0;
}
//***********************************************************************
void HT::concat(const HT &rightExp)
{
	for (int i = 0, j=0; i<hPower; ++i) {
		if (rightExp.hashTable[i]) {
			LIST* t = rightExp.hashTable[i];
			while (t) {
				addHT(t->key, (t->pos) + power - j);
				++j;
				t = t->next;
			}
		}
	}
	//power = power + rightExp.power;
}
//***********************************************************************
void HT::excl(const HT& rightExp)
{
	/*int *position = new int[rightExp.power + 1];
	LIST* t;
	if (t = findKey(rightExp.findPos(0)->key))
		position[0] = t->pos;
	else
		 return;
	for (int j = 1; j < rightExp.power; j++)
	{
		if (t = findKey(rightExp.findPos(j)->key))
			position[j] = t->pos;
		else
		 return;
		if (position[j] - position[j - 1] != 1)
		 return;
	}
	if (!(t = findKey(rightExp.findPos(0)->key)))
	return;
	else
	stPos = t->pos;
	//erase(position[0], position[rightExp.power - 1]);*/
	if (!power || !rightExp.power || power<rightExp.power)
		return;
	int stPos;
	LIST* t = findKey(rightExp.findPos(0)->key);
	int i, j=0;
	while (t->next && j == 0){
		if(t->key == rightExp.findPos(0)->key){
			i = t->pos;
			j = 0;
			stPos = t->pos;
			while (i<power && j < rightExp.power) {
				if (findPos(i + j)->key != rightExp.findPos(j)->key) {
					j = 0;
					break;
				}
				++j;
			}
		}
		t = t->next;
	}
	if(j!=0)
		erase(stPos, stPos + rightExp.power - 1);
}
//***********************************************************************
void HT::erase(int start, int finish)
{
	LIST* t, *t1;
	bool b = true;
	for (int i = 0; i < hPower; ++i){
		if (hashTable[i]) {
			t = hashTable[i];
			while (b) {
				b = false;
				if(t)
					if (t->pos >= start && t->pos <= finish) {
						hashTable[i] = t->next;
						delete t;
						b = true;
					}
				t = hashTable[i];
			}
			t1 = t;
			if(t)
				t = t->next;
			while (t) {
				if (t->pos >= start && t->pos <= finish) {
					t1->next = t->next;
					delete t;
					t = t1->next;
				}
				t1 = t;
				if (t)
					t = t->next;
			}
		}
	}
	for (int i = 0; i < hPower; i++){
		if (hashTable[i]){
			t = hashTable[i];
			while (t){
				if (t->pos>finish)
					t->pos -= (finish - start + 1);
				t = t->next;
			}
		}
	} 
	power -= (finish - start + 1);
}
//***********************************************************************
void HT::addHT(int val, int pos)
{
	++power;
	LIST* t = new LIST;
	t->pos = pos;
	t->key = val;
	int hv = hashFunc(val);
	if (hashTable[hv])
		t->next = hashTable[hv];
	else
		t->next = nullptr;
	hashTable[hv] = t;
}
//***********************************************************************
HT::LIST* HT::findPos(int key) const
{
	if (power) {
		LIST* t;
		for (int i = 0; i < hPower; ++i) {
			if (hashTable[i]){
				t = hashTable[i];
				while (t) {
					if (t->pos == key)
						return t;
					else
						t = t->next;
				}
			}
		}
	}
	return nullptr;
}
//***********************************************************************
HT::LIST* HT::findKey(int val) const
{
	if (power) {
		LIST* t;
		int hv = hashFunc(val);
		if (hashTable[hv]){
			t = hashTable[hv];
			while (t) {
				if (t->key == val)
					return t;
				else
					t = t->next;
			}
		}
	}
	return nullptr;
}
//***********************************************************************
//Основная функция
int main(int argc, char** argv)
{
	srand(time(nullptr));
	setlocale(0, ".1251");
	int pause;
	do{
		int st = -1, fin = -1, choose = -1;
		HT A('A'), B('B'), C(B);
		switch (pause = menu(0)){
		case 1:
			A.fileSet(); B.fileSet();
			cout << "Демонстрационные последовательности:" << endl;
			break;
		case 2:
			A.genSet(); B.genSet();
			cout << "Сгенерированные последовательности:" << endl;
			break;
		case 3:
			A.inpSet(); B.inpSet();
			cout << "Введённые последовательности:" << endl;
			break;
		case 0:
			cout << "До новых встреч!" << endl;
			break;
		default:
			cout << "Такого пункта не существует, повторите ввод!" << endl;
		}
		do{
			if (A.getPower() || B.getPower()) {
				A.getInf();
				A.getInfSeq();
				B.getInf();
				B.getInfSeq();
				switch (pause = menu(1)) {
				case 1:
					A.concat(B);
					break;
				case 2:
					while (st == -1) {
						cout << "Введите начальную позицию с которой следует удалить: ";
						cin >> st;
					}
					while (fin == -1) {
						cout << "Введите конечную позицию с которой следует удалить: ";
						cin >> fin;
					}
					while (choose < 0 || choose >1) {
						cout << "Введите 0 чтобы укоротить последовательность A, 1 для B: ";
						cin >> choose;
					}
					if (choose) {
						B.erase(st, fin);
					}
					else {
						A.erase(st, fin);
					}
					break;
				case 3:
					A.excl(B);
					break;
				case 0:
					break;
				default:
					cout << "Такого пункта не существует, повторите ввод!" << endl;
				}
			}
		} while (pause);
		cout << "Для выхода в меню введите любое число, для выхода 0: ";
		cin >> pause;
	} while (pause);
	return 0;
}
//***********************************************************************
//Функции
int menu(int type)
{
	int point;
	do {
		cin.clear();
		cin.sync();
		cout << "Выберите пункт меню" << endl;
		switch (type) {
			case 0:
				cout << "1 - Демо последовательности" << endl;
				cout << "2 - Сгенерировать последовательности" << endl;
				cout << "3 - Ввести последовательности" << endl;
				cout << "0 - Выход" << endl;
				break;
			case 1: 
				cout << "1 - CONCAT (Сцепление последовательности A с B)" << endl;
				cout << "2 - ERASE (Укорачивание последовательности)" << endl;
				cout << "3 - EXCL (Исключение последовательности B из A)" << endl;
				cout << "0 - Выход" << endl;
				break;
		}
		cout << ">";
		cin >> point;
		if (cin.fail())
			cout << "Что-то пошло не так, выберите пункт меню повторно" << endl;
	} while (cin.fail());
	return point;
}