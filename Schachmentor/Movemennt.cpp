#include "stdafx.h"
#include "Movemennt.h"


Movemennt::Movemennt()
{
	conv = new Convert();
}


Movemennt::~Movemennt()
{
}

int ** Movemennt::getMovesperFigure(Brett * board, Figur * fig)
{
	int index = 0;
	int ** moves = new int*[29];
	// Felder für Pawn-----------------------------------------------------------------------------------------------------------------
	// Weiss-------------------------------------------------------------------------------------------------------------------------
	if (fig->getTyp() == 'P')
	{
		if ((fig->getPosy() + 1) < 8 && board->getField(fig->getPosx(), (fig->getPosy() + 1)) == 0)
		{
			moves[index] = new int[3];
			moves[index][0] = fig->getPosx();
			moves[index][1] = fig->getPosy() + 1;
			moves[index][2] = 0;
			index++;
		}
		if (fig->getPosx() == 1 && board->getField(fig->getPosx(), (fig->getPosy() + 1)) == 0 && board->getField(fig->getPosx(), (fig->getPosy() + 2)) == 0)
		{
			moves[index] = new int[3];
			moves[index][0] = fig->getPosx();
			moves[index][1] = fig->getPosy() + 2;
			moves[index][2] = 0;
			index++;
		}
		if ((fig->getPosx() + 1) < 8 && (fig->getPosy() + 1) < 8 && board->getField(fig->getPosx() + 1, fig->getPosy() + 1) < 0)
		{
			moves[index] = new int[3];
			moves[index][0] = fig->getPosx() + 1;
			moves[index][1] = fig->getPosy() + 1;
			moves[index][2] = conv->getWert(board->touchSchwarz(-(board->getField(fig->getPosx() + 1, fig->getPosy() + 1) + 1))->getTyp());
			index++;
		}
		if ((fig->getPosx() + 1) < 8 && (fig->getPosy() - 1) > -1 && board->getField(fig->getPosx() + 1, fig->getPosy() - 1) < 0)
		{
			moves[index] = new int[3];
			moves[index][0] = fig->getPosx() + 1;
			moves[index][1] = fig->getPosy() - 1;
			moves[index][2] = conv->getWert(board->touchSchwarz(-(board->getField(fig->getPosx() + 1, fig->getPosy() - 1) + 1))->getTyp());
			index++;
		}
	}
	//Schwarz
	else if (fig->getTyp() == 'p')
	{
		if ( (fig->getPosy() - 1) > -1 && board->getField(fig->getPosx(), (fig->getPosy() - 1)) == 0)
		{
			moves[index] = new int[3];
			moves[index][0] = fig->getPosx();
			moves[index][1] = fig->getPosy() - 1;
			moves[index][2] = 0;
			index++;
		}
		if (fig->getPosx() == 6 && board->getField(fig->getPosx(), (fig->getPosy() - 1)) == 0 && board->getField(fig->getPosx(), (fig->getPosy() - 2)) == 0)
		{
			moves[index] = new int[3];
			moves[index][0] = fig->getPosx();
			moves[index][1] = fig->getPosy() - 2;
			moves[index][2] = 0;
			index++;
		}
		if ((fig->getPosx() - 1) < -1 && (fig->getPosy() + 1) < 8 && board->getField(fig->getPosx() - 1, fig->getPosy() + 1) > 0)
		{
			moves[index] = new int[3];
			moves[index][0] = fig->getPosx() - 1;
			moves[index][1] = fig->getPosy() + 1;
			moves[index][2] = -conv->getWert(board->touchWeiss((board->getField(fig->getPosx() - 1, fig->getPosy() + 1) - 1))->getTyp());
			index++;
		}
		if ((fig->getPosx() - 1) > -1 && (fig->getPosy() - 1) > -1 && board->getField(fig->getPosx() - 1, fig->getPosy() - 1) > 0)
		{
			moves[index] = new int[3];
			moves[index][0] = fig->getPosx() - 1;
			moves[index][1] = fig->getPosy() - 1;
			moves[index][2] = -conv->getWert(board->touchWeiss((board->getField(fig->getPosx() - 1, fig->getPosy() - 1) - 1))->getTyp());
			index++;
		}
	}
	// Springer ------------------------------------------------------------------------------------------------------------
	else if (toupper(fig->getTyp()) == 'N' )
	{
		if ((fig->getPosx() + 2) < 7 && (fig->getPosy() + 1) < 8 ) 
		{
			if (board->getField(fig->getPosx() + 2, fig->getPosy() + 1) == 0)
			{
				moves[index] = new int[3];
				moves[index][0] = fig->getPosx() + 2;
				moves[index][1] = fig->getPosy() + 1;
				moves[index][2] = 0;
			}
			else if (isupper(fig->getTyp()) && board->getField(fig->getPosx() + 2, fig->getPosy() + 1) < 0)
			{
				moves[index] = new int[3];
				moves[index][0] = fig->getPosx() + 2;
				moves[index][1] = fig->getPosy() + 1;
				moves[index][2]= conv->getWert(board->touchSchwarz(-(board->getField(fig->getPosx() + 2 , fig->getPosy() + 1) + 1))->getTyp());
			}
			else if (!isupper(fig->getTyp()) && board->getField(fig->getPosx() + 2, fig->getPosy() + 1) > 0)
			{
				moves[index] = new int[3];
				moves[index][0] = fig->getPosx() + 2;
				moves[index][1] = fig->getPosy() + 1;
				moves[index][2] = -conv->getWert(board->touchWeiss(board->getField(fig->getPosx() + 2, fig->getPosy() + 1) - 1)->getTyp());
			}
			index++;
		}
		if ((fig->getPosx() + 2) < 8 && (fig->getPosy() - 1) > -1)
		{
			if(board->getField(fig->getPosx() + 2, fig->getPosy() - 1) == 0)
			{
				moves[index] = new int[3];
				moves[index][0] = fig->getPosx() + 2;
				moves[index][1] = fig->getPosy() - 1;
				moves[index][2] = 0;
			}
			else if (isupper(fig->getTyp()) && board->getField(fig->getPosx() + 2, fig->getPosy() - 1) < 0)
			{
				moves[index] = new int[3];
				moves[index][0] = fig->getPosx() + 2;
				moves[index][1] = fig->getPosy() - 1;
				moves[index][2] = conv->getWert(board->touchSchwarz(-(board->getField(fig->getPosx() + 2, fig->getPosy() - 1) + 1))->getTyp());
			}
			else if (!isupper(fig->getTyp()) && board->getField(fig->getPosx() + 2, fig->getPosy() - 1) > 0)
			{
				moves[index] = new int[3];
				moves[index][0] = fig->getPosx() + 2;
				moves[index][1] = fig->getPosy() - 1;
				moves[index][2] = -conv->getWert(board->touchWeiss(board->getField(fig->getPosx() + 2, fig->getPosy() - 1) - 1)->getTyp());
			}
			index++;
		}
		if ((fig->getPosx() - 2) > -1 && (fig->getPosy() + 1) < 8 )
		{
			if (board->getField(fig->getPosx() - 2, fig->getPosy() + 1) == 0)
			{
				moves[index] = new int[3];
				moves[index][0] = fig->getPosx() - 2;
				moves[index][1] = fig->getPosy() + 1;
				moves[index][2] = 0;
			}
			else if (isupper(fig->getTyp()) && board->getField(fig->getPosx() - 2, fig->getPosy() + 1) < 0)
			{
				moves[index] = new int[3];
				moves[index][0] = fig->getPosx() - 2;
				moves[index][1] = fig->getPosy() + 1;
				moves[index][2] = conv->getWert(board->touchSchwarz(-(board->getField(fig->getPosx() - 2, fig->getPosy() + 1) + 1))->getTyp());
			}
			else if (!isupper(fig->getTyp()) && board->getField(fig->getPosx() - 2, fig->getPosy() + 1) > 0)
			{
				moves[index] = new int[3];
				moves[index][0] = fig->getPosx() - 2;
				moves[index][1] = fig->getPosy() + 1;
				moves[index][2] = -conv->getWert(board->touchWeiss(board->getField(fig->getPosx() - 2, fig->getPosy() + 1) - 1)->getTyp());
			}
			index++;
		}
		if ((fig->getPosx() - 2) > -1 && (fig->getPosy() - 1) > -1 )
		{
			if (board->getField(fig->getPosx() - 2, fig->getPosy() - 1) == 0)
			{
				moves[index] = new int[3];
				moves[index][0] = fig->getPosx() - 2;
				moves[index][1] = fig->getPosy() - 1;
				moves[index][2] = 0;
			}
			else if (isupper(fig->getTyp()) && board->getField(fig->getPosx() - 2, fig->getPosy() - 1) < 0)
			{
				moves[index] = new int[3];
				moves[index][0] = fig->getPosx() - 2;
				moves[index][1] = fig->getPosy() - 1;
				moves[index][2] = conv->getWert(board->touchSchwarz(-(board->getField(fig->getPosx() - 2, fig->getPosy() - 1) + 1))->getTyp());
			}
			else if (!isupper(fig->getTyp()) && board->getField(fig->getPosx() - 2, fig->getPosy() - 1) > 0)
			{
				moves[index] = new int[3];
				moves[index][0] = fig->getPosx() - 2;
				moves[index][1] = fig->getPosy() - 1;
				moves[index][2] = -conv->getWert(board->touchWeiss(board->getField(fig->getPosx() - 2, fig->getPosy() - 1) - 1)->getTyp());
			}
			index++;
		}
		if ((fig->getPosx() + 1) < 8 && (fig->getPosy() + 2) < 8 )
		{
			if (board->getField(fig->getPosx() + 1, fig->getPosy() + 2) == 0)
			{
				moves[index] = new int[3];
				moves[index][0] = fig->getPosx() + 1;
				moves[index][1] = fig->getPosy() + 2;
				moves[index][2] = 0;
			}
			if (isupper(fig->getTyp()) && board->getField(fig->getPosx() + 1, fig->getPosy() + 2) < 0)
			{
				moves[index] = new int[3];
				moves[index][0] = fig->getPosx() + 1;
				moves[index][1] = fig->getPosy() + 2;
				moves[index][2] = conv->getWert(board->touchSchwarz(-(board->getField(fig->getPosx() + 1, fig->getPosy() + 2) + 1))->getTyp());
			}
			else if (!isupper(fig->getTyp()) && board->getField(fig->getPosx() + 1, fig->getPosy() + 2) > 0)
			{
				moves[index] = new int[3];
				moves[index][0] = fig->getPosx() + 1;
				moves[index][1] = fig->getPosy() + 2;
				moves[index][2] = -conv->getWert(board->touchWeiss(board->getField(fig->getPosx() + 1, fig->getPosy() + 2) - 1)->getTyp());
			}
			index++;
		}
		if ((fig->getPosx() - 1) > -1 && (fig->getPosy() + 2) < 8 )
		{
			if (board->getField(fig->getPosx() - 1, fig->getPosy() + 2) == 0)
			{
				moves[index] = new int[3];
				moves[index][0] = fig->getPosx() - 1;
				moves[index][1] = fig->getPosy() + 2;
				moves[index][2] = 0;
			}
			else if (isupper(fig->getTyp()) && board->getField(fig->getPosx() - 1, fig->getPosy() + 2) < 0)
			{
				moves[index] = new int[3];
				moves[index][0] = fig->getPosx() - 1;
				moves[index][1] = fig->getPosy() + 2;
				moves[index][2] = conv->getWert(board->touchSchwarz(-(board->getField(fig->getPosx() - 1, fig->getPosy() + 2) + 1))->getTyp());
			}
			else if (!isupper(fig->getTyp()) && board->getField(fig->getPosx() - 1, fig->getPosy() + 2) > 0)
			{
				moves[index] = new int[3];
				moves[index][0] = fig->getPosx() - 1;
				moves[index][1] = fig->getPosy() + 2;
				moves[index][2] = -conv->getWert(board->touchWeiss(board->getField(fig->getPosx() - 1, fig->getPosy() + 2) - 1)->getTyp());
			}
			index++;
		}
		else if ((fig->getPosx() + 1) < 8 && (fig->getPosy() - 2) > -1)
		{
			if (board->getField(fig->getPosx() + 1, fig->getPosy() - 2) == 0)
			{
				moves[index] = new int[3];
				moves[index][0] = fig->getPosx() + 1;
				moves[index][1] = fig->getPosy() - 2;
				moves[index][2] = 0;
			}
			else if (isupper(fig->getTyp()) && board->getField(fig->getPosx() + 1, fig->getPosy() - 2) < 0)
			{
				moves[index] = new int[3];
				moves[index][0] = fig->getPosx() + 1;
				moves[index][1] = fig->getPosy() - 2;
				moves[index][2] = conv->getWert(board->touchSchwarz(-(board->getField(fig->getPosx() + 1, fig->getPosy() - 2) + 1))->getTyp());
			}
			else if (!isupper(fig->getTyp()) && board->getField(fig->getPosx() + 1, fig->getPosy() - 2) > 0)
			{
				moves[index] = new int[3];
				moves[index][0] = fig->getPosx() + 1;
				moves[index][1] = fig->getPosy() - 2;
				moves[index][2] = -conv->getWert(board->touchWeiss(board->getField(fig->getPosx() + 1, fig->getPosy() - 2) - 1)->getTyp());
			}
			index++;
		}
		if ((fig->getPosx() - 1) > -1 && (fig->getPosy() -2 ) > -1 )
		{
			if (board->getField(fig->getPosx() - 1, fig->getPosy() - 2) == 0)
			{
				moves[index] = new int[3];
				moves[index][0] = fig->getPosx() - 1;
				moves[index][1] = fig->getPosy() - 2;
				moves[index][2] = 0;
			}
			if (isupper(fig->getTyp()) && board->getField(fig->getPosx() - 1, fig->getPosy() - 2) < 0)
			{
				moves[index] = new int[3];
				moves[index][0] = fig->getPosx() - 1;
				moves[index][1] = fig->getPosy() - 2;
				moves[index][2] = conv->getWert(board->touchSchwarz(-(board->getField(fig->getPosx() - 1, fig->getPosy() - 2) + 1))->getTyp());
			}
			else if (!isupper(fig->getTyp()) && board->getField(fig->getPosx() - 1, fig->getPosy() - 2) > 0)
			{
				moves[index] = new int[3];
				moves[index][0] = fig->getPosx() - 1;
				moves[index][1] = fig->getPosy() - 2;
				moves[index][2] = -conv->getWert(board->touchWeiss(board->getField(fig->getPosx() - 1, fig->getPosy() - 2) - 1)->getTyp());
			}
			index++;
		}
	}
	// läufer,Rook und queen-----------------------------------------------------------------------------------------------------
	else if (toupper(fig->getTyp()) == 'B' || toupper(fig->getTyp()) == 'Q' && toupper(fig->getTyp()) == 'R')
	{
		// Läufer und Queen------------------------------------------------------------------------------------------------------
		if (toupper(fig->getTyp()) == 'B' || toupper(fig->getTyp()) == 'Q')
		{
			bool notend[4];
			notend[0] = true;
			notend[1] = true;
			notend[2] = true;
			notend[3] = true;
			for (int i = 0; i < 8; i++)
			{
					if (notend[0] && (fig->getPosx() + i) < 8 && (fig->getPosy() + i) < 8 )
					{
						if (board->getField(fig->getPosx() + i, fig->getPosy() + i) == 0)
						{
							moves[index] = new int[3];
							moves[index][0] = fig->getPosx() + i;
							moves[index][1] = fig->getPosy() + i;
							moves[index][2] = 0;
						}
						else if (isupper(fig->getTyp()) && board->getField(fig->getPosx() + i, fig->getPosy() + i) < 0)
						{
							moves[index] = new int[3];
							moves[index][0] = fig->getPosx() + i;
							moves[index][1] = fig->getPosy() + i;
							moves[index][2] = conv->getWert(board->touchSchwarz(-(board->getField(fig->getPosx() +i, fig->getPosy() +i) + 1))->getTyp());
							notend[0] = false;
						}
						else if (!isupper(fig->getTyp()) && board->getField(fig->getPosx() + i, fig->getPosy() + i) > 0)
						{
							moves[index] = new int[3];
							moves[index][0] = fig->getPosx() + i;
							moves[index][1] = fig->getPosy() + i;
							moves[index][2] = -conv->getWert(board->touchWeiss((board->getField(fig->getPosx() + i, fig->getPosy() + i) - 1))->getTyp());
							notend[0] = false;
						}
						index++;
					}
					else
					{
						notend[0] = false;
					}
					if (notend[1] && (fig->getPosx() + i) < 8 && (fig->getPosy() - i) > -1 )
					{
						if (board->getField(fig->getPosx() + i, fig->getPosy() - i) == 0)
						{
							moves[index] = new int[3];
							moves[index][0] = fig->getPosx() + i;
							moves[index][1] = fig->getPosy() - i;
							moves[index][2] = 0;
						}
						else if (isupper(fig->getTyp()) && board->getField(fig->getPosx() + i, fig->getPosy() - i) < 0)
						{
							moves[index] = new int[3];
							moves[index][0] = fig->getPosx() + i;
							moves[index][1] = fig->getPosy() - i;
							moves[index][2] = conv->getWert(board->touchSchwarz(-(board->getField(fig->getPosx() + i, fig->getPosy() - i) + 1))->getTyp());
							notend[1] = false;
						}
						else if (!isupper(fig->getTyp()) && board->getField(fig->getPosx() + i, fig->getPosy() - i) > 0)
						{
							moves[index] = new int[3];
							moves[index][0] = fig->getPosx() + i;
							moves[index][1] = fig->getPosy() - i;
							moves[index][2] = -conv->getWert(board->touchWeiss((board->getField(fig->getPosx() + i, fig->getPosy() - i) - 1))->getTyp());
							notend[1] = false;
						}
						index++;
					}
					else
					{
						notend[1] = false;
					}
					if (notend[2] && (fig->getPosx() - i) > -1 && (fig->getPosy() + i) < 8 )
					{
						if (board->getField(fig->getPosx() - i, fig->getPosy() + i) == 0)
						{
							moves[index] = new int[3];
							moves[index][0] = fig->getPosx() - i;
							moves[index][1] = fig->getPosy() + i;
							moves[index][2] = 0;
						}
						else if (board->getField(fig->getPosx() - i, fig->getPosy() + i) < 0)
						{
							moves[index] = new int[3];
							moves[index][0] = fig->getPosx() - i;
							moves[index][1] = fig->getPosy() + i;
							moves[index][2] = conv->getWert(board->touchSchwarz(-(board->getField(fig->getPosx() - i, fig->getPosy() + i) + 1))->getTyp());
							notend[2] = false;
						}
						else if (!isupper(fig->getTyp()) && board->getField(fig->getPosx() - i, fig->getPosy() + i) > 0)
						{
							moves[index] = new int[3];
							moves[index][0] = fig->getPosx() - i;
							moves[index][1] = fig->getPosy() + i;
							moves[index][2] = -conv->getWert(board->touchWeiss((board->getField(fig->getPosx() - i, fig->getPosy() + i) - 1))->getTyp());
							notend[2] = false;
						}
						index++;
					}
					else
					{
						notend[2] = false;
					}
					if (notend[3] && (fig->getPosx() - i) > -1 && (fig->getPosy() - i) > -1 )
					{
						if (board->getField(fig->getPosx() - i, fig->getPosy() - i) == 0)
						{
							moves[index] = new int[3];
							moves[index][0] = fig->getPosx() - i;
							moves[index][1] = fig->getPosy() - i;
							moves[index][2] = 0;
						}
						else if (board->getField(fig->getPosx() - i, fig->getPosy() - i) < 0)
						{
							moves[index] = new int[3];
							moves[index][0] = fig->getPosx() - i;
							moves[index][1] = fig->getPosy() - i;
							moves[index][2] = conv->getWert(board->touchSchwarz(-(board->getField(fig->getPosx() - i, fig->getPosy() - i) + 1))->getTyp());
							notend[3] = false;
						}
						else if (!isupper(fig->getTyp()) && board->getField(fig->getPosx() - i, fig->getPosy() - i) > 0)
						{
							moves[index] = new int[3];
							moves[index][0] = fig->getPosx() - i;
							moves[index][1] = fig->getPosy() - i;
							moves[index][2] = -conv->getWert(board->touchWeiss((board->getField(fig->getPosx() - i, fig->getPosy() - i) - 1))->getTyp());
							notend[3] = false;
						}
						index++;
					}
					else
					{
						notend[3] = false;
					}
			}
		}
		// Turm und Queen--------------------------------------------------------------------------------------------------------
		if (toupper(fig->getTyp()) == 'R' || toupper(fig->getTyp()) == 'Q')
		{
			bool notend[4];
			notend[0] = true;
			notend[1] = true;
			notend[2] = true;
			notend[3] = true;
			for (int i = 0; i < 8; i++)
			{
				if (notend[0] && (fig->getPosx() + i) < 8 )
				{
					if (board->getField(fig->getPosx() + i, fig->getPosy()) == 0)
					{
						moves[index] = new int[3];
						moves[index][0] = fig->getPosx() + i;
						moves[index][1] = fig->getPosy();
						moves[index][2] = 0;
					}
					else if (isupper(fig->getTyp()) && board->getField(fig->getPosx() + i, fig->getPosy()) < 0)
					{
						moves[index] = new int[3];
						moves[index][0] = fig->getPosx() + i;
						moves[index][1] = fig->getPosy();
						moves[index][2] = conv->getWert(board->touchSchwarz(-(board->getField(fig->getPosx() + i, fig->getPosy()) + 1))->getTyp());
						notend[0] = false;
					}
					else if (!isupper(fig->getTyp()) && board->getField(fig->getPosx() + i, fig->getPosy()) > 0)
					{
						moves[index] = new int[3];
						moves[index][0] = fig->getPosx() + i;
						moves[index][1] = fig->getPosy();
						moves[index][2] = -conv->getWert(board->touchWeiss((board->getField(fig->getPosx() + i, fig->getPosy()) - 1))->getTyp());
						notend[0] = false;
					}
					index++;
				}
				else
				{
					notend[0] = false;
				}
				if (notend[1] && (fig->getPosx() - i) > -1 )
				{
					if (board->getField(fig->getPosx() - i, fig->getPosy()) == 0)
					{
						moves[index] = new int[3];
						moves[index][0] = fig->getPosx() - i;
						moves[index][1] = fig->getPosy();
						moves[index][2] = 0;
					}
					else if (isupper(fig->getTyp()) && board->getField(fig->getPosx() - i, fig->getPosy()) < 0)
					{
						moves[index] = new int[3];
						moves[index][0] = fig->getPosx() - i;
						moves[index][1] = fig->getPosy();
						moves[index][2] = conv->getWert(board->touchSchwarz(-(board->getField(fig->getPosx() - i, fig->getPosy()) + 1))->getTyp());
						notend[1] = false;
					}
					else if (!isupper(fig->getTyp()) && board->getField(fig->getPosx() - i, fig->getPosy()) > 0)
					{
						moves[index] = new int[3];
						moves[index][0] = fig->getPosx() - i;
						moves[index][1] = fig->getPosy();
						moves[index][2] = -conv->getWert(board->touchWeiss((board->getField(fig->getPosx() - i, fig->getPosy()) - 1))->getTyp());
						notend[1] = false;
					}
					index++;
				}
				else
				{
					notend[1] = false;
				}
				if (notend[2] && (fig->getPosy() + i) < 8 )
				{
					if (board->getField(fig->getPosx(), fig->getPosy() + i) == 0)
					{
						moves[index] = new int[3];
						moves[index][0] = fig->getPosx();
						moves[index][1] = fig->getPosy() + i;
						moves[index][2] = 0;
					}
					else if (isupper(fig->getTyp()) && board->getField(fig->getPosx(), fig->getPosy() + i) < 0)
					{
						moves[index] = new int[3];
						moves[index][0] = fig->getPosx();
						moves[index][1] = fig->getPosy() + i;
						moves[index][2] = conv->getWert(board->touchSchwarz(-(board->getField(fig->getPosx(), fig->getPosy() + i) + 1))->getTyp());
						notend[2] = false;
					}
					else if (!isupper(fig->getTyp()) && board->getField(fig->getPosx() - i, fig->getPosy()) > 0)
					{
						moves[index] = new int[3];
						moves[index][0] = fig->getPosx();
						moves[index][1] = fig->getPosy() + i;
						moves[index][2] = -conv->getWert(board->touchWeiss((board->getField(fig->getPosx() , fig->getPosy() + i) - 1))->getTyp());
						notend[2] = false;
					}
					index++;
				}
				else
				{
					notend[2] = false;
				}
				if (notend[3] && (fig->getPosy() - i) > -1 )
				{
					if (board->getField(fig->getPosx(), fig->getPosy() - i) == 0)
					{
						moves[index] = new int[3];
						moves[index][0] = fig->getPosx();
						moves[index][1] = fig->getPosy() - i;
						moves[index][2] = 0;
					}
					else if (isupper(fig->getTyp()) && board->getField(fig->getPosx() , fig->getPosy() - i) < 0)
					{
						moves[index] = new int[3];
						moves[index][0] = fig->getPosx();
						moves[index][1] = fig->getPosy() - i;
						moves[index][2] = conv->getWert(board->touchSchwarz(-(board->getField(fig->getPosx() , fig->getPosy() - i) + 1))->getTyp());
						notend[3] = false;
					}
					else if (!isupper(fig->getTyp()) && board->getField(fig->getPosx(), fig->getPosy() - i) > 0)
					{
						moves[index] = new int[3];
						moves[index][0] = fig->getPosx();
						moves[index][1] = fig->getPosy() - i;
						moves[index][2] = -conv->getWert(board->touchWeiss((board->getField(fig->getPosx(), fig->getPosy() - i) - 1))->getTyp());
						notend[3] = false;
					}
					index++;
				}
				else
				{
					notend[3] = false;
				}
			}
		}
	}

	// König-------------------------------------------------------------------------------------------------------------------
	else if (fig->getTyp() == 'K' || fig->getTyp() == 'k')
	{
		if (fig->getPosx() + 1 < 8 && fig->getPosy() + 1 < 8)
		{
			if (board->getField(fig->getPosx() + 1, fig->getPosy() + 1) == 0)
			{
				moves[index] = new int[3];
				moves[index][0] = fig->getPosx() + 1;
				moves[index][1] = fig->getPosy() + 1;
				moves[index][2] = 0;
			}
			if (isupper(fig->getTyp()) && board->getField(fig->getPosx() + 1, fig->getPosy() + 1) > 0)
			{
				moves[index] = new int[3];
				moves[index][0] = fig->getPosx() + 1;
				moves[index][1] = fig->getPosy() + 1;
				moves[index][2] = conv->getWert(board->touchSchwarz(-(board->getField(fig->getPosx() + 1, fig->getPosy() + 1) + 1))->getTyp());
			}
			else if (!isupper(fig->getTyp()) && board->getField(fig->getPosx() + 1, fig->getPosy() + 1) < 0)
			{
				moves[index] = new int[3];
				moves[index][0] = fig->getPosx() + 1;
				moves[index][1] = fig->getPosy() + 1;
				moves[index][2] = -conv->getWert(board->touchWeiss((board->getField(fig->getPosx() + 1, fig->getPosy() + 1) - 1))->getTyp());
			}
			index++;
		}
		if (fig->getPosx() + 1 < 8 && fig->getPosy() - 1 > -1 )
		{
			if (board->getField(fig->getPosx() + 1, fig->getPosy() - 1) == 0)
			{
				moves[index] = new int[3];
				moves[index][0] = fig->getPosx() + 1;
				moves[index][1] = fig->getPosy() - 1;
				moves[index][2] = 0;
			}
			if (isupper(fig->getTyp()) && board->getField(fig->getPosx() + 1, fig->getPosy() - 1) > 0)
			{
				moves[index] = new int[3];
				moves[index][0] = fig->getPosx() + 1;
				moves[index][1] = fig->getPosy() - 1;
				moves[index][2] = conv->getWert(board->touchSchwarz(-(board->getField(fig->getPosx() + 1, fig->getPosy() - 1) + 1))->getTyp());
			}
			else if (!isupper(fig->getTyp()) && board->getField(fig->getPosx() + 1, fig->getPosy() - 1) < 0)
			{
				moves[index] = new int[3];
				moves[index][0] = fig->getPosx() + 1;
				moves[index][1] = fig->getPosy() - 1;
				moves[index][2] = -conv->getWert(board->touchWeiss((board->getField(fig->getPosx() + 1, fig->getPosy() - 1) - 1))->getTyp());
			}
			index++;
		}
		if (fig->getPosx() - 1 > -1 && fig->getPosy() + 1 < 8 )
		{
			if (board->getField(fig->getPosx() - 1, fig->getPosy() + 1) == 0)
			{
				moves[index] = new int[3];
				moves[index][0] = fig->getPosx() - 1;
				moves[index][1] = fig->getPosy() + 1;
				moves[index][2] = 0;
			}
			else if (isupper(fig->getTyp()) && board->getField(fig->getPosx() - 1, fig->getPosy() + 1) > 0)
			{
				moves[index] = new int[3];
				moves[index][0] = fig->getPosx() - 1;
				moves[index][1] = fig->getPosy() + 1;
				moves[index][2] = conv->getWert(board->touchSchwarz(-(board->getField(fig->getPosx() - 1, fig->getPosy() + 1) + 1))->getTyp());
			}
			else if (!isupper(fig->getTyp()) && board->getField(fig->getPosx() - 1, fig->getPosy() + 1) < 0)
			{
				moves[index] = new int[3];
				moves[index][0] = fig->getPosx() - 1;
				moves[index][1] = fig->getPosy() + 1;
				moves[index][2] = -conv->getWert(board->touchWeiss((board->getField(fig->getPosx() - 1, fig->getPosy() + 1) - 1))->getTyp());
			}
			index++;
		}
		if (fig->getPosx() - 1 > -1 && fig->getPosy() - 1 > -1 )
		{
			if (board->getField(fig->getPosx() - 1, fig->getPosy() - 1) == 0)
			{
				moves[index] = new int[3];
				moves[index][0] = fig->getPosx() - 1;
				moves[index][1] = fig->getPosy() - 1;
				moves[index][2] = 0;
			}
			else if (isupper(fig->getTyp()) && board->getField(fig->getPosx() - 1, fig->getPosy() - 1) > 0)
			{
				moves[index] = new int[3];
				moves[index][0] = fig->getPosx() - 1;
				moves[index][1] = fig->getPosy() - 1;
				moves[index][2] = conv->getWert(board->touchSchwarz(-(board->getField(fig->getPosx() - 1, fig->getPosy() - 1) + 1))->getTyp());
			}
			else if (!isupper(fig->getTyp()) && board->getField(fig->getPosx() - 1, fig->getPosy() - 1) < 0)
			{
				moves[index] = new int[3];
				moves[index][0] = fig->getPosx() - 1;
				moves[index][1] = fig->getPosy() - 1;
				moves[index][2] = -conv->getWert(board->touchWeiss((board->getField(fig->getPosx() - 1, fig->getPosy() - 1) - 1))->getTyp());
			}
			index++;
		}
		//---------------------------
		if (fig->getPosy() + 1 < 8 )
		{
			if (board->getField(fig->getPosx(), fig->getPosy() + 1) == 0)
			{
				moves[index] = new int[3];
				moves[index][0] = fig->getPosx();
				moves[index][1] = fig->getPosy() + 1;
				moves[index][2] = 0;
			}
			else if (isupper(fig->getTyp()) && board->getField(fig->getPosx() , fig->getPosy() + 1) > 0)
			{
				moves[index] = new int[3];
				moves[index][0] = fig->getPosx();
				moves[index][1] = fig->getPosy() + 1;
				moves[index][2] = conv->getWert(board->touchSchwarz(-(board->getField(fig->getPosx() , fig->getPosy() + 1) + 1))->getTyp());
			}
			else if (!isupper(fig->getTyp()) && board->getField(fig->getPosx() , fig->getPosy() + 1) < 0)
			{
				moves[index] = new int[3];
				moves[index][0] = fig->getPosx();
				moves[index][1] = fig->getPosy() + 1;
				moves[index][2] = -conv->getWert(board->touchWeiss((board->getField(fig->getPosx(), fig->getPosy() + 1) - 1))->getTyp());
			}
			index++;
		}
		if (fig->getPosy() - 1 > -1 )
		{
			if (board->getField(fig->getPosx(), fig->getPosy() - 1) == 0)
			{
				moves[index] = new int[3];
				moves[index][0] = fig->getPosx();
				moves[index][1] = fig->getPosy() - 1;
				moves[index][2] = 0;
			}
			else if (isupper(fig->getTyp()) && board->getField(fig->getPosx() , fig->getPosy() - 1) > 0)
			{
				moves[index] = new int[3];
				moves[index][0] = fig->getPosx();
				moves[index][1] = fig->getPosy() - 1;
				moves[index][2] = conv->getWert(board->touchSchwarz(-(board->getField(fig->getPosx() , fig->getPosy() - 1) + 1))->getTyp());
			}
			else if (!isupper(fig->getTyp()) && board->getField(fig->getPosx(), fig->getPosy() - 1) < 0)
			{
				moves[index] = new int[3];
				moves[index][0] = fig->getPosx();
				moves[index][1] = fig->getPosy() - 1;
				moves[index][2] = -conv->getWert(board->touchWeiss((board->getField(fig->getPosx(), fig->getPosy() - 1) - 1))->getTyp());
			}
			index++;
		}
		if (fig->getPosx() - 1 > -1 )
		{
			if (board->getField(fig->getPosx() - 1, fig->getPosy()) == 0)
			{
				moves[index] = new int[3];
				moves[index][0] = fig->getPosx() - 1;
				moves[index][1] = fig->getPosy();
				moves[index][2] = 0;
			}
			else if (isupper(fig->getTyp()) && board->getField(fig->getPosx() - 1, fig->getPosy()) > 0)
			{
				moves[index] = new int[3];
				moves[index][0] = fig->getPosx() - 1;
				moves[index][1] = fig->getPosy();
				moves[index][2] = conv->getWert(board->touchSchwarz(-(board->getField(fig->getPosx() - 1, fig->getPosy()) + 1))->getTyp());
			}
			else if (!isupper(fig->getTyp()) && board->getField(fig->getPosx() - 1, fig->getPosy()) < 0)
			{
				moves[index] = new int[3];
				moves[index][0] = fig->getPosx() - 1;
				moves[index][1] = fig->getPosy();
				moves[index][2] = -conv->getWert(board->touchWeiss((board->getField(fig->getPosx() - 1, fig->getPosy()))-1)->getTyp());
			}
			index++;
		}
		if (fig->getPosx() + 1 < 8 )
		{
			if (board->getField(fig->getPosx() + 1, fig->getPosy()) == 0)
			{
				moves[index] = new int[3];
				moves[index][0] = fig->getPosx() + 1;
				moves[index][1] = fig->getPosy();
				moves[index][2] = 0;
			}
			if (isupper(fig->getTyp()) && board->getField(fig->getPosx() + 1, fig->getPosy()) > 0)
			{
				moves[index] = new int[3];
				moves[index][0] = fig->getPosx() + 1;
				moves[index][1] = fig->getPosy();
				moves[index][2] = conv->getWert(board->touchSchwarz(-(board->getField(fig->getPosx() + 1, fig->getPosy()) + 1))->getTyp());
			}
			else if (!isupper(fig->getTyp()) && board->getField(fig->getPosx() + 1, fig->getPosy()) < 0)
			{
				moves[index] = new int[3];
				moves[index][0] = fig->getPosx() + 1;
				moves[index][1] = fig->getPosy();
				moves[index][2] = -conv->getWert(board->touchWeiss((board->getField(fig->getPosx() + 1, fig->getPosy()) - 1))->getTyp());
			}
			index++;
		}
		if (board->getCastlKingside(true) && fig->getPosx()==0 && board->getField(fig->getPosx() + 1, fig->getPosy()) == 0 && board->getField(fig->getPosx() + 2, fig->getPosy()) == 0)
		{
			if (!this->testRochadeAngriffKS(board, fig))
			{
				moves[index] = new int[3];
				moves[index][0] = fig->getPosx() + 2;
				moves[index][1] = fig->getPosy();
				moves[index][2] = ROCHADE;
				index++;
			}
		}
		if (board->getCastlQueenside(true) && fig->getPosx() == 0 && board->getField(fig->getPosx() - 1, fig->getPosy()) == 0 && board->getField(fig->getPosx() - 2, fig->getPosy()) == 0 && board->getField(fig->getPosx() - 3, fig->getPosy()) == 0)
		{
			if (!this->testRochadeAngriffQS(board, fig))
			{
				moves[index] = new int[3];
				moves[index][0] = fig->getPosx() - 2;
				moves[index][1] = fig->getPosy();
				moves[index][2] = ROCHADE;
				index++;
			}
		}
		if (board->getCastlKingside(false) && fig->getPosx() == 7 && board->getField(fig->getPosx() + 1, fig->getPosy()) == 0 && board->getField(fig->getPosx() + 2, fig->getPosy()) == 0)
		{
			if (!this->testRochadeAngriffKS(board, fig))
			{
				moves[index] = new int[3];
				moves[index][0] = fig->getPosx() + 2;
				moves[index][1] = fig->getPosy();
				moves[index][2] = ROCHADE;
				index++;
			}
		}
		if (board->getCastlQueenside(false) && fig->getPosx() == 7 && board->getField(fig->getPosx() - 1, fig->getPosy()) == 0 && board->getField(fig->getPosx() - 2, fig->getPosy()) == 0 && board->getField(fig->getPosx() - 3, fig->getPosy()) == 0)
		{
			if (!this->testRochadeAngriffQS(board, fig))
			{
				moves[index] = new int[3];
				moves[index][0] = fig->getPosx() - 2;
				moves[index][1] = fig->getPosy();
				moves[index][2] = ROCHADE;
				index++;
			}
		}
	}
	moves[index] = new int[3];
	moves[index][0] = -1;
	moves[index][1] = -1;
	moves[index][2] = 0;
	return nullptr;
}

