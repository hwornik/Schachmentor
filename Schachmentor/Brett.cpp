#include "stdafx.h"
#include "Brett.h"


Brett::Brett()
{
	for (int i = 0; i < 16; i++)
	{
		Schwarz[i] = NULL;
		Weiss[i] = NULL ;
	}
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
	delete Schwarz;
	delete Weiss;
}

int Brett::getField(int i, int j)
{
	return Board[i][j];
}

void Brett::setField(int i, int j, int wert)
{
	Board[i][j] = wert;
}

int Brett::getKingPos(bool white, bool xwert)
{
	int i=1,j=1;
	if (white)
		i = 0;
	if (xwert)
		j = 0;
	return this->kingpos[i][j];
}

void Brett::setKingPos(bool white, int x, int y)
{
	int i = 1;
	if (white)
		i = 0;
	this->kingpos[i][0] = x;
	this->kingpos[i][1] = y;
}

int Brett::getBewertung()
{
	return this->bewertg;
}

void Brett::setBewertung(int wert)
{
	this->bewertg = wert;
}

Figur * Brett::touchSchwarz(int number)
{
	return Schwarz[number];
}

Figur * Brett::touchWeiss(int number)
{
	return Weiss[number];
}

bool Brett::addnewFigurWeiss()
{
	if (this->maxweiss < 16)
	{
		Weiss[maxweiss] = new Figur();
		maxweiss++;
		return true;
	}
	return false;
}

bool Brett::addnewFigurSchwarz()
{
	if (this->maxweiss < 16)
	{
		Schwarz[maxweiss] = new Figur();
		maxschwarz++;
		return true;
	}
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

void Brett::setFigurenwert(int wert)
{
	this->figwert = wert;
}

int Brett::getFigurenwert()
{
	return this->figwert;
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

void Brett::setEnPassant(bool enpass)
{
	this->enpassant = enpass;
}

bool Brett::getEnPassant()
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
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			Board[i][j] = 0;
		}
	}
	bewertg = 0;
	figwert = 0;
}


