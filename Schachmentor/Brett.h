#pragma once
#include <ctype.h>
#include <iostream>

#include "Figur.h"

class Brett
{
public:
	Brett();
	~Brett();
	int getField(int i, int j);
	int getKingPos(bool white,bool xwert);
	void setKingPos(bool white, int x, int y);
	Figur *touchFigur(int number, bool white);
	bool addnewFigur(bool white);
	bool deleteFigure(int boardint);
	int getFigurmax(bool white);
	Figur * getFigur(int nr,bool white);
	bool getWhitetoMove();
	void setWhitetoMove(bool white);
	void setCastlKingside(bool white, bool castle);
	void setCastlQueenside(bool white, bool castle);
	bool getCastlKingside(bool white);
	bool getCastlQueenside(bool white);
	void setEnPassant(int line);
	int getEnPassant();
	void setZugNr(int zug);
	void setHalbzug(int zug);
	int getZugNr();
	int getHalbzug();
	void reset();
	void makeMove(Figur *fig, int nachx, int nachy);

private:
	int maxschwarz;
	int maxweiss;
	Figur *Schwarz[16];
	Figur *Weiss[16];
	bool whitetoMove;
	bool castleKs[2];
	bool castleQs[2];
	int enpassant;
	int zugnr;
	int halbzug;
};