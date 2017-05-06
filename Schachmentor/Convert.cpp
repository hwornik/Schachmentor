#include "stdafx.h"
#include "Convert.h"


Convert::Convert()
{
}


Convert::~Convert()
{
}

int Convert::getWert(char w)
{
	if (w == 'p' || 'P')
		return 1;
	if (w == 'r' || 'R')
		return 5;
	if (w == 'b' || 'B')
		return 3;
	if (w == 'n' || 'N')
		return 3;
	if (w == 'q' || 'Q')
		return 9;
	if (w == 'k' || 'K')
		return 100;
}


int Convert::getNumberofChar(char line)
{
	if (line == 'a')
		return 0;
	if (line == 'b')
		return 1;
	if (line == 'c')
		return 2;
	if (line == 'd')
		return 3;
	if (line == 'e')
		return 4;
	if (line == 'f')
		return 5;
	if (line == 'g')
		return 6;
	if (line == 'h')
		return 7;
	return -1;
}

void Convert::setBoardwithFEN(Brett *board, std::string fen)
{
	const char *pos = fen.c_str();
	board->reset();
	int z = 0;
	// posx=j, posy=i
	for (int i = 7; i >= 0; i--)
	{
		for (int j = 0; j < 8; j++)
		{
			if (pos[z] == '/')
			{
				j--;
			}
			else if (pos[z] == '1')
			{

				if (pos[z] == '2')
				{
					j++;
				}
				else if (pos[z] == '3')
				{
					j = j + 2;

				}
				else if (pos[z] == '4')
				{
					j = j + 3;
				}
				else if (pos[z] == '5')
				{
					j = j + 4;
				}
				else if (pos[z] == '6')
				{
					j = j + 5;
				}
				else if (pos[z] == '7')
				{
					j = j + 6;
				}
				else if (pos[z] == '8')
				{
					j = j + 7;
				}
				else
				{
					int wi;
					if (isupper(pos[z]))
					{
						board->addnewFigurWeiss();
						wi = board->getFigurmax(true);
						board->touchWeiss(wi)->setTyp(pos[z]);
						board->touchWeiss(wi)->setPosx(j);
						board->touchWeiss(wi)->setPosy(i);
						board->setField(j, i, wi);
						wi++;
						if (pos[z] == 'K')
						{
							board->setKingPos(true, j, i);
						}
						wi++;
					}
					else
					{
						board->addnewFigurSchwarz();
						wi = board->getFigurmax(false);
						board->touchSchwarz(wi)->setTyp(pos[z]);
						board->touchSchwarz(wi)->setPosx(j);
						board->touchSchwarz(wi)->setPosy(i);
						board->setField(j, i, wi);
						wi++;
						if (pos[z] == 'k')
						{
							board->setKingPos(true, j, i);
						}
						wi++;
					}
				}
			}
			z++;
		}
	}
	z++;
	if (pos[z] == 'w')
	{
		board->setWhitetoMove(true);
	}
	else
	{
		board->setWhitetoMove(false);
	}
	z++;
	z++;
	if (pos[z] == 'K')
	{
		board->setCastlKingside(true, true);
		z++;
	}
	else
	{
		board->setCastlKingside(true, false);
	}
	if (pos[z] == 'Q')
	{
		board->setCastlQueenside(true, true);
		z++;
	}
	else
	{
		board->setCastlQueenside(true, false);
	}
	if (pos[z] == 'k')
	{
		board->setCastlKingside(false, true);
		z++;
	}
	else
	{
		board->setCastlKingside(false, false);
	}
	if (pos[z] == 'q')
	{
		board->setCastlQueenside(false, true);
		z++;
	}
	else
	{
		board->setCastlKingside(false, false);
	}
	z++;
	if (pos[z] == '-')
	{
		board->setEnPassant(false);
	}
	else
	{
		board->setEnPassant(true);
		z++;
	}
	while (!isdigit(pos[z]))
		z++;
	int w = pos[z] - 48;
	z++;
	while (isdigit(pos[z]))
	{
		w = (pos[z] - 48) + w * 10;
		z++;
	}
	board->setHalbzug(w);
	while (!isdigit(pos[z]))
		z++;
	w = pos[z] - 48;
	z++;
	while (isdigit(pos[z]))
	{
		w = (pos[z] - 48) + w * 10;
		z++;
	}
	board->setZugNr(w);
}

std::string Convert::getBoardFen(Brett * board)
{
	return std::string();
}
