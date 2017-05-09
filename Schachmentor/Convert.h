#pragma once
#include <string.h>
#include <sstream>
#include <iostream>

#include "Brett.h"
#include "Constants.h"

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

