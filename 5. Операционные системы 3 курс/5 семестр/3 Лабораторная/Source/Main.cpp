#include <iostream>
#include "FileSystemAPI.h"
#include "AsyncCopy.h"

using namespace std;

int menu();

int main() {
	setlocale(0, ".1251");
	int notExit;
	
	do {
		switch (notExit = menu())
		{
		case 1:
			showDrivesList();
			break;
		case 2:
			showDriveInfo();
			break;
		case 3:
			createFolder();
			break;
		case 4:
			deleteFolder();
			break;
		case 5:
			createFile();
			break;
		case 6:
			copyFile();
			break;
		case 7:
			moveFile();
			break;
		case 8:
			fileInfo();
			break;
		case 9:
			changeFileAttributes();
			break;
		case 10:
			changeCreationTime();
			break;
		case 11:
			asyncCopyOfFile();
			break;
		case 0:
			break;
		default:
			if(notExit)
				cout << "Такого варианта нет, повторите ввод" << endl;
		}
		if(notExit)
			system("pause");
	} while (notExit);
	cin.get();
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
		cout << "1 - Вывод списка дисков" << endl;
		cout << "2 - Вывести информацию о диске" << endl;
		cout << "3 - Создать каталог" << endl;
		cout << "4 - Удалить каталог" << endl;
		cout << "5 - Создать файл" << endl;
		cout << "6 - Копировать файл" << endl;
		cout << "7 - Переместить файл" << endl;
		cout << "8 - Информация о файле" << endl;
		cout << "9 - Изменить атрибуты файла" << endl;
		cout << "10 - Изменить время создания файла" << endl;
		cout << "11 - Асинхронное копирование файла" << endl;

		cout << "0 - Выход" << endl;
		cout << "> ";
		cin >> point;
		if (cin.fail())
			cout << "Что-то пошло не так, выберите пункт меню повторно" << endl;
	} while (cin.fail());
	system("cls");
	return point;
}