#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <time.h>
#include <fstream>
#include <unordered_map>
#include <iterator>
#include <vector>

enum { hPower = 8, arrPower = 16 };

using namespace std;

typedef unordered_multimap<int, int> HT;

auto keySel = [](auto pair) {return pair.first;};  //Лямбда функции (селекторы пары)
auto valSel = [](auto pair) {return pair.second;};

//***********************************************************************
//Прототипы функций
int menu(int);

void getInf(const HT& T, char name)
{
	if (!T.empty()) {
		unsigned n = T.bucket_count();
		for (unsigned i = 0; i<n; ++i) {
			cout << "A[" << i << "]: ";
			for (auto it = T.cbegin(i); it != T.cend(i); ++it)
				cout << "{" << it->first << ":" << it->second << "} ";
			cout << "\n";
		}
	}
	else
		cout << "Хеш-таблица " << name << " пустая";
	cout << endl;
}
//***********************************************************************
void getInfSeq(const HT& T, char name)
{
	if (!T.empty()) {
		cout << name << " = <";
		int s = T.size();
		for (int i = 0; i < s; ++i) {
			for (HT::const_iterator it = T.cbegin(); it != T.cend(); ++it)
				if (it->second == i) {
					cout << it->first << ' ';
					break;
				}
		}
		cout << "\b>" << endl;
	}
	else
		cout << name << " - Пустая последовательность!"<<endl;
}
//***********************************************************************
void genSet(HT& T)
{
	T.clear();
	int t = rand() % (arrPower + 1);
	for (int i = 0; i < t; ++i) {
		T.insert(HT::value_type((rand() % hPower + 1), i));
	}
}
//***********************************************************************
void inpSet(HT& T, char name)
{
	T.clear();
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
			T.insert(HT::value_type(t, i));
			++i;
	}
	cout << endl;
}
//***********************************************************************
int fileSet(HT& T, char name='a')
{
	T.clear();
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
		T.insert(HT::value_type(t, i));
	}
	fclose(file);
	return 0;
}
//***********************************************************************
void concat(HT& leftExp, const HT &rightExp)
{
	if (!rightExp.empty()) {
		int newPos = leftExp.size();
		int s = rightExp.size();
		for (int i = 0; i < s; ++i) {
			for (HT::const_iterator it = rightExp.cbegin(); it != rightExp.cend(); ++it)
				if (it->second == i) {
					leftExp.insert(HT::value_type((*it).first, newPos++));
					break;
				}
		}
	}
}
//***********************************************************************
void erase(HT& T, int start, int finish)
{
	if (!T.empty()) {
		int s = T.size();
		for (int i = start; i < s && i <= finish; ++i) {
			for (HT::iterator it = T.begin(); it != T.end(); ++it)
				if (it->second == i) {
					T.erase(it);
					break;
				}
		}
		for (auto &temp : T)
			if (temp.second >= finish)
				temp.second = temp.second - (finish - start) - 1;
	}
}
//***********************************************************************
int excl(HT& leftExp, const HT& rightExp)
{
	int stPos = -1, curPos = -1, step = 0;
	
	if (!rightExp.empty() && !leftExp.empty()) {
		if (leftExp.size() < rightExp.size())
			return 1;
		int sizeL = leftExp.size();
		int sizeR = rightExp.size();
		for (int i = 0; i < sizeL && (curPos - stPos + 1) != sizeR; ++i) {
			for (HT::const_iterator itL = leftExp.cbegin(); itL != leftExp.cend(); ++itL)
				if (itL->second == i) {
					if (stPos == -1) {
						HT::const_iterator itR = rightExp.cbegin();
						for (; itR != rightExp.cend() && itR->second != 0; ++itR);
						if (itR->first == itL->first)
							curPos = stPos = itL->second;
					}
					else
						for (HT::const_iterator itR = rightExp.cbegin(); itR != rightExp.cend(); ++itR)
							if (itR->first == itL->first) {
								if (itL->second > curPos && itL->second - curPos == 1) {
									curPos = itL->second;
								}
							}
					if ((curPos - stPos +1) == sizeR)
						break;
					if (curPos != itL->second)
						stPos = -1;
				}
			
		}

		if(stPos!=-1)
			erase(leftExp, stPos, stPos + rightExp.size()-1);
		else return 1;
	}
	return 0;
}
//***********************************************************************
void mapAnd(const HT& leftExp, const HT& rightExp, HT& result)
{
	result.clear();
	vector<int> vl(leftExp.size()), vr(rightExp.size()), vm;
	transform(leftExp.begin(), leftExp.end(), vl.begin(), keySel);  
	transform(rightExp.begin(), rightExp.end(), vr.begin(), keySel);
	sort(vl.begin(), vl.end());
	sort(vr.begin(), vr.end());
	set_intersection(vl.cbegin(), vl.cend(), vr.cbegin(), vr.cend(), inserter(vm, vm.begin()));
	int i = 0;
	for (auto it = vm.cbegin(); it != vm.cend(); ++it, ++i)
		result.insert(HT::value_type((*it), i));
}
//***********************************************************************

