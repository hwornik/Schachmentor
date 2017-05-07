#pragma once
#include "Brett.h"
class Hashbrett
{
public:
	Hashbrett();
	~Hashbrett();
	Hashbrett *getnextBrother();
	Hashbrett *getpreviusBrother();
	Hashbrett *getnextChild();
	Hashbrett *getpreviousChild();
	void setnextBrother(Hashbrett *hashboard);
	void setpreviusBrother(Hashbrett *hashboard);
	void setnextChild(Hashbrett *hashboard);
	void setpreviousChild(Hashbrett *hashboard);
	void setZug(char zug[5]);
	void setBoard(Brett *board);
	Brett * getBoard();
	char* getZug();
private:
	Brett *board;
	Hashbrett *nextBrother, *previousBrother,*nextChild,*previousChild;
	char zug[5];
};

