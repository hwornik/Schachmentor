#pragma once
#include "Brett.h"
class Hashbrett
{
public:
	Hashbrett();
	~Hashbrett();
private:
	Brett *board;
	Hashbrett *nextBrother, *previousBrother,*nextChild,*previousChild;
};

