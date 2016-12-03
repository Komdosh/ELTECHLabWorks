#include <windows.h>
#include <iostream>
#include <iomanip>
#include <omp.h>
#include <AclAPI.h>
#include <AccCtrl.h>

using namespace std;

typedef struct _Thread {
	HANDLE hThread;
	volatile unsigned int nextBlockIndex;
	double threadPi;
	volatile bool finished;
	volatile bool calculating;
} Thread;

//Now 2016 and processors are faster (10*5 is not a problem)
const int BLOCK_SIZE = 10*500;
const int N = 100000000;
const int TOTAL_BLOCKS = N / BLOCK_SIZE+(N % BLOCK_SIZE ? 1 : 0);

Thread *pThreads;


int menu();
void win32Processing();
DWORD WINAPI worker(LPVOID);
double OMP();
__declspec(thread) DWORD dwTlsThreadIndex;

int main()
{
	
	setlocale(0, ".1251");
	int notExit;

	switch (notExit = menu())
	{
	case 1:
		win32Processing();
		break;
	case 2:
		OMP();
		break;
	case 0:
		break;
	default:
		if (notExit)
			cout << "Такого варианта нет" << endl;
	}

	system("pause");
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
		cout << "1 - Win32 API" << endl;
		cout << "2 - Open Multi-Processing" << endl;
		cout << "0 - Выход" << endl;
		cout << ">";
		cin >> point;
		if (cin.fail())
			cout << "Что-то пошло не так, выберите пункт меню повторно" << endl;
	} while (cin.fail());
	system("cls");
	return point;
	
}
volatile LONG nextBlock = 0;
int numOfThreads = 1;
int* iterationPerThread;
void win32Processing() {
	srand(time(NULL));
	double pi = 0, start = 0, end = 0;
	cout << "Всего блоков: " << TOTAL_BLOCKS << "\n";
	cout << "Потоков : ";
	cin >> numOfThreads;
	iterationPerThread = new int[numOfThreads];
	pThreads = new Thread[numOfThreads];
	for (int i = 0; i < numOfThreads; ++i) {
		iterationsPerThread[i] = 0;
		pThreads[i].nextBlockIndex = nextBlock++;
		pThreads[i].threadPi = 0;
		pThreads[i].finished = false;
		pThreads[i].calculating = false;
		pThreads[i].hThread = CreateThread(NULL, 0, worker, (LPVOID)i, CREATE_SUSPENDED, NULL);
	}
	HANDLE* handlesArray = new HANDLE[numOfThreads];

	for (int i = 0; i < numOfThreads; ++i) {
		handlesArray[i] = pThreads[i].hThread;
	}

	start = GetTickCount();
	for (int i = 0; i < numOfThreads; i++) {
		ResumeThread(pThreads[i].hThread);
	}
		
	while (nextBlock <= TOTAL_BLOCKS) {
		int i;
		//rand() % numOfThreads
		for (i = rand() % numOfThreads; ; i = (i + 1) % numOfThreads) {
			SwitchToThread();
			if (!pThreads[i].calculating || nextBlock > TOTAL_BLOCKS)
				break;
		}
		ResumeThread(pThreads[i].hThread);
	}
	//cout << nextBlock << endl;
	for (int i = 0; i < numOfThreads; i++){
		ResumeThread(pThreads[i].hThread);
		//cout << i << "  " << iterationPerThread[i] << endl;
	}
	
	DWORD check = WaitForMultipleObjects(numOfThreads, handlesArray, true, INFINITE);

	end = GetTickCount();
	for (int i = 0; i < numOfThreads; ++i) {
		pi += pThreads[i].threadPi;
		
	}
		

	pi /= N;
	cout << setprecision(70) << "Пи = " << pi << endl;
	cout << "Время потрачено: " << (end - start) << " мс" << endl;
	for (int i = 0; i < numOfThreads; ++i) {
		CloseHandle(pThreads[i].hThread);
	}
}
DWORD WINAPI worker(LPVOID lpParameter) {
	dwTlsThreadIndex = (DWORD)lpParameter;
	pThreads[dwTlsThreadIndex].calculating = true;
	unsigned long int beginIndex = 0;
	unsigned long int endIndex = 0;
	while (nextBlock <= TOTAL_BLOCKS) {
		double intermediatePi = 0;
		beginIndex = pThreads[dwTlsThreadIndex].nextBlockIndex*BLOCK_SIZE;
		endIndex = (pThreads[dwTlsThreadIndex].nextBlockIndex + 1)*BLOCK_SIZE;
		if (endIndex > N)
			endIndex = N;
		
		for (unsigned long int i = beginIndex; i < endIndex; i++) {
			double xi = (i + 0.5) / N;
			intermediatePi += 4 / (1 + xi*xi);
		}

		pThreads[dwTlsThreadIndex].threadPi += intermediatePi;

		pThreads[dwTlsThreadIndex].calculating = false;

		SuspendThread(pThreads[dwTlsThreadIndex].hThread);
		pThreads[dwTlsThreadIndex].nextBlockIndex = InterlockedExchangeAdd(&nextBlock, 1);//nextBlock++;
		//++iterationPerThread[dwTlsThreadIndex];
		pThreads[dwTlsThreadIndex].calculating = true;
		
	}
	pThreads[dwTlsThreadIndex].finished = true;
	return 0;
}

double OMP() {
	int maxThreads;

	cout << "Максимум потоков: ";
	cin >> maxThreads;

	omp_set_dynamic(0);
	omp_set_num_threads(maxThreads);
	double start = GetTickCount();
	double pi = 0;
#pragma omp parallel for schedule(dynamic, BLOCK_SIZE) reduction(+:pi)
	for (int i = 0; i < N; i++) {
		double xi = (i + 0.5) / N;
		pi += 4 / (1 + xi*xi);
	}
	double end = GetTickCount();

	pi /= N;
	cout << setprecision(70) << "Пи = " << pi << endl;
	cout << "Время потрачено: " << (end - start) << " мс" << endl;

	return pi;
}
