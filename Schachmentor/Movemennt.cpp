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
	// Schwarz-------------------------------------------------------------------------------------------------------------------------
	if ( fig->getTyp() ==  'P')
	{
		if (board->getField(fig->getPosx(), (fig->getPosy() + 1)) == 0)
		{
			moves[index] = new int[3];
			moves[index][0] = fig->getPosx();
			moves[index][1] = fig->getPosy() + 1;
			moves[index][2] = 0;
			index++;
		}
		else if (fig->getPosx()==1 && board->getField(fig->getPosx(), (fig->getPosy() + 1)) == 0 && board->getField(fig->getPosx(), (fig->getPosy() + 2)) == 0)
		{
			moves[index] = new int[3];
			moves[index][0] = fig->getPosx();
			moves[index][1] = fig->getPosy() + 2;
			moves[index][2] = 0;
			index++;
		}
		else if (board->getField(fig->getPosx() + 1, fig->getPosy() + 1) < 0)
		{
			moves[index] = new int[3];
			moves[index][0] = fig->getPosx() + 1;
			moves[index][1] = fig->getPosy() + 1;
			moves[index][2] = conv->getWert(board->touchSchwarz(-(board->getField(fig->getPosx() + 1, fig->getPosy() + 1)+1))->getTyp());
			index++;
		}
		else if (board->getField(fig->getPosx() + 1, fig->getPosy() - 1) < 0)
		{
			moves[index] = new int[3];
			moves[index][0] = fig->getPosx() + 1;
			moves[index][1] = fig->getPosy() - 1;
			moves[index][2] = conv->getWert(board->touchSchwarz(-(board->getField(fig->getPosx() + 1, fig->getPosy() - 1) + 1))->getTyp());
			index++;
		}
		else if (fig->getTyp() == 'p')
		{
			if (board->getField(fig->getPosx(), (fig->getPosy() - 1)) == 0)
			{
				moves[index] = new int[3];
				moves[index][0] = fig->getPosx();
				moves[index][1] = fig->getPosy() - 1;
				moves[index][2] = 0;
				index++;
			}
			else if (fig->getPosx() == 6 && board->getField(fig->getPosx(), (fig->getPosy() - 1)) == 0 && board->getField(fig->getPosx(), (fig->getPosy() - 2)) == 0)
			{
				moves[index] = new int[3];
				moves[index][0] = fig->getPosx();
				moves[index][1] = fig->getPosy() - 2;
				moves[index][2] = 0;
				index++;
			}
			else if (board->getField(fig->getPosx() - 1, fig->getPosy() + 1) > 0)
			{
				moves[index] = new int[3];
				moves[index][0] = fig->getPosx() - 1;
				moves[index][1] = fig->getPosy() + 1;
				moves[index][2] = -conv->getWert(board->touchWeiss((board->getField(fig->getPosx() - 1, fig->getPosy() + 1) - 1))->getTyp());
				index++;
			}
			else if (board->getField(fig->getPosx() - 1, fig->getPosy() - 1) > 0)
			{
				moves[index] = new int[3];
				moves[index][0] = fig->getPosx() - 1;
				moves[index][1] = fig->getPosy() - 1;
				moves[index][2] = -conv->getWert(board->touchWeiss((board->getField(fig->getPosx() - 1, fig->getPosy() - 1) - 1))->getTyp());
				index++;
			}
		}
		// Springer ------------------------------------------------------------------------------------------------------------
		// Weiss----------------------------------------------------------------------------------------------------------------
		if (fig->getTyp() == 'N')
		{
			if ((fig->getPosx() + 2) < 7 && (fig->getPosy() + 1) < 7 && board->getField(fig->getPosx() + 2, fig->getPosy() + 1) <= 0)
			{
				moves[index] = new int[3];
				moves[index][0] = fig->getPosx() + 2;
				moves[index][1] = fig->getPosy() + 1;
				if (board->getField(fig->getPosx() + 2, fig->getPosy() + 1) < 0)
				{
					moves[index][2]= conv->getWert(board->touchSchwarz(-(board->getField(fig->getPosx() + 2 , fig->getPosy() + 1) + 1))->getTyp());
				}
				else
				{
					moves[index][2] = 0;
				}
				index++;
			}
			else if ((fig->getPosx() + 2) < 7 && (fig->getPosy() - 1) > -1 && board->getField(fig->getPosx() + 2, fig->getPosy() - 1) <= 0)
			{
				moves[index] = new int[3];
				moves[index][0] = fig->getPosx() + 2;
				moves[index][1] = fig->getPosy() - 1;
				if (board->getField(fig->getPosx() + 2, fig->getPosy() - 1) < 0)
				{
					moves[index][2] = conv->getWert(board->touchSchwarz(-(board->getField(fig->getPosx() + 2, fig->getPosy() - 1) + 1))->getTyp());
				}
				else
				{
					moves[index][2] = 0;
				}
				index++;
			}
			else if ((fig->getPosx() - 2) > -1 && (fig->getPosy() + 1) < 7 && board->getField(fig->getPosx() - 2, fig->getPosy() + 1) <= 0)
			{
				moves[index] = new int[3];
				moves[index][0] = fig->getPosx() - 2;
				moves[index][1] = fig->getPosy() + 1;
				if (board->getField(fig->getPosx() - 2, fig->getPosy() + 1) < 0)
				{
					moves[index][2] = conv->getWert(board->touchSchwarz(-(board->getField(fig->getPosx() - 2, fig->getPosy() + 1) + 1))->getTyp());
				}
				else
				{
					moves[index][2] = 0;
				}
				index++;
			}
			else if ((fig->getPosx() - 2) > -1 && (fig->getPosy() - 1) > -1 && board->getField(fig->getPosx() - 2, fig->getPosy() - 1) <= 0)
			{
				moves[index] = new int[3];
				moves[index][0] = fig->getPosx() - 2;
				moves[index][1] = fig->getPosy() - 1;
				if (board->getField(fig->getPosx() - 2, fig->getPosy() - 1) < 0)
				{
					moves[index][2] = conv->getWert(board->touchSchwarz(-(board->getField(fig->getPosx() - 2, fig->getPosy() - 1) + 1))->getTyp());
				}
				else
				{
					moves[index][2] = 0;
				}
				index++;
			}
			else if ((fig->getPosx() + 1) < 7 && (fig->getPosy() + 2) < 7 && board->getField(fig->getPosx() + 1, fig->getPosy() + 2) <= 0)
			{
				moves[index] = new int[3];
				moves[index][0] = fig->getPosx() + 1;
				moves[index][1] = fig->getPosy() + 2;
				if (board->getField(fig->getPosx() + 1, fig->getPosy() + 2) < 0)
				{
					moves[index][2] = conv->getWert(board->touchSchwarz(-(board->getField(fig->getPosx() + 1, fig->getPosy() + 2) + 1))->getTyp());
				}
				else
				{
					moves[index][2] = 0;
				}
				index++;
			}
			else if ((fig->getPosx() - 1) > -1 && (fig->getPosy() + 2) < 7 && board->getField(fig->getPosx() - 1, fig->getPosy() + 2) <= 0)
			{
				moves[index] = new int[3];
				moves[index][0] = fig->getPosx() - 1;
				moves[index][1] = fig->getPosy() + 2;
				if (board->getField(fig->getPosx() - 1, fig->getPosy() + 2) < 0)
				{
					moves[index][2] = conv->getWert(board->touchSchwarz(-(board->getField(fig->getPosx() - 1, fig->getPosy() + 2) + 1))->getTyp());
				}
				else
				{
					moves[index][2] = 0;
				}
				index++;
			}
			else if ((fig->getPosx() + 1) < 7 && (fig->getPosy() - 2) > -1 && board->getField(fig->getPosx() + 1, fig->getPosy() - 2) <= 0)
			{
				moves[index] = new int[3];
				moves[index][0] = fig->getPosx() + 1;
				moves[index][1] = fig->getPosy() - 2;
				if (board->getField(fig->getPosx() + 1, fig->getPosy() - 2) < 0)
				{
					moves[index][2] = conv->getWert(board->touchSchwarz(-(board->getField(fig->getPosx() + 1, fig->getPosy() - 2) + 1))->getTyp());
				}
				else
				{
					moves[index][2] = 0;
				}
				index++;
			}
			else if ((fig->getPosx() - 1) > -1 && (fig->getPosy() -2 ) > -1 && board->getField(fig->getPosx() - 1, fig->getPosy() - 2) <= 0)
			{
				moves[index] = new int[3];
				moves[index][0] = fig->getPosx() - 1;
				moves[index][1] = fig->getPosy() - 2;
				if (board->getField(fig->getPosx() - 1, fig->getPosy() - 2) < 0)
				{
					moves[index][2] = conv->getWert(board->touchSchwarz(-(board->getField(fig->getPosx() - 1, fig->getPosy() - 2) + 1))->getTyp());
				}
				else
				{
					moves[index][2] = 0;
				}
				index++;
			}
		}
		// Schwarz--------------------------------------------------------------------------------------------------------------
		if (fig->getTyp() == 'n')
		{
			if ((fig->getPosx() + 2) < 7 && (fig->getPosy() + 1) < 7 && board->getField(fig->getPosx() + 2, fig->getPosy() + 1) >= 0)
			{
				moves[index] = new int[3];
				moves[index][0] = fig->getPosx() + 2;
				moves[index][1] = fig->getPosy() + 1;
				if (board->getField(fig->getPosx() + 2, fig->getPosy() + 1) < 0)
				{
					moves[index][2] = -conv->getWert(board->touchWeiss(board->getField(fig->getPosx() + 2, fig->getPosy() + 1) - 1)->getTyp());
				}
				else
				{
					moves[index][2] = 0;
				}
				index++;
			}
			else if ((fig->getPosx() + 2) < 7 && (fig->getPosy() - 1) > -1 && board->getField(fig->getPosx() + 2, fig->getPosy() - 1) <= 0)
			{
				moves[index] = new int[3];
				moves[index][0] = fig->getPosx() + 2;
				moves[index][1] = fig->getPosy() - 1;
				if (board->getField(fig->getPosx() + 2, fig->getPosy() - 1) < 0)
				{
					moves[index][2] = -conv->getWert(board->touchWeiss((board->getField(fig->getPosx() + 2, fig->getPosy() - 1) - 1))->getTyp());
				}
				else
				{
					moves[index][2] = 0;
				}
				index++;
			}
			else if ((fig->getPosx() - 2) > -1 && (fig->getPosy() + 1) < 7 && board->getField(fig->getPosx() - 2, fig->getPosy() + 1) <= 0)
			{
				moves[index] = new int[3];
				moves[index][0] = fig->getPosx() - 2;
				moves[index][1] = fig->getPosy() + 1;
				if (board->getField(fig->getPosx() - 2, fig->getPosy() + 1) < 0)
				{
					moves[index][2] = -conv->getWert(board->touchWeiss((board->getField(fig->getPosx() - 2, fig->getPosy() + 1) - 1))->getTyp());
				}
				else
				{
					moves[index][2] = 0;
				}
				index++;
			}
			else if ((fig->getPosx() - 2) > -1 && (fig->getPosy() - 1) > -1 && board->getField(fig->getPosx() - 2, fig->getPosy() - 1) <= 0)
			{
				moves[index] = new int[3];
				moves[index][0] = fig->getPosx() - 2;
				moves[index][1] = fig->getPosy() - 1;
				if (board->getField(fig->getPosx() - 2, fig->getPosy() - 1) < 0)
				{
					moves[index][2] = -conv->getWert(board->touchWeiss((board->getField(fig->getPosx() - 2, fig->getPosy() - 1) - 1))->getTyp());
				}
				else
				{
					moves[index][2] = 0;
				}
				index++;
			}
			else if ((fig->getPosx() + 1) < 7 && (fig->getPosy() + 2) < 7 && board->getField(fig->getPosx() + 1, fig->getPosy() + 2) <= 0)
			{
				moves[index] = new int[3];
				moves[index][0] = fig->getPosx() + 1;
				moves[index][1] = fig->getPosy() + 2;
				if (board->getField(fig->getPosx() + 1, fig->getPosy() + 2) < 0)
				{
					moves[index][2] = -conv->getWert(board->touchWeiss((board->getField(fig->getPosx() + 1, fig->getPosy() + 2) - 1))->getTyp());
				}
				else
				{
					moves[index][2] = 0;
				}
				index++;
			}
			else if ((fig->getPosx() - 1) > -1 && (fig->getPosy() + 2) < 7 && board->getField(fig->getPosx() - 1, fig->getPosy() + 2) <= 0)
			{
				moves[index] = new int[3];
				moves[index][0] = fig->getPosx() - 1;
				moves[index][1] = fig->getPosy() + 2;
				if (board->getField(fig->getPosx() - 1, fig->getPosy() + 2) < 0)
				{
					moves[index][2] = -conv->getWert(board->touchWeiss((board->getField(fig->getPosx() - 1, fig->getPosy() + 2) - 1))->getTyp());
				}
				else
				{
					moves[index][2] = 0;
				}
				index++;
			}
			else if ((fig->getPosx() + 1) < 7 && (fig->getPosy() - 2) > -1 && board->getField(fig->getPosx() + 1, fig->getPosy() - 2) <= 0)
			{
				moves[index] = new int[3];
				moves[index][0] = fig->getPosx() + 1;
				moves[index][1] = fig->getPosy() - 2;
				if (board->getField(fig->getPosx() + 1, fig->getPosy() - 2) < 0)
				{
					moves[index][2] = -conv->getWert(board->touchWeiss((board->getField(fig->getPosx() + 1, fig->getPosy() - 2) - 1))->getTyp());
				}
				else
				{
					moves[index][2] = 0;
				}
				index++;
			}
			else if ((fig->getPosx() - 1) > -1 && (fig->getPosy() - 2) > -1 && board->getField(fig->getPosx() - 1, fig->getPosy() - 2) <= 0)
			{
				moves[index] = new int[3];
				moves[index][0] = fig->getPosx() - 1;
				moves[index][1] = fig->getPosy() - 2;
				if (board->getField(fig->getPosx() - 1, fig->getPosy() - 2) < 0)
				{
					moves[index][2] = -conv->getWert(board->touchSchwarz((board->getField(fig->getPosx() - 1, fig->getPosy() - 2) - 1))->getTyp());
				}
				else
				{
					moves[index][2] = 0;
				}
				index++;
			}
		}
		// Läufer und Queen--------------------------------------------------------------------------------------------------------
		moves[index] = new int[3];
		moves[index][0] = -1;
		moves[index][1] = -1;
		moves[index][2] = 0;

	}
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
		if (board->getField(fig->getPosx(), (fig->getPosy() + 1)) == 0)
		{
			if (move[0][0] == move[1][0])
			{
				if (move[0][1] == (move[1][1] - 1))
				{
					return true;
				}
				else
				{
					if (board->getField(fig->getPosx(), (fig->getPosy() + 2)) == 0)
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
		else if (board->getField(fig->getPosx() + 1, (fig->getPosy() + 1)) < 0 && move[0][0] == (move[1][0] +1) && move[0][1]==(move[1][1]+1))
		{
			return true;
		}
		else if (board->getField(fig->getPosx() + 1, (fig->getPosy() - 1)) < 0 && move[0][0] == (move[1][0] + 1) && move[0][1] == (move[1][1] - 1))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	if (fig->getTyp() == 'p')
	{
		if (board->getField(fig->getPosx(), (fig->getPosy() - 1)) == 0)
		{
			if (move[0][0] == move[1][0])
			{
				if (move[0][1] == (move[1][1] + 1))
				{
					return true;
				}
				else
				{
					if (board->getField(fig->getPosx(), (fig->getPosy() - 2)) == 0)
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
			else if (board->getField(fig->getPosx() - 1, (fig->getPosy() + 1)) > 0 && move[0][0] == (move[1][0] - 1) && move[0][1] == (move[1][1] + 1))
			{
				return true;
			}
			else if (board->getField(fig->getPosx() - 1, (fig->getPosy() - 1)) > 0 && move[0][0] == (move[1][0] - 1) && move[0][1] == (move[1][1] - 1))
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
	if (fig->getTyp() == 'N')
	{
		if ((fig->getPosx() + 2) < 7 && (fig->getPosy() + 1) < 7 && board->getField(fig->getPosx() + 2, fig->getPosy() + 1) <= 0)
		{
			return true;
		}
		else if ((fig->getPosx() + 2) < 7 && (fig->getPosy() - 1) > -1 && board->getField(fig->getPosx() + 2, fig->getPosy() - 1) <= 0)
		{
			return true;
		}
		else if ((fig->getPosx() - 2) > -1 && (fig->getPosy() + 1) < 7 && board->getField(fig->getPosx() - 2, fig->getPosy() + 1) <= 0)
		{
			return true;
		}
		else if ((fig->getPosx() - 2) > -1 && (fig->getPosy() - 1) > -1 && board->getField(fig->getPosx() - 2, fig->getPosy() - 1) <= 0)
		{
			return true;
		}
		else if ((fig->getPosx() + 1) < 7 && (fig->getPosy() + 2) < 7 && board->getField(fig->getPosx() + 1, fig->getPosy() + 2) <= 0)
		{
			return true;
		}
		else if ((fig->getPosx() - 1) > -1 && (fig->getPosy() + 2) < 7 && board->getField(fig->getPosx() - 1, fig->getPosy() + 2) <= 0)
		{
			return true;
		}
		else if ((fig->getPosx() + 1) < 7 && (fig->getPosy() - 2) > -1 && board->getField(fig->getPosx() + 1, fig->getPosy() - 2) <= 0)
		{
			return true;
		}
		else if ((fig->getPosx() - 1) > -1 && (fig->getPosy() - 2) > -1 && board->getField(fig->getPosx() - 1, fig->getPosy() - 2) <= 0)
		{
			return true;
		}
	}
	// Schwarz--------------------------------------------------------------------------------------------------------------
	if (fig->getTyp() == 'n')
	{
		if ((fig->getPosx() + 2) < 7 && (fig->getPosy() + 1) < 7 && board->getField(fig->getPosx() + 2, fig->getPosy() + 1) >= 0)
		{
			return true;
		}
		else if ((fig->getPosx() + 2) < 7 && (fig->getPosy() - 1) > -1 && board->getField(fig->getPosx() + 2, fig->getPosy() - 1) <= 0)
		{
			return true;
		}
		else if ((fig->getPosx() - 2) > -1 && (fig->getPosy() + 1) < 7 && board->getField(fig->getPosx() - 2, fig->getPosy() + 1) <= 0)
		{
			return true;
		}
		else if ((fig->getPosx() - 2) > -1 && (fig->getPosy() - 1) > -1 && board->getField(fig->getPosx() - 2, fig->getPosy() - 1) <= 0)
		{
			return true;
		}
		else if ((fig->getPosx() + 1) < 7 && (fig->getPosy() + 2) < 7 && board->getField(fig->getPosx() + 1, fig->getPosy() + 2) <= 0)
		{
			return true;
		}
		else if ((fig->getPosx() - 1) > -1 && (fig->getPosy() + 2) < 7 && board->getField(fig->getPosx() - 1, fig->getPosy() + 2) <= 0)
		{
			return true;
		}
		else if ((fig->getPosx() + 1) < 7 && (fig->getPosy() - 2) > -1 && board->getField(fig->getPosx() + 1, fig->getPosy() - 2) <= 0)
		{
			return true;
		}
		else if ((fig->getPosx() - 1) > -1 && (fig->getPosy() - 2) > -1 && board->getField(fig->getPosx() - 1, fig->getPosy() - 2) <= 0)
		{
			return true;
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
		if (fig->getTyp() == 'P' &&  move.length()>4)
		{
			promo = move.at(4);
			wert = conv->getWert(promo);
			if (wert > 0 && wert < 10)
			{
				wert = conv->getWert(fig->getTyp()) - wert;
				board->setFigurenwert(board->getFigurenwert() + wert);
			}
		}
		else if (fig->getTyp() == 'K'  && movemade[0][0] == 4 && movemade[0][1]==0)
		{
			if (board->getCastlKingside(true) && movemade[1][0]== 6 && movemade[0][1]==0)
			{
				if (board->getField(5, 0) == 0 && board->getField(6, 0) == 0 )
				{
					rochKS = true;
				}
			}
			else if (board->getCastlQueenside(true) && movemade[1][0] == 2 && movemade[0][1] == 0)
			{
				if (board->getField(3, 0) == 0 && board->getField(2, 0) == 0 && board->getField(2, 0) == 0)
				{
					rochQS = true;
				}
			}
		}
	}
	else
	{
		fig = board->touchSchwarz(-(z + 1));
		if (fig->getTyp() == 'p' &&  move.length() > 4)
		{
			promo = move.at(4);
			wert = conv->getWert(promo);
			if (wert > 0 && wert < 10)
			{
				wert = conv->getWert(fig->getTyp()) - wert;
				board->setFigurenwert(board->getFigurenwert() - wert);
			}
		}
		else if (fig->getTyp() == 'k'  && movemade[0][0] == 4 && movemade[0][1] == 7)
		{
			if (board->getCastlKingside(true) && movemade[1][0] == 6 && movemade[0][1] == 7)
			{
				if (board->getField(5, 7) == 0 && board->getField(6, 7) == 0)
				{
					rochKS = true;
				}
			}
			else if (board->getCastlQueenside(true) && movemade[1][0] == 2 && movemade[0][1] == 7)
			{
				if (board->getField(3, 7) == 0 && board->getField(2, 7) == 0 && board->getField(2, 7) == 0)
				{
					rochQS = true;
				}
			}
		}
	}
	if (this->proveMove(movemade, fig, board))
	{
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
		if (trade)
		{
			if (z > 0)
			{
				board->touchWeiss(z - 1)->setTyp(promo);
			}
			else
			{
				board->touchSchwarz(-(z + 1))->setTyp(promo);
			}
		}
		board->setWhitetoMove(!board->getWhitetoMove());
		return true;
	}
	return false;
}

