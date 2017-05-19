#include "stdafx.h"
#include "Taktik.h"


Taktik::Taktik()
{
	conv = new Convert();
}


Taktik::~Taktik()
{
}

int Taktik::bewertungFig(Brett *board)
{
	int weisswert = 0, schwarzwert = 0, wi = 0, si = 0;
	for (int i = 0; i < 16; i++)
	{
		if (board->touchFigur(i,true) != NULL)
		{
			weisswert += conv->getWert(board->touchFigur(i,true)->getTyp());
			wi++;
		}
		if (board->touchFigur(i,false) != NULL)
		{
			schwarzwert += conv->getWert(board->touchFigur(i,false)->getTyp());
		}
	}
	board->setFigurenwert(weisswert - schwarzwert);
	return board->getFigurenwert();
}