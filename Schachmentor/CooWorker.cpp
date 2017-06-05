#include "stdafx.h"
#include "CooWorker.h"


CooWorker::CooWorker()
{
}


CooWorker::~CooWorker()
{
}



bool CooWorker::startupCalc( bool tree, int maxthread, Hashbrett *boards[], Movemennt * move, int tiefe, int godepth, std::string zug[], int wertzug[], std::string bestmove[], std::string ponder[], bool *whitesearch)
{
	PMYSCDATA pDataArray[THREADCOUNT];
	DWORD   dwThreadIdArray[THREADCOUNT];
	HANDLE  hThreadArray[THREADCOUNT];

	// Create MAX_THREADS worker threads.
	if (maxthread > THREADCOUNT)
		maxthread = THREADCOUNT;
	for (int i = 0; i<maxthread; i++)
	{
		// Allocate memory for thread data.

		pDataArray[i] = (PMYSCDATA)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY,
			sizeof(MYSCDATA));

		if (pDataArray[i] == NULL)
		{
			// If the array allocation fails, the system is out of memory
			// so there is no point in trying to print an error message.
			// Just terminate execution.
			ExitProcess(2);
		}

		// Generate unique data for each thread to work with.

		pDataArray[i]->bestmove =&bestmove[i] ;
		pDataArray[i]->boards = boards[i];;
		pDataArray[i]->godepth = godepth;
		pDataArray[i]->move = move;
		pDataArray[i]->ponder = &ponder[i];
		pDataArray[i]->tiefe = tiefe;
		pDataArray[i]->wertzug = &wertzug[i];
		pDataArray[i]->whitesearch = whitesearch;
		pDataArray[i]->zug = zug[i];

		// Create the thread to begin execution on its own.
		if (tree)
		{
			hThreadArray[i] = CreateThread(
				NULL,                   // default security attributes
				0,                      // use default stack size  
				CalcTree,       // thread function name
				pDataArray[i],          // argument to thread function 
				0,                      // use default creation flags 
				&dwThreadIdArray[i]);   // returns the thread identifier 


										// Check the return value for success.
										// If CreateThread fails, terminate execution. 
										// This will automatically clean up threads and memory. 
		}
		else
		{
			hThreadArray[i] = CreateThread(
				NULL,                   // default security attributes
				0,                      // use default stack size  
				Calc,       // thread function name
				pDataArray[i],          // argument to thread function 
				0,                      // use default creation flags 
				&dwThreadIdArray[i]);   // returns the thread identifier 
		}

		// Check the return value for success.
		// If CreateThread fails, terminate execution. 
		// This will automatically clean up threads and memory. 

		if (hThreadArray[i] == NULL)
		{
			ErrorHandler(TEXT("CreateThread"));
			ExitProcess(3);
		}
	} // End of main thread creation loop.

	  // Wait until all threads have terminated.

	WaitForMultipleObjects(maxthread, hThreadArray, TRUE, INFINITE);

	// Close all thread handles and free memory allocations.

	for (int i = 0; i<maxthread; i++)
	{
		CloseHandle(hThreadArray[i]);
	/*	if (pDataArray[i] != NULL)
		{
			HeapFree(GetProcessHeap(), 0, pDataArray[i]);
			pDataArray[i] = NULL;    // Ensure address is not reused.
		}*/
	}

	return 0;
}
int CooWorker::waitdownCalc(HANDLE aThread[THREADCOUNT])
{
	WaitForMultipleObjects(THREADCOUNT, aThread, TRUE, INFINITE);
	for (int i = 0; i < THREADCOUNT; i++)
		CloseHandle(aThread[i]);
	return -1;
}


int CooWorker::shutdownCalc(int maxthread, HANDLE aThread[THREADCOUNT])
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

void CooWorker::ErrorHandler(LPTSTR lpszFunction)
{
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