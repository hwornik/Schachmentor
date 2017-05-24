#include "stdafx.h"
#include "Worker.h"

Worker::Worker()
{
}


Worker::~Worker()
{
}

void Worker::ErrorHandler(LPTSTR lpszFunction)
{
	HANDLE hStdout;
	// Retrieve the system error message for the last-error code.

	LPVOID lpMsgBuf;
	LPVOID lpDisplayBuf;
	DWORD dw = GetLastError();

	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM |
		FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,
		dw,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf,
		0, NULL);

	// Display the error message.

	lpDisplayBuf = (LPVOID)LocalAlloc(LMEM_ZEROINIT,
		(lstrlen((LPCTSTR)lpMsgBuf) + lstrlen((LPCTSTR)lpszFunction) + 40) * sizeof(TCHAR));
	StringCchPrintf((LPTSTR)lpDisplayBuf,
		LocalSize(lpDisplayBuf) / sizeof(TCHAR),
		TEXT("%s failed with error %d: %s"),
		lpszFunction, dw, lpMsgBuf);
	MessageBox(NULL, (LPCTSTR)lpDisplayBuf, TEXT("Error"), MB_OK);

	// Free error-handling buffer allocations.

	LocalFree(lpMsgBuf);
	LocalFree(lpDisplayBuf);
}

int Worker::startupDelete(Hashbrett *deleteone, Hashbrett *deletetwo)
{
	// Allocate memory for thread data.
	//*hasharray = new Brett[hashsize];
	pDData = (PMYDDATA)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY,
		sizeof(MYDDATA));

	if (pDData == NULL)
	{
		// If the array allocation fails, the system is out of memory
		// so there is no point in trying to print an error message.
		// Just terminate execution.
		ExitProcess(2);
	}
	pDData->deleteone = deleteone;
	pDData->deletetwo = deletetwo;

	// Generate unique data for each thread to work with.
	// Create the thread to begin execution on its own.

	hThreadD = CreateThread(
		NULL,                   // default security attributes
		0,                      // use default stack size  
		DeleteHashbrett,         // thread function name
		pDData,          // argument to thread function 
		0,                      // use default creation flags 
		&dwThreadIdD);   // returns the thread identifier 


						 // Check the return value for success.
						 // If CreateThread fails, terminate execution. 
						 // This will automatically clean up threads and memory. 

	if (hThreadD == NULL)
	{
		ErrorHandler(TEXT("CreateThread"));
		ExitProcess(3);
	}


	return 0;
}

int Worker::startupSearchTree(Hashbrett *searchtree, bool *quit, bool *end, bool *endatDepth, bool *whitesearch)
{
	// Allocate memory for thread data.
	//*hasharray = new Brett[hashsize];
	pSData = (PMYSDATA)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY,
		sizeof(MYSDATA));

	if (pSData == NULL)
	{
		// If the array allocation fails, the system is out of memory
		// so there is no point in trying to print an error message.
		// Just terminate execution.
		ExitProcess(2);
	}
	pSData->searchtree = searchtree;
	pSData->quitsearch = quit;
	pSData->stopsearch = end;
	pSData->endatDepthakt = endatDepth;
	pSData->whitesearch = whitesearch;
	// Generate unique data for each thread to work with.
	// Create the thread to begin execution on its own.

	hThreadS = CreateThread(
		NULL,                   // default security attributes
		0,                      // use default stack size  
		searchMoveTree,         // thread function name
		pSData,          // argument to thread function 
		0,                      // use default creation flags 
		&dwThreadIdS);   // returns the thread identifier 


						 // Check the return value for success.
						 // If CreateThread fails, terminate execution. 
						 // This will automatically clean up threads and memory. 

	if (hThreadS == NULL)
	{
		ErrorHandler(TEXT("CreateThread"));
		ExitProcess(3);
	}


	return 0;
}

DWORD WINAPI Worker::DeleteHashbrett(LPVOID lpParam)
{
	HANDLE hStdoutD;
	PMYDDATA pDData;

	TCHAR msgBuf[BUF_SIZE];
	size_t cchStringSize;
	DWORD dwChars;

	// Make sure there is a console to receive output results. 

	hStdoutD = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hStdoutD == INVALID_HANDLE_VALUE)
		return 1;

	// Cast the parameter to the correct data type.
	// The pointer is known to be valid because 
	// it was checked for NULL before the thread was created.
	DeleteHash *delhash = new DeleteHash();
	pDData = (PMYDDATA)lpParam;
	// Print thread ende
	if (pDData->deleteone != NULL)
	{
		delhash->delHash(pDData->deleteone);
	}
	if (pDData->deletetwo != NULL)
	{
		delhash->delHash(pDData->deletetwo);
	}
	return 0;
}

DWORD WINAPI Worker::searchMoveTree(LPVOID lpParam)
{
	HANDLE hStdoutS;
	PMYSDATA pSData;

	TCHAR msgBuf[BUF_SIZE];
	size_t cchStringSize;
	DWORD dwChars;

	// Make sure there is a console to receive output results. 

	hStdoutS = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hStdoutS == INVALID_HANDLE_VALUE)
		return 1;

	// Cast the parameter to the correct data type.
	// The pointer is known to be valid because 
	// it was checked for NULL before the thread was created.
	pSData = (PMYSDATA)lpParam;
	// Begin Work
	Calculus *calc = new Calculus();
	Movemennt *move = new Movemennt();
	int white = pSData->searchtree->getBoard()->getWhitetoMove();
	//std::cout << "#Thread start#";
	int *wertzug,wert=1000;
	if (*pSData->whitesearch)
		wert = -1000;
	std::string *bestmove, *ponder;
	std::string best, pond;
	bestmove = &best;
	ponder = &pond;
	wertzug = &wert;
	
	//while (pSData->searchtree->getChild(white) != NULL)
	{
		calc->traversSearch(pSData->searchtree->getChild(white), move, 0, 0, "",wertzug, bestmove, ponder, pSData->whitesearch);
	}
	// Print thread ende *move
	//std::cout << "#Thread ende#";
	std::cout << "bestmove " << *bestmove << " ponder " << *ponder << " " << wert;
	return 0;
}