bool Movemennt::proveMove(int ** move, Figur * fig, Brett * board)
{
	if (board->getWhitetoMove() && !isupper(fig->getTyp()))
		return false;
	if (!board->getWhitetoMove() && isupper(fig->getTyp()))
		return false;
	// Felder für Pawn
	if (fig->getTyp() == 'P')
	{
		std::cout << "test P\n";
		if ( (fig->getPosy() + 1) < 8 && board->getField(fig->getPosx(), (fig->getPosy() + 1)) == 0)
		{
			if (move[0][0] == move[1][0])
			{
				if (move[0][1] == (move[1][1] - 1))
				{
					return true;
				}
				else
				{
					if (fig->getPosy()==1 && board->getField(fig->getPosx(), (fig->getPosy() + 2)) == 0)
					{
						if (move[0][1] == (move[1][1] - 2))
						{
							return true;
						}
						else
						{
							return false;
						}
					}
					else
					{
						return false;
					}
				}
			}
			else
			{
				return false;
			}

		}
		else if ((fig->getPosx() + 1) < 8 &&  (fig->getPosy() + 1)< 8 && board->getField(fig->getPosx() + 1, (fig->getPosy() + 1)) < 0 && move[0][0] == (move[1][0] +1) && move[0][1]==(move[1][1]+1))
		{
			return true;
		}
		else if ((fig->getPosx() + 1) < 8 && (fig->getPosy() - 1) > -1 && board->getField(fig->getPosx() + 1, (fig->getPosy() - 1)) < 0 && move[0][0] == (move[1][0] + 1) && move[0][1] == (move[1][1] - 1))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else if (fig->getTyp() == 'p')
	{
		std::cout << "test p\n";
		if ((fig->getPosy() - 1) > -1 && board->getField(fig->getPosx(), (fig->getPosy() - 1)) == 0)
		{
			if (move[0][0] == move[1][0])
			{
				if (move[0][1] == (move[1][1] + 1))
				{
					return true;
				}
				else
				{
					if (fig->getPosy() == 6 && board->getField(fig->getPosx(), (fig->getPosy() - 2)) == 0)
					{
						if (move[0][1] == (move[1][1] + 2))
						{
							return true;
						}
						else
						{
							return false;
						}
					}
					else
					{
						return false;
					}
				}
			}
			else if ((fig->getPosx() - 1) > -1 && (fig->getPosy() + 1) < 8 && board->getField(fig->getPosx() - 1, (fig->getPosy() + 1)) > 0 && move[0][0] == (move[1][0] - 1) && move[0][1] == (move[1][1] + 1))
			{
				return true;
			}
			else if ((fig->getPosx() - 1) > -1 && (fig->getPosy() - 1) > -1 && board->getField(fig->getPosx() - 1, (fig->getPosy() - 1)) > 0 && move[0][0] == (move[1][0] - 1) && move[0][1] == (move[1][1] - 1))
			{
				return true;
			}
			else
			{
				return false;
			}

		}

		else
		{
			return false;
		}
	}
	// Springer ------------------------------------------------------------------------------------------------------------
	// Weiss----------------------------------------------------------------------------------------------------------------
	else if (fig->getTyp() == 'N')
	{
		std::cout << "test N\n";
		if (move[1][0] == (fig->getPosx() + 2) && (fig->getPosy() + 1) == move[1][1] && board->getField(fig->getPosx() + 2, fig->getPosy() + 1) <= 0)
		{
				return true;
		}
		if (move[1][0] == (fig->getPosx() + 2) && (fig->getPosy() - 1) == move[1][1] && board->getField(fig->getPosx() + 2, fig->getPosy() - 1) <= 0)
		{
				return true;
		}
		if (move[1][0] == (fig->getPosx() - 2) && (fig->getPosy() + 1) == move[1][1] && board->getField(fig->getPosx() - 2, fig->getPosy() + 1) <= 0)
		{
				return true;
		}
		if (move[1][0] == (fig->getPosx() - 2) && (fig->getPosy() - 1) == move[1][1] && board->getField(fig->getPosx() - 2, fig->getPosy() - 1) <= 0)
		{
				return true;
		}
		if (move[1][0] == (fig->getPosx() + 1) && (fig->getPosy() + 2) == move[1][1] && board->getField(fig->getPosx() + 1, fig->getPosy() + 2) <= 0)
		{
				return true;
		}
		if (move[1][0] == (fig->getPosx() - 1) && (fig->getPosy() + 2) == move[1][1] && board->getField(fig->getPosx() - 1, fig->getPosy() + 2) <= 0)
		{
				return true;
		}
		else if (move[1][0] == (fig->getPosx() + 1) && (fig->getPosy() - 2) == move[1][1] && board->getField(fig->getPosx() + 1, fig->getPosy() - 2) <= 0)
		{
				return true;
		}
		if (move[1][0] == (fig->getPosx() + 2) && (fig->getPosy() + 1) == move[1][1] && board->getField(fig->getPosx() - 1, fig->getPosy() - 2) <= 0)
		{
				return true;
		}
		return false;
	}
	// Schwarz--------------------------------------------------------------------------------------------------------------
	else if (fig->getTyp() == 'n')
	{
		std::cout << "test n\n";
		if (move[1][0] == (fig->getPosx() + 2) && (fig->getPosy() + 1) == move[1][1] && board->getField(fig->getPosx() + 2, fig->getPosy() + 1) >= 0)
		{
				return true;
		}
		if (move[1][0] == (fig->getPosx() + 2) && (fig->getPosy() - 1) == move[1][1] && board->getField(fig->getPosx() + 2, fig->getPosy() - 1) >= 0)
		{
				return true;
		}
		if (move[1][0] == (fig->getPosx() - 2) && (fig->getPosy() + 1) == move[1][1] && board->getField(fig->getPosx() - 2, fig->getPosy() + 1) >= 0)
		{
				return true;
		}
		if (move[1][0] == (fig->getPosx() - 2) && (fig->getPosy() - 1) == move[1][1] && board->getField(fig->getPosx() - 2, fig->getPosy() - 1) >= 0)
		{
				return true;
		}
		if (move[1][0] == (fig->getPosx() + 1) && (fig->getPosy() + 2) == move[1][1] && board->getField(fig->getPosx() + 1, fig->getPosy() + 2) >= 0)
		{
				return true;
		}
		if (move[1][0] == (fig->getPosx() - 1) && (fig->getPosy() + 2) == move[1][1] && board->getField(fig->getPosx() - 1, fig->getPosy() + 2) >= 0)
		{
				return true;
		}
		if (move[1][0] == (fig->getPosx() + 1) && (fig->getPosy() - 2) == move[1][1] && board->getField(fig->getPosx() + 1, fig->getPosy() - 2) >= 0)
		{
				return true;
		}
		if (move[1][0] == (fig->getPosx() - 1) && (fig->getPosy() - 2) == move[1][1] && board->getField(fig->getPosx() - 1, fig->getPosy() - 2) >= 0)
		{
				return true;
		}
		return false;
	}
	// läufer,Rook und queen-----------------------------------------------------------------------------------------------------
	else if (toupper(fig->getTyp()) == 'B' || toupper(fig->getTyp()) == 'Q' || toupper(fig->getTyp()) == 'R')
	{
		// Läufer und Queen------------------------------------------------------------------------------------------------------
		if (toupper(fig->getTyp()) == 'B' || toupper(fig->getTyp()) == 'Q')
		{
			std::cout << "test qQ Bb\n";
			bool notend[4];
			notend[0] = true;
			notend[1] = true;
			notend[2] = true;
			notend[3] = true;
			for (int i = 0; i < 8; i++)
			{
				if (notend[0] && (fig->getPosx() + i) < 8 && (fig->getPosy() + i) < 8 )
				{
					if (move[1][0] == (fig->getPosx() + i) && (fig->getPosy() + i) == move[1][1] && board->getField(fig->getPosx() + i, fig->getPosy() + i) == 0)
						return true;
					if (isupper(fig->getTyp()) && board->getField(fig->getPosx() + i, fig->getPosy() + i) < 0)
					{
						notend[0] = false;
						if (move[1][0] == (fig->getPosx() + i) && (fig->getPosy() + i) == move[1][1])
							return true;
					}
					else if (!isupper(fig->getTyp()) && board->getField(fig->getPosx() + i, fig->getPosy() + i) > 0)
					{
						notend[0] = false;
						if (move[1][0] == (fig->getPosx() + i) && (fig->getPosy() + i) == move[1][1])
							return true;
					}
				}
				else
				{
					notend[0] = false;
				}
				if (notend[1] && (fig->getPosx() + i) < 8 && (fig->getPosy() - i) > -1 )
				{
					if (move[1][0] == (fig->getPosx() + i) && (fig->getPosy() - i) == move[1][1] && board->getField(fig->getPosx() + i, fig->getPosy() - i) == 0)
						return true;
					if (isupper(fig->getTyp()) && board->getField(fig->getPosx() + i, fig->getPosy() - i) < 0)
					{
						notend[1] = false;
						if (move[1][0] == (fig->getPosx() + i) && (fig->getPosy() - i) == move[1][1])
							return true;
					}
					else if (!isupper(fig->getTyp()) && board->getField(fig->getPosx() + i, fig->getPosy() - i) > 0)
					{
						notend[1] = false;
						if (move[1][0] == (fig->getPosx() + i) && (fig->getPosy() - i) == move[1][1])
							return true;
					}
				}
				else
				{
					notend[1] = false;
				}
				if (notend[2] && (fig->getPosx() - i) > -1 && (fig->getPosy() + i) < 8 )
				{
					if (move[1][0] == (fig->getPosx() - i) && (fig->getPosy() + i) == move[1][1] && board->getField(fig->getPosx() - i, fig->getPosy() + i) == 0)
						return true;
					if (board->getField(fig->getPosx() - i, fig->getPosy() + i) < 0)
					{
						notend[2] = false;
						if (move[1][0] == (fig->getPosx() - i) && (fig->getPosy() + i) == move[1][1])
							return true;
					}
					else if (!isupper(fig->getTyp()) && board->getField(fig->getPosx() - i, fig->getPosy() + i) > 0)
					{
						notend[2] = false;
						if (move[1][0] == (fig->getPosx() - i) && (fig->getPosy() + i) == move[1][1])
							return true;
					}
				}
				else
				{
					notend[2] = false;
				}
				if (notend[3] && (fig->getPosx() - i) > -1 && (fig->getPosy() - i) > -1 )
				{
					if (move[1][0] == (fig->getPosx() - i) && (fig->getPosy() - i) == move[1][1] && board->getField(fig->getPosx() - i, fig->getPosy() - i) == 0)
						return true;
					if (board->getField(fig->getPosx() - i, fig->getPosy() - i) < 0)
					{
						notend[3] = false;
						if (move[1][0] == (fig->getPosx() - i) && (fig->getPosy() - i) == move[1][1])
							return true;
					}
					else if (!isupper(fig->getTyp()) && board->getField(fig->getPosx() - i, fig->getPosy() - i) > 0)
					{
						notend[3] = false;
						if (move[1][0] == (fig->getPosx() - i) && (fig->getPosy() - i) == move[1][1])
							return true;
					}
				}
				else
				{
					notend[3] = false;
				}
			}
		}
		// Turm und Queen--------------------------------------------------------------------------------------------------------
		if (toupper(fig->getTyp()) == 'R' || toupper(fig->getTyp()) == 'Q')
		{
			std::cout << "test qQ Rr\n";
			bool notend[4];
			notend[0] = true;
			notend[1] = true;
			notend[2] = true;
			notend[3] = true;
			for (int i = 0; i < 8; i++)
			{
				if (notend[0] && (fig->getPosx() + i) < 8 )
				{
					if (move[1][0] == (fig->getPosx() + i) && fig->getPosy() == move[1][1] && board->getField(fig->getPosx() + i, fig->getPosy()) == 0)
						return true;
					if (isupper(fig->getTyp()) && board->getField(fig->getPosx() + i, fig->getPosy()) < 0)
					{
						notend[0] = false;
						if (move[1][0] == (fig->getPosx() + i) && fig->getPosy() == move[1][1])
							return true;
					}
					else if (!isupper(fig->getTyp()) && board->getField(fig->getPosx() + i, fig->getPosy()) > 0)
					{
						notend[0] = false;
						if (move[1][0] == (fig->getPosx() + i) && fig->getPosy() == move[1][1])
							return true;
					}
				}
				else
				{
					notend[0] = false;
				}
				if (notend[1] && (fig->getPosx() - i) > -1 )
				{
					if (move[1][0] == (fig->getPosx() - i) && fig->getPosy() == move[1][1] && board->getField(fig->getPosx() - i, fig->getPosy()) == 0)
						return true;
					if (isupper(fig->getTyp()) && board->getField(fig->getPosx() - i, fig->getPosy()) < 0)
					{
						notend[1] = false;
						if (move[1][0] == (fig->getPosx() - i) && fig->getPosy() == move[1][1])
							return true;
					}
					else if (!isupper(fig->getTyp()) && board->getField(fig->getPosx() - i, fig->getPosy()) > 0)
					{
						notend[1] = false;
						if (move[1][0] == (fig->getPosx() - i) && fig->getPosy() == move[1][1])
							return true;
					}
				}
				else
				{
					notend[1] = false;
				}
				if (notend[2] && (fig->getPosy() + i) < 8 )
				{
					if (move[1][0] == fig->getPosx() && (fig->getPosy()+1) == move[1][1] && board->getField(fig->getPosx(), fig->getPosy() + i) == 0)
						return true;
					if (isupper(fig->getTyp()) && board->getField(fig->getPosx(), fig->getPosy() + i) < 0)
					{
						notend[2] = false;
						if (move[1][0] == fig->getPosx() && (fig->getPosy() + 1) == move[1][1])
							return true;
					}
					else if (!isupper(fig->getTyp()) && board->getField(fig->getPosx() - i, fig->getPosy()) > 0)
					{
						notend[2] = false;
						if (move[1][0] == fig->getPosx() && (fig->getPosy() + 1) == move[1][1])
							return true;
					}
				}
				else
				{
					notend[2] = false;
				}
				if (notend[3] && (fig->getPosy() - i) > -1 )
				{
					if (move[1][0] == fig->getPosx() && (fig->getPosy() - 1) == move[1][1] && board->getField(fig->getPosx(), fig->getPosy() - i) == 0)
						return true;
					if (isupper(fig->getTyp()) && board->getField(fig->getPosx(), fig->getPosy() - i) < 0)
					{
						notend[3] = false;
						if (move[1][0] == fig->getPosx() && (fig->getPosy() - 1) == move[1][1])
							return true;
					}
					else if (!isupper(fig->getTyp()) && board->getField(fig->getPosx(), fig->getPosy() - i) > 0)
					{
						notend[3] = false;
						if (move[1][0] == fig->getPosx() && (fig->getPosy() - 1) == move[1][1])
							return true;
					}
				}
				else
				{
					notend[3] = false;
				}
			}
		}
		return false;
	}
	// König-------------------------------------------------------------------------------------------------------------------
	else if (fig->getTyp() == 'K' || fig->getTyp() == 'k')
	{
		std::cout << "test Kk\n";
		if ((fig->getPosx() + 1 < 8) && fig->getPosy() + 1 < 8 )
		{
			if (move[1][0] == (fig->getPosx() + 1) && (fig->getPosy() + 1) == move[1][1] && board->getField(fig->getPosx() + 1, fig->getPosy() + 1) == 0)
				return true;
			if (isupper(fig->getTyp()) && board->getField(fig->getPosx() + 1, fig->getPosy() + 1) > 0)
			{
				if (move[1][0] == (fig->getPosx() + 1) && (fig->getPosy() + 1) == move[1][1])
					return true;
			}
			else if (!isupper(fig->getTyp()) && board->getField(fig->getPosx() + 1, fig->getPosy() + 1) < 0)
			{
				if (move[1][0] == (fig->getPosx() + 1) && (fig->getPosy() + 1) == move[1][1])
					return true;
			}
		}
		else if ((fig->getPosx() + 1) < 8 && fig->getPosy() - 1 > -1 )
		{
			if (move[1][0] == (fig->getPosx() + 1) && (fig->getPosy() - 1) == move[1][1] && board->getField(fig->getPosx() + 1, fig->getPosy() - 1) == 0)
				return true;
			if (isupper(fig->getTyp()) && board->getField(fig->getPosx() + 1, fig->getPosy() - 1) > 0)
			{
				if (move[1][0] == (fig->getPosx() + 1) && (fig->getPosy() - 1) == move[1][1])
					return true;
			}
			else if (!isupper(fig->getTyp()) && board->getField(fig->getPosx() + 1, fig->getPosy() - 1) < 0)
			{
				if (move[1][0] == (fig->getPosx() + 1) && (fig->getPosy() - 1) == move[1][1])
					return true;
			}
		}
		else if ((fig->getPosx() - 1) > -1 )
		{
			if (move[1][0] == (fig->getPosx() - 1) && (fig->getPosy() + 1) == move[1][1] && fig->getPosy() + 1 < 8 && board->getField(fig->getPosx() - 1, fig->getPosy() + 1) == 0)
				return true;
			if (isupper(fig->getTyp()) && board->getField(fig->getPosx() - 1, fig->getPosy() + 1) > 0)
			{
				if (move[1][0] == (fig->getPosx() - 1) && (fig->getPosy() + 1) == move[1][1])
					return true;
			}
			else if (!isupper(fig->getTyp()) && board->getField(fig->getPosx() - 1, fig->getPosy() + 1) < 0)
			{
				if (move[1][0] == (fig->getPosx() - 1) && (fig->getPosy() + 1) == move[1][1])
					return true;
			}
		}
		else if (fig->getPosx() - 1 > -1 && fig->getPosy() - 1 > -1 )
		{
			if (move[1][0] == (fig->getPosx() - 1) && (fig->getPosy() - 1) == move[1][1] && board->getField(fig->getPosx() - 1, fig->getPosy() - 1) == 0)
				return true;
			if (isupper(fig->getTyp()) && board->getField(fig->getPosx() - 1, fig->getPosy() - 1) > 0)
			{
				if (move[1][0] == (fig->getPosx() - 1) && (fig->getPosy() - 1) == move[1][1])
					return true;
			}
			else if (!isupper(fig->getTyp()) && board->getField(fig->getPosx() - 1, fig->getPosy() - 1) < 0)
			{
				if (move[1][0] == (fig->getPosx() - 1) && (fig->getPosy() - 1) == move[1][1])
					return true;
			}
		}
		//---------------------------
		else if (fig->getPosy() + 1 < 8 )
		{
			if (move[1][0] == fig->getPosx()  && (fig->getPosy() + 1) == move[1][1] && board->getField(fig->getPosx(), fig->getPosy() + 1) == 0)
				return true;
			if (isupper(fig->getTyp()) && board->getField(fig->getPosx(), fig->getPosy() + 1) > 0)
			{
				if (move[1][0] == fig->getPosx() && (fig->getPosy() + 1) == move[1][1])
					return true;
			}
			else if (!isupper(fig->getTyp()) && board->getField(fig->getPosx(), fig->getPosy() + 1) < 0)
			{
				if (move[1][0] == fig->getPosx() && (fig->getPosy() + 1) == move[1][1])
					return true;
			}
		}
		else if (fig->getPosy() - 1 > -1)
		{
			if (move[1][0] == fig->getPosx() && (fig->getPosy() - 1) == move[1][1] && board->getField(fig->getPosx(), fig->getPosy() - 1) == 0)
				return true;
			if (isupper(fig->getTyp()) && board->getField(fig->getPosx(), fig->getPosy() - 1) > 0)
			{
				if (move[1][0] == fig->getPosx() && (fig->getPosy() - 1) == move[1][1])
					return true;
			}
			else if (!isupper(fig->getTyp()) && board->getField(fig->getPosx(), fig->getPosy() - 1) < 0)
			{
				if (move[1][0] == fig->getPosx() && (fig->getPosy() - 1) == move[1][1])
					return true;
			}
		}
		else if (fig->getPosx() - 1 > -1 )
		{
			if ((move[1][0] == fig->getPosx() - 1) && (fig->getPosy() - 1) == move[1][1] && board->getField(fig->getPosx() - 1, fig->getPosy()) == 0)
				return true;
			if (isupper(fig->getTyp()) && board->getField(fig->getPosx() - 1, fig->getPosy()) > 0)
			{
				if ((move[1][0] == fig->getPosx() - 1) && (fig->getPosy() - 1) == move[1][1])
					return true;
			}
			else if (!isupper(fig->getTyp()) && board->getField(fig->getPosx() - 1, fig->getPosy()) < 0)
			{
				if ((move[1][0] == fig->getPosx() - 1) && (fig->getPosy() - 1) == move[1][1])
					return true;
			}
		}
		else if (fig->getPosx() + 1 < 8 )
		{
			if ((move[1][0] == fig->getPosx() + 1) && (fig->getPosy() + 1) == move[1][1] && board->getField(fig->getPosx() + 1, fig->getPosy()) == 0)
				return true;
			if (isupper(fig->getTyp()) && board->getField(fig->getPosx() + 1, fig->getPosy()) > 0)
			{
				if ((move[1][0] == fig->getPosx() + 1) && (fig->getPosy() + 1) == move[1][1])
					return true;
			}
			else if (!isupper(fig->getTyp()) && board->getField(fig->getPosx() + 1, fig->getPosy()) < 0)
			{
				if ((move[1][0] == fig->getPosx() + 1) && (fig->getPosy() + 1) == move[1][1])
					return true;
			}
		}
		else if (board->getCastlKingside(true) && fig->getPosx() == 0 && board->getField(fig->getPosx() + 1, fig->getPosy()) == 0 && board->getField(fig->getPosx() + 2, fig->getPosy()) == 0)
		{
			if (!this->testRochadeAngriffKS(board, fig))
			{
				if ((move[1][0] == fig->getPosx() + 2) && fig->getPosy() == move[1][1])
					return true;
			}
		}
		else if (board->getCastlQueenside(true) && fig->getPosx() == 0 && board->getField(fig->getPosx() - 1, fig->getPosy()) == 0 && board->getField(fig->getPosx() - 2, fig->getPosy()) == 0 && board->getField(fig->getPosx() - 3, fig->getPosy()) == 0)
		{
			if (!this->testRochadeAngriffQS(board, fig))
			{
				if ((move[1][0] == fig->getPosx() - 2) && fig->getPosy() == move[1][1])
					return true;
			}
		}
		else if (board->getCastlKingside(false) && fig->getPosx() == 7 && board->getField(fig->getPosx() + 1, fig->getPosy()) == 0 && board->getField(fig->getPosx() + 2, fig->getPosy()) == 0)
		{
			if (!this->testRochadeAngriffKS(board, fig))
			{
				if ((move[1][0] == fig->getPosx() + 2) && fig->getPosy() == move[1][1])
					return true;
			}
		}
		else if (board->getCastlQueenside(false) && fig->getPosx() == 7 && board->getField(fig->getPosx() - 1, fig->getPosy()) == 0 && board->getField(fig->getPosx() - 2, fig->getPosy()) == 0 && board->getField(fig->getPosx() - 3, fig->getPosy()) == 0)
		{
			if (!this->testRochadeAngriffQS(board, fig))
			{
				if ((move[1][0] == fig->getPosx() - 2) && fig->getPosy() == move[1][1])
					return true;
			}
		}
	}
	return nullptr;
}

bool Movemennt::makeMove(Brett * board, std::string move)
{
	int **movemade;
	Figur *fig;
	bool trade = false, rochKS=false, rochQS=false;
	char promo = ' ';
	int wert;
	movemade = conv->getMoveIntfromChar(move);
	int z,w=0;
	z = board->getField(movemade[0][0], movemade[0][1]);
	if (z == 0)
		return false;
	if (z > 0)
	{
		fig = board->touchWeiss(z - 1);
	}
	else
	{
		fig = board->touchSchwarz(-(z + 1));
	}
	if (this->proveMove(movemade, fig, board))
	{
		std::cout << "start move\n";
		if (fig->getTyp() == 'p' &&  move.length() > 4 && fig->getPosy()==1)
		{
			promo = move.at(4);
			wert = conv->getWert(promo);
			if (wert > 0 && wert < 10)
			{
				wert = conv->getWert(fig->getTyp()) - wert;
				board->setFigurenwert(board->getFigurenwert() - wert);
				fig->setTyp(promo);
			}
		}
		if (fig->getTyp() == 'P' &&  move.length() > 4 && fig->getPosy() == 6)
		{
			promo = move.at(4);
			wert = conv->getWert(promo);
			if (wert > 0 && wert < 10)
			{
				wert = conv->getWert(fig->getTyp()) - wert;
				board->setFigurenwert(board->getFigurenwert() + wert);
				fig->setTyp(promo);
			}
		}
		int ze=board->getField(movemade[1][0], movemade[1][1]);
		if (ze != 0)
		{
			if (ze > 0)
			{
				w = conv->getWert(board->touchWeiss(ze - 1)->getTyp());
				board->setFigurenwert(board->getFigurenwert()-w);
			}
			else
			{
				w = conv->getWert(board->touchSchwarz(-(ze + 1))->getTyp());
				board->setFigurenwert(board->getFigurenwert()+w);
			}
			board->deleteFigure(ze);
		}
		board->makeMove(fig, movemade[1][0], movemade[1][1]);
		if ((toupper(fig->getTyp())) == 'K'  && movemade[0][0] == 4 && movemade[1][0] == 6)
		{
			z = board->getField(movemade[0][0],7);
			if (z == 0)
				return false;
			if (z > 0)
			{
				fig = board->touchWeiss(z - 1);
				board->makeMove(fig, movemade[0][0],5);
			}
			else
			{
				fig = board->touchWeiss(-(z + 1));
				board->makeMove(fig, movemade[0][0], 5);
			}
		}
		if ((toupper(fig->getTyp())) == 'K'  && movemade[0][0] == 4 && movemade[1][0] == 2)
		{
			z = board->getField(movemade[0][0], 0);
			if (z == 0)
				return false;
			if (z > 0)
			{
				fig = board->touchWeiss(z - 1);
				board->makeMove(fig, movemade[0][0], 3);
			}
			else
			{
				fig = board->touchWeiss(-(z + 1));
				board->makeMove(fig, movemade[0][0], 3);
			}
		}
		board->setWhitetoMove(!board->getWhitetoMove());
		return true;
	}
	return false;
}

bool Movemennt::testRochadeAngriffKS(Brett * board, Figur * fig)
{
	return false;
}

bool Movemennt::testRochadeAngriffQS(Brett * board, Figur * fig)
{
	return false;
}

