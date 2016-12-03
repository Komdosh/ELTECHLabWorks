#include <windows.h>
#include <iostream>

using namespace std;

int main()
{
	const int READER_COUNT = 8;
	const int WRITER_COUNT = 8;

	const int SEMAPHORE_MAX_VALUE = 6;
	const int MEMORY_PAGE_COUNT = 6;
	const int MEMORY_PAGE_SIZE = 4096;

	const char MemoryName[] = "myMap6Work";

	const char WriterSemaphoreName[] = "Writer semaphore";
	const char ReaderSemaphoreName[] = "Reader semaphore";
	const char* MutexName[] = { "mutexNum0", "mutexNum1", "mutexNum2", "mutexNum3", "mutexNum4", "mutexNum5" };

	LPCSTR writerProgramPath = "C:/Users/Komdosh/Documents/Visual Studio 2015/Projects/6 ОС/Writer/x64/Release/Writer.exe";
	LPCSTR readerProgramPath = "C:/Users/Komdosh/Documents/Visual Studio 2015/Projects/6 ОС/Reader/x64/Release/Reader.exe";

	PROCESS_INFORMATION piWriterProcessInfo[WRITER_COUNT];
	PROCESS_INFORMATION piReaderProcessInfo[READER_COUNT];

	HANDLE phMemoryPageMutex[MEMORY_PAGE_COUNT];

	HANDLE hWriterSemaphore = CreateSemaphoreA(NULL, SEMAPHORE_MAX_VALUE, SEMAPHORE_MAX_VALUE, WriterSemaphoreName);
	if (!hWriterSemaphore)
		cout << "Couldn't create writer semaphore\n";

	HANDLE hReaderSemaphore = CreateSemaphoreA(NULL, SEMAPHORE_MAX_VALUE, SEMAPHORE_MAX_VALUE, ReaderSemaphoreName);
	if (!hReaderSemaphore)
		cout << "Couldn't create reader semaphore\n";

	for (int i = 0; i < MEMORY_PAGE_COUNT; i++)
	{
		phMemoryPageMutex[i] = CreateMutexA(NULL, false, MutexName[i]);
		if (!phMemoryPageMutex[i])
			cout << "Couldn't create " << i << " mutex\n";
	}

	HANDLE hFile = CreateFileA("C:\\sharefile.txt",
		GENERIC_READ | GENERIC_WRITE, 
		FILE_SHARE_READ | FILE_SHARE_WRITE,
		NULL,
		CREATE_NEW,
		FILE_ATTRIBUTE_NORMAL, 
		NULL);
	if (hFile)
		cout << "Manager: C:/sharefile.txt created\n";

	HANDLE hMemory = CreateFileMappingA(hFile, NULL, PAGE_READWRITE, 0,
		MEMORY_PAGE_COUNT*MEMORY_PAGE_SIZE + MEMORY_PAGE_COUNT * sizeof(char), MemoryName);
	if (!hMemory)
		cout << "Manager: couldn't create file mapping. error code: " << GetLastError() << endl;

	char* memory = (char*)MapViewOfFile(hMemory, FILE_MAP_ALL_ACCESS, 0, 0, 0);
	if (!memory)
		cout << "Manager: couldn't map view of file\n";
	ZeroMemory(memory, MEMORY_PAGE_COUNT*MEMORY_PAGE_SIZE + MEMORY_PAGE_COUNT * sizeof(char));

	for (int i = 0; i < WRITER_COUNT; i++) {
		STARTUPINFOA startinfo = { sizeof(startinfo) };
		if (CreateProcessA(writerProgramPath, NULL, NULL, NULL, TRUE, 0, NULL, NULL, &startinfo, &(piWriterProcessInfo[i])) == NULL)
			cout << "Manager: couldn't create writer process #" << i << " error code: " << GetLastError() << endl;
		else
			cout << "Writer " << i << " created\n";
		Sleep(100);
	}
	for (int i = 0; i < READER_COUNT; i++) {
		STARTUPINFOA startinfo = { sizeof(startinfo) };
		if (CreateProcessA(readerProgramPath, NULL, NULL, NULL, TRUE, 0, NULL, NULL, &startinfo, &(piWriterProcessInfo[i])) == NULL)
			cout << "Manager: couldn't create reader process #" << i << " error code: " << GetLastError() << "\n";
		else
			cout << "Reader " << i << " created\n";
		Sleep(100);
	}

	for (int i = 0; i < WRITER_COUNT; i++) {
		cout << "Manager: waiting writer #" << i << "\n";
		WaitForSingleObject(piWriterProcessInfo[i].hProcess, 2000);
	}
	for (int i = 0; i < READER_COUNT; i++) {
		cout << "Manager: waiting reader #" << i << "\n";
		WaitForSingleObject(piReaderProcessInfo[i].hProcess, 2000);
	}
	cout << "Program finished\n";
	system("pause");
	return 0;
}