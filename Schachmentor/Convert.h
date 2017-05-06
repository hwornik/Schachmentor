#pragma once
#include <string.h>
#include <sstream>

#include "Brett.h"
class Convert
{
public:
	Convert();
	~Convert();
	int getWert(char w);
	int getNumberofChar(char line);
	void setBoardwithFEN(Brett * board, std::string fen);
	std::string getBoardFen(Brett * board);
};