void mapOr(const HT& leftExp, const HT& rightExp, HT& result)
{
	result.clear();
	vector<int> vl(leftExp.size()), vr(rightExp.size()), vm;
	transform(leftExp.begin(), leftExp.end(), vl.begin(), keySel);   
	transform(rightExp.begin(), rightExp.end(), vr.begin(), keySel); 
	sort(vl.begin(), vl.end());
	sort(vr.begin(), vr.end());
	set_union(vl.cbegin(), vl.cend(), vr.cbegin(), vr.cend(), inserter(vm, vm.begin()));
	int i=0;
	for (auto it = vm.cbegin(); it != vm.cend(); ++it, ++i)
		result.insert(HT::value_type((*it), i));
}
//***********************************************************************
//Основная функция
int main(int argc, char** argv)
{
	try {
		srand(time(nullptr));
		setlocale(0, ".1251");
		int pausev, pause;
		do {
			HT A, B, C, D, E, F, G;
			switch (pause = menu(0)) {
			case 1:
				fileSet(A, 'A'); fileSet(B, 'B');
				break;
			case 2:
				genSet(A); genSet(B);
				break;
			case 3:
				inpSet(A, 'A'); inpSet(B, 'B');
				break;
			case 0:
				cout << "До новых встреч!" << endl;
				system("pause");
				break;
			default:
				cout << "Такого пункта не существует, повторите ввод!" << endl;
			}
			if(pause)
				do {
					switch (pausev = menu(1)) {
					case 1:
						do {
							int st = -1, fin = -1;
							//getInf(A, 'A');
							getInfSeq(A, 'A');
							//getInf(B, 'B');
							getInfSeq(B, 'B');
							switch (pause = menu(2)) {
							case 1:
								concat(A, B);
								break;
							case 2:
								while (st == -1 || st > (int)A.size()) {
									if (st > (int)A.size())
										cout << "Начальная позиция больше, чем количество элементов!" << endl;
									cout << "Введите начальную позицию с которой следует удалить: ";
									cin >> st;
								}
								while (fin == -1) {
									cout << "Введите конечную позицию с которой следует удалить: ";
									cin >> fin;
								}
								if (fin > (int)A.size()) {
									cout << "Конечная позиция больше, чем размер набора,\n \
										Набор будет удалён до конца" << endl;;
								}
								erase(A, st, fin);
								break;
							case 3:
								if (excl(A, B)){
									cout << "в A нет подпоследовательности B" << endl;
								}
								break;
							case 0:
								break;
							default:
								cout << "Такого пункта не существует, повторите ввод!" << endl;
							}
							if (pause > 0 && pause < 4) {
								cout << "Результат: ";
								getInfSeq(A, 'A');
								system("pause");
								system("cls");
							}
						} while (pause);
						break;
					case 2:
						do {
							//getInf(A, 'A');
							getInfSeq(A, 'A');
							//getInf(B, 'B');
							getInfSeq(B, 'B');
							switch (pause = menu(3)) {
							case 1:
								mapOr(A, B, C);
								break;
							case 2:
								mapAnd(A, B, C);
								break;
							case 3:
								fileSet(C, 'C');
								fileSet(D, 'D');
								getInfSeq(A, 'A');
								getInfSeq(B, 'B');
								getInfSeq(C, 'C');
								getInfSeq(D, 'D');
								mapAnd(A, B, F);
								mapAnd(C, D, G);
								mapOr(F, G, E);
								cout << "Результат A&B|C&D:\n";
								getInfSeq(E, 'E');
								cout << endl;
								system("pause");
								system("cls");
							case 0:
								break;
							default:
								cout << "Такого пункта не существует, повторите ввод!" << endl;
							}
							if (pause > 0 && pause < 3) {
								cout << "Результат: ";
								getInfSeq(C, 'C');
								cout << endl;
								system("pause");
								system("cls");
							}
							
						} while (pause);
						break;
					case 0:
						break;
					default:
						cout << "Такого пункта не существует, повторите ввод!" << endl;
					}
					
					pause = 1;
				} while (pausev);
			//cout << "Для выхода в меню введите любое число, для выхода 0: ";
			//cin >> pause;
		} while (pause);
	}
	catch (...) {
		cout << "Произошёл сбой!" << endl;
	}
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
				cout << "1 - Работа с последовательностями" << endl;
				cout << "2 - Работа с множествами" << endl;
				cout << "0 - Выход в надменю" << endl;
				break;
			case 2: 
				cout << "1 - CONCAT (Сцепление последовательности A с B)" << endl;
				cout << "2 - ERASE (Укорачивание последовательности A)" << endl;
				cout << "3 - EXCL (Исключение последовательности B из A)" << endl;
				cout << "0 - Выход в надменю" << endl;
				break;
			case 3:
				cout << "1 - A|B" << endl;
				cout << "2 - A&B" << endl;
				cout << "3 - A&B|C&D" << endl;
				cout << "0 - Выход в надменю" << endl;
				break;
		}
		cout << ">";
		cin >> point;
		if (cin.fail())
			cout << "Что-то пошло не так, выберите пункт меню повторно" << endl;
	} while (cin.fail());
	system("cls");
	return point;
}