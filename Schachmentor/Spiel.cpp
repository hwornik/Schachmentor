#include "stdafx.h"
#include "Spiel.h"

Spiel::Spiel()
{
	beenden = false;
	indexmoves = 0;
	moves = new char*[32];
	hashsize = 512;
	stop = false;
}


Spiel::~Spiel()
{
}

int Spiel::startup()
{
	hasharray = new Hashbrett*[hashsize];
		// Allocate memory for thread data.
		//*hasharray = new Brett[hashsize];
		pData = (PMYDATA)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY,
			sizeof(MYDATA));

		if (pData == NULL)
		{
			// If the array allocation fails, the system is out of memory
			// so there is no point in trying to print an error message.
			// Just terminate execution.
			ExitProcess(2);
		}
		eingabe = -1;
		ready = true;
		// Generate unique data for each thread to work with.
		int i = 1;
		pData->quit = &beenden;
		pData->input = &eingabe;
		pData->ready = &ready;
		pData->fenstring = &fen;
		pData->movestodo = moves;
		pData->movemade = &move;
		pData->gamehash = new Hashbrett();
		Brett *board = new Brett();
		Convert *conv = new Convert();
		conv->setBoardwithFEN(board, STARTFEN);
		pData->gamehash->setBoard(board);
		delete conv;
		// Create the thread to begin execution on its own.

		hThread = CreateThread(
			NULL,                   // default security attributes
			0,                      // use default stack size  
			CentralControl,         // thread function name
			pData,          // argument to thread function 
			0,                      // use default creation flags 
			&dwThreadId);   // returns the thread identifier 


									// Check the return value for success.
									// If CreateThread fails, terminate execution. 
									// This will automatically clean up threads and memory. 

		if (hThread == NULL)
		{
			ErrorHandler(TEXT("CreateThread"));
			ExitProcess(3);
		}
	

	return 0;
}

int Spiel::shutdown()
{
	// close the while schleife im Thread
	this->beenden = true;

	// Wait until all threads have terminated.
	WaitForSingleObject( hThread, TRUE);

	// Close all thread handles and free memory allocations.
	CloseHandle(hThread);
	if (pData != NULL)
	{
		HeapFree(GetProcessHeap(), 0, pData);
		pData = NULL;    // Ensure address is not reused.
	}
	return 0;
}

void Spiel::setHashsize(int hash)
{
	this->hashsize = hash;
}

void Spiel::setBoardwithFen(std::string fen)
{
}


void Spiel::searchMoves(char *smove)
{
	moves[indexmoves] = smove;
	indexmoves++;
}

bool Spiel::startAction(int action)
{
	while (!ready)
		Sleep(100);
	this->eingabe = action;
	return false;
}

bool Spiel::setFenString(std::string fen)
{
	this->fen = fen;
	return false;
}

bool Spiel::setMoveMadebyGUI(std::string move)
{
	this->move = move;
	return false;
}

bool Spiel::getPonder()
{
	return this->ponder;
}

void Spiel::setWTime(int wtime)
{
	this->wtime = wtime;
}

void Spiel::setBTime(int btime)
{
	this->btime = btime;
}

void Spiel::setWinc(int winc)
{
	this->winc = winc;
}

void Spiel::setBinc(int binc)
{
	this->binc = binc;
}

void Spiel::setMovestogo(int movestogo)
{
	this->movestogo = movestogo;
}

void Spiel::setDepth(int depth)
{
	this->depth = depth;
}

void Spiel::setNodes(int nodes)
{
	this->nodes = nodes;
}

void Spiel::setMate(int mate)
{
	this->mate = mate;
}

void Spiel::setMovetime(int movetime)
{
	this->movetime = movetime;
}

void Spiel::setGoinfinite(bool infinite)
{
	this->infinite = infinite;
}

int Spiel::getWTime()
{
	return this->wtime;
}

int Spiel::getBTime()
{
	return this->btime;
}

int Spiel::getWinc()
{
	return this->winc;
}

int Spiel::getBinc()
{
	return this->binc;
}

int Spiel::getMovestogo()
{
	return this->movestogo;
}

int Spiel::getDepth()
{
	return this->depth;
}

int Spiel::getNodes()
{
	return this->nodes;
}

int Spiel::getMate()
{
	return this->mate;
}

int Spiel::getMovetime()
{
	return this->movetime;
}

bool Spiel::getGoinfinite()
{
	return this->infinite;
}

int Spiel::getHashsize()
{
	return this->hashsize;
}

void Spiel::setPonder(bool ponder)
{
	this->ponder = ponder;
}

void Spiel::stopthinking()
{
	this->stop = true;
}

