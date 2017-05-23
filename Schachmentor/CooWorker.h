#pragma once
#include <windows.h>
#include <stdio.h>


#include "Calculus.h"

//#define MAX_SEM_COUNT 10
#define THREADCOUNT 8
//HANDLE ghSemaphore;

typedef struct MySCData {
	Hashbrett *boards;
	Movemennt * move;
	int tiefe;
	int godepth;
	std::string zug;
	int *wertzug;
	std::string *bestmove;
	std::string *ponder;
	bool *whitesearch;
} MYSCDATA, *PMYSCDATA;

class CooWorker
{
public:
	CooWorker();
	~CooWorker();
	bool startupCalc(int ThreadNr, Hashbrett *boards, Movemennt * move, int tiefe, int godepth, std::string zug, int *wertzug, std::string *bestmove, std::string *ponder, bool *whitesearch);
	int shutdownCalc();
	int waitdownCalc();
private:
	static DWORD WINAPI Calc(LPVOID);
	HANDLE aThread[THREADCOUNT];
	DWORD ThreadID;
	PMYSCDATA pSCData;
};

