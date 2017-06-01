#include "stdafx.h"
#include "Brett.h"


Brett::Brett()
{
	for (int i = 0; i < 16; i++)
	{
		Schwarz[i] = NULL;
		Weiss[i] = NULL ;
	}
	this->zugnr = 1;
	this->halbzug = 0;
	maxweiss = 0;
	maxschwarz = 0;
}


Brett::~Brett()
{
	for (int i = 0; i < 16; i++)
	{
		if (Schwarz[i] != NULL)
			delete Schwarz[i];
		if (Weiss[i] != NULL)
			delete Weiss[i];
	}
}

int Brett::getField(int i, int j)
{
	for (int ix = 0; ix < maxweiss; ix++)
	{
		if (Weiss[ix]->getPosx() == i && Weiss[ix]->getPosy() == j)
			return ix + 1;
	}
	for (int ix = 0; ix < maxschwarz; ix++)
	{
		if (Schwarz[ix]->getPosx() == i && Schwarz[ix]->getPosy() == j)
			return -(ix + 1);
	}
	return 0;
}
int Brett::getKingPos(bool white, bool xwert)
{
	if (white)
	{
		for (int i = 0; i < maxweiss; i++)
		{
			if (Weiss[i]->getTyp() == 'K')
			{
				if (xwert)
				{
					return Weiss[i]->getPosx();
				}
				else
				{
					return Weiss[i]->getPosy();
				}
			}
		}
	}
	else
	{
		for (int i = 0; i < maxschwarz; i++)
		{
			if (Schwarz[i]->getTyp() == 'k')
			{
				if (xwert)
				{
					return Schwarz[i]->getPosx();
				}
				else
				{
					return Schwarz[i]->getPosy();
				}
			}
		}
	}


}

void Brett::setKingPos(bool white, int x, int y)
{
	if (white)
	{
		for (int i = 0; i < maxweiss; i++)
		{
			if (Weiss[i]->getTyp() == 'K')
			{
					Weiss[i]->setPosx(x);
					Weiss[i]->setPosy(y);
			}
		}
	}
	else
	{
		for (int i = 0; i < maxschwarz; i++)
		{
			if (Schwarz[i]->getTyp() == 'k')
			{
				Schwarz[i]->setPosx(x);
				Schwarz[i]->setPosy(y);
			}
		}
	}
}


Figur * Brett::touchFigur(int number, bool white)
{
	if (white)
		if (number < maxweiss)
			return Weiss[number];
		else
		{
			std::cout << "rrrrrrr" << number;
			return Weiss[0];
		}
	else
		if (number < maxschwarz)
			return Schwarz[number];
		else
		{
			std::cout << "rrrrrrr" << number;
			return Schwarz[0];
		}
}

bool Brett::addnewFigur(bool white)
{
	if (white)
	{
		if (this->maxweiss < 16)
		{
			Weiss[maxweiss] = new Figur();
			maxweiss++;
			return true;
		}
	}
	else
	{
		if (this->maxschwarz < 16)
		{
			Schwarz[maxschwarz] = new Figur();
			maxschwarz++;
			return true;
		}
	}
	return false;
}


bool Brett::deleteFigure(int boardint)
{
	if (boardint < 0)
	{
		boardint = -(boardint + 1);
		delete Schwarz[boardint];
		for (int i = boardint; i < (maxschwarz -1); i++)
		{
			Schwarz[i] = Schwarz[i + 1];
		}
		maxschwarz--;
		for(int i=maxschwarz;i<16;i++)
			Schwarz[i] = NULL;
	}
	else if (boardint > 0)
	{
		boardint = boardint - 1;
		delete Weiss[boardint];
		for (int i = boardint; i < (maxweiss - 1); i++)
		{
			Weiss[i] = Weiss[i + 1];
		}
		maxweiss--;
		for (int i = maxweiss; i<16; i++)
			Weiss[i] = NULL;
	}
	else
		return false;
}

int Brett::getFigurmax(bool white)
{
	if (white)
	{
		return maxweiss;
	}
	else
	{
		return maxschwarz;
	}
}

Figur * Brett::getFigur(int nr, bool white)
{
	if (white)
	{
		return this->Weiss[nr];
	}
	else
	{
		return this->Schwarz[nr];
	}
}


bool Brett::getWhitetoMove()
{
	return this->whitetoMove;
}

void Brett::setWhitetoMove(bool white)
{
	this->whitetoMove = white;
}

void Brett::setCastlKingside(bool white, bool castle)
{
	int i = 1;
	if (white)
		i = 0;
	this->castleKs[i] = castle;
}

void Brett::setCastlQueenside(bool white, bool castle)
{
	int i = 1;
	if (white)
		i = 0;
	this->castleQs[i] = castle;
}

bool Brett::getCastlKingside(bool white)
{
	int i = 1;
	if (white)
		i = 0;
	return this->castleKs[i];
}

bool Brett::getCastlQueenside(bool white)
{
	int i = 1;
	if (white)
		i = 0;
	return this->castleQs[i];
}

void Brett::setEnPassant(int line)
{
	this->enpassant = line;
}

int Brett::getEnPassant()
{
	return this->enpassant;
}

void Brett::setZugNr(int zug)
{
	this->zugnr = zug;
}

void Brett::setHalbzug(int zug)
{
	this->halbzug = zug;
}

int Brett::getZugNr()
{
	return this->zugnr;
}

int Brett::getHalbzug()
{
	return this->halbzug;
}

void Brett::reset()
{
	for (int i = 0; i < 16; i++)
	{
		if (Schwarz[i] != NULL)
		{
			delete Schwarz[i];
			Schwarz[i] = NULL;
		}
		if (Weiss[i] != NULL)
		{
			delete Weiss[i];
			Weiss[i] = NULL;
		}
	}
}

void Brett::makeMove(Figur * fig, int nachx, int nachy)
{
	fig->setPosx(nachx);
	fig->setPosy(nachy);
}




