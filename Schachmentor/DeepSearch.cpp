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
	bool white = searchtree->getBoard()->getWhitetoMove();
	Moving *movesperfig, *loschen;
	int moveindex = 0;
	int tiefe = 0;
	int godepth = 3;
	Convert *conv = new Convert();
	aktuell = searchtree;
	Calculus *calc = new Calculus();
	int *wertzug, wert = 1000;
	if (whitesearch)
		wert = -1000;
	std::string *bestmove, *ponder;
	std::string pond, best;
	bestmove = &best;
	ponder = &pond;
	wertzug = &wert;
	CooWorker *coop = new CooWorker();
	int thread = 0;
	bool proof = true;
	int werte[THREADCOUNT];
	int maxthread = 0;
	std::string bester[THREADCOUNT], pondi[THREADCOUNT];
	for (int i = 0; i < THREADCOUNT; i++)
	{
		werte[i] = 1000;
		if (*whitesearch)
			werte[i] = -1000;
		bester[i] = " ";
		pondi[i] = " ";
	}
	for (int i = 0; i < searchtree->getBoard()->getFigurmax(white); i++)
	{
		movesperfig = moves->getMovesperFigure(searchtree->getBoard(), searchtree->getBoard()->getFigur(i, white));
		while (movesperfig->getnext() != NULL)
		{
			loschen = movesperfig;
			movesperfig = movesperfig->getnext();
			Hashbrett *hash = new Hashbrett();
			hash->setBoard(moves->copyBoard(searchtree->getBoard()));
			hash->getBoard()->setFigurenwert(searchtree->getBoard()->getFigurenwert() + movesperfig->getW());
			moves->makeMove(hash->getBoard()->getFigur(i, white), movesperfig->getX(), movesperfig->getY(), ' ', hash);
			hash->setZugFolge(searchtree->getZugFolge() + " " + hash->getZug());
			hash->setFenString(conv->getBoardFen(hash->getBoard()));
			aktuell->setChild(hash, white);
			//std::cout << hash->getZug() << " ";
			aktuell = aktuell->getChild(white);
			/// Threads starten
			//calc->deepSearch(aktuell, moves, tiefe, godepth, hash->getZug(), wertzug, bestmove, ponder, whitesearch);
			coop->startupCalc(false, thread, aktuell, moves, tiefe, godepth, hash->getZug(), &werte[thread], &bester[thread], &pondi[thread], whitesearch);
			thread++;
			maxthread++;
			if (thread > THREADCOUNT)
			{
				std::cout <<"#########################" << maxthread << "\n";
				coop->waitdownCalc();
				maxthread = 0;
				thread = 0;
				for (int i = 0; i < THREADCOUNT; i++)
				{
					if (*whitesearch)
					{
						if (wert < werte[i])
						{
							//std::cout << bester[i] << "\n";
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
			}
			///// threads ende
			delete loschen;
			moveindex++;
		}

		delete movesperfig;
	}
	coop->shutdownCalc(maxthread);
	for (int i = 0; i < maxthread; i++)
	{
		if (*whitesearch)
		{
			if (wert < werte[i])
			{
				*bestmove = bester[i];
				*ponder = pond;
				wert = werte[i];
			}
		}
		else
		{
			if (wert > werte[i])
			{
				*bestmove = bester[i];
				*ponder = *bestmove;
				wert = werte[i];
			}
		}
		werte[i] = 1000;
		if (*whitesearch)
			werte[i] = -1000;
		bester[i] = " ";
		pondi[i] = " ";
	}
	std::cout << "bestmove " << *bestmove << " ponder " << *ponder << " " << wert;
	//return 0;
}

void DeepSearch::searchMoveToTree(Hashbrett *searchtree, bool *quit, bool *end, bool *endatDepth, bool *whitesearch)
{
	Hashbrett *aktuell,*links,*getrennnt[THREADCOUNT],*links2;
	aktuell = searchtree;
	int maxthread = 0;
	CooWorker *coop = new CooWorker();
	int thread = 0;
	int tiefe = 0;
	int godepth = 0;
	int werte[THREADCOUNT];
	std::string *bestmove, *ponder;
	std::string bester[THREADCOUNT], pondi[THREADCOUNT];
	std::string pond, best;
	bestmove = &best;
	ponder = &pond;
	int *wertzug, wert = 1000;
	wertzug = &wert;
	if (*whitesearch)
		wert = -1000;
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
		aktuell = searchtree->getChild(*whitesearch);//richtiger knoten
		std::cout << aktuell->getZug() +"Mom";
		if (aktuell->getChild(!*whitesearch))
		{
			links=aktuell->getChild(!*whitesearch);
			if (links->getChild(*whitesearch))
			{
				links = links->getChild(*whitesearch);
			}
		}
	}
	if (links)
	{
		while (links->getChild(*whitesearch))
		{
			links->setZugFolge(links->getZugFolge().substr(5, links->getZugFolge().length()));
			std::cout << "l:" + links->getZugFolge() + " ";
			getrennnt[thread] = links;
			links2 = links->getChild(*whitesearch);
			getrennnt[thread]->setChild(NULL, *whitesearch);
				coop->startupCalc(true, thread, links, moves, tiefe, godepth, links->getZug(), &werte[thread], &bester[thread], &pondi[thread], whitesearch);
				thread++;
				maxthread++;
				if (thread >= THREADCOUNT)
				{
					coop->waitdownCalc();
					maxthread = 0;
					thread = 0;
					for (int i = 0; i < THREADCOUNT; i++)
					{
						if(i<THREADCOUNT+1)
							getrennnt[thread]->setChild(getrennnt[thread+1], *whitesearch);
						if(i==THREADCOUNT)
							getrennnt[thread]->setChild(links2, *whitesearch);
						std::cout << wert << " " << werte[i] << bester[i]+ "\n";
						if (*whitesearch)
						{
							if (wert < werte[i])
							{
								std::cout << bester[i] << "\n";
								*ponder = *bestmove;
								*bestmove = bester[i];
								wert = werte[i];
							}
						}
						else
						{
							if (wert > werte[i])
							{
								std::cout << bester[i] << "\n";
								*ponder = *bestmove;
								*bestmove = bester[i];
								wert = werte[i];
							}
						}

						bester[i] = " ";
						pondi[i] = " ";
					}
				}
				///// threads ende
				links = links2;
		}
		std::cout << "l:" + links->getZug() + " ";
		coop->startupCalc(true, thread, links, moves, tiefe, godepth, searchtree->getZug(), &werte[thread], &bester[thread], &pondi[thread], whitesearch);
		thread++;
		maxthread++;
		coop->shutdownCalc(maxthread);
		for (int i = 0; i < maxthread; i++)
		{
			if (i<maxthread + 1)
				getrennnt[thread]->setChild(getrennnt[thread + 1], *whitesearch);
			//if (i == THREADCOUNT)
			//	getrennnt[thread]->setChild(links2, *whitesearch);
			std::cout << wert << " " << werte[i] << bester[i] + "\n";
			if (*whitesearch)
			{
				if (wert < werte[i])
				{
					*bestmove = bester[i];
					*ponder = pond;
					wert = werte[i];
				}
			}
			else
			{
				if (wert > werte[i])
				{
					*bestmove = bester[i];
					*ponder = *bestmove;
					wert = werte[i];
				}
			}
		}
		std::cout << "bestmove " << *bestmove << " ponder " << *ponder << " " << wert;
	}

}