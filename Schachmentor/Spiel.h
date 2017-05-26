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
#include "ThreadData.h"
#include "DeepSearch.h"
#include "Worker.h"


class Spiel
{
public:
	Spiel();
	~Spiel();
	int startup();
	int shutdown();
	void setHashsize(int hash);
	void setBoardwithFen(std::string fen);
	void searchMoves(char *smove);
	bool startAction(int action);
	bool setFenString(std::string fen);
	bool setMoveMadebyGUI(std::string move);
	bool getPonder();
	int getWTime();
	int getBTime();
	int getWinc();
	int getBinc();
	int getMovestogo();
	int getDepth();
	int getNodes();
	int getMate();
	int getMovetime();
	bool getGoinfinite();
	int getHashsize();
	void setWTime(int wtime);
	void setBTime(int btime);
	void setWinc(int winc);
	void setBinc(int binc);
	void setMovestogo(int movestogo);
	void setDepth(int depth);
	void setNodes(int nodes);
	void setMate(int mate);
	void setMovetime(int movetime);
	void setGoinfinite(bool infinite);
	void setPonder(bool ponder);
	void stopthinking();
private:
	Hashbrett **hasharray;
	bool beenden;
	bool stop;
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
	bool ponder;
	int wtime;
	int btime;
	int winc;
	int binc;
	int movestogo;
	int depth;
	int nodes;
	int mate;
	int movetime;
	bool infinite;
	int hashsize;
};

