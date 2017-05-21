#pragma once
#include <sstream>
#include <string.h>

#include "Brett.h"
#include "Figur.h"
#include "Convert.h"
#include "Moving.h"
#include "Hashbrett.h"

class Movemennt
{
public:
	Movemennt();
	~Movemennt();
	Moving * getMovesperFigure(Brett *board, Figur *fig);
	bool proveMove(int** move,Figur *fig, Brett *board);
	bool makeMove(Hashbrett * hash, std::string move);
	bool makeMove(int vonx, int vony, int nachx, int nachy,char promo, Hashbrett * hash);
	bool testRochadeAngriffKS(Brett *board, Figur *fig);
	bool testRochadeAngriffQS(Brett *board, Figur *fig);
	Brett *copyBoard(Brett *board);
private:
	Convert *conv;
};

