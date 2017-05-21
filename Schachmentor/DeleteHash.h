#pragma once
#include <iostream>

#include "Hashbrett.h"

class DeleteHash
{
public:
	DeleteHash();
	~DeleteHash();
	void delHash(Hashbrett *board);
private:
	Hashbrett *liste,*zeiger;
};

