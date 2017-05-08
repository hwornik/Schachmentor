#pragma once
#include <ctime>
#include <iostream>
#include <sstream>
#include <string.h>

#include "Comunicate.h"
#include "Spiel.h"

#define NAKED 0
#define UCI 1
#define UCISTARTUP 11
#define STARTFEN "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 0"
#define WHITE 0
#define BLACK 1
#define VERSION_STRING "1.1"
#define COMPILE_STRING " compiled 23.03.2016"

static const char BRETTFARBEN[8][8] = { { 'b','w','b','w','b','w','b','w' },
{ 'w','b','w','b','w','b','w','b' },
{ 'b','w','b','w','b','w','b','w' },
{ 'w','b','w','b','w','b','w','b' },
{ 'b','w','b','w','b','w','b','w' },
{ 'w','b','w','b','w','b','w','b' },
{ 'b','w','b','w','b','w','b','w' },
{ 'w','b','w','b','w','b','w','b' } };

static const char BRETTFELDER[8][8] = { { '#',' ','#',' ','#',' ','#',' ' },
{ ' ','#',' ','#',' ','#',' ','#' },
{ '#',' ','#',' ','#',' ','#',' ' },
{ ' ','#',' ','#',' ','#',' ','#' },
{ '#',' ','#',' ','#',' ','#',' ' },
{ ' ','#',' ','#',' ','#',' ','#' },
{ '#',' ','#',' ','#',' ','#',' ' },
{ ' ','#',' ','#',' ','#',' ','#' } };
//Befehle für Spiel:
#define PRINT 11
#define WAITING -1

class Compute
{
public:
	Compute();
	~Compute();
	bool start();
private:
	Spiel *game;
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
	int getIntfromchar(std::string command);
};

