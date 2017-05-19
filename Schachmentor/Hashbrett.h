#pragma once
#include <sstream>

#include "Brett.h"
class Hashbrett
{
public:
	Hashbrett();
	~Hashbrett();
	Hashbrett *getChild(bool white);
	void setChild(Hashbrett *hashboard, bool white);
	void setZug(char zug[5]);
	void setBoard(Brett *board);
	Brett * getBoard();
	char* getZug();
	std::string getFenString();
	void setFenString(std::string fenstring);
private:
	Brett *board;
	Hashbrett *weiss, *schwarz;
	char zug[5];
	std::string fenstring;
};

