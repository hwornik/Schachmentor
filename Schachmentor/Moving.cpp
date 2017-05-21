#include "stdafx.h"
#include "Moving.h"


Moving::Moving()
{
	x = -1;
	y = -1;
	w = 0;
	move = NULL;
}


Moving::~Moving()
{
}

int Moving::getX()
{
	return this->x;
}

int Moving::getY()
{
	return this->y;
}

int Moving::getW()
{
	return this->w;
}

void Moving::setX(int x)
{
	this->x = x;
}

void Moving::setY(int y)
{
	this->y = y;
}

void Moving::setW(int w)
{
	this->w = w;
}

Moving * Moving::getnext()
{
	return this->move;
}

void Moving::setNext(Moving *move)
{
	this->move=move;
}
