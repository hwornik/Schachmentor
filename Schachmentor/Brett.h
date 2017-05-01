#pragma once
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
private:
	Figur *Schwarz[16];
	Figur *Weiss[16];
	

};