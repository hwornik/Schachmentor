#include "stdafx.h"
#include "Hashbrett.h"


Hashbrett::Hashbrett()
{
	weiss = NULL;
	schwarz = NULL;
	zug = "";
	figwert = 0;
}


Hashbrett::~Hashbrett()
{
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
void Hashbrett::setFigurenwert(int wert)
{
	this->figwert = wert;
}

int Hashbrett::getFigurenwert()
{
	return this->figwert;
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

bool Hashbrett::getWhitetoMove()
{
	return this->whitetomove;
}

void Hashbrett::setWhitetoMove(bool white)
{
	whitetomove = white;
}