int Worker::startupSearch(Hashbrett *searchtree, bool *quit, bool *end, bool *endatDepth, bool *whitesearch)
{
	// Allocate memory for thread data.
	//*hasharray = new Brett[hashsize];
	pSData = (PMYSDATA)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY,
		sizeof(MYSDATA));

	if (pSData == NULL)
	{
		// If the array allocation fails, the system is out of memory
		// so there is no point in trying to print an error message.
		// Just terminate execution.
		ExitProcess(2);
	}
	pSData->searchtree = searchtree;
	pSData->quitsearch = quit;
	pSData->stopsearch = end;
	pSData->endatDepthakt = endatDepth;
	pSData->whitesearch = whitesearch;
	// Generate unique data for each thread to work with.
	// Create the thread to begin execution on its own.

	hThreadS = CreateThread(
		NULL,                   // default security attributes
		0,                      // use default stack size  
		searchMove,         // thread function name
		pSData,          // argument to thread function 
		0,                      // use default creation flags 
		&dwThreadIdS);   // returns the thread identifier 


						 // Check the return value for success.
						 // If CreateThread fails, terminate execution. 
						 // This will automatically clean up threads and memory. 

	if (hThreadS == NULL)
	{
		ErrorHandler(TEXT("CreateThread"));
		ExitProcess(3);
	}


	return 0;
}

DWORD WINAPI Worker::searchMove(LPVOID lpParam)
{
	HANDLE hStdoutS;
	PMYSDATA pSData;

	TCHAR msgBuf[BUF_SIZE];
	size_t cchStringSize;
	DWORD dwChars;

	pSData = (PMYSDATA)lpParam;
	// Make sure there is a console to receive output results. 

	hStdoutS = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hStdoutS == INVALID_HANDLE_VALUE)
		return 1;
	Movemennt *moves = new Movemennt();
	Hashbrett * aktuell;
	bool white=pSData->searchtree->getBoard()->getWhitetoMove();
	Moving *movesperfig,*loschen;
	int moveindex = 0;
	int tiefe = 0;
	int godepth = 3;
	Convert *conv = new Convert();
	aktuell = pSData->searchtree;
	Calculus *calc = new Calculus();
	int *wertzug , wert=1000;
	if (*pSData->whitesearch)
		wert = -1000;
	std::string *bestmove, *ponder;
	std::string pond,best;
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
		if (*pSData->whitesearch)
			werte[i] = -1000;
		bester[i] = " ";
		pondi[i] = " ";
	}
	for (int i = 0; i < pSData->searchtree->getBoard()->getFigurmax(white); i++)
	{
		movesperfig=moves->getMovesperFigure(pSData->searchtree->getBoard(), pSData->searchtree->getBoard()->getFigur(i, white));
		while (movesperfig->getnext() != NULL)
		{
			loschen = movesperfig;
			movesperfig = movesperfig->getnext();
			Hashbrett *hash = new Hashbrett();
			hash->setBoard(moves->copyBoard(pSData->searchtree->getBoard()));
			hash->getBoard()->setFigurenwert(pSData->searchtree->getBoard()->getFigurenwert() + movesperfig->getW());
			hash->setChild(NULL, true);
			hash->setChild(NULL, false);
			moves->makeMove(hash->getBoard()->getFigur(i, white), movesperfig->getX(), movesperfig->getY(), ' ', hash);
		
				hash->setZugFolge(hash->getZug());
				hash->setFenString(conv->getBoardFen(hash->getBoard()));
				aktuell->setChild(hash, white);
				//std::cout << hash->getZug() << " ";
				aktuell = aktuell->getChild(white);
				/// Threads starten
				//calc->deepSearch(aktuell, moves, tiefe, godepth, hash->getZug(), wertzug, bestmove, ponder, pSData->whitesearch);
				coop->startupCalc(thread, aktuell, moves, tiefe, godepth, hash->getZug(), &werte[thread], &bester[thread], &pondi[thread], pSData->whitesearch);
				thread++;
				maxthread++;
				if (thread >= THREADCOUNT)
				{
					coop->waitdownCalc();
					maxthread = 0;
					for (int i = 0; i < THREADCOUNT; i++)
					{
						if (*pSData->whitesearch)
						{
							if (wert < werte[i])
							{
								std::cout << bester[i] << "\n";
								*bestmove = bester[i];
								*ponder = *bestmove;
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
						if (*pSData->whitesearch)
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
	for (int i = 0; i < maxthread; i++)
	{
		if (*pSData->whitesearch)
		{
			if (wert < werte[i])
			{
				*bestmove = bester[i];
				*ponder = *bestmove;
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
		if (*pSData->whitesearch)
			werte[i] = -1000;
		bester[i] = " ";
		pondi[i] = " ";
	}

	coop->shutdownCalc(maxthread);
	std::cout << "bestmove " << *bestmove << " ponder " << *ponder << " " << wert;
	return 0;
}