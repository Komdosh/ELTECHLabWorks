#include <windows.h>
#include <iostream>
#include <clocale>
using namespace std;


int main()
{
	setlocale(0, ".1251");

	HANDLE hPipe;
	HANDLE hWriteEvent;
	OVERLAPPED olpWrite;

	char buffer[255];

	cout << "Приложение сервер\nДля завершения работы введите '!stop'" << endl;
	hPipe = CreateNamedPipe("\\\\.\\pipe\\pipeapp", PIPE_ACCESS_OUTBOUND | WRITE_DAC | FILE_FLAG_OVERLAPPED,
		PIPE_TYPE_MESSAGE | PIPE_WAIT, 1, 0, 0, NMPWAIT_USE_DEFAULT_WAIT, NULL);
	if (hPipe == INVALID_HANDLE_VALUE)
		cout << "Не удалось создать канал. код ошибки: " << GetLastError() << endl;
	else 
		cout << "Канал создан" << endl;

	hWriteEvent = CreateEventA(NULL, TRUE, FALSE, "pipeEvent");
	if (hWriteEvent != INVALID_HANDLE_VALUE)
		cout << "Событие создано\n";
	else
		cout << "Не удалось создать событие. код ошибки: " << GetLastError() << endl;

	cout << "Соединение.. ";
	if (ConnectNamedPipe(hPipe, NULL))
		cout << "установлено" << endl;
	else
		cout << endl << "ошибка соединения" << endl;
	
	while (true)
	{
		cout << "Сообщение: ";
		cin >> buffer;
		ZeroMemory(&olpWrite, sizeof(olpWrite));
		olpWrite.hEvent = hWriteEvent;
		WriteFile(hPipe, buffer, 255, NULL, &olpWrite);
		if (!strcmp(buffer, "!stop")) {
			break;
		}
		if (WaitForSingleObject(hWriteEvent, INFINITE) == WAIT_OBJECT_0)
			cout << "отправлено\n";
		else 
			cout << "ошибка \n";
	}


	cout << "Отсоединение сервера ";
	if (DisconnectNamedPipe(hPipe))
		cout << "успешно" << endl;
	else
		cout << "не удалось" << endl;

	CloseHandle(hPipe);
	CloseHandle(hWriteEvent);

	system("pause");
	return 0;
}