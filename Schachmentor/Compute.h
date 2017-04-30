#pragma once
#include "Comunicate.h"
class Compute
{
public:
	Compute();
	~Compute();
	bool start();
private:
	bool end;
	Comunicate *mycom;
};

