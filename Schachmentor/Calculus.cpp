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
	HANDLE hStdout;
	TCHAR msgBuf[BUF_SIZE];
	size_t cchStringSize;
	DWORD dwChars;

	// Make sure there is a console to receive output results. 

	hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	//if (hStdout == INVALID_HANDLE_VALUE)
	//	return 1;

	Hashbrett * aktuell;
	tiefe++;
	bool white = boards->getBoard()->getWhitetoMove();
	Moving *movesperfig, *loschen;
	int moveindex = 0;
	aktuell = boards;
	std::string str;
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
			if (godepth >= tiefe)
			{
				Hashbrett *hash = new Hashbrett();
				hash->setBoard(move->copyBoard(boards->getBoard()));
				hash->getBoard()->setFigurenwert(boards->getBoard()->getFigurenwert() + movesperfig->getW());
				move->makeMove(hash->getBoard()->getFigur(i, white), movesperfig->getX(), movesperfig->getY(), ' ', hash);
				hash->setZugFolge(boards->getZugFolge() + " " + hash->getZug());
				//str=hash->getZugFolge();
				hash->setFenString(conv->getBoardFen(hash->getBoard()));
				aktuell->setChild(hash, white);
				aktuell = aktuell->getChild(white);
				this->deepSearch(aktuell, move, tiefe, godepth, zug, wertzug, bestmove, ponder, whitesearch);
			}
			if(godepth == tiefe)
			{
				//std::cout << "info score cp " << hash->getBoard()->getFigurenwert() * 10 << " pv " + hash->getZugFolge() << " " << "\n";
				std::string str= aktuell->getZugFolge();
				TCHAR *param = new TCHAR[str.size() + 1];
				param[str.size()] = 0;
				//As much as we'd love to, we can't use memcpy() because
				//sizeof(TCHAR)==sizeof(char) may not be true:
				std::copy(str.begin(), str.end(), param);
				StringCchPrintf(msgBuf, BUF_SIZE, TEXT("info score cp %d pv %d.Zug %s\n"),
					aktuell->getBoard()->getFigurenwert() * 10,aktuell->getBoard()->getZugNr(), param);
				StringCchLength(msgBuf, BUF_SIZE, &cchStringSize);
				WriteConsole(hStdout, msgBuf, (DWORD)cchStringSize, &dwChars, NULL);
				if(*whitesearch)
				{
					if (*wertzug <= aktuell->getBoard()->getFigurenwert())
					{
						*wertzug = aktuell->getBoard()->getFigurenwert();
						*ponder = *bestmove;
						*bestmove = aktuell->getZugFolge().substr(0, 5);
					}
				}
				else
				{
					if (*wertzug >= aktuell->getBoard()->getFigurenwert())
					{
						*wertzug = aktuell->getBoard()->getFigurenwert();
						*ponder = *bestmove;
						*bestmove = aktuell->getZugFolge().substr(0, 5);
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
	if (boards->getChild(true) != NULL)
	{
		traversSearch(boards->getChild(true), move, tiefe, godepth, zug, wertzug, bestmove, ponder, whitesearch);
	}
	if (boards->getChild(false) != NULL)
	{
		traversSearch(boards->getChild(false), move, tiefe, godepth, zug, wertzug, bestmove, ponder, whitesearch);
		//if (boards->getChild(false) != NULL)
		//	traversSearch(boards->getChild(false), move, tiefe, godepth, zug, wertzug, bestmove, ponder, whitesearch);
	}
	if (boards->getChild(true) == NULL && boards->getChild(false) == NULL)
	{
		godepth = 2;
		tiefe = 0;
		this->deepSearch(boards, move, tiefe, godepth, zug, wertzug, bestmove, ponder, whitesearch);
	}
}
