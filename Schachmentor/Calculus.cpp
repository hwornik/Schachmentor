#include "stdafx.h"
#include "Calculus.h"


Calculus::Calculus()
{
}


Calculus::~Calculus()
{
}

void Calculus::deepSearch(Hashbrett * boards, Movemennt * move, int tiefe, int godepth, std::string zug,int *wertzug, std::string *bestmove, std::string *ponder,bool *whitesearch)
{
	Hashbrett * aktuell;
	tiefe++;
	bool white = boards->getBoard()->getWhitetoMove();
	Moving *movesperfig, *loschen;
	int moveindex = 0;
	aktuell = boards;
	Convert *conv = new Convert();
	for (int i = 0; i < boards->getBoard()->getFigurmax(white); i++)
	{
		movesperfig = move->getMovesperFigure(boards->getBoard(), boards->getBoard()->getFigur(i, white));
		while (movesperfig->getnext() != NULL)
		{
			loschen = movesperfig;
			movesperfig = movesperfig->getnext();
			loschen->setNext(NULL);
			delete loschen;
			Hashbrett *hash = new Hashbrett();
			hash->setBoard(move->copyBoard(boards->getBoard()));
			hash->getBoard()->setFigurenwert(boards->getBoard()->getFigurenwert() + movesperfig->getW());
			move->makeMove(hash->getBoard()->getFigur(i, white), movesperfig->getX(), movesperfig->getY(), ' ', hash);
			hash->setZugFolge(boards->getZugFolge()+" "+hash->getZug());
			hash->setFenString(conv->getBoardFen(hash->getBoard()));
			aktuell->setChild(hash, white);
			aktuell = aktuell->getChild(white);
			if (godepth > tiefe)
			{
				this->deepSearch(hash, move, tiefe, godepth,zug, wertzug, bestmove, ponder,whitesearch);
			}
			if (godepth == tiefe)
			{
				std::cout << "info score cp " << hash->getBoard()->getFigurenwert() * 10 << " pv " + hash->getZugFolge() << " " << "\n";
				if(*whitesearch)
				{
					if (*wertzug < hash->getBoard()->getFigurenwert())
					{
						*wertzug = hash->getBoard()->getFigurenwert();
						*ponder = *bestmove;
						*bestmove = hash->getZugFolge().substr(0, 5);
					}
				}
				else
				{
					if (*wertzug > hash->getBoard()->getFigurenwert())
					{
						*wertzug = hash->getBoard()->getFigurenwert();
						*ponder = *bestmove;
						*bestmove = hash->getZugFolge().substr(0, 5);
					}
				}
			}
			moveindex++;
			//tiefe--;
		}
		delete movesperfig;
		//std::cout << "---------------------------------------------------------\n";
	}
	//std::cout << moveindex << " Zuge gefunden Depth\n";
}

void Calculus::traversSearch(Hashbrett * boards, Movemennt * move, int tiefe, int godepth, std::string zug, int *wertzug, std::string *bestmove, std::string *ponder, bool *whitesearch)
{
	godepth = 1;
	if (boards->getChild(true) != NULL)
		traversSearch(boards->getChild(true),move,tiefe,godepth,zug, wertzug, bestmove, ponder, whitesearch);
	if (boards->getChild(false) != NULL)
		traversSearch(boards->getChild(false), move, tiefe, godepth, zug, wertzug, bestmove, ponder, whitesearch);
	if (boards->getChild(boards->getBoard()->getWhitetoMove()) == NULL)
	{
		tiefe = 0;
		boards->setZugFolge(boards->getZugFolge().substr(5, boards->getZugFolge().length()));
		this->deepSearch(boards, move, tiefe, godepth, zug, wertzug, bestmove, ponder, whitesearch);
	}
}
