#include "stdafx.h"
#include "Hashbrett.h"


Hashbrett::Hashbrett()
{
	board = new Brett();
	weiss = NULL;
	schwarz = NULL;
	zug = "";
}


Hashbrett::~Hashbrett()
{
	if (this->board != NULL)
		delete this->board;
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

void Hashbrett::setZug(std::string zug)
{
		this->zug = zug;
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

std::string Hashbrett::getZug()
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

std::string Hashbrett::getZugFolge()
{
	return this->zugfolge;
}

void Hashbrett::setZugFolge(std::string zugfolge)
{
	this->zugfolge = zugfolge;
}


