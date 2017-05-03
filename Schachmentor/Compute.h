#pragma once
#include <ctime>
#include <iostream>
#include <sstream>
#include <string.h>

#include "Comunicate.h"

#define NAKED 0
#define UCI 1
#define UCISTARTUP 11
#define STARTFEN "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 0"
#define WHITE 0
#define BLACK 1
#define VERSION_STRING "1.1"
#define COMPILE_STRING " compiled 23.03.2016"

class Compute
{
public:
	Compute();
	~Compute();
	bool start();
private:
	bool end;
	Comunicate *mycom;
	void readInput();
	bool ucistartup(std::string command);
	std::string  command;
	bool uci(std::string command);
	bool naked(std::string  command);
	bool setSearchmoves(std::string command);
	int mode;
	int myside;
	int ismove(char * command);
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
};

