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
		if (board->touchWeiss(i) != NULL)
		{
			weisswert += conv->getWert(board->touchWeiss(i)->getTyp());
			wi++;
		}
		if (board->touchWeiss(i) != NULL)
		{
			schwarzwert += conv->getWert(board->touchWeiss(i)->getTyp());
		}
	}
	board->setFigurenwert(weisswert - schwarzwert);
	return board->getFigurenwert();
}