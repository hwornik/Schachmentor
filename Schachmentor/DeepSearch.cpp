#include "stdafx.h"
#include "DeepSearch.h"


DeepSearch::DeepSearch()
{
}


DeepSearch::~DeepSearch()
{
}

void DeepSearch::searchMove(Hashbrett *searchtree, bool *quit, bool *end, bool *endatDepth, bool *whitesearch)
{
	Movemennt *moves = new Movemennt();
	Hashbrett * aktuell;
	Hashbrett *hash[THREADCOUNT];
	Moving *movesperfig, *loschen;
	int moveindex = 0;
	int tiefe = 0;
	int godepth = 3;
	Convert *conv = new Convert();
	aktuell=searchtree;
	Calculus *calc = new Calculus();
	int *wertzug, wert = 1000;
	if (whitesearch)
		wert = -1000;
	std::string *bestmove, *ponder;
	std::string pond, best, aktzug[THREADCOUNT];
	bestmove = &best;
	ponder = &pond;
	wertzug = &wert;
	CooWorker *coop = new CooWorker();
	int thread = 0;
	bool proof = true;
	int werte[THREADCOUNT];
	int maxthread = 0;
	std::string bester[THREADCOUNT], bestzug[THREADCOUNT], pondi[THREADCOUNT];
	for (int i = 0; i < THREADCOUNT; i++)
	{
		werte[i] = 1000;
		if (*whitesearch)
			werte[i] = -1000;
		bester[i] = " ";
		pondi[i] = " ";
	}
	Brett *board = new Brett();
	conv->setBoardwithFEN(board, aktuell->getFenString());
	bool white = board->getWhitetoMove();
	searchtree->setWhitetoMove(board->getWhitetoMove());
	for (int i = 0; i < board->getFigurmax(white); i++)
	{
		movesperfig = moves->getMovesperFigure(board, board->getFigur(i, white));
		while (movesperfig->getnext() != NULL)
		{
			loschen = movesperfig;
			movesperfig = movesperfig->getnext();
			hash[thread] = new Hashbrett();
			hash[thread]->setFigurenwert(searchtree->getFigurenwert() + movesperfig->getW());
			Brett *boardmove = new Brett();
			boardmove = moves->copyBoard(board);
			moves->makeMove(boardmove->getFigur(i, white), movesperfig->getX(), movesperfig->getY(), ' ', hash[thread], boardmove,false);
			//Schwarz am zug
			hash[thread]->setZugFolge(searchtree->getZugFolge() + " " + hash[thread]->getZug());
			bestzug[thread] = hash[thread]->getZug();
			hash[thread]->setFenString(conv->getBoardFen(boardmove));
			delete boardmove;
			aktzug[thread]=hash[thread]->getZug();
			aktuell->setChild(hash[thread], white);
			//std::cout << hash->getZug() << " ";
			aktuell = aktuell->getChild(white);
			thread++;
			maxthread++;
			if (thread >= THREADCOUNT)
			{
				std::cout << "round 1" << maxthread;
				coop->startupCalc(false, maxthread, hash, moves, tiefe, godepth, aktzug, werte, bester, pondi, whitesearch);
				maxthread = 0;
				thread = 0;
				for (int i = 0; i < THREADCOUNT; i++)
				{
					//delete hash[i];
					std::cout << bester[i] << "\n";
					if (*whitesearch)
					{
						if (wert < werte[i])
						{
							*ponder = *bestmove;
							*bestmove = bestzug[i];
							wert = werte[i];
						}
					}
					else
					{
						if (wert > werte[i])
						{
							*ponder = *bestmove;
							*bestmove = bestzug[i];
							wert = werte[i];
						}
					}
					werte[i] = 1000;
					if (*whitesearch)
						werte[i] = -1000;
					bester[i] = " ";
					pondi[i] = " ";
				}
			}
			///// threads ende
			delete loschen;
			moveindex++;
		}

		delete movesperfig;
	}
	coop->startupCalc(false, maxthread, hash, moves, tiefe, godepth, aktzug, werte, bester, pondi, whitesearch);
	for (int i = 0; i < maxthread; i++)
	{
		std::cout << werte[i] << " " << aktzug[i] << "\n";
		if (*whitesearch)
		{
			//delete hash[i];
			if (wert < werte[i])
			{
				*ponder = *bestmove;
				*bestmove = bestzug[i];
				wert = werte[i];
			}
		}
		else
		{
			if (wert > werte[i])
			{
				*ponder = *bestmove;
				*bestmove = bestzug[i];
				wert = werte[i];
			}
		}
		werte[i] = 1000;
		if (*whitesearch)
			werte[i] = -1000;
		bester[i] = " ";
		pondi[i] = " ";
	}
	delete board;
	std::cout << "bestmove " << *bestmove << " ponder " << *ponder << " " << wert;
	//return 0;
}

