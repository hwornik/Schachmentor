#include "stdafx.h"
#include "Hashbrett.h"


Hashbrett::Hashbrett()
{
	board = NULL;
	weiss = NULL;
	schwarz = NULL;
}


Hashbrett::~Hashbrett()
{
	if (board != NULL)
		delete board;
}

Hashbrett * Hashbrett::getChild(bool white)
{
	if (white)
		return weiss;
	else
		return schwarz;
}


void Hashbrett::setChild(Hashbrett * hashboard,bool white)
{
	if(white)
		this->weiss = hashboard;
	else
		this->schwarz = hashboard;
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
