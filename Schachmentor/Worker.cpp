#include "stdafx.h"
#include "Worker.h"

/*

				Weisszüge = Brother
				Schwarzzüge = Child

*/

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

int Worker::startuprekonHash(std::string fenkey, Hashbrett * oldhash, Hashbrett * gamehash, bool * rekonfigureHash, bool * stopsearchhash)
{
	// Allocate memory for thread data.
	//*hasharray = new Brett[hashsize];
	pRData = (PMYRDATA)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY,
		sizeof(MYRDATA));

	if (pRData == NULL)
	{
		// If the array allocation fails, the system is out of memory
		// so there is no point in trying to print an error message.
		// Just terminate execution.
		ExitProcess(2);
	}
	pRData->deleteone = oldhash;
	pRData->insertTree = gamehash;
	pRData->fenkey = fenkey;
	pRData->rekonfigureHash = rekonfigureHash;
	pRData->stopsearchhash = stopsearchhash;

	// Generate unique data for each thread to work with.
	// Create the thread to begin execution on its own.

	hThreadR = CreateThread(
		NULL,                   // default security attributes
		0,                      // use default stack size  
		rekonfHashbrett,         // thread function name
		pRData,          // argument to thread function 
		0,                      // use default creation flags 
		&dwThreadIdR);   // returns the thread identifier 


						 // Check the return value for success.
						 // If CreateThread fails, terminate execution. 
						 // This will automatically clean up threads and memory. 

	if (hThreadR == NULL)
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
	std::cout << "#Thread ende#";
	return 0;
}

DWORD WINAPI Worker::rekonfHashbrett(LPVOID lpParam)
{
	HANDLE hStdoutR;
	PMYRDATA pRData;

	TCHAR msgBuf[BUF_SIZE];
	size_t cchStringSize;
	DWORD dwChars;

	// Make sure there is a console to receive output results. 

	hStdoutR = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hStdoutR == INVALID_HANDLE_VALUE)
		return 1;

	// Cast the parameter to the correct data type.
	// The pointer is known to be valid because 
	// it was checked for NULL before the thread was created.
	DeleteHash *delhash = new DeleteHash();
	pRData = (PMYRDATA)lpParam;
	Worker *delWorker = new Worker();
	// Begin Work
	Hashbrett *aktuell, *loschenA, *loschenB;
	aktuell=pRData->deleteone;
	bool white = aktuell->getBoard()->getWhitetoMove();
	while (aktuell->getChild(!white) != NULL)
	{
		if (aktuell->getFenString().compare(pRData->fenkey) == 0)
		{

			pRData->insertTree = aktuell;
			loschenB = aktuell->getChild(!white);
			aktuell->setChild(NULL, !white);
			loschenA->setChild(NULL, !white);
			delWorker->startupDelete(pRData->deleteone, loschenB);
			return 0;
		}
		loschenA = aktuell;
		aktuell = aktuell->getChild(!white);
	}
	// Print thread ende
	std::cout << "#Thread ende#";
	return 0;
}
