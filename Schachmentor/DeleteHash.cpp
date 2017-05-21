#include "stdafx.h"
#include "DeleteHash.h"


DeleteHash::DeleteHash()
{
	liste = new Hashbrett();
	zeiger = liste;
}


DeleteHash::~DeleteHash()
{
	delete liste;
}

void DeleteHash::delHash(Hashbrett * board)
{
	if (board != NULL)
	{
		if (board->getChild(true) != NULL)
			delHash(board->getChild(true));
		if (board->getChild(false) != NULL)
			delHash(board->getChild(false));
		delete board;
		board = NULL;
	}
}

