#pragma once
#include <ctime>
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
	void readInput();
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
};

