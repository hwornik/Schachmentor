#pragma once
#include <sstream>

#include "Brett.h"
class Hashbrett
{
public:
	Hashbrett();
	~Hashbrett();
	Hashbrett *getBrother();
	Hashbrett *getChild();
	void setBrother(Hashbrett *hashboard);
	void setChild(Hashbrett *hashboard);
	void setZug(char zug[5]);
	void setBoard(Brett *board);
	Brett * getBoard();
	char* getZug();
	std::string getFenString();
	void setFenString(std::string fenstring);
private:
	Brett *board;
	Hashbrett *brother, *child;
	char zug[5];
	std::string fenstring;
};

