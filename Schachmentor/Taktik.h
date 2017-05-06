#pragma once
#include "Brett.h"
#include "Convert.h"

class Taktik
{
public:
	Taktik();
	~Taktik();
	int bewertungFig(Brett *board);
private:
	Convert *conv;
};

