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
	void setZug(std::string zug);
	void setBoard(Brett *board);
	Brett * getBoard();
	std::string getZug();
	std::string getFenString();
	void setFenString(std::string fenstring);
	std::string getZugFolge();
	void setZugFolge(std::string zugfolge);
private:
	Brett *board;
	Hashbrett *weiss, *schwarz;
	std::string zug;
	std::string fenstring;
	std::string zugfolge;
};

