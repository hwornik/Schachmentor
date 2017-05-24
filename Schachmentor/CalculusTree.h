#pragma once
#include "Hashbrett.h"
#include "Movemennt.h"
#include "CooWorker.h"

class CalculusTree
{
public:
	CalculusTree();
	~CalculusTree();
	void traversSearch(Hashbrett * boards, Movemennt * move, int tiefe, int godepth, std::string zug, int * wertzug, std::string * bestmove, std::string * ponder, bool * whitesearch);
	int getThreadN();
	void incThreadN();
	int setThreadNZero();
private:
	CooWorker *coop;
	static int thread;
	int werte[THREADCOUNT];
	int maxthread = 0;
	std::string bester[THREADCOUNT], pondi[THREADCOUNT];
};


