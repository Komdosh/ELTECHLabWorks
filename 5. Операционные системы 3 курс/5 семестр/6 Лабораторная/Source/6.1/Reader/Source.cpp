#include <windows.h>
#include <fstream>
#include <time.h>
#include <stdlib.h>

using namespace std;

int main()
{
	const int MEMORY_PAGE_COUNT = 6;
	const int MEMORY_PAGE_SIZE = 4096;
	const char MemoryName[] = "myMap6Work";
	const char WriterSemaphoreName[] = "Writer Semaphore";
	const char ReaderSemaphoreName[] = "Reader Semaphore";
	const char* mutexName[] = { "mutexNum0", "mutexNum1", "mutexNum2", "mutexNum3", "mutexNum4", "mutexNum5" };

	srand(time(NULL));
	fstream LogFile;
	LogFile.open("C:\\log.txt", fstream::out | fstream::app);

	HANDLE hReaderSemaphore = OpenSemaphoreA(SEMAPHORE_ALL_ACCESS, FALSE, ReaderSemaphoreName);
	if (!hReaderSemaphore)
		LogFile << "Reader: couldn't open reader semaphore\n";
	HANDLE hWriterSemaphore = OpenSemaphoreA(SEMAPHORE_ALL_ACCESS, FALSE, WriterSemaphoreName);
	if (!hWriterSemaphore)
		LogFile << "Writer: couldn't open writer semaphore\n";
		

	HANDLE hMemory = OpenFileMappingA(FILE_MAP_ALL_ACCESS, FALSE, MemoryName);
	if (!hMemory)
		LogFile << "Reader: couldn't open file mapping\n";

	char* memory = (char*)MapViewOfFile(hMemory, FILE_MAP_ALL_ACCESS, 0, 0, 0);
	if (!memory)
		LogFile << "Reader: couldn't map view of file\n";
	VirtualLock((PVOID)memory, MEMORY_PAGE_COUNT*MEMORY_PAGE_SIZE + MEMORY_PAGE_COUNT * sizeof(char));

	char data[MEMORY_PAGE_SIZE];
	int page = 0;

	for (int i = 0; i<2;i++) {
		LogFile << GetTickCount() << " reader: wait semaphore \n";
		WaitForSingleObject(hWriterSemaphore, INFINITE);
		LogFile << GetTickCount() << " reader: ready \n";
		Sleep(10);
		for (int j = 0; j < MEMORY_PAGE_COUNT; j++)
		{
			page = (GetCurrentThreadId() + j) % MEMORY_PAGE_COUNT;
			if (memory[page] == 1)
				break;
			if (j == MEMORY_PAGE_COUNT - 1) {
				j = 0;
				//LogFile << GetTickCount() << " reader: non-empty page not found, waiting. \n";
				Sleep(300);
			}
		}

		int offset = page * MEMORY_PAGE_SIZE + MEMORY_PAGE_COUNT * sizeof(char);
		HANDLE mutex = OpenMutexA(MUTEX_ALL_ACCESS, TRUE, mutexName[page]);
		WaitForSingleObject(mutex, INFINITE);
		if (mutex != NULL)
		{
			LogFile << GetTickCount() << " reader: start reading\n";
			Sleep(10);
			if (memory[page] == 0) {
				LogFile << GetTickCount() << " reader: page collision! page = " << page << "\n";
				i++;
				ReleaseMutex(mutex);
				ReleaseSemaphore(hWriterSemaphore, 1, NULL);
			}
			else {
				memory[page] = 0;
				memcpy(data, memory + offset, MEMORY_PAGE_SIZE);
				LogFile << GetTickCount() << " reader: reading completed. page " << page << " : " << data << ". waiting\n";
				ReleaseMutex(mutex);
				ReleaseSemaphore(hReaderSemaphore, 1, NULL);
			}
		}
		Sleep(200 + rand() % 500);
	}
	return 0;
}