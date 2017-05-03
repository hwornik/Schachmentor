#pragma once
#include <windows.h>
#include <tchar.h>
#include <strsafe.h>

#define MAX_THREADS 3
#define BUF_SIZE 255

typedef struct MyData {
	int val1;
	int val2;
} MYDATA, *PMYDATA;


class Spiel
{
public:
	Spiel();
	~Spiel();
	int startup();
	int shutdown();
private:
	static DWORD WINAPI CentralControl(LPVOID lpParam);
	void ErrorHandler(LPTSTR lpszFunction);
	PMYDATA pData;
	DWORD   dwThreadId;
	HANDLE  hThread;
};

