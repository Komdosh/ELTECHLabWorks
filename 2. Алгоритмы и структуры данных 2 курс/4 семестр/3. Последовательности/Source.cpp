#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <time.h>
#include <fstream>
#include "Classes.h"

using namespace std;
//***********************************************************************
//��������� �������
int menu(int);
//***********************************************************************
//����������� �����
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
//���������� ���������� HT
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
//�������-����� HT
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
		cout << "���-������� " << name << " ������";
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
		cout << name << " - ������ ������������������!"<<endl;
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
	cout << "���� ��������� " << name << endl;
	cout << "������� ���������� ��������� �� 0 �� 16:" << endl;
	do {
		cin.clear();
		cin.sync();
		cin >> size;
		if (size < 0 || size>16 || cin.fail())
			cout << "����� �� 0 �� 16!\n������� ��������:";
	} while (size < 0 || size>16 || cin.fail());
	cout << "������� �������� ��������� �� 0 �� 99 ��� ��������" << endl;
	for (int i = 0; i < size;) {
		cin.clear();
		cin.sync();
		cout << i << "-� ����� " << name << ":";
		cin >> t;
		if (t<0 || t>99 || cin.fail())
			cout << "����� �� 0 �� 99!\n������� ������ ��������\n";
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
		return 1;         //����� �� ����������
	fseek(file, 0, SEEK_END);
	if (!ftell(file))
		return 2;         //���� ������
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
	int *position = new int[rightExp.power + 1];
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
	erase(position[0], position[rightExp.power - 1]);
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
//�������� �������
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
			cout << "���������������� ������������������:" << endl;
			break;
		case 2:
			A.genSet(); B.genSet();
			cout << "��������������� ������������������:" << endl;
			break;
		case 3:
			A.inpSet(); B.inpSet();
			cout << "�������� ������������������:" << endl;
			break;
		case 0:
			cout << "�� ����� ������!" << endl;
			break;
		default:
			cout << "������ ������ �� ����������, ��������� ����!" << endl;
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
					//B = *C;

					//A.getInf();
					//A.getInfSeq();
					break;
				case 2:
					while (st == -1) {
						cout << "������� ��������� ������� � ������� ������� �������: ";
						cin >> st;
					}
					while (fin == -1) {
						cout << "������� �������� ������� � ������� ������� �������: ";
						cin >> fin;
					}
					while (choose < 0 || choose >1) {
						cout << "������� 0 ����� ��������� ������������������ A, 1 ��� B: ";
						cin >> choose;
					}
					if (choose) {
						B.erase(st, fin);
						//B.getInf();
						//B.getInfSeq();
					}
					else {
						A.erase(st, fin);
						//A.getInf();
						//A.getInfSeq();
					}
					break;
				case 3:
					A.excl(B);
					//A.getInf();
					//A.getInfSeq();
					break;
				case 0:
					break;
				default:
					cout << "������ ������ �� ����������, ��������� ����!" << endl;
				}
			}
		} while (pause);
		cout << "��� ������ � ���� ������� ����� �����, ��� ������ 0: ";
		cin >> pause;
	} while (pause);
	return 0;
}
//***********************************************************************
//�������
int menu(int type)
{
	int point;
	do {
		cin.clear();
		cin.sync();
		cout << "�������� ����� ����" << endl;
		switch (type) {
			case 0:
				cout << "1 - ���� ������������������" << endl;
				cout << "2 - ������������� ������������������" << endl;
				cout << "3 - ������ ������������������" << endl;
				cout << "0 - �����" << endl;
				break;
			case 1: 
				cout << "1 - CONCAT (��������� ������������������ A � B)" << endl;
				cout << "2 - ERASE (������������ ������������������)" << endl;
				cout << "3 - EXCL (���������� ������������������ B �� A)" << endl;
				cout << "0 - �����" << endl;
				break;
		}
		cout << ">";
		cin >> point;
		if (cin.fail())
			cout << "���-�� ����� �� ���, �������� ����� ���� ��������" << endl;
	} while (cin.fail());
	return point;
}