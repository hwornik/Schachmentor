#pragma once
#include "Figur.h"
#include "Movemennt.h"
#include "Hashbrett.h"

class Calculus
{
public:
	Calculus();
	~Calculus();
	void deepSearch(Hashbrett *boards, Movemennt * move, int tiefe,int godepth, std::string zug, int *wertzug, std::string *bestmove, std::string *ponder, bool *whitesearch);
	void traversSearch(Hashbrett * boards, Movemennt * move, int tiefe, int godepth, std::string zug, int *wertzug, std::string *bestmove, std::string *ponder, bool *whitesearch);
};

