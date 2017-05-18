#pragma once
#include "Hashbrett.h"

typedef struct MyData {
	bool *quit;
	bool *endsearch;
	int *input;
	bool *ready;
	std::string *fenstring;
	char **movestodo;
	std::string *movemade;
	Hashbrett *gamehash;
} MYDATA, *PMYDATA;

typedef struct MyDData {
	Hashbrett *deleteone;
	Hashbrett *deletetwo;
} MYDDATA, *PMYDDATA;

typedef struct MyRData {
	Hashbrett *deleteone;
	Hashbrett *deletetwo;
	Hashbrett *insertTree;
	bool *rekonfigureHash ;
	bool *stopsearchhash;
} MYRDATA, *PMYRDATA;