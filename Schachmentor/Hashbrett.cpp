#include "stdafx.h"
#include "Hashbrett.h"


Hashbrett::Hashbrett()
{
	board = NULL;
	brother = NULL;
	child = NULL;
}


Hashbrett::~Hashbrett()
{
	if (board != NULL)
		delete board;
}

Hashbrett * Hashbrett::getBrother()
{
	return brother;
}

Hashbrett * Hashbrett::getChild()
{
	return child;
}

void Hashbrett::setBrother(Hashbrett * hashboard)
{
	this->brother = hashboard;
}

void Hashbrett::setChild(Hashbrett * hashboard)
{
	this->child = hashboard;
}

void Hashbrett::setZug(char zug[5])
{
	for(int i=0;i<5;i++)
		this->zug[i] = zug[i];
}

void Hashbrett::setBoard(Brett * board)
{
	if (this->board != NULL)
		delete this->board;
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
