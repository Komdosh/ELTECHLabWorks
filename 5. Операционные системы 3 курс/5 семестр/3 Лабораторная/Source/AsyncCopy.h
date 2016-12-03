#pragma once
#include <windows.h>
#include <iostream>
#include <string>

using namespace std;

void asyncCopyOfFile();
VOID WINAPI asyncRead(DWORD Code, DWORD nBytes, LPOVERLAPPED lpOv);
VOID WINAPI asyncWrite(DWORD Code, DWORD nBytes, LPOVERLAPPED lpOv);