void DeepSearch::searchMoveToTree(Hashbrett *searchtree, bool *quit, bool *end, bool *endatDepth, bool *whitesearch)
{
	Hashbrett *aktuell,*links[THREADCOUNT],*links2;
	aktuell = searchtree;
	int maxthread = 0;
	CooWorker *coop = new CooWorker();
	int thread = 0;
	int tiefe = 0;
	int godepth = 0;
	int werte[THREADCOUNT];
	std::string *bestmove, *ponder;
	std::string bester[THREADCOUNT], pondi[THREADCOUNT], aktzug[THREADCOUNT], bestzug[THREADCOUNT];
	Calculus *calc=new Calculus();
	std::string pond, best;
	bestmove = &best;
	ponder = &pond;
	int *wertzug, wert = 1000;
	if (*whitesearch)
		wert = -1000;
	wertzug = &wert;
	for (int i = 0; i < THREADCOUNT; i++)
	{
		werte[i] = 1000;
		if (*whitesearch)
			werte[i] = -1000;
		bester[i] = " ";
		pondi[i] = " ";
	}
	Movemennt *moves = new Movemennt();
	if (searchtree->getChild(*whitesearch))
	{
		links[0] = searchtree->getChild(*whitesearch);//richtiger knoten
		links[0] = links[0]->getChild(*whitesearch);
			while (links[thread])
			{
				//links->setZugFolge(links->getZug());
				//std::cout << "l:";// +links[thread]->getZugFolge() + " "
				links[thread + 1] = links[thread]->getChild(*whitesearch);
				links[thread]->setChild(NULL, *whitesearch);
				aktzug[thread] = links[thread]->getZug();
				//coop->startupCalc(aThread[thread],true, thread, links[thread], moves, tiefe, godepth, links[thread]->getZug(), &werte[thread], &bester[thread], &pondi[thread], whitesearch);
				thread++;
				maxthread++;
				/*if (thread >= THREADCOUNT)
				{
					//searchtree->setChild(links[1], *whitesearch);
					//coop->waitdownCalc(*aThread);
					coop->startupCalc(true, maxthread, links, moves, tiefe, godepth, aktzug, werte, bester, pondi, whitesearch);
					maxthread = 0;
					thread = 0;
					for (int i = 0; i < THREADCOUNT; i++)
					{

						if (i < THREADCOUNT-1)
							links[i]->setChild(links[i + 1], *whitesearch);
						std::cout << wert << " " << werte[i] << bester[i] + "\n";
						if (*whitesearch)
						{
							if (wert < werte[i])
							{
								*ponder = *bestmove;
								*bestmove = bester[i];
								wert = werte[i];
							}
						}
						else
						{
							if (wert > werte[i])
							{
								*ponder = *bestmove;
								*bestmove = bester[i];
								wert = werte[i];
							}
						}
						werte[i] = 1000;
						if (*whitesearch)
							werte[i] = -1000;
						bester[i] = " ";
						pondi[i] = " ";

					}
						//std::cout << "xx:" + links[THREADCOUNT]->getZug() + "
						links[0] = links[THREADCOUNT];
				}
				///// threads ende*/
			}
			//std::cout << "l:" + maxthread << " ";
			if (maxthread > 0)
			{
				//WaitForMultipleObjects(maxthread, *aThread, TRUE, INFINITE);
				coop->startupCalc(true, maxthread, links, moves, tiefe, godepth, aktzug, werte, bester, pondi, whitesearch);

				// Close thread and semaphore handles
				if (maxthread > THREADCOUNT)
					maxthread = THREADCOUNT;
				//for (int i = 0; i < maxthread; i++)
					//CloseHandle(aThread[i]);
				for (int i = 0; i < maxthread; i++)
				{
					if (i < maxthread - 1)
						links[i]->setChild(links[i + 1], *whitesearch);
					//if (i == THREADCOUNT)
					//	getrennnt[thread]->setChild(links2, *whitesearch);
					std::cout << wert << " c " << werte[i] << aktzug[i] + "\n";
					if (*whitesearch)
					{
						if (wert < werte[i])
						{

							*ponder = *bestmove;
							*bestmove = aktzug[i];
							wert = werte[i];
						}
					}
					else
					{
						if (wert > werte[i])
						{
							*ponder = *bestmove;
							*bestmove = aktzug[i];
							wert = werte[i];
						}
					}
				}
			}
			std::cout << "bestmove " << *bestmove << " ponder " << *ponder << " " << wert;
		}
}