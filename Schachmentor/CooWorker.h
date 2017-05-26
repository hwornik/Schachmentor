#pragma once
#include <windows.h>
#include <stdio.h>

#include "Constants.h"
#include "Calculus.h"

//#define MAX_SEM_COUNT 10
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
	bool startupCalc(bool tree,int ThreadNr, Hashbrett *boards, Movemennt * move, int tiefe, int godepth, std::string zug, int *wertzug, std::string *bestmove, std::string *ponder, bool *whitesearch);
	int shutdownCalc(int maxthread);
	int waitdownCalc();
private:
	static DWORD WINAPI Calc(LPVOID);
	static DWORD WINAPI CalcTree(LPVOID lpParam);
	HANDLE aThread[THREADCOUNT];
	DWORD ThreadID;
	PMYSCDATA pSCData;
};

