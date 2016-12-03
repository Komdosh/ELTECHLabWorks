#include "VirtualMemoryAPI.h"

using namespace std;

void systemInfo() {
	SYSTEM_INFO systemInfo;
	GetSystemInfo(&systemInfo);
	cout << "Информация о вычислительной системе:" << endl;
	cout << "Архитектура процессора: ";
	switch (systemInfo.wProcessorArchitecture)
	{
	case 0:
		cout << "Intel x86" << endl;
		break;
	case 5:
		cout << "ARM" << endl;
		break;
	case 6:
		cout << "Intel Itanium-based" << endl;
		break;
	case 9:
		cout << "x64 (AMD or Intel)" << endl;
		break;
	default:
		cout << "Неизвестная архитектура" << endl;
		break;
	}
	cout << "Количество ядер: " << systemInfo.dwNumberOfProcessors << endl;
	cout << "Тип процессора: ";
	switch (systemInfo.dwProcessorType)
	{
	case 386:
		cout << "Intel 386" << endl;
		break;
	case 486:
		cout << "Intel 486" << endl;
		break;
	case 586:
		cout << "Intel Pentium" << endl;
		break;
	case 2200:
		cout << "Intel IA64" << endl;
		break;
	case 8664:
		cout << "AMD x8664" << endl;
		break;
	default:
		cout << "ARM" << endl;
		break;
	}
	cout << "Уровень процессора (CPU vendor): " << systemInfo.wProcessorLevel << endl;
	cout << "Размер страницы: " << systemInfo.dwPageSize << endl;
	cout << "Минимальный адрес для приложений: " << systemInfo.lpMinimumApplicationAddress << endl;
	cout << "Максимальный адрес для приложений: " << systemInfo.lpMaximumApplicationAddress << endl;
	bitset<8> x(systemInfo.dwActiveProcessorMask);
	cout << "Активные ядра: " << x << endl;
}
void virtualMemoryStatus() {
	const int divider = 1024;
	const int width = 12;
	MEMORYSTATUSEX memoryStatusEx;
	memoryStatusEx.dwLength = sizeof(memoryStatusEx);
	GlobalMemoryStatusEx(&memoryStatusEx);
	cout.width(width-1);
	cout << memoryStatusEx.dwMemoryLoad << "% памяти используется\n";
	cout.width(width);
	cout << memoryStatusEx.ullTotalPhys / divider << " всего Kb памяти\n";
	cout.width(width);
	cout << memoryStatusEx.ullAvailPhys / divider << " доступно Kb памяти\n";
	cout.width(width);
	cout << memoryStatusEx.ullTotalPageFile / divider << " всего Kb страничного файла\n";
	cout.width(width);
	cout << memoryStatusEx.ullAvailPageFile / divider << " доступно Kb страничного файла\n";
	cout.width(width);
	cout << memoryStatusEx.ullTotalVirtual / divider << " всего Kb виртуальной памяти\n";
	cout.width(width);
	cout << memoryStatusEx.ullAvailVirtual / divider << " доступно Kb виртуальной памяти\n";
	cout.width(width);
	cout << memoryStatusEx.ullAvailExtendedVirtual / divider << " доступно Kb расширенной памяти\n";
}
void virtualPageStatus(DWORD address) {
	MEMORY_BASIC_INFORMATION memoryInfo;
	SYSTEM_INFO systemInfo;
	GetSystemInfo(&systemInfo);

	if (!address) {
		cout << "Введите адрес в диапазоне от 0x" << systemInfo.lpMinimumApplicationAddress 
			<< " до 0x" << systemInfo.lpMaximumApplicationAddress << "): 0x";
		cin >> hex >> address;
	}

	VirtualQuery((LPCVOID)address, &memoryInfo, sizeof(memoryInfo));
	cout << "Базовый адрес: 0x" << memoryInfo.BaseAddress << endl;
	cout << "Базовый адрес выделенной памяти: 0x"  << memoryInfo.AllocationBase << endl;

	cout << "Размер региона: " << memoryInfo.RegionSize << endl;

	cout << "Режим доступа: 0x" << hex << memoryInfo.Protect << endl;
	if (memoryInfo.Protect & PAGE_NOACCESS) cout << "  PAGE_NOACCESS" << endl;
	if (memoryInfo.Protect & PAGE_READONLY) cout << "  PAGE_READONLY" << endl;
	if (memoryInfo.Protect & PAGE_READWRITE) cout << "  PAGE_READWRITE" << endl;
	if (memoryInfo.Protect & PAGE_EXECUTE_WRITECOPY) cout << "  PAGE_EXECUTE_WRITECOPY" << endl;
	if (memoryInfo.Protect & PAGE_EXECUTE) cout << "  PAGE_EXECUTE" << endl;
	if (memoryInfo.Protect & PAGE_EXECUTE_READ) cout << "  PAGE_EXECUTE_READ" << endl;
	if (memoryInfo.Protect & PAGE_EXECUTE_READ) cout << "  PAGE_EXECUTE_READ" << endl;
	if (memoryInfo.Protect & PAGE_EXECUTE_READWRITE) cout << "  PAGE_EXECUTE_READWRITE" << endl;
	if (memoryInfo.Protect & PAGE_EXECUTE_WRITECOPY) cout << "  PAGE_EXECUTE_WRITECOPY" << endl;
	if (memoryInfo.Protect & PAGE_GUARD) cout << "  PAGE_GUARD" << endl;
	if (memoryInfo.Protect & PAGE_NOCACHE) cout << "  PAGE_NOCACHE" << endl;
	if (memoryInfo.Protect & PAGE_WRITECOMBINE) cout << "  PAGE_WRITECOMBINE" << endl;
	cout << "Состояние страницы: 0x" << hex << memoryInfo.State << endl;
	if (memoryInfo.State & MEM_COMMIT) cout << "  MEM_COMMIT" << endl;
	if (memoryInfo.State & MEM_FREE) cout << "  MEM_FREE" << endl;
	if (memoryInfo.State & MEM_RESERVE) cout << "  MEM_RESERVE" << endl;
	cout << "Тип страницы: 0x" << hex << memoryInfo.Type << endl;
	if (memoryInfo.Type & MEM_IMAGE) cout << "  MEM_IMAGE" << endl;
	if (memoryInfo.Type & MEM_MAPPED) cout << "  MEM_MAPPED" << endl;
	if (memoryInfo.Type & MEM_PRIVATE) cout << "  MEM_PRIVATE" << endl;
	cout << dec;
}
void separateReserveCommit() {
	PVOID pMemory = 0;
	PVOID pBaseAddress = 0;
	DWORD dwSize = 0;
	cout << "Базовый адрес (0 для автоматического задания адреса системой): 0x";
	cin >> hex >> pBaseAddress;

	cout << "Размер (в байтах): ";
	cin >> dec >> dwSize;

	pMemory = VirtualAlloc(pBaseAddress, dwSize, MEM_RESERVE, PAGE_READWRITE);
	if (pMemory != NULL) {
		cout << "\n\nПамяти зарезервирована: \n";
		virtualPageStatus((DWORD)pMemory);
	}
	else {
		cout << "Не удалось выделить память!" << endl;
		return;
	}

	pMemory = VirtualAlloc(pMemory, dwSize, MEM_COMMIT, PAGE_READWRITE);
	if (pMemory != NULL) {
		cout << "\n\nПамять использована:\n";
		virtualPageStatus((DWORD)pMemory);
	}
	else {
		cout << "Не удалось выделить память!" << endl;
		return;
	}
	//VirtualFree(pMemory, dwSize, MEM_DECOMMIT);
	//cout << "\n\nПамять вышла из использования: \n";
	//virtualPageStatus((DWORD)pMemory);

	//VirtualFree(pMemory, 0, MEM_RELEASE);
	//cout << "\n\nПамять очищена: \n";
	//virtualPageStatus((DWORD)pMemory);
}
void simultaneousReserveCommit() {
	PVOID pMemory = 0;
	PVOID pBaseAddress = 0;
	DWORD dwSize = 0;
	cout << "Базовый адрес (0 для автоматического задания адреса системой): 0x";
	cin >> hex >> pBaseAddress;

	cout << "Размер (в байтах): ";
	cin >> dec >> dwSize;

	pMemory = VirtualAlloc(pBaseAddress, dwSize, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
	if (pMemory != NULL) {
		cout << "\n\nПамять выделена: \n";
		virtualPageStatus((DWORD)pMemory);
	}
	else {
		cout << "Не удалось выделить память!" << endl;
		return;
	}

	//VirtualFree(pMemory, 0, MEM_RELEASE);
	//cout << "\n\nПамять очищена: \n";
	//virtualPageStatus((DWORD)pMemory);
}
void writeData() {
	PVOID pMemory = 0;
	PVOID pBaseAddress = 0;
	DWORD dwSize = 0;
	int data = 0;
	cout << "Базовый адрес (0 для автоматического задания адреса системой): 0x";
	cin >> hex >> pBaseAddress;
	MEMORY_BASIC_INFORMATION memoryInfo;
	VirtualQuery((LPCVOID)pBaseAddress, &memoryInfo, sizeof(memoryInfo));
	if (memoryInfo.Protect & PAGE_NOACCESS) {
		cout << "Память защищена" << endl;
		return;
	}

	cout << "Данные: ";
	cin >> dec >> data;

	if (pBaseAddress) {
		memcpy(pBaseAddress, &data, sizeof(int));
		cout << "Чтение памяти (0x" << hex << pBaseAddress << dec << "): " << (*(PDWORD)pBaseAddress) << endl;
	}
	else {
		pMemory = VirtualAlloc(pBaseAddress, sizeof(int), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
		memcpy(pMemory, &data, sizeof(int));
		cout << "Чтение памяти (0x" << hex << pMemory << dec << "): " << (*(PDWORD)pMemory) << endl;
		//VirtualFree(pMemory, 0, MEM_RELEASE);
	}
}
void protectVirtualPage() {
	PVOID pMemory = 0;
	PVOID pBaseAddress = 0;
	DWORD dwSize = 0;
	cout << "Базовый адрес (0 для автоматического задания адреса системой): 0x";
	cin >> hex >> pBaseAddress;

	if (pBaseAddress) {
		DWORD flOldProtect = 0;
		VirtualProtect(pBaseAddress, sizeof(int), PAGE_NOACCESS, &flOldProtect);
		cout << "\n\nПамять защищена: \n";
		virtualPageStatus((DWORD)pBaseAddress);
	}
	else {
		pMemory = VirtualAlloc(pBaseAddress, sizeof(int), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
		if (pMemory != NULL) {
			cout << "\n\nПамять выделена: \n";
			virtualPageStatus((DWORD)pMemory);
		}

		DWORD flOldProtect = 0;
		VirtualProtect(pMemory, sizeof(int), PAGE_NOACCESS, &flOldProtect);
		cout << "\n\nПамять защищена: \n";
		virtualPageStatus((DWORD)pMemory);

		VirtualFree(pMemory, 0, MEM_RELEASE);
	}
}

void freeVirtualPage(DWORD address) {
	PVOID pMemory = 0;

	if (!address) {
		SYSTEM_INFO systemInfo;
		GetSystemInfo(&systemInfo);
		cout << "Введите адрес в диапазоне от 0x" << systemInfo.lpMinimumApplicationAddress
			<< " до 0x" << systemInfo.lpMaximumApplicationAddress << "): 0x";
		cin >> hex >> address;
	}

	VirtualFree((LPVOID)address, 0, MEM_RELEASE);
	cout << "\n\nПамять очищена: \n";
	virtualPageStatus((DWORD)address);
}