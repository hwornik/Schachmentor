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
	if (w == 'p' || w == 'P')
		return 1;
	if (w == 'r' || w == 'R')
		return 5;
	if (w == 'b' || w == 'B')
		return 3;
	if (w == 'n' || w == 'N')
		return 3;
	if (w == 'q' || w == 'Q')
		return 9;
	if (w == 'k' || w == 'K')
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
int Convert::getcharfromNumber(int line)
{
	return NUMBERTOCHAR[line];
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
						if (pos[z] == 'K')
						{
							board->setKingPos(true, j, i);
						}
					}
					else
					{
						board->addnewFigurSchwarz();
						wi = board->getFigurmax(false);
						board->touchSchwarz(wi)->setTyp(pos[z]);
						board->touchSchwarz(wi)->setPosx(j);
						board->touchSchwarz(wi)->setPosy(i);
						board->setField(j, i, -wi);
						if (pos[z] == 'k')
						{
							board->setKingPos(true, j, i);
						}
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
		board->setEnPassant(-1);
	}
	else
	{
		board->setEnPassant(this->getNumberofChar(pos[z]));
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
	char fenstring[85];
	for (register int i = 0; i < 85; i++)
	{
		fenstring[i] = ' ';
	}
	fenstring[84] = '\0';
	int z = 0;
	int leer;
	for (int i = 7; i >= 0; i--)
	{
		leer = 0;
		for (int j = 0; j < 8; j++)
		{
			if (board->getField(j,i) == 0)
			{
				leer++;
			}
			else
			{
				if (leer > 0)
				{
					fenstring[z] = (char)leer + 48;
					leer = 0;
					z++;
				}
				if (board->getField(j, i) > 0)
				{
					fenstring[z] = board->touchWeiss(board->getField(j, i)-1)->getTyp();
				}
				else
				{
					fenstring[z] = board->touchSchwarz(-(board->getField(j, i)+1))->getTyp();
				}

				z++;
			}
		}
		if (leer > 0)
		{
			fenstring[z] = (char)leer + 48;
			leer = 0;
			z++;
		}
		if (i >0 && i<7)
		{
			fenstring[z] = '/';
			z++;
		}
	}
	fenstring[z] = ' ';
	z++;
	if (board->getWhitetoMove())
	{
		fenstring[z] = 'w';
	}
	else
	{
		fenstring[z] = 'b';
	}
	//Für richtigen FenString notwendig
	z++;
	fenstring[z] = ' ';
	z++;
	if (board->getCastlKingside(true))
	{
		fenstring[z] = 'K';
		z++;
	}
	if (board->getCastlQueenside(true))
	{
		fenstring[z] = 'Q';
		z++;
	}
	if (board->getCastlKingside(false))
	{
		fenstring[z] = 'k';
		z++;
	}
	if (board->getCastlQueenside(false))
	{
		fenstring[z] = 'q';
		z++;
	}
	fenstring[z] = ' ';
	z++;
	if (board->getEnPassant() < 0)
	{
		fenstring[z] = '-';
	}
	else
	{		
		fenstring[z] = this->getcharfromNumber(board->getEnPassant());
	}
	z++;
	fenstring[z] = ' ';
	z++;
	fenstring[z] = board->getHalbzug();
	z++;
	fenstring[z] = ' ';
	z++;
	fenstring[z] = board->getZugNr();
}

void Convert::displayBoard(Brett *board)
{
	for (int i = 8; i > 0; i--)
	{
		for (int j = 1; j < 9; j++)
		{
			int x;
			x = board->getField(j, i);
			if (x != 0)
			{
				if (x > 0)
				{
					x = x - 1;
					std::cout << board->touchWeiss(x)->getTyp();
				}
				else
				{
					x = -(x + 1);
					std::cout << board->touchSchwarz(x)->getTyp();
				}
			}
			else
			{
				std::cout << BRETTFARBEN[j][i];
			}
		}
		printf("\n");
	}
	if (board->getWhitetoMove())
	{
		printf("White to Move");
	}
	else
	{
		printf("Black to Move");
	}
	printf("\n");
}