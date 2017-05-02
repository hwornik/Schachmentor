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
static const char CHARTONUMBER[8] = { 'a','b','c','d','e','f','g','h' };

class Brett
{
public:
	Brett();
	~Brett();
	static int getNumberofChar(char line);
	bool setBoardfromFEN(char pos[100]);
	char getField(int i, int j);
private:
	char Board[8][8];
	void reset();
	int bewertung();
	int getWert(char w);
	Figur *Schwarz[16];
	Figur *Weiss[16];
	int kingpos[2][2];
	int bewertg;
	int figwert;
	bool whitetoMove;
	bool castleKs[2];
	bool castleQs[2];
	int enpassant[2];
	int zugnr;
	int halbzug;
};