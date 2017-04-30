#pragma once
#include "Figur.h"
class Brett
{
public:
	Brett();
	~Brett();
private:
	Figur *Schwarz[16];
	Figur *Weiss[16];
};

