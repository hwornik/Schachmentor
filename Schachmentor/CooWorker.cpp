#include "stdafx.h"
#include "CooWorker.h"


CooWorker::CooWorker()
{
}


CooWorker::~CooWorker()
{
}



bool CooWorker::startupCalc(bool tree, int ThreadNr, Hashbrett *boards, Movemennt * move, int tiefe, int godepth, std::string zug, int *wertzug, std::string *bestmove, std::string *ponder, bool *whitesearch)
{
	// Allocate memory for thread data.
	//*hasharray = new Brett[hashsize];
	pSCData = (PMYSCDATA)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY,
		sizeof(MYSCDATA));

	if (pSCData == NULL)
	{
		// If the array allocation fails, the system is out of memory
		// so there is no point in trying to print an error message.
		// Just terminate execution.
		ExitProcess(2);
	}
	pSCData->bestmove = bestmove;
	pSCData->boards = boards;
	pSCData->godepth = godepth;
	pSCData->move = move;
	pSCData->ponder = ponder;
	pSCData->tiefe = tiefe;
	pSCData->wertzug = wertzug;
	pSCData->whitesearch = whitesearch;
	pSCData->zug = zug;

	// Generate unique data for each thread to work with.
	// Create the thread to begin execution on its own.

	// Create a semaphore with initial and max counts of MAX_SEM_COUNT

	/*ghSemaphore = CreateSemaphore(
		NULL,           // default security attributes
		MAX_SEM_COUNT,  // initial count
		MAX_SEM_COUNT,  // maximum count
		NULL);          // unnamed semaphore

	if (ghSemaphore == NULL)
	{
		printf("CreateSemaphore error: %d\n", GetLastError());
		return 1;
	}*/

	// Create worker threads
	if (tree)
	{
		if (ThreadNr < THREADCOUNT)
		{
			aThread[ThreadNr] = CreateThread(
				NULL,       // default security attributes
				0,          // default stack size
				(LPTHREAD_START_ROUTINE)CalcTree,
				pSCData,       // no thread function arguments
				0,          // default creation flags
				&ThreadID); // receive thread identifier

			if (aThread[ThreadNr] == NULL)
			{
				printf("CreateThread error: %d\n", GetLastError());
				return 1;
			}
		}
	}
	else
	{
		if (ThreadNr < THREADCOUNT)
		{
			aThread[ThreadNr] = CreateThread(
				NULL,       // default security attributes
				0,          // default stack size
				(LPTHREAD_START_ROUTINE)Calc,
				pSCData,       // no thread function arguments
				0,          // default creation flags
				&ThreadID); // receive thread identifier

			if (aThread[ThreadNr] == NULL)
			{
				printf("CreateThread error: %d\n", GetLastError());
				return 1;
			}
		}
	}
	return 0;
}
int CooWorker::waitdownCalc()
{
	WaitForMultipleObjects(THREADCOUNT, aThread, TRUE, INFINITE);
	return -1;
}


int CooWorker::shutdownCalc(int maxthread)
{
	// Wait for all threads to terminate

	WaitForMultipleObjects(THREADCOUNT, aThread, TRUE, INFINITE);

	// Close thread and semaphore handles
	if (maxthread > THREADCOUNT)
		maxthread = THREADCOUNT;
	for (int i = 0; i < maxthread; i++)
		CloseHandle(aThread[i]);

	//CloseHandle(ghSemaphore);
	return 0;
}

DWORD WINAPI CooWorker::Calc(LPVOID lpParam)
{
	HANDLE hStdoutS;
	PMYSCDATA pSCData;

	TCHAR msgBuf[BUF_SIZE];
	size_t cchStringSize;
	DWORD dwChars;
	
	pSCData = (PMYSCDATA)lpParam;

	DWORD dwWaitResult;
	BOOL bContinue = TRUE;
	Calculus *calc = new Calculus();
	calc->deepSearch(pSCData->boards, pSCData->move, pSCData->tiefe, pSCData->godepth, pSCData->zug, pSCData->wertzug, pSCData->bestmove, pSCData->ponder, pSCData->whitesearch);
	//Kritischer Bereich
	/*while (bContinue)
	{
		// Try to enter the semaphore gate.

		dwWaitResult = WaitForSingleObject(
			ghSemaphore,   // handle to semaphore
			0L);           // zero-second time-out interval

		switch (dwWaitResult)
		{
			// The semaphore object was signaled.
		case WAIT_OBJECT_0:
			// TODO: Perform task
			printf("Thread %d: wait succeeded\n", GetCurrentThreadId());
			bContinue = FALSE;

			// Simulate thread spending time on task
			//Sleep(5);

			// Release the semaphore when task is finished

			if (!ReleaseSemaphore(
				ghSemaphore,  // handle to semaphore
				1,            // increase count by one
				NULL))       // not interested in previous count
			{
				printf("ReleaseSemaphore error: %d\n", GetLastError());
			}
			break;

			// The semaphore was nonsignaled, so a time-out occurred.
		case WAIT_TIMEOUT:
			printf("Thread %d: wait timed out\n", GetCurrentThreadId());
			break;
		}
	}*/
	// kritischer Bereich ende
	return TRUE;
}

DWORD WINAPI CooWorker::CalcTree(LPVOID lpParam)
{

	PMYSCDATA pSCData;

	pSCData = (PMYSCDATA)lpParam;

	Calculus *calc = new Calculus();
	calc->traversSearch(pSCData->boards, pSCData->move, pSCData->tiefe, pSCData->godepth, pSCData->zug, pSCData->wertzug, pSCData->bestmove, pSCData->ponder, pSCData->whitesearch);
	return TRUE;
}