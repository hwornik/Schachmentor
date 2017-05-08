#pragma once
#include <ctype.h>

#include "Figur.h"

class Brett
{
public:
	Brett();
	~Brett();
	int getField(int i, int j);
	void setField(int i, int j,int wert);
	int getKingPos(bool white,bool xwert);
	void setKingPos(bool white, int x, int y);
	int getBewertung();
	void setBewertung(int wert);
	Figur *touchSchwarz(int number);
	Figur *touchWeiss(int number);
	bool addnewFigurWeiss();
	bool addnewFigurSchwarz();
	bool deleteFigure(int boardint);
	int getFigurmax(bool white);
	void setFigurenwert(int wert);
	int getFigurenwert();
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
	bool makeMove(Figur *fig, int nachx, int nachy);

private:
	int board[8][8];
	int maxschwarz;
	int maxweiss;
	Figur *Schwarz[16];
	Figur *Weiss[16];
	int kingpos[2][2];
	int bewertg;
	int figwert;
	bool whitetoMove;
	bool castleKs[2];
	bool castleQs[2];
	int enpassant;
	int zugnr;
	int halbzug;
};