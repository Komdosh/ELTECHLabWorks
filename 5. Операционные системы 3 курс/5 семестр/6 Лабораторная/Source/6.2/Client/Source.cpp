#include <iostream>
#include <windows.h>
#include <clocale>

using namespace std;
char msg[255];
bool exitBool = false;
VOID CALLBACK FileIOCompletionRoutine(DWORD, DWORD, LPOVERLAPPED) {
	if (!strcmp(msg, "!stop"))
		exitBool = true;
	else
		cout << "check: " << msg << endl;
}

int main()
{
	setlocale(0, ".1251");

	HANDLE hOutPipe;
	char answer;
	int timeoutCur=0, timeoutMax = 10;
	while (timeoutCur<timeoutMax) {
		cout << "Попытка подключения " << timeoutCur << endl;
		hOutPipe = CreateFile("\\\\.\\pipe\\pipeapp", GENERIC_READ, 0, NULL, OPEN_ALWAYS, FILE_FLAG_OVERLAPPED, NULL);
		if (hOutPipe == INVALID_HANDLE_VALUE) {
			cout << "Не удалось подключиться, переподключение через 1 секунду" << endl;
		}
		else {
			cout << "Соединение успешно установлено" << endl;
			break;
		}
		++timeoutCur;
		Sleep(1000);
	}
	if (timeoutCur == timeoutMax) {
		cout << "Время подключения истекло, подключение не удалось, завершение программы"<<endl;
		system("pause");
		return -1;
	}
	
	while (true)
	{
		OVERLAPPED olpReadOverlapper;
		ZeroMemory(&olpReadOverlapper, sizeof(olpReadOverlapper));
		
		cout << "Ожидание сообщения\n";

		//DWORD bytesExpected = 0;
		//do{
		//	PeekNamedPipe(hOutPipe, NULL, 0, NULL, &bytesExpected, NULL);
		//} while (bytesExpected != 255);

		if (!ReadFileEx(hOutPipe, msg, 255, &olpReadOverlapper, FileIOCompletionRoutine)){
			cout << "Ошибка чтения" << endl;
			return 1;
		}
		SleepEx(INFINITE, 1);
		if (exitBool)
			break;
	}
	CloseHandle(hOutPipe);
	cout << "Соединение закрыто\n";

	system("pause");
	return 0;
}