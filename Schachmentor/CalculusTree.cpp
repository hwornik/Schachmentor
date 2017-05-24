#include "stdafx.h"
#include "CalculusTree.h"


CalculusTree::CalculusTree()
{
	coop = new CooWorker();
}


CalculusTree::~CalculusTree()
{
}

void CalculusTree::traversSearch(Hashbrett * boards, Movemennt * move, int tiefe, int godepth, std::string zug, int *wertzug, std::string *bestmove, std::string *ponder, bool *whitesearch)
{
	godepth = 2;
	if (boards->getChild(true) != NULL)
		traversSearch(boards->getChild(true), move, tiefe, godepth, zug, wertzug, bestmove, ponder, whitesearch);
	if (boards->getChild(false) != NULL)
		traversSearch(boards->getChild(false), move, tiefe, godepth, zug, wertzug, bestmove, ponder, whitesearch);
	if (boards->getChild(boards->getBoard()->getWhitetoMove()) == NULL)
	{
		for (int i = 0; i < THREADCOUNT; i++)
		{
			werte[i] = 1000;
			if (whitesearch)
				werte[i] = -1000;
			bester[i] = " ";
			pondi[i] = " ";
		}
		static int thread = 0;
		tiefe = 0;
		boards->setZugFolge(boards->getZugFolge().substr(5, boards->getZugFolge().length()));
		//this->deepSearch(boards, move, tiefe, godepth, zug, wertzug, bestmove, ponder, whitesearch);
		this->coop->startupCalc(thread, boards, move, tiefe, godepth, boards->getZug(), &werte[thread], &bester[thread], &pondi[thread], whitesearch);
		thread++;
		maxthread++;
		if (thread >= THREADCOUNT)
		{
			coop->waitdownCalc();
			maxthread = 0;
			static int thread = 0;
			for (int i = 0; i < THREADCOUNT; i++)
			{
				if (*whitesearch)
				{
					if (*wertzug < werte[i])
					{
						std::cout << bester[i] << "\n";
						*bestmove = bester[i];
						*ponder = *bestmove;
						*wertzug = werte[i];
					}
				}
				else
				{
					if (*wertzug > werte[i])
					{
						*bestmove = bester[i];
						*ponder = *bestmove;
						*wertzug = werte[i];
					}
				}
				werte[i] = 1000;
				if (whitesearch)
					werte[i] = -1000;
				bester[i] = " ";
				pondi[i] = " ";
			}
		}
	}
}
