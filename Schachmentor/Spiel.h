#pragma once
#include <windows.h>
#include <tchar.h>
#include <strsafe.h>
#include <sstream>
#include <string.h>
#include <iostream>

#include "Brett.h"

#define MAX_THREADS 3
#define BUF_SIZE 255

typedef struct MyData {
	bool *quit;
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
	void setBrettwithFEN(std::string fen);
	void setHash(std::string hash);
	void makeMoves(std::string moves);
private:
	Brett board;
	bool beenden;
	static DWORD WINAPI CentralControl(LPVOID lpParam);
	void ErrorHandler(LPTSTR lpszFunction);
	PMYDATA pData;
	DWORD   dwThreadId;
	HANDLE  hThread;
};

