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

	void setFigurenwert(int wert);

	int getFigurenwert();

	std::string getZug();
	std::string getFenString();
	void setFenString(std::string fenstring);
	std::string getZugFolge();
	void setZugFolge(std::string zugfolge);
	bool getWhitetoMove();
	void setWhitetoMove(bool white);
private:
	Hashbrett *weiss, *schwarz;
	std::string zug;
	std::string fenstring;
	std::string zugfolge;
	bool whitetomove;
	int figwert;
};

