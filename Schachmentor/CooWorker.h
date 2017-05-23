#pragma once
#include <windows.h>
#include <stdio.h>

#define MAX_SEM_COUNT 10
#define THREADCOUNT 12
HANDLE ghSemaphore;
class CooWorker
{
public:
	CooWorker();
	~CooWorker();
	bool startupCalc(int ThreadNr);
	int shutdownCalc();
private:
	static DWORD WINAPI Calc(LPVOID);
	HANDLE aThread[THREADCOUNT];
	DWORD ThreadID;
};

