#include "stdafx.h"
#include "Brett.h"


Brett::Brett()
{
	for (int i = 0; i < 16; i++)
	{
		Schwarz[i] = NULL;
		Weiss[i] = NULL ;
		if (i < 8)
		{
			for (int j = 0; j < 8; j++)
				board[i][j] = 0;
		}
	}
	this->zugnr = 1;
	this->halbzug = 0;
	maxweiss = 0;
	maxschwarz = 0;
	kingpos[2][2] = {};
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
	return board[i][j];
}

void Brett::setField(int i, int j, int wert)
{
	board[i][j] = wert;
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

Figur * Brett::touchFigur(int number, bool white)
{
		if (white)
			return Weiss[number];
		else
			return Schwarz[number];
}

bool Brett::addnewFigur(bool white)
{
	if (white)
	{
		if (this->maxweiss < 15)
		{
			Weiss[maxweiss] = new Figur();
			maxweiss++;
			return true;
		}
	}
	else
	{
		if (this->maxschwarz < 15)
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
		for (int i = boardint; i < (maxschwarz +1); i++)
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
		for (int i = boardint; i < (maxweiss + 1); i++)
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
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			board[i][j] = 0;
		}
	}
	bewertg = 0;
	figwert = 0;
}

void Brett::makeMove(Figur * fig, int nachx, int nachy)
{
	int oldnr=board[fig->getPosx()][fig->getPosy()];
	board[fig->getPosx()][fig->getPosy()] = 0;
	fig->setPosx(nachx);
	fig->setPosy(nachy);
	board[nachx][nachy] = oldnr;
}




