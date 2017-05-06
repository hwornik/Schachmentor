#pragma once
#include <ctype.h>

#include "Figur.h"

static const char BRETTFARBEN[8][8] = {  { 'b','w','b','w','b','w','b','w' },
										{ 'w','b','w','b','w','b','w','b' },
										{ 'b','w','b','w','b','w','b','w' },
										{ 'w','b','w','b','w','b','w','b' },
										{ 'b','w','b','w','b','w','b','w' },
										{ 'w','b','w','b','w','b','w','b' },
										{ 'b','w','b','w','b','w','b','w' },
										{ 'w','b','w','b','w','b','w','b' } };
static const char NUMBERTOCHAR[8] = { 'a','b','c','d','e','f','g','h' };

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
	int getFigurmax(bool white);
	void setFigurenwert(int wert);
	int getFigurenwert();
	bool getWhitetoMove();
	void setWhitetoMove(bool white);
	void setCastlKingside(bool white, bool castle);
	void setCastlQueenside(bool white, bool castle);
	bool getCastlKingside(bool white);
	bool getCastlQueenside(bool white);
	void setEnPassant(bool enpass);
	bool getEnPassant();
	void setZugNr(int zug);
	void setHalbzug(int zug);
	int getZugNr();
	int getHalbzug();
	void reset();
private:
	int Board[8][8];
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
	bool enpassant;
	int zugnr;
	int halbzug;
};