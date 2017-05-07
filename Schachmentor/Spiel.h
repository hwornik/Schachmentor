#pragma once
#include <windows.h>
#include <tchar.h>
#include <strsafe.h>
#include <sstream>
#include <string.h>
#include <iostream>

#include "Brett.h"
#include "Hashbrett.h"
#include "Convert.h"

#define MAX_THREADS 3
#define BUF_SIZE 255
#define PRINT 11
#define WAITING -1

typedef struct MyData {
	bool *quit;
	bool *endsearch;
	int *input;
	bool *ready;
	int val1;
	int val2;
} MYDATA, *PMYDATA;


class Spiel
{
public:
	Spiel();
	~Spiel();
	int startup(int hashsize);
	int shutdown();
	void setHash(std::string hash);
	void setBoardwithFen(std::string fen);
	void makeMoves(std::string moves);
	bool startAction(int action);
private:
	Convert *conv;
	Brett board;
	Hashbrett **hasharray;
	bool beenden;
	static DWORD WINAPI CentralControl(LPVOID lpParam);
	void ErrorHandler(LPTSTR lpszFunction);
	PMYDATA pData;
	DWORD   dwThreadId;
	HANDLE  hThread;
	int eingabe;
	bool ready;
};

