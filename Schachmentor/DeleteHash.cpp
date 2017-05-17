#include "stdafx.h"
#include "DeleteHash.h"


DeleteHash::DeleteHash()
{
}


DeleteHash::~DeleteHash()
{
}

void DeleteHash::delHash(Hashbrett * board)
{
	if (board != NULL)
		delHash(board->getBrother());
	if (board != NULL)
		delHash(board->getChild());
	delete board;
}
