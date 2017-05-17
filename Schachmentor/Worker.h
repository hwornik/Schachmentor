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
private:
	static DWORD WINAPI DeleteHashbrett(LPVOID lpParam);
	DWORD   dwThreadIdD;
	HANDLE  hThreadD;
	PMYDDATA pDData;
};

