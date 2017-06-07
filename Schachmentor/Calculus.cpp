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
	Moving *movesperfig, *loschen;
	int moveindex = 0;	
	aktuell = boards;
	std::string str;
	Convert *conv = new Convert();
	Brett *board = new Brett();
	conv->setBoardwithFEN(board, aktuell->getFenString());
	bool white = board->getWhitetoMove();
	boards->setWhitetoMove(board->getWhitetoMove());
	for (int i = 0; i < board->getFigurmax(white); i++)
	{
		movesperfig = move->getMovesperFigure(board, board->getFigur(i, white));
		while (movesperfig->getnext() != NULL)
		{
			loschen = movesperfig;
			movesperfig = movesperfig->getnext();
			loschen->setNext(NULL);
			delete loschen;
			Hashbrett *hash = new Hashbrett();
			Brett* boardmove=move->copyBoard(board);
			hash->setFigurenwert(boards->getFigurenwert() + movesperfig->getW());
			move->makeMove(boardmove->getFigur(i, white), movesperfig->getX(), movesperfig->getY(), ' ', hash,boardmove,false);
			hash->setZugFolge(boards->getZugFolge() + " " + hash->getZug());
			//str=hash->getZugFolge();
			hash->setFenString(conv->getBoardFen(boardmove));
			delete boardmove;
			aktuell->setChild(hash, white);
			aktuell = aktuell->getChild(white);
			if (godepth > tiefe)
			{
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
				StringCchPrintf(msgBuf, BUF_SIZE, TEXT("info score cp %d pv %s %d\n"),
					aktuell->getFigurenwert() * 10, param,tiefe);
				StringCchLength(msgBuf, BUF_SIZE, &cchStringSize);
				WriteConsole(hStdout, msgBuf, (DWORD)cchStringSize, &dwChars, NULL);
				*wertzug = (*wertzug+(aktuell->getFigurenwert()*100))/2;
				/*if(*whitesearch)
				{
					if (*wertzug <= aktuell->getFigurenwert())
					{
						*wertzug = aktuell->getFigurenwert();
						*ponder = *bestmove;
						*bestmove = aktuell->getZugFolge().substr(0, 5);
					}
				}
				else
				{
					if (*wertzug >= aktuell->getFigurenwert())
					{
						*wertzug = aktuell->getFigurenwert();
						*ponder = *bestmove;
						*bestmove = aktuell->getZugFolge().substr(0, 5);
					}
				}*/
			}
			moveindex++;
			//tiefe--;
		}
		delete movesperfig;
		//std::cout << "---------------------------------------------------------\n";
	}
	delete board;
	//std::cout << moveindex << " Zuge gefunden Depth\n";
}

void Calculus::traversSearch(Hashbrett * boards, Movemennt * move, int tiefe, int godepth, std::string zug, int *wertzug, std::string *bestmove, std::string *ponder, bool *whitesearch)
{
	if (boards->getChild(true)!=NULL)
	{
		traversSearch(boards->getChild(true), move, tiefe, godepth, zug, wertzug, bestmove, ponder, whitesearch);
	}
	if (boards->getChild(false) != NULL)
	{
		traversSearch(boards->getChild(false), move, tiefe, godepth, zug, wertzug, bestmove, ponder, whitesearch);
		//if (boards->getChild(false) != NULL)
		//	traversSearch(boards->getChild(false), move, tiefe, godepth, zug, wertzug, bestmove, ponder, whitesearch);
	}
	//std::cout << boards->getZug() << " ";
	if (boards->getChild(boards->getWhitetoMove()) == NULL)
	{
		godepth = 1;
		tiefe = 0;
		boards->setZugFolge(boards->getZugFolge().substr(5, boards->getZugFolge().length()));
		this->deepSearch(boards, move, tiefe, godepth, zug, wertzug, bestmove, ponder, whitesearch);
	}
}

void Calculus::deepSearchT(Hashbrett * boards, Movemennt * move, int tiefe, int godepth, std::string zug, int *wertzug, std::string *bestmove, std::string *ponder, bool *whitesearch)
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
	Moving *movesperfig, *loschen;
	int moveindex = 0;
	aktuell = boards;
	std::string str;
	Convert *conv = new Convert();
	Brett *board = new Brett();
	conv->setBoardwithFEN(board, aktuell->getFenString());
	bool white = board->getWhitetoMove();
	boards->setWhitetoMove(board->getWhitetoMove());
	for (int i = 0; i < board->getFigurmax(white); i++)
	{
		movesperfig = move->getMovesperFigure(board, board->getFigur(i, white));
		while (movesperfig->getnext() != NULL)
		{
			loschen = movesperfig;
			movesperfig = movesperfig->getnext();
			loschen->setNext(NULL);
			delete loschen;
			Hashbrett *hash = new Hashbrett();
			Brett *boardmove=move->copyBoard(board);
			hash->setFigurenwert(boards->getFigurenwert() + movesperfig->getW());
			move->makeMove(boardmove->getFigur(i, white), movesperfig->getX(), movesperfig->getY(), ' ', hash,boardmove,false);
			hash->setZugFolge(boards->getZugFolge() + " " + hash->getZugFolge());
			hash->setZug(zug);
			//str=hash->getZugFolge();
			hash->setFenString(conv->getBoardFen(boardmove));
			delete boardmove;
			aktuell->setChild(hash, white);
			aktuell = aktuell->getChild(white);

				//std::cout << "info score cp " << hash->getBoard()->getFigurenwert() * 10 << " pv " + hash->getZugFolge() << " " << "\n";
				std::string str = aktuell->getZugFolge();
				TCHAR *param = new TCHAR[str.size() + 1];
				param[str.size()] = 0;
				//As much as we'd love to, we can't use memcpy() because
				//sizeof(TCHAR)==sizeof(char) may not be true:
				std::copy(str.begin(), str.end(), param);
				StringCchPrintf(msgBuf, BUF_SIZE, TEXT("info score cp %d pv %d.Zug %s %d\n"),
					aktuell->getFigurenwert() * 10, 2, param, tiefe);
				StringCchLength(msgBuf, BUF_SIZE, &cchStringSize);
				WriteConsole(hStdout, msgBuf, (DWORD)cchStringSize, &dwChars, NULL);
				*wertzug += aktuell->getFigurenwert();
				/*if (*whitesearch)
				{
					if (*wertzug <= aktuell->getFigurenwert())
					{
						*wertzug = aktuell->getFigurenwert();
						*ponder = *bestmove;
						*bestmove = aktuell->getZug();
					}
				}
				else
				{
					if (*wertzug >= aktuell->getFigurenwert())
					{
						*wertzug = aktuell->getFigurenwert();
						*ponder = *bestmove;
						*bestmove = aktuell->getZug();
					}
				}*/
			
			moveindex++;
			//tiefe--;
		}
		delete movesperfig;
		//std::cout << "---------------------------------------------------------\n";
	}
	delete board;
	//std::cout << moveindex << " Zuge gefunden Depth\n";
}
