#pragma once
#include <ctime>
#include <iostream>
#include <sstream>
#include <string.h>

#include "Comunicate.h"
#include "Spiel.h"
#include "Convert.h"


class Compute
{
public:
	Compute();
	~Compute();
	bool start();
private:
	Spiel *game;
	Convert *conv;
	bool end;
	Comunicate *mycom;
	int hashsize;
	void readInput();
	bool ucistartup(std::string command);
	std::string  command;
	bool uci(std::string command);
	bool naked(std::string  command);
	bool setSearchmoves(std::string command);
	int mode;
	int myside;
	bool ismove(char * command,int lange);
	void displayBoard();
	void printSearchHeader();
	void printStats();
	void printHelp();
	void printWelcome();
	char starUpCalc();
	clock_t movetime;
	bool searchmvs;
	void loadFromFen(std::string pos);
	std::string Ponder="",Hash="", NalimovCache="", NalimovPath="", MultiPV="",
		OwnBook="", ClearHash="", PositionLearning="", BookFile="", BookSize="",
		Selectivity="", ClearBook="";
	int getIntfromchar(std::string command);
};

