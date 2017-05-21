#pragma once
#include "Figur.h"
#include "Movemennt.h"
#include "Hashbrett.h"

class Calculus
{
public:
	Calculus();
	~Calculus();
	void deepSearch(Hashbrett *boards, Movemennt * move, int tiefe,int godepth, std::string zug);
	void traversSearch(Hashbrett * boards, Movemennt * move, int tiefe, int godepth, std::string zug);
};

