#pragma once

#define WINVER 0x0500

#include <iostream>
#include <windows.h>
#include <winbase.h>
#include <io.h>
#include <stdio.h>
#include <tchar.h>
#include <string>
#include <bitset>

void systemInfo();
void virtualMemoryStatus();
void virtualPageStatus(DWORD address);
void separateReserveCommit();
void simultaneousReserveCommit();
void writeData();
void protectVirtualPage();
void freeVirtualPage(DWORD address);