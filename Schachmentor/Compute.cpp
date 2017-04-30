/*
	Hauptprogramm steuert alle Abläufe
*/

#include "stdafx.h"
#include "Compute.h"


Compute::Compute()
{
}


Compute::~Compute()
{
	mycom = new Comunicate();
}


bool Compute::start()
{
	while (!end)
	{
		if (mycom->input())
			this->readInput();
	}
	return true;
}
