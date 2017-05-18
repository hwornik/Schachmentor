#pragma once
#include <windows.h>
#include <strsafe.h>
#include <iostream>

#include "ThreadData.h"
#include "DeleteHash.h"
#include "Hashbrett.h"
#include "Constants.h"
class Worker
{
public:
	Worker();
	~Worker();
	void ErrorHandler(LPTSTR lpszFunction);
	int startupDelete(Hashbrett *deleteone, Hashbrett *deletetwo);
	int startuprekonHash(std::string fenkey, Hashbrett *oldhash, Hashbrett *gamehash, bool *rekonfigureHash, bool *stopsearchhash);
private:
	static DWORD WINAPI DeleteHashbrett(LPVOID lpParam);
	DWORD   dwThreadIdD;
	HANDLE  hThreadD;
	PMYDDATA pDData;
	static DWORD WINAPI rekonfHashbrett(LPVOID lpParam);
	DWORD   dwThreadIdR;
	HANDLE  hThreadR;
	PMYRDATA pRData;
};

