#pragma once
#include <string.h>
#include <sstream>
#include <iostream>

#include "Brett.h"

static const char NUMBERTOCHAR[8] = { 'a','b','c','d','e','f','g','h' };

class Convert
{
public:
	Convert();
	~Convert();
	int getWert(char w);
	int getNumberofChar(char line);
	int getcharfromNumber(int line);
	void setBoardwithFEN(Brett * board, std::string fen);
	std::string getBoardFen(Brett * board);
	void displayBoard(Brett * board);
};

