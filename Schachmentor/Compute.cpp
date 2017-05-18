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
	conv = new Convert();
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
		if (command.length() > 1)
		{
			for (int i = 0; i < (command.length() - 2); i++)
			{
				if (i < (command.length() -2) && command.compare(i, 3, "uci") == 0)
				{
					this->ucistartup(command);
				}
				else if ((i < (command.length() - 4)) && command.compare(i, 5, "naked") == 0)
				{
					this->naked(command);
				}
			}
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
	char *cstr = new char[command.length() + 1];
	strcpy(cstr, command.c_str());
	char *pch;
	pch = strtok(cstr, " ");
	std::string word;
	word = pch;
	while (pch != NULL)
	{
		if (mode == -1)
		{
			std::cout << "Schachmentor engine 1\n";
			std::cout << "written by Wornik Hans\n";

			//< option name Ponder type check default false
			std::cout << "option name Hash type spin default 512 min 1 max 1024\n";
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
		//> setoption name NalimovCache value 4
		//> setoption name NalimovPath value D : \tbs
		//> setoption name Position Learning value true
		//> setoption name BookFile value dbbook.bin
		//> setoption name Book Size value Big
		//> setoption name Selectivity value 5
		if (word.compare("setoption") == 0)// setoption part----------------------------------------------------------
		{
			if (pch != NULL)
				pch = strtok(NULL, " ");
			while (pch != NULL)
			{
				word = pch;
				if (word.compare("name") == 0)// name part------------------------------------------------------------
				{
					if (pch != NULL)
					{
						pch = strtok(NULL, " ");
						while (pch != NULL)
						{
							word = pch;
							if (word.compare("Hash")==0)// Hash part------------------------------------
							{
									pch = strtok(NULL, " ");
									while (pch != NULL)
									{
										if (word.compare("value"))// Hash value setzen------------------
										{
											pch = strtok(NULL, " ");
											if (pch != NULL)
											{
												word = pch;
												int x = this->getIntfromchar(word);
												if(x> -1)
													game->setHashsize(x);
												pch = strtok(NULL, " ");
											}
										}
									}
							}
							if (pch != NULL)
								pch = strtok(NULL, " ");
						}
					}
				}
				if (pch != NULL)
					pch = strtok(NULL, " ");
			}
		}
		//> isready
		//< readyok
		if (word.compare("isready") == 0)
		{
			game->startup();
			mode = 1;	// wechsle in normalen ucimodus
			return true;
		}
		//--------------------------------------------------------
		// Startup end
		//--------------------------------------------------------
		if (pch != NULL)
			pch = strtok(NULL, " ");
	}
	return false;
}

bool Compute::uci(std::string command)
{
	char *cstr = new char[command.length() + 1];
	strcpy(cstr, command.c_str());
	char *pch;
	pch = strtok(cstr, " ");
	std::string word;
	while (pch != NULL)
	{
		word = pch;
		if (word.compare("show") == 0)
		{
			this->game->startAction(PRINT);
		}
		//--------------------------------------------------------
		//> setoption name Hash value 1
		//--------------------------------------------------------
		//--------------------------------------------------------
		//> setoption name Clear Book Learning | >setoption name Clear Book Learning value true 
		//--------------------------------------------------------
		//----------------------------------------------------------
		// > setoption name MultiPV value 3   3 komplette Berechnungen gleichzeitig
		//----------------------------------------------------------
		if (word.compare("setoption") == 0)//go Untermenu-------------------------------------
		{
		}
		word = pch;
		//--------------------------------------------------------
		//> ucinewgame
		//--------------------------------------------------------
		if (word.compare("ucinewgame") == 0)
		{
			this->game->startAction(RESETGAME);
		}
		word = pch;
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
		if (word.compare("position") == 0)//go Untermenu-------------------------------------
		{
		}
		word = pch;
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
		if (word.compare("go") == 0)//go Untermenu-------------------------------------
		{
			pch = strtok(NULL, " ");
			while (pch != NULL)
			{
				word = pch;
				if (word.compare("searchmoves")==0)
				{
					pch = strtok(NULL, " ");
					while (pch != NULL)
					{
						word = pch;
						if (this->ismove(pch,word.length()))
						{
							game->searchMoves(pch);
							pch = strtok(NULL, " ");
						}
						else
						{
							break;
						}
					}
				}
				if (pch != NULL)
				{
					word = pch;
					if (word.compare("ponder") == 0)
					{

					}
					if (word.compare("wtime") == 0)
					{
						pch = strtok(NULL, " ");
						if (pch != NULL)
						{
							word = pch;
							int x = this->getIntfromchar(word);
							if (x > -1)
								game->setWTime(x);
						}
					}
					if (word.compare("btime") == 0)
					{
						pch = strtok(NULL, " ");
						if (pch != NULL)
						{
							word = pch;
							int x = this->getIntfromchar(word);
							if (x > -1)
								game->setBTime(x);
						}
					}
					if (word.compare("winc") == 0)
					{
						pch = strtok(NULL, " ");
						if (pch != NULL)
						{
							word = pch;
							int x = this->getIntfromchar(word);
							if (x > -1)
								game->setWinc(x);
						}
					}
					if (word.compare("binc") == 0)
					{
						pch = strtok(NULL, " ");
						if (pch != NULL)
						{
							word = pch;
							int x = this->getIntfromchar(word);
							if (x > -1)
								game->setBinc(x);
						}
					}
					if (word.compare("movestogo") == 0)
					{
						pch = strtok(NULL, " ");
						if (pch != NULL)
						{
							word = pch;
							int x = this->getIntfromchar(word);
							if (x > -1)
								game->setMovestogo(x);
						}
					}
					if (word.compare("depth") == 0)
					{
						pch = strtok(NULL, " ");
						if (pch != NULL)
						{
							word = pch;
							int x = this->getIntfromchar(word);
							if (x > -1)
								game->setDepth(x);
						}
					}
					if (word.compare("nodes") == 0)
					{
						pch = strtok(NULL, " ");
						if (pch != NULL)
						{
							word = pch;
							int x = this->getIntfromchar(word);
							if (x > -1)
								game->setNodes(x);
						}
					}
					if (word.compare("mate") == 0)
					{
						pch = strtok(NULL, " ");
						if (pch != NULL)
						{
							word = pch;
							int x = this->getIntfromchar(word);
							if (x > -1)
								game->setMate(x);
						}
					}
					if (word.compare("movetime") == 0)
					{
						pch = strtok(NULL, " ");
						if (pch != NULL)
						{
							word = pch;
							int x = this->getIntfromchar(word);
							if (x > -1)
								game->setMovetime(x);
						}
					}
					if (word.compare("invinite") == 0)
					{
						game->setGoinfinite(true);
					}
				}
				if (pch != NULL)
					pch = strtok(NULL, " ");
			}
			game->startAction(STARTCOMPUTING);
		}
		if (pch != NULL)
		{
			word = pch;
			//----------------------------------------------------------
			//> stop
			//----------------------------------------------------------
			if (word.compare("stop") == 0)
			{
				game->stopthinking();
				this->end = true;
			}
			//----------------------------------------------------------
			//> quit
			//----------------------------------------------------------
			if (word.compare("quit") == 0)
			{
				game->shutdown();
				this->end = true;
			}
			//----------------------------------------------------------
			//>ponderhit   Ponder played
			//----------------------------------------------------------
			if (word.compare("ponderhit") == 0)
			{
				game->setPonder(true);
				this->end = true;
			}
		}
		if (pch != NULL)
			pch = strtok(NULL, " ");
	}
	return false;
}

bool Compute::naked(std::string command)
{
	char *cstr = new char[command.length() + 1];
	strcpy(cstr, command.c_str());
	char *pch;
	pch = strtok(cstr, " ");
	std::string word;
	while (pch != NULL)
	{
		word = pch;
		if (mode == -1)
		{
			std::cout << "Schachmentor engine 1\n";
			std::cout << "written by Wornik Hans\n";
			std::cout << "Konsolenmodus\n";
			game->startup();
			mode = NAKED;
		}
		if (word.compare(0, 10, "ucinewgame") == 0)
		{
			this->game->setFenString(STARTFEN);
			this->game->startAction(SETBOARDWITHFEN);
		}
		if (word.compare(0, 4, "show") == 0)
		{
			this->game->startAction(PRINT);
		}
		if (word.compare(0, 7, "showfen") == 0)
		{
			this->game->startAction(SHOWFEN);
		}
		if (word.compare(0, 8, "makemove") == 0)
		{
			pch = strtok(NULL, " ");
			word = pch;
			this->game->setMoveMadebyGUI(word);
			this->game->startAction(MAKEMOVE);
		}
		if (word.compare(0, 4, "quit") == 0)
		{
			game->shutdown();
			this->end = true;
		}
		pch = strtok(NULL, " ");
	}
	delete[] cstr;
	return false;
}

bool Compute::setSearchmoves(std::string command)
{
	return false;
}

bool Compute::ismove(char * command,int lange)
{
	if (lange < 4)
		return false;
	if (conv->getNumberofChar(command[0]) == -1)
		return false;
	if (!isdigit(command[1]))
		return false;
	if (conv->getNumberofChar(command[2]) == -1)
		return false;
	if (!isdigit(command[3]))
		return false;
	if (lange == 5)
	{
		int x = conv->getWert(command[4]);
		if (x < 0 || x>9)
		{
			return false;
		}
	}
	return true;
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
	bool ok = false;
	for (int i = 0; i < l;i++)
	{
		c = cstr[i] - 48;
		if (c >= 0 && c < 10)
		{
			ok = true;
			zahl = c + zahl * 10;
		}
	}
	if (zahl >= 0 && ok)
		return zahl;
	else
		return -1;
}
