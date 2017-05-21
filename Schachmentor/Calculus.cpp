#include "stdafx.h"
#include "Calculus.h"


Calculus::Calculus()
{
}


Calculus::~Calculus()
{
}

void Calculus::deepSearch(Hashbrett * boards, Movemennt * move, int tiefe, int godepth, std::string zug)
{
	Hashbrett * aktuell;
	tiefe++;
	bool white = boards->getBoard()->getWhitetoMove();
	Moving *movesperfig, *loschen;
	int moveindex = 0;
	aktuell = boards;
	for (int i = 0; i < boards->getBoard()->getFigurmax(white); i++)
	{
		movesperfig = move->getMovesperFigure(boards->getBoard(), boards->getBoard()->getFigur(i, white));
		while (movesperfig->getnext() != NULL)
		{
			loschen = movesperfig;
			movesperfig = movesperfig->getnext();
			Hashbrett *hash = new Hashbrett();
			hash->setBoard(move->copyBoard(boards->getBoard()));
			hash->getBoard()->setFigurenwert(boards->getBoard()->getFigurenwert() + movesperfig->getW());
			move->makeMove(boards->getBoard()->getFigur(i, white)->getPosx(), boards->getBoard()->getFigur(i, white)->getPosy(), movesperfig->getX(), movesperfig->getY(),' ',hash);
			hash->setZugFolge(boards->getZugFolge()+" "+hash->getZug());
			aktuell->setChild(hash, white);
			aktuell = aktuell->getChild(white);
			if (godepth > tiefe)
			{
				this->deepSearch(hash, move, tiefe, godepth,zug);
			}
			delete loschen;
			if(godepth == tiefe)
			std::cout << "info "+hash->getZugFolge() << " " << hash->getBoard()->getFigurenwert() << "\n";
			moveindex++;
			//tiefe--;
		}
		delete movesperfig;
		//std::cout << "---------------------------------------------------------\n";
	}
	std::cout << moveindex << " Zuge gefunden Depth\n";
}
