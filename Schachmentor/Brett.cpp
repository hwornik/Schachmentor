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
