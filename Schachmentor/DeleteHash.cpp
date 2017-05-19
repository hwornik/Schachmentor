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
		delHash(board->getChild(true));
	if (board != NULL)
		delHash(board->getChild(false));
	delete board;
}