DWORD WINAPI Spiel::CentralControl(LPVOID lpParam)
{
	HANDLE hStdout;
	PMYDATA pData;

	TCHAR msgBuf[BUF_SIZE];
	size_t cchStringSize;
	DWORD dwChars;

	Worker *work = new Worker();

	bool rekonfigureHash = false;
	bool stopsearchhash = false;
	// Make sure there is a console to receive output results. 

	hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hStdout == INVALID_HANDLE_VALUE)
		return 1;

	// Cast the parameter to the correct data type.
	// The pointer is known to be valid because 
	// it was checked for NULL before the thread was created.

	pData = (PMYDATA)lpParam;
	Convert *conv = new Convert();
	Brett *board = new Brett();
	Movemennt *moves = new Movemennt();
	Hashbrett *oldhash;
	bool timeout = false;
	bool white;
	// Print the parameter values using thread-safe functions.
	StringCchPrintf(msgBuf, BUF_SIZE, TEXT("readyok\n"));
	//	pData->val1, pData->val2);
	StringCchLength(msgBuf, BUF_SIZE, &cchStringSize);
	WriteConsole(hStdout, msgBuf, (DWORD)cchStringSize, &dwChars, NULL);
	// Print thread ende
	while(!*pData->quit)
	{
		if (*pData->input == PRINT)
		{
			if(pData->gamehash!=NULL)
				if(pData->gamehash->getBoard()!=NULL)
					conv->displayBoard(pData->gamehash->getBoard());
			moves->printHash(pData->gamehash);
			*pData->input = WAITING;
			*pData->ready = true;
		}
		if (*pData->input == SETBOARDWITHFEN)
		{
			if (pData->gamehash == NULL)
			{
				pData->gamehash = new Hashbrett();
				board = new Brett();
				conv->setBoardwithFEN(board, *pData->fenstring);
				pData->gamehash->setBoard(board);
				pData->gamehash->setFenString(conv->getBoardFen(pData->gamehash->getBoard()));
			}
			else if (pData->gamehash == NULL)
			{
				board = new Brett();
				conv->setBoardwithFEN(board, *pData->fenstring);
				pData->gamehash->setBoard(board);
				pData->gamehash->setFenString(conv->getBoardFen(pData->gamehash->getBoard()));
			}
			else
			{
				oldhash = pData->gamehash;
				pData->gamehash = new Hashbrett();
				board = new Brett();
				conv->setBoardwithFEN(board, *pData->fenstring);
				pData->gamehash->setBoard(board);
				std::string fenkey = conv->getBoardFen(pData->gamehash->getBoard());
				pData->gamehash->setFenString(fenkey);
				// search in hash ob board bereits vorkommt und linke dann die gefunden hashbretter zum Hauptbrett;
				// work->rekonfHash(febkey,oldhash,pData->gamehash,&rekonfigureHash,&stopsearchhash);
			}
			*pData->input = WAITING;
			*pData->ready = true;
		}
		if (*pData->input == SHOWFEN)
		{
			std::cout << "\n" << conv->getBoardFen(board) << "\n";
			*pData->input = WAITING;
			*pData->ready = true;
		}
		if (*pData->input == MAKEMOVE)
		{
			Hashbrett *loschen;
			loschen = pData->gamehash;
			pData->gamehash = new Hashbrett();
			pData->gamehash->setBoard(moves->copyBoard(loschen->getBoard()));
			if (moves->proveMove(pData->gamehash, *pData->movemade))
			{
				moves->makeMove(pData->gamehash, *pData->movemade);
				int white = pData->gamehash->getBoard()->getWhitetoMove();
				bool rekonf = true, stops = false;
				pData->gamehash->setFenString(conv->getBoardFen(pData->gamehash->getBoard()));
				Hashbrett *newgame = moves->rekonfHash(loschen, pData->gamehash->getFenString());
				if (newgame != NULL)
				{
					pData->gamehash->setChild(newgame, white);
					rekonfigureHash = true;
				}
				else
				{
					rekonfigureHash = false;
				}
			}
			else
			{
				pData->gamehash = loschen;
			}
			*pData->input = WAITING;
			*pData->ready = true;
		}
		if (*pData->input == STARTCOMPUTING)
		{
			moves->printHash(pData->gamehash);
			if (rekonfigureHash)
			{
				rekonfigureHash = false;
				white = pData->gamehash->getBoard()->getWhitetoMove();
				work->startupSearchTree(pData->gamehash, pData->quit, pData->endsearch, &timeout,&white);
				moves->printHash(pData->gamehash);
			}
			else
			{
				Hashbrett *one, *two;
				one = pData->gamehash->getChild(true);
				two = pData->gamehash->getChild(false);
				pData->gamehash->setChild(NULL, false);
				pData->gamehash->setChild(NULL,true);
				work->startupDelete(one, two);
				white = pData->gamehash->getBoard()->getWhitetoMove();
				work->startupSearch(pData->gamehash, pData->quit, pData->endsearch, &timeout,&white);
			}
			*pData->input = WAITING;
			*pData->ready = true;
		}
		if (*pData->input == RESETGAME)
		{
			Hashbrett *loschen;
			loschen = pData->gamehash;
			pData->gamehash = new Hashbrett();
			work->startupDelete(loschen, NULL);
			Brett *board = new Brett();
			conv->setBoardwithFEN(board, STARTFEN);
			pData->gamehash->setBoard(board);
			*pData->input = WAITING;
			*pData->ready = true;
		}
		Sleep(100);
	}
	std::cout << "#Tschau#\n";
	return 0;
}

void Spiel::ErrorHandler(LPTSTR lpszFunction)
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