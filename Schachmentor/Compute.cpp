/*
	Hauptprogramm steuert alle Abläufe
*/

#include "stdafx.h"
#include "Compute.h"


Compute::Compute()
{
}


Compute::~Compute()
{
	mycom = new Comunicate();
}


bool Compute::start()
{
	while (!end)
	{
		if (mycom->input())
			this->readInput();
	}
	return true;
}

void Compute::readInput()
{
}

bool Compute::uci(std::string command)
{
	// Commands
	//----------------------------------------------------
	// Starup
	//----------------------------------------------------
	// uci -> 
	// id name Engine Name 
	// id author Name
	//< option name Ponder type check default false
	//< option name Hash type spin default 1 min 1 max 1024
	//< option name NalimovCache type spin min 1 max 16 default 2
	//< option name NalimovPath type string default <empty>
	//< option name MultiPV type spin min 1 max 20 default 1
	//< option name OwnBook type check default true
	// optional:
	//< option name Clear Hash type button 
	//< option name Position Learning type check default true
	//< option name BookFile type string default dbbook.bin
	//< option name Book Size type combo default Big var Small var Medium var Big
	//< option name Selectivity type spin min 0 max 15 default 5
	//< option name Clear Book Learning type button
	// optional end.
	//< uciok
	//-----------------------------------------------------
	// gui set options now and then send isready
	//-----------------------------------------------------
	//> setoption name Ponder value true
	//> setoption name Hash value 16
	//> setoption name NalimovCache value 4
	//> setoption name NalimovPath value D : \tbs
	//> setoption name Position Learning value true
	//> setoption name BookFile value dbbook.bin
	//> setoption name Book Size value Big
	//> setoption name Selectivity value 5
	//> isready
	//< readyok
	//--------------------------------------------------------
	// Startup end
	//--------------------------------------------------------
	//--------------------------------------------------------
	//> setoption name Hash value 1
	//--------------------------------------------------------
	//--------------------------------------------------------
	//> setoption name Clear Book Learning | >setoption name Clear Book Learning value true 
	//--------------------------------------------------------
	//--------------------------------------------------------
	//> ucinewgame
	//--------------------------------------------------------
	//--------------------------------------------------------
	//> position startpos
	//--------------------------------------------------------
	//--------------------------------------------------------
	//>position startpos moves g1f3 d7d5 b2b3 c8g4 c1b2 b8c6 h2h3
	//--------------------------------------------------------
	//--------------------------------------------------------
	//>position fen 8/1K6/1Q6/8/5r2/4rk2/8/8 w - - 0 0 
	//--------------------------------------------------------
	//--------------------------------------------------------
	//> position fen 8/1K6/1Q6/8/5r2/4rk2/8/8 w - - 0 0 moves b6b1 e3e2 
	//---------------------------------------------------------
	//---------------------------------------------------------
	// go Kommands:
	//> go +
	//searchmoves
	//ponder bool
	//wtime  integer
	//btime	integer
	//winc	integer
	//binc	integer
	//movestogo moves to next time control
	//depth	integer
	//nodes	integer
	//mate integer
	//movetime integer im millisec
	//infinite
	//----------------------------------------------------------
	//----------------------------------------------------------
	//> stop
	//----------------------------------------------------------
	//----------------------------------------------------------
	//> quit
	//----------------------------------------------------------
	//----------------------------------------------------------
	//>ponderhit   Ponder played
	//----------------------------------------------------------
	//----------------------------------------------------------
	// > setoption name MultiPV value 3   3 komplette Berechnungen gleichzeitig
	//----------------------------------------------------------
	return false;
}

bool Compute::naked(std::string command)
{
	return false;
}

bool Compute::setSearchmoves(std::string command)
{
	return false;
}

int Compute::ismove(char * command)
{
	return 0;
}

void Compute::displayBoard()
{
}

void Compute::printSearchHeader()
{
}

void Compute::printStats()
{
}

void Compute::printHelp()
{
}

void Compute::printWelcome()
{
}

char Compute::starUpCalc()
{
	return 0;
}

void Compute::loadFromFen(std::string pos)
{
}
