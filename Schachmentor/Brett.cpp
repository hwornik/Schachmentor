#include "stdafx.h"
#include "Brett.h"


Brett::Brett()
{
	for (int i = 0; i < 16; i++)
	{
		Schwarz[i] = NULL;
		Weiss[i] = NULL;
	}
}


Brett::~Brett()
{
	for (int i = 0; i < 16; i++)
	{
		if (Schwarz[i] != NULL)
			delete Schwarz[i];
		if (Weiss[i] != NULL)
			delete Weiss[i];
	}
	delete Schwarz;
	delete Weiss;
}

int Brett::getNumberofChar(char line)
{
	if(line=='a')
		return 0;
	if (line == 'b')
		return 1;
	if (line == 'c')
		return 2;
	if (line == 'd')
		return 3;
	if (line == 'e')
		return 4;
	if (line == 'f')
		return 5;
	if (line == 'g')
		return 6;
	if (line == 'h')
		return 7;
	return -1;
}
