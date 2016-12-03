#include <iostream>
#include "VirtualMemoryAPI.h"

using namespace std;

int menu();

int main() {
	setlocale(0, ".1251");
	int notExit;

	do {
		switch (notExit = menu())
		{
		case 1:
			systemInfo();
			break;
		case 2:
			virtualMemoryStatus();
			break;
		case 3:
			virtualPageStatus(0);
			break;
		case 4:
			separateReserveCommit();
			break;
		case 5:
			simultaneousReserveCommit();
			break;
		case 6:
			writeData();
			break;
		case 7:
			protectVirtualPage();
			break;
		case 8:
			freeVirtualPage(0);
			break;
		case 0:
			break;
		default:
			if (notExit)
				cout << "Такого варианта нет, повторите ввод" << endl;
		}
		if (notExit)
			system("pause");
	} while (notExit);
	return 0;
}

int menu()
{
	system("cls");
	int point;
	do {
		cin.clear();
		cin.sync();

		cout << "Выберите пункт меню" << endl;
		cout << "1 - Информация о вычислительной системе" << endl;
		cout << "2 - Статус памяти" << endl;
		cout << "3 - Состояние участка виртуальной памяти" << endl;
		cout << "4 - Раздельное резервирование региона и передача физ. памяти" << endl;
		cout << "5 - Одновременное резервирование региона и передача физ. памяти" << endl;
		cout << "6 - Запись данных" << endl;
		cout << "7 - Защита доступа региона памяти" << endl;
		cout << "8 - Очистить память" << endl;
		cout << "0 - Выход" << endl;
		cout << "> ";
		cin >> point;
		if (cin.fail())
			cout << "Что-то пошло не так, выберите пункт меню повторно" << endl;
	} while (cin.fail());
	system("cls");
	return point;
}