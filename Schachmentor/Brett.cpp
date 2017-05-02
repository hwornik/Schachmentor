#include "stdafx.h"
#include "Brett.h"


Brett::Brett()
{
	
}


Brett::~Brett()
{
	for (int i = 0; i < 16; i++)
	{
		if (Schwarz[i] != NULL)
			delete Schwarz[i];
		if (Weiss[i] != NULL)
			delete Weiss[i];
	}
	delete Schwarz;
	delete Weiss;
}

int Brett::getNumberofChar(char line)
{
	if(line=='a')
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

bool Brett::setBoardfromFEN(char pos[100])
{
	this->reset();
	int z = 0,wi=0,si=0;
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
					j=j+2;

				}
				else if (pos[z] == '4')
				{
					j=j+3;
				}
				else if (pos[z] == '5')
				{
					j=j+4;
				}
				else if (pos[z] == '6')
				{
					j=j+5;
				}
				else if (pos[z] == '7')
				{
					j=j+6;
				}
				else if (pos[z] == '8')
				{
					j=j+7;
				}
				else
				{
					if (isupper(pos[z]))
					{
						this->Weiss[wi] = new Figur();;
						this->Weiss[wi]->setTyp(pos[z]);
						this->Weiss[wi]->setPosx(j);
						this->Weiss[wi]->setPosy(i);
						this->Board[i][j] = wi + 1;
						wi++;
						if (pos[z] == 'K')
						{
							this->kingpos[0][0] = j;
							this->kingpos[0][1] = i;
						}
						wi++;
					}
					else
					{
						this->Schwarz[si] = new Figur();
						this->Schwarz[si]->setTyp(pos[z]);
						this->Schwarz[si]->setPosx(j);
						this->Schwarz[si]->setPosy(i);
						this->Board[i][j] = -(si + 1);
						if (pos[z] == 'k')
						{
							this->kingpos[1][0] = j;
							this->kingpos[1][1] = i;
						}
						si++;
					}
				}
			}
			z++;
		}
	}
	z++;
	if (pos[z] == 'w')
	{
		this->whitetoMove = true;
	}
	else
	{
		this->whitetoMove = false;
	}
	z++;
	z++;
	if (pos[z] == 'K')
	{
		this->castleKs[0] = true;
		z++;
	}
	else
	{
		this->castleKs[0] = false;
	}
	if (pos[z] == 'Q')
	{
		this->castleQs[0] = true;
		z++;
	}
	else
	{
		this->castleQs[0] = false;
	}
	if (pos[z] == 'k')
	{
		this->castleKs[1] = true;
		z++;
	}
	else
	{
		this->castleKs[1] = false;
	}
	if (pos[z] == 'q')
	{
		this->castleQs[1] = true;
		z++;
	}
	else
	{
		this->castleQs[1] = false;
	}
	z++;
	if (pos[z] == '-')
	{
		this->enpassant[0] = 0;
		this->enpassant[1] = 0;
	}
	else
	{
		this->enpassant[0] = pos[z];
		z++;
		this->enpassant[0] = pos[z];
	}
	while (!isdigit(pos[z]))
		z++;
	this->halbzug = pos[z] - 48;
	z++;
	while (isdigit(pos[z]))
	{
		this->halbzug = (pos[z] - 48) * 10;
		z++;
	}
	while (!isdigit(pos[z]))
		z++;
	this->zugnr = pos[z] - 48;
	z++;
	while (isdigit(pos[z]))
	{
		this->zugnr = (pos[z] - 48) * 10;
		z++;
	}
	return 0;

}

char Brett::getField(int i, int j)
{
	return Board[i][j];
}

void Brett::reset()
{
	for (int i = 0; i < 16; i++)
	{
		if (Schwarz[i] != NULL)
		{
			delete Schwarz[i];
			Schwarz[i] = NULL;
		}
		if (Weiss[i] != NULL)
		{
			delete Weiss[i];
			Weiss[i] = NULL;
		}
	}
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			Board[i][j] = 0;
		}
	}
	bewertg = 0;
	figwert = 0;
}

int Brett::bewertung()
{
	int weisswert = 0, schwarzwert = 0, wi = 0,si=0;
	for (int i = 0; i < 16; i++)
	{
		if (this->Weiss[wi] != NULL)
		{
			weisswert += getWert(Weiss[wi]->getTyp());
			wi++;
		}
		if (this->Schwarz[si] != NULL)
		{
			schwarzwert += getWert(Schwarz[si]->getTyp());
		}
	}
	this->figwert = weisswert - schwarzwert;
	return this->figwert;
}

int Brett::getWert(char w)
{
	if(w=='p'  ||  'P')
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
