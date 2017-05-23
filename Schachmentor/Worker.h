#pragma once
#include <windows.h>
#include <strsafe.h>
#include <iostream>

#include "ThreadData.h"
#include "DeleteHash.h"
#include "Hashbrett.h"
#include "Constants.h"
#include "Movemennt.h"
#include "Calculus.h"

class Worker
{
public:
	Worker();
	~Worker();
	void ErrorHandler(LPTSTR lpszFunction);
	int startupDelete(Hashbrett *deleteone, Hashbrett *deletetwo);
	int startupSearchTree(Hashbrett *searchtree, bool *quit, bool *end, bool *endatDepth, bool *whitesearch);
	int startupSearch(Hashbrett *searchtree, bool *quit,bool *end,bool *endatDepth, bool *whitesearch);
private:
	static DWORD WINAPI DeleteHashbrett(LPVOID lpParam);
	DWORD   dwThreadIdD;
	HANDLE  hThreadD;
	PMYDDATA pDData;
	static DWORD WINAPI searchMoveTree(LPVOID lpParam);
	DWORD   dwThreadIdR;
	HANDLE  hThreadR;
	PMYRDATA pRData;
	static DWORD WINAPI searchMove(LPVOID lpParam);
	DWORD   dwThreadIdS;
	HANDLE  hThreadS;
	PMYSDATA pSData;
};

