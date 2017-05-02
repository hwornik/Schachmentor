#include "stdafx.h"
#include "Figur.h"


Figur::Figur()
{ 
	typ = ' ';
	posx = -1;
	posy = -1;
}


Figur::~Figur()
{
}

void Figur::setTyp(char typ)
{
	this->typ = typ;
}

void Figur::setPosx(int posx)
{
	this->posx = posx;
}

void Figur::setPosy(int posy)
{
	this->posy = posy;
}

char Figur::getTyp()
{
	return this->typ;
}

int Figur::getPosx()
{
	return this->posx;
}

int Figur::getPosy()
{
	return this->posy;
}
