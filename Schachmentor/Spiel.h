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
#include "Constants.h"
#include "Movemennt.h"


typedef struct MyData {
	bool *quit;
	bool *endsearch;
	int *input;
	bool *ready;
	std::string *fenstring;
	char **movestodo;
	std::string *movemade;
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
	void searchMoves(char *smove);
	bool startAction(int action);
	bool setFenString(std::string fen);
	bool setMoveMadebyGUI(std::string move);
private:
	Hashbrett **hasharray;
	bool beenden;
	static DWORD WINAPI CentralControl(LPVOID lpParam);
	void ErrorHandler(LPTSTR lpszFunction);
	PMYDATA pData;
	DWORD   dwThreadId;
	HANDLE  hThread;
	int eingabe;
	bool ready;
	std::string fen;
	char **moves;
	int indexmoves;
	std::string move;
};

