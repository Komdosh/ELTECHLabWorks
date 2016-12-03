#include "AsyncCopy.h"

int streamCount;
int numbersOfByteToWrite;
int bufferMultiplier;
CHAR **buffersArray;  
OVERLAPPED *overlapIn, *overlapOut;
HANDLE original, copyFile; 
LARGE_INTEGER fileSize, endOfFile;
LONGLONG  doneCount, recordCount; 

void asyncCopyOfFile() {
	int overlapOperationsCount = 0;
	numbersOfByteToWrite = 4096;
	bufferMultiplier = 1;

	char sourceCharFile[250], destinationCharFile[250];

	cout << "Введите путь к файлу (латинскими буквами, без пробелов): ";
	cin >> sourceCharFile;
	cout << "Введите путь куда скопировать файл (латинскими буквами, без пробелов): ";
	cin >> destinationCharFile;
	cout << "Количество перекрывающих операций: ";
	cin >> overlapOperationsCount;
	cout << "Множитель буфера: ";
	cin >> bufferMultiplier;
	numbersOfByteToWrite *= bufferMultiplier;
	cout << "Один блок = " << numbersOfByteToWrite << " б." << endl;

	buffersArray = new CHAR*[overlapOperationsCount];
	for (int i = 0; i<overlapOperationsCount; i++)
		buffersArray[i] = new CHAR[numbersOfByteToWrite];

	overlapIn = new OVERLAPPED[overlapOperationsCount];
	overlapOut = new OVERLAPPED[overlapOperationsCount];

	LARGE_INTEGER curPosIn;
	wchar_t source[250], destination[250];
	mbstowcs(source, sourceCharFile, 250);
	mbstowcs(destination, destinationCharFile, 250);
	original = CreateFile(source, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_FLAG_OVERLAPPED | FILE_FLAG_NO_BUFFERING, NULL);
	copyFile = CreateFile(destination, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_FLAG_OVERLAPPED | FILE_FLAG_NO_BUFFERING, NULL);

	GetFileSizeEx(original, &fileSize);

	cout << "Размер файла = " << fileSize.QuadPart << " б." << endl;

	recordCount = fileSize.QuadPart / numbersOfByteToWrite;
	if ((fileSize.QuadPart % numbersOfByteToWrite) != 0) 
		++recordCount;
	cout << "Количество блоков = " << recordCount << endl;

	DWORD startCopyTime, endCopyTime;
	startCopyTime = GetTickCount();
	curPosIn.QuadPart = 0;

	for (int i = 0; i < overlapOperationsCount; ++i) {
		overlapIn[i].hEvent = (HANDLE)i;
		overlapOut[i].hEvent = (HANDLE)i;
		overlapIn[i].Offset = curPosIn.LowPart;
		overlapIn[i].OffsetHigh = curPosIn.HighPart;
		if (curPosIn.QuadPart < fileSize.QuadPart)
			ReadFileEx(original, buffersArray[i], numbersOfByteToWrite, &overlapIn[i], asyncRead);
		curPosIn.QuadPart += (LONGLONG)numbersOfByteToWrite;
	}

	doneCount = 0;
	while (doneCount < 2 * recordCount)
		SleepEx(INFINITE, true); 

	cout << "Копирование успешно завершено!" << endl;

	delete[] overlapIn;
	delete[] overlapOut;
	for (int i = 0; i < overlapOperationsCount; ++i)
		delete[]buffersArray[i];
	delete[] buffersArray;

	endOfFile.QuadPart = fileSize.QuadPart;
	endOfFile.HighPart = fileSize.HighPart;
	SetFilePointerEx(copyFile, endOfFile, 0, FILE_BEGIN);
	SetEndOfFile(copyFile);

	CloseHandle(original);
	CloseHandle(copyFile);
	endCopyTime = GetTickCount();
	cout << "Время потрачено: " << endCopyTime - startCopyTime << " мс" << endl;
}

VOID WINAPI asyncRead(DWORD Code, DWORD nBytes, LPOVERLAPPED lpOv) {

	++doneCount;

	LARGE_INTEGER curPosIn, curPosOut;
	DWORD i = (DWORD)(lpOv->hEvent);

	curPosIn.LowPart = overlapIn[i].Offset;
	curPosIn.HighPart = overlapIn[i].OffsetHigh;
	curPosOut.QuadPart = curPosIn.QuadPart;
	overlapOut[i].Offset = curPosOut.LowPart;
	overlapOut[i].OffsetHigh = curPosOut.HighPart;
	WriteFileEx(copyFile, buffersArray[i], numbersOfByteToWrite, &overlapOut[i], asyncWrite);
	curPosIn.QuadPart += numbersOfByteToWrite * (LONGLONG)(streamCount);
	overlapIn[i].Offset = curPosIn.LowPart;
	overlapIn[i].OffsetHigh = curPosIn.HighPart;
}

VOID WINAPI asyncWrite(DWORD Code, DWORD nBytes, LPOVERLAPPED lpOv){

	++doneCount;

	LARGE_INTEGER curPosIn;
	DWORD i = (DWORD)(lpOv->hEvent);
	
	curPosIn.LowPart = overlapIn[i].Offset;
	curPosIn.HighPart = overlapIn[i].OffsetHigh;
	if (curPosIn.QuadPart < fileSize.QuadPart){
		ReadFileEx(original, buffersArray[i], numbersOfByteToWrite, &overlapIn[i], asyncRead);
	}
}