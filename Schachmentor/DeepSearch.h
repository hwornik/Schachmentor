#pragma once
#include <iostream>

#include "Hashbrett.h"
#include "Movemennt.h"
#include "Convert.h"
#include "Calculus.h"
#include "CooWorker.h"

class DeepSearch
{
public:
	DeepSearch();
	~DeepSearch();
	void searchMove(Hashbrett * searchtree, bool * quit, bool * end, bool * endatDepth, bool * whitesearch);
	void searchMoveToTree(Hashbrett * searchtree, bool * quit, bool * end, bool * endatDepth, bool * whitesearch);
};

