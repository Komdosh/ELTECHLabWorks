#include <iostream>
#include <windows.h>
#include <stdio.h>

using namespace std;

int main()
{
	setlocale(0, ".1251");
	char answer = 0;
	HANDLE hFile;
	HANDLE hMapFile;
	LPVOID lpMapAddress;
	wchar_t filename[250] = L"tempTextFile.txt";
	char data[1024];
	cout << "Данные для передачи: ";
	cin >> data;

	hFile = CreateFile(filename, GENERIC_ALL, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile != INVALID_HANDLE_VALUE)
		cout << "Файл успешно создан" << endl;

	hMapFile = CreateFileMappingA(hFile, NULL, PAGE_READWRITE, 0, 1024, "myMappedFile");

	if (hMapFile != INVALID_HANDLE_VALUE)
		cout << "Маппинг объекта создан" << endl;

	lpMapAddress = MapViewOfFile(hMapFile, FILE_MAP_ALL_ACCESS, 0, 0, 0);

	memcpy(lpMapAddress, data, strlen(data));
	cout << "Адрес проекции: 0x" << lpMapAddress <<endl;

	cout << "Закрыть проекцию? (y/n) ";
	cin >> answer;
	if (answer == 'y') {
		UnmapViewOfFile(lpMapAddress);
	}
	CloseHandle(hMapFile);
	CloseHandle(hFile);
	return 0;
}