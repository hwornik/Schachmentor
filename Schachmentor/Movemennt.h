#pragma once
#include <sstream>
#include <string.h>

#include "Brett.h"
#include "Figur.h"
#include "Convert.h"

class Movemennt
{
public:
	Movemennt();
	~Movemennt();
	int** getMovesperFigure(Brett *board, Figur *fig); 
	bool proveMove(int** move,Figur *fig, Brett *board);
	bool makeMove(Brett *board, std::string move);
	bool testRochadeAngriffKS(Brett *board, Figur *fig);
	bool testRochadeAngriffQS(Brett *board, Figur *fig);
private:
	Convert *conv;
};

