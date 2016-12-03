#pragma once

#define _WIN32_WINNT 0x501

#include <iostream>
#include <windows.h>
#include <io.h>
#include <stdio.h>
#include <tchar.h>
#include <string>
#include <sstream>

void showDrivesList();
void showDriveInfo();
void createFolder();
void deleteFolder();
void createFile();
void copyFile();
void moveFile();
void fileInfo();
void changeFileAttributes();
void changeCreationTime();


#if (_WIN32 >= 0x0500)
WINBASEAPI BOOL WINAPI GetFileSizeEx(HANDLE, PLARGE_INTEGER);
#endif

VOID WINAPI asyncRead(DWORD Code, DWORD nBytes, LPOVERLAPPED pOv);
VOID WINAPI asyncWrite(DWORD Code, DWORD nBytes, LPOVERLAPPED pOv);