/*
	Hauptprogramm steuert alle Abläufe
*/

#include "stdafx.h"
#include "Compute.h"


Compute::Compute()
{
	mode = -1;
	end = false;
	game = new Spiel();
	mycom = new Comunicate();
	hashsize = 512;
}


Compute::~Compute()
{

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
	std::getline(std::cin, command);
	if (mode == UCI)
		this->uci(command);
	else if(mode == UCISTARTUP)
		this->ucistartup(command);
	else if (mode == NAKED)
		this->naked(command);
	else if (mode == -1)
	{
		if (command.compare("uci") == 0)
		{
			this->ucistartup(command);
		}
		else if (command.compare("naked") == 0)
		{
			this->naked(command);
		}
	}
}

bool Compute::ucistartup(std::string command)
{
	// Commands
	//----------------------------------------------------
	// Starup
	//----------------------------------------------------
	// uci -> 
	// id name Engine Name 
	// id author Name
	if (mode == -1)
	{
		std::cout << "Schachmentor engine 1\n";
		std::cout << "written by Wornik Hans\n";

		//< option name Ponder type check default false
		std::cout << "option name Hash type spin default 512 min 1 max 1024";
		//< option name NalimovCache type spin min 1 max 16 default 2
		//< option name NalimovPath type string default <empty>
		//< option name MultiPV type spin min 1 max 20 default 1
		//< option name OwnBook type check default true
		// optional:---------
		//< option name Clear Hash type button 
		//< option name Position Learning type check default true
		//< option name BookFile type string default dbbook.bin
		//< option name Book Size type combo default Big var Small var Medium var Big
		//< option name Selectivity type spin min 0 max 15 default 5
		//< option name Clear Book Learning type button
		// optional end.-----
		//< uciok
		std::cout << "uciok\n";
	}
	mode = 11; // startupmodus
	//-----------------------------------------------------
	// gui set options now and then send isready
	//-----------------------------------------------------
	//> setoption name Ponder value true
	//> setoption name Hash value 16
	std::cout << command.substr(0, 20) << "#\n";
	if (command.compare(0,19,"setoption name Hash") == 0)
	{
		int z = command.length();
		hashsize=this->getIntfromchar(command.substr(26,z));
	}
	//> setoption name NalimovCache value 4
	//> setoption name NalimovPath value D : \tbs
	//> setoption name Position Learning value true
	//> setoption name BookFile value dbbook.bin
	//> setoption name Book Size value Big
	//> setoption name Selectivity value 5
	//> isready
	//< readyok
	if (command.compare("isready") == 0)
	{
		mode = 1;	// wechsle in normalen ucimodus
		std::cout << "readyok\n";
		return true;
	}
	//--------------------------------------------------------
	// Startup end
	//--------------------------------------------------------
	return false;
}

bool Compute::uci(std::string command)
{
	//--------------------------------------------------------
	//> setoption name Hash value 1
	//--------------------------------------------------------
	//--------------------------------------------------------
	//> setoption name Clear Book Learning | >setoption name Clear Book Learning value true 
	//--------------------------------------------------------
	//--------------------------------------------------------
	//> ucinewgame
	//--------------------------------------------------------
	if (command.compare(0, 10, "ucinewgame") == 0)
	{
		this->game->startAction(RESETGAME);
	}
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
	if (command.compare(0, 2, "go") == 0)
	{
		game->startup(hashsize);
	}
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
	if (command.compare("quit")==0)
	{
		game->shutdown();
		this->end = true;
	}
	return false;
}

bool Compute::naked(std::string command)
{
	if (mode == -1)
	{
		std::cout << "Schachmentor engine 1\n";
		std::cout << "written by Wornik Hans\n";
		std::cout << "Konsolenmodus\n";
		game->startup(hashsize);
		mode = NAKED;
	}
	if (command.compare("ucinewgame") == 0)
	{
		this->game->setFenString(STARTFEN);
		this->game->startAction(SETBOARDWITHFEN);
	}
	if (command.compare("show") == 0)
	{
		this->game->startAction(PRINT);
		std::cout << "Print";
	}
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

int Compute::getIntfromchar(std::string command)
{
	const char *cstr = command.c_str();
	int l = command.length();
	int c, zahl = 0;
	for (int i = 0; i < l;i++)
	{
		c = cstr[i] - 48;
		if (c >= 0 && c < 10)
			zahl = c+ zahl*10;
	}
	return zahl;
}
