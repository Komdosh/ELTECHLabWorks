#include <iostream>
#include <windows.h>

using namespace std;

int main()
{
	setlocale(0, ".1251");
	char answer;
	HANDLE hMapFile;
	PVOID lpMapAddress;
	char data[1024];

	hMapFile = OpenFileMappingA(FILE_MAP_ALL_ACCESS, FALSE, "myMappedFile");
	if (hMapFile != INVALID_HANDLE_VALUE)
		cout << "Проекция открыта\n";

	lpMapAddress = MapViewOfFile(hMapFile, FILE_MAP_ALL_ACCESS, 0, 0, 0);
	if (lpMapAddress == 0){
		cerr << "Не удаётся открыть проекцию файла\n";
		system("pause");
		return 1;
	}
	memcpy(data, (char*)lpMapAddress, 1024);
	cout << "Данные по адресу (0x"<< lpMapAddress <<"): " << data << "\n";

	cout << "Закрыть проекцию? (y/n) ";
	cin >> answer;
	if (answer == 'y') {
		UnmapViewOfFile(lpMapAddress);
	}
	CloseHandle(hMapFile);
	return 0;
}