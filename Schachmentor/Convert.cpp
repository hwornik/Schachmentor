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
	return -1;
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
				z++;
			}
			if (pos[z] != '1')
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
						board->addnewFigur(true);
						wi = board->getFigurmax(true) - 1;
						board->touchFigur(wi,true)->setTyp(pos[z]);
						board->touchFigur(wi,true)->setPosx(j);
						board->touchFigur(wi,true)->setPosy(i);
						if (pos[z] == 'K')
						{
							board->setKingPos(true, j, i);
						}
					}
					else
					{
						board->addnewFigur(false);
						wi = board->getFigurmax(false) - 1;
						board->touchFigur(wi,false)->setTyp(pos[z]);
						board->touchFigur(wi,false)->setPosx(j);
						board->touchFigur(wi,false)->setPosy(i);
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
	char fenstring[100];
	int z = 0;
	int leer;
	for (int i = 7; i >= 0; i--)
	{
		leer = 0;
		if (i != 0)
		{
			fenstring[z] = '/';
			z++;
		}
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
				if (board->getField(j, i) > 0 && board->getField(j, i) < board->getFigurmax(true))
				{
					fenstring[z] = board->touchFigur(board->getField(j, i) - 1, true)->getTyp();
					z++;
				}
				else if (board->getField(j, i) < 0 && board->getField(j, i) > -board->getFigurmax(false))
				{
					fenstring[z] = board->touchFigur(-(board->getField(j, i) + 1), false)->getTyp();
					z++;
				}
			}
		}
		if (leer > 0)
		{
			fenstring[z] = (char)leer + 48;
			leer = 0;
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
	fenstring[z] = (char)board->getHalbzug() + 48;
	z++;
	fenstring[z] = ' ';
	z++;
	fenstring[z] = (char)board->getZugNr() + 48;
	z++;
	fenstring[z] = '\n';
	std::string strfen = fenstring;
	return strfen.substr(0,z);
}

void Convert::displayBoard(Brett *board)
{
	printf("\n");
	for (int i = 7; i >= 0; i--)
	{
		for (int j = 0; j < 8; j++)
		{
			int x;
			x = board->getField(j, i);
			//std::cout << '#' << x << '#';
			if (x != 0)
			{
				if (x > 0)
				{
					x = x - 1;
					std::cout << board->touchFigur(x, true)->getTyp();
				}
				else
				{
					x = -(x + 1);
					std::cout << board->touchFigur(x, false)->getTyp();
				}
			}
			else
			{
				std::cout << BRETTFELDER[j][i];
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

int ** Convert::getMoveIntfromChar(std::string move)
{
	const char *moveone = move.c_str();
	int **mademove = new int*[2];
	mademove[0] = new int[2];
	mademove[1] = new int[2];
	int ind = 0;
	if (!isalpha(moveone[ind]))
		ind++;
	mademove[0][0] = this->getNumberofChar(moveone[ind]);
	ind++;
	mademove[0][1] = this->getIntfromNumber(moveone[ind]);
	ind++;
	mademove[1][0] = this->getNumberofChar(moveone[ind]);
	ind++;
	mademove[1][1] = this->getIntfromNumber(moveone[ind]);
	return mademove;
}

int Convert::getIntfromNumber(char n)
{
	if (n == '1')
		return 0;
	if (n == '2')
		return 1;
	if (n == '3')
		return 2;
	if (n == '4')
		return 3;
	if (n == '5')
		return 4;
	if (n == '6')
		return 5;
	if (n == '7')
		return 6;
	if (n == '8')
		return 7;
	return -1;
}

char Convert::getNumberfromInt(int n)
{
	if (n == 0)
		return '1';
	if (n == 1)
		return '2';
	if (n == 2)
		return '3';
	if (n == 3)
		return '4';
	if (n == 4)
		return '5';
	if (n == 5)
		return '6';
	if (n == 6)
		return '7';
	if (n == 7)
		return '8';
	return ' ';
}
std::string Convert::getStringfromInt(int vonx, int vony, int nachx, int nachy, char promo)
{
	char word[5] = { ' ' };
	word[0] = this->getcharfromNumber(vonx);
	word[1] = this->getNumberfromInt(vony);
	word[2] = this->getcharfromNumber(nachx);
	word[3] = this->getNumberfromInt(nachy);
	if(this->getWert(promo)>0)
		word[4] = promo;
	std::string str=word;
	return str;
}
