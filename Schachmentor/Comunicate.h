#pragma once
#include <istream>
#include <windows.h>

class Comunicate
{
public:
	Comunicate();
	~Comunicate();
	int input();
private:
	int pipe;
	typedef void* HANDLE;
	HANDLE hstdin;
	int inputmethod;
	bool ponder;
};

