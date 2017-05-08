#include "stdafx.h"
#include "Hashbrett.h"


Hashbrett::Hashbrett()
{
	board = NULL;
	nextBrother = NULL;
	previousBrother = NULL;
	nextChild = NULL;
	previousChild = NULL;
}


Hashbrett::~Hashbrett()
{
	if (board != NULL)
		delete board;
}

Hashbrett * Hashbrett::getnextBrother()
{
	return nextBrother;
}

Hashbrett * Hashbrett::getpreviusBrother()
{
	return previousBrother;
}

Hashbrett * Hashbrett::getnextChild()
{
	return nextChild;
}

Hashbrett * Hashbrett::getpreviousChild()
{
	return previousChild;
}

void Hashbrett::setnextBrother(Hashbrett * hashboard)
{
	this->nextBrother = hashboard;
}

void Hashbrett::setpreviusBrother(Hashbrett * hashboard)
{
	this->previousBrother = hashboard;
}

void Hashbrett::setnextChild(Hashbrett * hashboard)
{
	this->nextChild = hashboard;
}

void Hashbrett::setpreviousChild(Hashbrett * hashboard)
{
	this->previousChild = hashboard;
}

void Hashbrett::setZug(char zug[5])
{
	for(int i=0;i<5;i++)
		this->zug[i] = zug[i];
}

void Hashbrett::setBoard(Brett * board)
{
	if (board != NULL)
		delete board;
	this->board = board;
}

Brett * Hashbrett::getBoard()
{
	return this->board;
}

char * Hashbrett::getZug()
{
	return this->zug;
}

std::string Hashbrett::getFenString()
{
	return this->fenstring;
}

void Hashbrett::setFenString(std::string fenstring)
{
	this->fenstring = fenstring;
}
