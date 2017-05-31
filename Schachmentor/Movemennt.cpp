#include "stdafx.h"
#include "Movemennt.h"


Movemennt::Movemennt()
{
	conv = new Convert();
	delhash = new DeleteHash();
}


Movemennt::~Movemennt()
{
}

Moving * Movemennt::getMovesperFigure(Brett * board, Figur * fig)
{
	Moving *moves,*aktuell;
	Moving *liste=new Moving();
	aktuell = liste;
	// Felder für Pawn-----------------------------------------------------------------------------------------------------------------
	// Weiss-------------------------------------------------------------------------------------------------------------------------
	if (fig->getTyp() == 'P')
	{
		if ((fig->getPosy() + 1) < 8 && board->getField(fig->getPosx(), (fig->getPosy() + 1)) == 0)
		{
			moves = new Moving();
			moves->setX(fig->getPosx());
			moves->setY(fig->getPosy() + 1);
			moves->setW(0);
			aktuell->setNext(moves);
			aktuell = aktuell->getnext();
		}
		if (fig->getPosy() == 1 && board->getField(fig->getPosx(), (fig->getPosy() + 1)) == 0 && board->getField(fig->getPosx(), (fig->getPosy() + 2)) == 0)
		{
			moves = new Moving();
			moves->setX(fig->getPosx());
			moves->setY(fig->getPosy() + 2);
			moves->setW(0);
			aktuell->setNext(moves);
			aktuell = aktuell->getnext();
		}
		if ((fig->getPosx() + 1) < 8 && (fig->getPosy() + 1) < 8 && board->getField(fig->getPosx() + 1, fig->getPosy() + 1) < 0)
		{
			moves = new Moving();
			moves->setX(fig->getPosx() + 1);
			moves->setY(fig->getPosy() + 1);
			moves->setW(conv->getWert(board->touchFigur(-(board->getField(fig->getPosx() + 1, fig->getPosy() + 1) + 1),false)->getTyp()));
			aktuell->setNext(moves);
			aktuell = aktuell->getnext();
		}
		if ((fig->getPosx() + 1) < 8 && (fig->getPosy() - 1) > -1 && board->getField(fig->getPosx() + 1, fig->getPosy() - 1) < 0)
		{
			moves = new Moving();
			moves->setX(fig->getPosx() + 1);
			moves->setY(fig->getPosy() - 1);
			moves->setW(conv->getWert(board->touchFigur(-(board->getField(fig->getPosx() + 1, fig->getPosy() - 1) + 1),false)->getTyp()));
			aktuell->setNext(moves);
			aktuell = aktuell->getnext();
		}
	}
	//Schwarz
	else if (fig->getTyp() == 'p')
	{
		if ( (fig->getPosy() - 1) > -1 && board->getField(fig->getPosx(), (fig->getPosy() - 1)) == 0)
		{
			moves = new Moving();
			moves->setX(fig->getPosx());
			moves->setY(fig->getPosy() - 1);
			moves->setW(0);
			aktuell->setNext(moves);
			aktuell = aktuell->getnext();
		}
		if (fig->getPosy() == 6 && board->getField(fig->getPosx(), (fig->getPosy() - 1)) == 0 && board->getField(fig->getPosx(), (fig->getPosy() - 2)) == 0)
		{
			moves = new Moving();
			moves->setX(fig->getPosx());
			moves->setY(fig->getPosy() - 2);
			moves->setW(0);
			aktuell->setNext(moves);
			aktuell = aktuell->getnext();
		}
		if ((fig->getPosx() - 1) > -1 && (fig->getPosy() + 1) < 8 && board->getField(fig->getPosx() - 1, fig->getPosy() + 1) > 0)
		{
			moves = new Moving();
			moves->setX(fig->getPosx() - 1);
			moves->setY(fig->getPosy() + 1);
			moves->setW(-conv->getWert(board->touchFigur((board->getField(fig->getPosx() - 1, fig->getPosy() + 1) - 1),true)->getTyp()));
			aktuell->setNext(moves);
			aktuell = aktuell->getnext();
		}
		if ((fig->getPosx() - 1) > -1 && (fig->getPosy() - 1) > -1 && board->getField(fig->getPosx() - 1, fig->getPosy() - 1) > 0)
		{
			moves = new Moving();
			moves->setX(fig->getPosx() - 1);
			moves->setY(fig->getPosy() - 1);
			moves->setW(-conv->getWert(board->touchFigur((board->getField(fig->getPosx() - 1, fig->getPosy() - 1) - 1),true)->getTyp()));
			aktuell->setNext(moves);
			aktuell = aktuell->getnext();
		}
	}
	// Springer ------------------------------------------------------------------------------------------------------------
	else if (toupper(fig->getTyp()) == 'N' )
	{
		if ((fig->getPosx() + 2) < 8 && (fig->getPosy() + 1) < 8 ) 
		{
			if (board->getField(fig->getPosx() + 2, fig->getPosy() + 1) == 0)
			{
				moves = new Moving();
				moves->setX(fig->getPosx() + 2);
				moves->setY(fig->getPosy() + 1);
				moves->setW(0);
				aktuell->setNext(moves);
				aktuell = aktuell->getnext();
			}
			else if (isupper(fig->getTyp()) && board->getField(fig->getPosx() + 2, fig->getPosy() + 1) < 0)
			{
				moves = new Moving();
				moves->setX(fig->getPosx() + 2);
				moves->setY(fig->getPosy() + 1);
				moves->setW(conv->getWert(board->touchFigur(-(board->getField(fig->getPosx() + 2 , fig->getPosy() + 1) + 1),false)->getTyp()));
				aktuell->setNext(moves);
				aktuell = aktuell->getnext();
			}
			else if (!isupper(fig->getTyp()) && board->getField(fig->getPosx() + 2, fig->getPosy() + 1) > 0)
			{
				moves = new Moving();
				moves->setX(fig->getPosx() + 2);
				moves->setY(fig->getPosy() + 1);
				moves->setW(-conv->getWert(board->touchFigur(board->getField(fig->getPosx() + 2, fig->getPosy() + 1) - 1,true)->getTyp()));
				aktuell->setNext(moves);
				aktuell = aktuell->getnext();
			}
		}
		if ((fig->getPosx() + 2) < 8 && (fig->getPosy() - 1) > -1)
		{
			if(board->getField(fig->getPosx() + 2, fig->getPosy() - 1) == 0)
			{
				moves = new Moving();
				moves->setX(fig->getPosx() + 2);
				moves->setY(fig->getPosy() - 1);
				moves->setW(0);
				aktuell->setNext(moves);
				aktuell = aktuell->getnext();
			}
			else if (isupper(fig->getTyp()) && board->getField(fig->getPosx() + 2, fig->getPosy() - 1) < 0)
			{
				moves = new Moving();
				moves->setX(fig->getPosx() + 2);
				moves->setY(fig->getPosy() - 1);
				moves->setW(conv->getWert(board->touchFigur(-(board->getField(fig->getPosx() + 2, fig->getPosy() - 1) + 1),false)->getTyp()));
				aktuell->setNext(moves);
				aktuell = aktuell->getnext();
			}
			else if (!isupper(fig->getTyp()) && board->getField(fig->getPosx() + 2, fig->getPosy() - 1) > 0)
			{
				moves = new Moving();
				moves->setX(fig->getPosx() + 2);
				moves->setY(fig->getPosy() - 1);
				moves->setW(-conv->getWert(board->touchFigur(board->getField(fig->getPosx() + 2, fig->getPosy() - 1) - 1,true)->getTyp()));
				aktuell->setNext(moves);
				aktuell = aktuell->getnext();
			}
		}
		if ((fig->getPosx() - 2) > -1 && (fig->getPosy() + 1) < 8 )
		{
			if (board->getField(fig->getPosx() - 2, fig->getPosy() + 1) == 0)
			{
				moves = new Moving();
				moves->setX(fig->getPosx() - 2);
				moves->setY(fig->getPosy() + 1);
				moves->setW(0);
				aktuell->setNext(moves);
				aktuell = aktuell->getnext();
			}
			else if (isupper(fig->getTyp()) && board->getField(fig->getPosx() - 2, fig->getPosy() + 1) < 0)
			{
				moves = new Moving();
				moves->setX(fig->getPosx() - 2);
				moves->setY(fig->getPosy() + 1);
				moves->setW(conv->getWert(board->touchFigur(-(board->getField(fig->getPosx() - 2, fig->getPosy() + 1) + 1),false)->getTyp()));
				aktuell->setNext(moves);
				aktuell = aktuell->getnext();
			}
			else if (!isupper(fig->getTyp()) && board->getField(fig->getPosx() - 2, fig->getPosy() + 1) > 0)
			{
				moves = new Moving();
				moves->setX(fig->getPosx() - 2);
				moves->setY(fig->getPosy() + 1);
				moves->setW(-conv->getWert(board->touchFigur(board->getField(fig->getPosx() - 2, fig->getPosy() + 1) - 1,true)->getTyp()));
				aktuell->setNext(moves);
				aktuell = aktuell->getnext();
			}
		}
		if ((fig->getPosx() - 2) > -1 && (fig->getPosy() - 1) > -1 )
		{
			if (board->getField(fig->getPosx() - 2, fig->getPosy() - 1) == 0)
			{
				moves = new Moving();
				moves->setX(fig->getPosx() - 2);
				moves->setY(fig->getPosy() - 1);
				moves->setW(0);
				aktuell->setNext(moves);
				aktuell = aktuell->getnext();
			}
			else if (isupper(fig->getTyp()) && board->getField(fig->getPosx() - 2, fig->getPosy() - 1) < 0)
			{
				moves = new Moving();
				moves->setX(fig->getPosx() - 2);
				moves->setY(fig->getPosy() - 1);
				moves->setW(conv->getWert(board->touchFigur(-(board->getField(fig->getPosx() - 2, fig->getPosy() - 1) + 1),false)->getTyp()));
				aktuell->setNext(moves);
				aktuell = aktuell->getnext();
			}
			else if (!isupper(fig->getTyp()) && board->getField(fig->getPosx() - 2, fig->getPosy() - 1) > 0)
			{
				moves = new Moving();
				moves->setX(fig->getPosx() - 2);
				moves->setY(fig->getPosy() - 1);
				moves->setW(-conv->getWert(board->touchFigur(board->getField(fig->getPosx() - 2, fig->getPosy() - 1) - 1,true)->getTyp()));
				aktuell->setNext(moves);
				aktuell = aktuell->getnext();
			}
		}
		if ((fig->getPosx() + 1) < 8 && (fig->getPosy() + 2) < 8 )
		{
			if (board->getField(fig->getPosx() + 1, fig->getPosy() + 2) == 0)
			{
				moves = new Moving();
				moves->setX(fig->getPosx() + 1);
				moves->setY(fig->getPosy() + 2);
				moves->setW(0);
				aktuell->setNext(moves);
				aktuell = aktuell->getnext();
			}
			if (isupper(fig->getTyp()) && board->getField(fig->getPosx() + 1, fig->getPosy() + 2) < 0)
			{
				moves = new Moving();
				moves->setX(fig->getPosx() + 1);
				moves->setY(fig->getPosy() + 2);
				moves->setW(conv->getWert(board->touchFigur(-(board->getField(fig->getPosx() + 1, fig->getPosy() + 2) + 1),false)->getTyp()));
				aktuell->setNext(moves);
				aktuell = aktuell->getnext();
			}
			else if (!isupper(fig->getTyp()) && board->getField(fig->getPosx() + 1, fig->getPosy() + 2) > 0)
			{
				moves = new Moving();
				moves->setX(fig->getPosx() + 1);
				moves->setY(fig->getPosy() + 2);
				moves->setW(-conv->getWert(board->touchFigur(board->getField(fig->getPosx() + 1, fig->getPosy() + 2) - 1,true)->getTyp()));
				aktuell->setNext(moves);
				aktuell = aktuell->getnext();
			}
		}
		if ((fig->getPosx() - 1) > -1 && (fig->getPosy() + 2) < 8 )
		{
			if (board->getField(fig->getPosx() - 1, fig->getPosy() + 2) == 0)
			{
				moves = new Moving();
				moves->setX(fig->getPosx() - 1);
				moves->setY(fig->getPosy() + 2);
				moves->setW(0);
				aktuell->setNext(moves);
				aktuell = aktuell->getnext();
			}
			else if (isupper(fig->getTyp()) && board->getField(fig->getPosx() - 1, fig->getPosy() + 2) < 0)
			{
				moves = new Moving();
				moves->setX(fig->getPosx() - 1);
				moves->setY(fig->getPosy() + 2);
				moves->setW(conv->getWert(board->touchFigur(-(board->getField(fig->getPosx() - 1, fig->getPosy() + 2) + 1),false)->getTyp()));
				aktuell->setNext(moves);
				aktuell = aktuell->getnext();
			}
			else if (!isupper(fig->getTyp()) && board->getField(fig->getPosx() - 1, fig->getPosy() + 2) > 0)
			{
				moves = new Moving();
				moves->setX(fig->getPosx() - 1);
				moves->setY(fig->getPosy() + 2);
				moves->setW(-conv->getWert(board->touchFigur(board->getField(fig->getPosx() - 1, fig->getPosy() + 2) - 1,true)->getTyp()));
				aktuell->setNext(moves);
				aktuell = aktuell->getnext();
			}
		}
		else if ((fig->getPosx() + 1) < 8 && (fig->getPosy() - 2) > -1)
		{
			if (board->getField(fig->getPosx() + 1, fig->getPosy() - 2) == 0)
			{
				moves = new Moving();
				moves->setX(fig->getPosx() + 1);
				moves->setY(fig->getPosy() - 2);
				moves->setW(0);
				aktuell->setNext(moves);
				aktuell = aktuell->getnext();
			}
			else if (isupper(fig->getTyp()) && board->getField(fig->getPosx() + 1, fig->getPosy() - 2) < 0)
			{
				moves = new Moving();
				moves->setX(fig->getPosx() + 1);
				moves->setY(fig->getPosy() - 2);
				moves->setW(conv->getWert(board->touchFigur(-(board->getField(fig->getPosx() + 1, fig->getPosy() - 2) + 1),false)->getTyp()));
				aktuell->setNext(moves);
				aktuell = aktuell->getnext();
			}
			else if (!isupper(fig->getTyp()) && board->getField(fig->getPosx() + 1, fig->getPosy() - 2) > 0)
			{
				moves = new Moving();
				moves->setX(fig->getPosx() + 1);
				moves->setY(fig->getPosy() - 2);
				moves->setW(-conv->getWert(board->touchFigur(board->getField(fig->getPosx() + 1, fig->getPosy() - 2) - 1,true)->getTyp()));
				aktuell->setNext(moves);
				aktuell = aktuell->getnext();
			}
		}
		if ((fig->getPosx() - 1) > -1 && (fig->getPosy() -2 ) > -1 )
		{
			if (board->getField(fig->getPosx() - 1, fig->getPosy() - 2) == 0)
			{
				moves = new Moving();
				moves->setX(fig->getPosx() - 1);
				moves->setY(fig->getPosy() - 2);
				moves->setW(0);
				aktuell->setNext(moves);
				aktuell = aktuell->getnext();
			}
			if (isupper(fig->getTyp()) && board->getField(fig->getPosx() - 1, fig->getPosy() - 2) < 0)
			{
				moves = new Moving();
				moves->setX(fig->getPosx() - 1);
				moves->setY(fig->getPosy() - 2);
				moves->setW(conv->getWert(board->touchFigur(-(board->getField(fig->getPosx() - 1, fig->getPosy() - 2) + 1),false)->getTyp()));
				aktuell->setNext(moves);
				aktuell = aktuell->getnext();
			}
			else if (!isupper(fig->getTyp()) && board->getField(fig->getPosx() - 1, fig->getPosy() - 2) > 0)
			{
				moves = new Moving();
				moves->setX(fig->getPosx() - 1);
				moves->setY(fig->getPosy() - 2);
				moves->setW(-conv->getWert(board->touchFigur(board->getField(fig->getPosx() - 1, fig->getPosy() - 2) - 1,true)->getTyp()));
				aktuell->setNext(moves);
				aktuell = aktuell->getnext();
			}
		}
	}
	// läufer,Rook und queen-----------------------------------------------------------------------------------------------------
	else if (toupper(fig->getTyp()) == 'B' || toupper(fig->getTyp()) == 'Q' && toupper(fig->getTyp()) == 'R')
	{
		// Läufer und Queen------------------------------------------------------------------------------------------------------
		if (toupper(fig->getTyp()) == 'B' || toupper(fig->getTyp()) == 'Q')
		{
			bool notend[4];
			notend[0] = true;
			notend[1] = true;
			notend[2] = true;
			notend[3] = true;
			for (int i = 1; i < 8; i++)
			{
					if (notend[0] && (fig->getPosx() + i) < 8 && (fig->getPosy() + i) < 8 )
					{
						if (board->getField(fig->getPosx() + i, fig->getPosy() + i) == 0)
						{
							moves = new Moving();
							moves->setX(fig->getPosx() + i);
							moves->setY(fig->getPosy() + i);
							moves->setW(0);
							aktuell->setNext(moves);
							aktuell = aktuell->getnext();
						}
						else if (isupper(fig->getTyp()) && board->getField(fig->getPosx() + i, fig->getPosy() + i) < 0)
						{
							moves = new Moving();
							moves->setX(fig->getPosx() + i);
							moves->setY(fig->getPosy() + i);
							moves->setW(conv->getWert(board->touchFigur(-(board->getField(fig->getPosx() +i, fig->getPosy() +i) + 1),false)->getTyp()));
							aktuell->setNext(moves);
							aktuell = aktuell->getnext();
							notend[0] = false;
						}
						else if (!isupper(fig->getTyp()) && board->getField(fig->getPosx() + i, fig->getPosy() + i) > 0)
						{
							moves = new Moving();
							moves->setX(fig->getPosx() + i);
							moves->setY(fig->getPosy() + i);
							moves->setW(-conv->getWert(board->touchFigur((board->getField(fig->getPosx() + i, fig->getPosy() + i) - 1),true)->getTyp()));
							aktuell->setNext(moves);
							aktuell = aktuell->getnext();
							notend[0] = false;
						}
						else
						{
							notend[0] = false;
						}
					}
					else
					{
						notend[0] = false;
					}
					if (notend[1] && (fig->getPosx() + i) < 8 && (fig->getPosy() - i) > -1 )
					{
						if (board->getField(fig->getPosx() + i, fig->getPosy() - i) == 0)
						{
							moves = new Moving();
							moves->setX(fig->getPosx() + i);
							moves->setY(fig->getPosy() - i);
							moves->setW(0);
							aktuell->setNext(moves);
							aktuell = aktuell->getnext();
						}
						else if (isupper(fig->getTyp()) && board->getField(fig->getPosx() + i, fig->getPosy() - i) < 0)
						{
							moves = new Moving();
							moves->setX(fig->getPosx() + i);
							moves->setY(fig->getPosy() - i);
							moves->setW(conv->getWert(board->touchFigur(-(board->getField(fig->getPosx() + i, fig->getPosy() - i) + 1),false)->getTyp()));
							aktuell->setNext(moves);
							aktuell = aktuell->getnext();
							notend[1] = false;
						}
						else if (!isupper(fig->getTyp()) && board->getField(fig->getPosx() + i, fig->getPosy() - i) > 0)
						{
							moves = new Moving();
							moves->setX(fig->getPosx() + i);
							moves->setY(fig->getPosy() - i);
							moves->setW(-conv->getWert(board->touchFigur((board->getField(fig->getPosx() + i, fig->getPosy() - i) - 1),true)->getTyp()));
							aktuell->setNext(moves);
							aktuell = aktuell->getnext();
							notend[1] = false;
						}
						else
						{
							notend[1] = false;
						}
					}
					else
					{
						notend[1] = false;
					}
					if (notend[2] && (fig->getPosx() - i) > -1 && (fig->getPosy() + i) < 8 )
					{
						if (board->getField(fig->getPosx() - i, fig->getPosy() + i) == 0)
						{
							moves = new Moving();
							moves->setX(fig->getPosx() - i);
							moves->setY(fig->getPosy() + i);
							moves->setW(0);
							aktuell->setNext(moves);
							aktuell = aktuell->getnext();
						}
						else if (isupper(fig->getTyp()) && board->getField(fig->getPosx() - i, fig->getPosy() + i) < 0)
						{
							moves = new Moving();
							moves->setX(fig->getPosx() - i);
							moves->setY(fig->getPosy() + i);
							moves->setW(conv->getWert(board->touchFigur(-(board->getField(fig->getPosx() - i, fig->getPosy() + i) + 1),false)->getTyp()));
							aktuell->setNext(moves);
							aktuell = aktuell->getnext();
							notend[2] = false;
						}
						else if (!isupper(fig->getTyp()) && board->getField(fig->getPosx() - i, fig->getPosy() + i) > 0)
						{
							moves = new Moving();
							moves->setX(fig->getPosx() - i);
							moves->setY(fig->getPosy() + i);
							moves->setW(-conv->getWert(board->touchFigur((board->getField(fig->getPosx() - i, fig->getPosy() + i) - 1),true)->getTyp()));
							aktuell->setNext(moves);
							aktuell = aktuell->getnext();
							notend[2] = false;
						}
						else
						{
							notend[2] = false;
						}
					}
					else
					{
						notend[2] = false;
					}
					if (notend[3] && (fig->getPosx() - i) > -1 && (fig->getPosy() - i) > -1 )
					{
						if (board->getField(fig->getPosx() - i, fig->getPosy() - i) == 0)
						{
							moves = new Moving();
							moves->setX(fig->getPosx() - i);
							moves->setY(fig->getPosy() - i);
							moves->setW(0);
							aktuell->setNext(moves);
							aktuell = aktuell->getnext();
						}
						else if (isupper(fig->getTyp()) && board->getField(fig->getPosx() - i, fig->getPosy() - i) < 0)
						{
							moves = new Moving();
							moves->setX(fig->getPosx() - i);
							moves->setY(fig->getPosy() - i);
							moves->setW(conv->getWert(board->touchFigur(-(board->getField(fig->getPosx() - i, fig->getPosy() - i) + 1),false)->getTyp()));
							aktuell->setNext(moves);
							aktuell = aktuell->getnext();
							notend[3] = false;
						}
						else if (!isupper(fig->getTyp()) && board->getField(fig->getPosx() - i, fig->getPosy() - i) > 0)
						{
							moves = new Moving();
							moves->setX(fig->getPosx() - i);
							moves->setY(fig->getPosy() - i);
							moves->setW(-conv->getWert(board->touchFigur((board->getField(fig->getPosx() - i, fig->getPosy() - i) - 1),true)->getTyp()));
							aktuell->setNext(moves);
							aktuell = aktuell->getnext();
							notend[3] = false;
						}
						else
						{
							notend[3] = false;
						}
					}
					else
					{
						notend[3] = false;
					}
			}
		}
		// Turm und Queen--------------------------------------------------------------------------------------------------------
		if (toupper(fig->getTyp()) == 'R' || toupper(fig->getTyp()) == 'Q')
		{
			bool notend[4];
			notend[0] = true;
			notend[1] = true;
			notend[2] = true;
			notend[3] = true;
			for (int i = 1; i < 8; i++)
			{
				if (notend[0] && (fig->getPosx() + i) < 8 )
				{
					if (board->getField(fig->getPosx() + i, fig->getPosy()) == 0)
					{
						moves = new Moving();
						moves->setX(fig->getPosx() + i);
						moves->setY(fig->getPosy());
						moves->setW(0);
						aktuell->setNext(moves);
						aktuell = aktuell->getnext();
					}
					else if (isupper(fig->getTyp()) && board->getField(fig->getPosx() + i, fig->getPosy()) < 0)
					{
						moves = new Moving();
						moves->setX(fig->getPosx() + i);
						moves->setY(fig->getPosy());
						moves->setW(conv->getWert(board->touchFigur(-(board->getField(fig->getPosx() + i, fig->getPosy()) + 1),false)->getTyp()));
						aktuell->setNext(moves);
						aktuell = aktuell->getnext();
						notend[0] = false;
					}
					else if (!isupper(fig->getTyp()) && board->getField(fig->getPosx() + i, fig->getPosy()) > 0)
					{
						moves = new Moving();
						moves->setX(fig->getPosx() + i);
						moves->setY(fig->getPosy());
						moves->setW(-conv->getWert(board->touchFigur((board->getField(fig->getPosx() + i, fig->getPosy()) - 1),true)->getTyp()));
						aktuell->setNext(moves);
						aktuell = aktuell->getnext();
						notend[0] = false;
					}
					else
					{
						notend[0] = false;
					}
				}
				else
				{
					notend[0] = false;
				}
				if (notend[1] && (fig->getPosx() - i) > -1 )
				{
					if (board->getField(fig->getPosx() - i, fig->getPosy()) == 0)
					{
						moves = new Moving();
						moves->setX(fig->getPosx() - i);
						moves->setY(fig->getPosy());
						moves->setW(0);
						aktuell->setNext(moves);
						aktuell = aktuell->getnext();
					}
					else if (isupper(fig->getTyp()) && board->getField(fig->getPosx() - i, fig->getPosy()) < 0)
					{
						moves = new Moving();
						moves->setX(fig->getPosx() - i);
						moves->setY(fig->getPosy());
						moves->setW(conv->getWert(board->touchFigur(-(board->getField(fig->getPosx() - i, fig->getPosy()) + 1),false)->getTyp()));
						aktuell->setNext(moves);
						aktuell = aktuell->getnext();
						notend[1] = false;
					}
					else if (!isupper(fig->getTyp()) && board->getField(fig->getPosx() - i, fig->getPosy()) > 0)
					{
						moves = new Moving();
						moves->setX(fig->getPosx() - i);
						moves->setY(fig->getPosy());
						moves->setW(-conv->getWert(board->touchFigur((board->getField(fig->getPosx() - i, fig->getPosy()) - 1),true)->getTyp()));
						aktuell->setNext(moves);
						aktuell = aktuell->getnext();
						notend[1] = false;
					}
					else
					{
						notend[1] = false;
					}
				}
				else
				{
					notend[1] = false;
				}
				if (notend[2] && (fig->getPosy() + i) < 8 )
				{
					if (board->getField(fig->getPosx(), fig->getPosy() + i) == 0)
					{
						moves = new Moving();
						moves->setX(fig->getPosx());
						moves->setY(fig->getPosy() + i);
						moves->setW(0);
						aktuell->setNext(moves);
						aktuell = aktuell->getnext();
					}
					else if (isupper(fig->getTyp()) && board->getField(fig->getPosx(), fig->getPosy() + i) < 0)
					{
						moves = new Moving();
						moves->setX(fig->getPosx());
						moves->setY(fig->getPosy() + i);
						moves->setW(conv->getWert(board->touchFigur(-(board->getField(fig->getPosx(), fig->getPosy() + i) + 1),false)->getTyp()));
						aktuell->setNext(moves);
						aktuell = aktuell->getnext();
						notend[2] = false;
					}
					else if (!isupper(fig->getTyp()) && board->getField(fig->getPosx() , fig->getPosy() + i) > 0)
					{
						moves = new Moving();
						moves->setX(fig->getPosx());
						moves->setY(fig->getPosy() + i);
						moves->setW(-conv->getWert(board->touchFigur((board->getField(fig->getPosx() , fig->getPosy() + i) - 1),true)->getTyp()));
						aktuell->setNext(moves);
						aktuell = aktuell->getnext();
						notend[2] = false;
					}
					else
					{
						notend[2] = false;
					}
				}
				else
				{
					notend[2] = false;
				}
				if (notend[3] && (fig->getPosy() - i) > -1 )
				{
					if (board->getField(fig->getPosx(), fig->getPosy() - i) == 0)
					{
						moves = new Moving();
						moves->setX(fig->getPosx());
						moves->setY(fig->getPosy() - i);
						moves->setW(0);
						aktuell->setNext(moves);
						aktuell = aktuell->getnext();
					}
					else if (isupper(fig->getTyp()) && board->getField(fig->getPosx() , fig->getPosy() - i) < 0)
					{
						moves = new Moving();
						moves->setX(fig->getPosx());
						moves->setY(fig->getPosy() - i);
						moves->setW(conv->getWert(board->touchFigur(-(board->getField(fig->getPosx() , fig->getPosy() - i) + 1),false)->getTyp()));
						aktuell->setNext(moves);
						aktuell = aktuell->getnext();
						notend[3] = false;
					}
					else if (!isupper(fig->getTyp()) && board->getField(fig->getPosx(), fig->getPosy() - i) > 0)
					{
						moves = new Moving();
						moves->setX(fig->getPosx());
						moves->setY(fig->getPosy() - i);
						moves->setW(-conv->getWert(board->touchFigur((board->getField(fig->getPosx(), fig->getPosy() - i) - 1),true)->getTyp()));
						aktuell->setNext(moves);
						aktuell = aktuell->getnext();
						notend[3] = false;
					}
					else
					{
						notend[3] = false;
					}
				}
				else
				{
					notend[3] = false;
				}
			}
		}
	}
	// König-------------------------------------------------------------------------------------------------------------------
	else if (fig->getTyp() == 'K' || fig->getTyp() == 'k')
	{
		if (fig->getPosx() + 1 < 8 && fig->getPosy() + 1 < 8)
		{
			if (board->getField(fig->getPosx() + 1, fig->getPosy() + 1) == 0)
			{
				moves = new Moving();
				moves->setX(fig->getPosx() + 1);
				moves->setY(fig->getPosy() + 1);
				moves->setW(0);
				aktuell->setNext(moves);
				aktuell = aktuell->getnext();
			}
			else if (isupper(fig->getTyp()) && board->getField(fig->getPosx() + 1, fig->getPosy() + 1) < 0)
			{
				moves = new Moving();
				moves->setX(fig->getPosx() + 1);
				moves->setY(fig->getPosy() + 1);
				moves->setW(conv->getWert(board->touchFigur(-(board->getField(fig->getPosx() + 1, fig->getPosy() + 1) + 1),false)->getTyp()));
				aktuell->setNext(moves);
				aktuell = aktuell->getnext();
			}
			else if (!isupper(fig->getTyp()) && board->getField(fig->getPosx() + 1, fig->getPosy() + 1) > 0)
			{
				moves = new Moving();
				moves->setX(fig->getPosx() + 1);
				moves->setY(fig->getPosy() + 1);
				moves->setW(-conv->getWert(board->touchFigur((board->getField(fig->getPosx() + 1, fig->getPosy() + 1) - 1),true)->getTyp()));
				aktuell->setNext(moves);
				aktuell = aktuell->getnext();
			}
		}
		if (fig->getPosx() + 1 < 8 && fig->getPosy() - 1 > -1 )
		{
			if (board->getField(fig->getPosx() + 1, fig->getPosy() - 1) == 0)
			{
				moves = new Moving();
				moves->setX(fig->getPosx() + 1);
				moves->setY(fig->getPosy() - 1);
				moves->setW(0);
				aktuell->setNext(moves);
				aktuell = aktuell->getnext();
			}
			if (isupper(fig->getTyp()) && board->getField(fig->getPosx() + 1, fig->getPosy() - 1) < 0)
			{
				moves = new Moving();
				moves->setX(fig->getPosx() + 1);
				moves->setY(fig->getPosy() - 1);
				moves->setW(conv->getWert(board->touchFigur(-(board->getField(fig->getPosx() + 1, fig->getPosy() - 1) + 1),false)->getTyp()));
				aktuell->setNext(moves);
				aktuell = aktuell->getnext();
			}
			else if (!isupper(fig->getTyp()) && board->getField(fig->getPosx() + 1, fig->getPosy() - 1) > 0)
			{
				moves = new Moving();
				moves->setX(fig->getPosx() + 1);
				moves->setY(fig->getPosy() - 1);
				moves->setW(-conv->getWert(board->touchFigur((board->getField(fig->getPosx() + 1, fig->getPosy() - 1) - 1),true)->getTyp()));
				aktuell->setNext(moves);
				aktuell = aktuell->getnext();
			}
		}
		if (fig->getPosx() - 1 > -1 && fig->getPosy() + 1 < 8 )
		{
			if (board->getField(fig->getPosx() - 1, fig->getPosy() + 1) == 0)
			{
				moves = new Moving();
				moves->setX(fig->getPosx() - 1);
				moves->setY(fig->getPosy() + 1);
				moves->setW(0);
				aktuell->setNext(moves);
				aktuell = aktuell->getnext();
			}
			else if (isupper(fig->getTyp()) && board->getField(fig->getPosx() - 1, fig->getPosy() + 1) < 0)
			{
				moves = new Moving();
				moves->setX(fig->getPosx() - 1);
				moves->setY(fig->getPosy() + 1);
				moves->setW(conv->getWert(board->touchFigur(-(board->getField(fig->getPosx() - 1, fig->getPosy() + 1) + 1),false)->getTyp()));
				aktuell->setNext(moves);
				aktuell = aktuell->getnext();
			}
			else if (!isupper(fig->getTyp()) && board->getField(fig->getPosx() - 1, fig->getPosy() + 1) > 0)
			{
				moves = new Moving();
				moves->setX(fig->getPosx() - 1);
				moves->setY(fig->getPosy() + 1);
				moves->setW(-conv->getWert(board->touchFigur((board->getField(fig->getPosx() - 1, fig->getPosy() + 1) - 1),true)->getTyp()));
				aktuell->setNext(moves);
				aktuell = aktuell->getnext();
			}
		}
		if (fig->getPosx() - 1 > -1 && fig->getPosy() - 1 > -1 )
		{
			if (board->getField(fig->getPosx() - 1, fig->getPosy() - 1) == 0)
			{
				moves = new Moving();
				moves->setX(fig->getPosx() - 1);
				moves->setY(fig->getPosy() - 1);
				moves->setW(0);
				aktuell->setNext(moves);
				aktuell = aktuell->getnext();
			}
			else if (isupper(fig->getTyp()) && board->getField(fig->getPosx() - 1, fig->getPosy() - 1) < 0)
			{
				moves = new Moving();
				moves->setX(fig->getPosx() - 1);
				moves->setY(fig->getPosy() - 1);
				moves->setW(conv->getWert(board->touchFigur(-(board->getField(fig->getPosx() - 1, fig->getPosy() - 1) + 1),false)->getTyp()));
				aktuell->setNext(moves);
				aktuell = aktuell->getnext();
			}
			else if (!isupper(fig->getTyp()) && board->getField(fig->getPosx() - 1, fig->getPosy() - 1) > 0)
			{
				moves = new Moving();
				moves->setX(fig->getPosx() - 1);
				moves->setY(fig->getPosy() - 1);
				moves->setW(-conv->getWert(board->touchFigur((board->getField(fig->getPosx() - 1, fig->getPosy() - 1) - 1),true)->getTyp()));
				aktuell->setNext(moves);
				aktuell = aktuell->getnext();
			}
		}
		//---------------------------
		if (fig->getPosy() + 1 < 8 )
		{
			if (board->getField(fig->getPosx(), fig->getPosy() + 1) == 0)
			{
				moves = new Moving();
				moves->setX(fig->getPosx());
				moves->setY(fig->getPosy() + 1);
				moves->setW(0);
				aktuell->setNext(moves);
				aktuell = aktuell->getnext();
			}
			else if (isupper(fig->getTyp()) && board->getField(fig->getPosx() , fig->getPosy() + 1) < 0)
			{
				moves = new Moving();
				moves->setX(fig->getPosx());
				moves->setY(fig->getPosy() + 1);
				moves->setW(conv->getWert(board->touchFigur(-(board->getField(fig->getPosx() , fig->getPosy() + 1) + 1),false)->getTyp()));
				aktuell->setNext(moves);
				aktuell = aktuell->getnext();
			}
			else if (!isupper(fig->getTyp()) && board->getField(fig->getPosx() , fig->getPosy() + 1) > 0)
			{
				moves = new Moving();
				moves->setX(fig->getPosx());
				moves->setY(fig->getPosy() + 1);
				moves->setW(-conv->getWert(board->touchFigur((board->getField(fig->getPosx(), fig->getPosy() + 1) - 1),true)->getTyp()));
				aktuell->setNext(moves);
				aktuell = aktuell->getnext();
			}
		}
		if (fig->getPosy() - 1 > -1 )
		{
			if (board->getField(fig->getPosx(), fig->getPosy() - 1) == 0)
			{
				moves = new Moving();
				moves->setX(fig->getPosx());
				moves->setY(fig->getPosy() - 1);
				moves->setW(0);
				aktuell->setNext(moves);
				aktuell = aktuell->getnext();
			}
			else if (isupper(fig->getTyp()) && board->getField(fig->getPosx() , fig->getPosy() - 1) < 0)
			{
				moves = new Moving();
				moves->setX(fig->getPosx());
				moves->setY(fig->getPosy() - 1);
				moves->setW(conv->getWert(board->touchFigur(-(board->getField(fig->getPosx() , fig->getPosy() - 1) + 1),false)->getTyp()));
				aktuell->setNext(moves);
				aktuell = aktuell->getnext();
			}
			else if (!isupper(fig->getTyp()) && board->getField(fig->getPosx(), fig->getPosy() - 1) > 0)
			{
				moves = new Moving();
				moves->setX(fig->getPosx());
				moves->setY(fig->getPosy() - 1);
				moves->setW(-conv->getWert(board->touchFigur((board->getField(fig->getPosx(), fig->getPosy() - 1) - 1),true)->getTyp()));
				aktuell->setNext(moves);
				aktuell = aktuell->getnext();
			}
		}
		if (fig->getPosx() - 1 > -1 )
		{
			if (board->getField(fig->getPosx() - 1, fig->getPosy()) == 0)
			{
				moves = new Moving();
				moves->setX(fig->getPosx() - 1);
				moves->setY(fig->getPosy());
				moves->setW(0);
				aktuell->setNext(moves);
				aktuell = aktuell->getnext();
			}
			else if (isupper(fig->getTyp()) && board->getField(fig->getPosx() - 1, fig->getPosy()) < 0)
			{
				moves = new Moving();
				moves->setX(fig->getPosx() - 1);
				moves->setY(fig->getPosy());
				moves->setW(conv->getWert(board->touchFigur(-(board->getField(fig->getPosx() - 1, fig->getPosy()) + 1),false)->getTyp()));
				aktuell->setNext(moves);
				aktuell = aktuell->getnext();
			}
			else if (!isupper(fig->getTyp()) && board->getField(fig->getPosx() - 1, fig->getPosy()) > 0)
			{
				moves = new Moving();
				moves->setX(fig->getPosx() - 1);
				moves->setY(fig->getPosy());
				moves->setW(-conv->getWert(board->touchFigur((board->getField(fig->getPosx() - 1, fig->getPosy()))-1,true)->getTyp()));
				aktuell->setNext(moves);
				aktuell = aktuell->getnext();
			}
		}
		if (fig->getPosx() + 1 < 8 )
		{
			if (board->getField(fig->getPosx() + 1, fig->getPosy()) == 0)
			{
				moves = new Moving();
				moves->setX(fig->getPosx() + 1);
				moves->setY(fig->getPosy());
				moves->setW(0);
				aktuell->setNext(moves);
				aktuell = aktuell->getnext();
			}
			if (isupper(fig->getTyp()) && board->getField(fig->getPosx() + 1, fig->getPosy()) < 0)
			{
				moves = new Moving();
				moves->setX(fig->getPosx() + 1);
				moves->setY(fig->getPosy());
				moves->setW(conv->getWert(board->touchFigur(-(board->getField(fig->getPosx() + 1, fig->getPosy()) + 1),false)->getTyp()));
				aktuell->setNext(moves);
				aktuell = aktuell->getnext();
			}
			else if (!isupper(fig->getTyp()) && board->getField(fig->getPosx() + 1, fig->getPosy()) > 0)
			{
				moves = new Moving();
				moves->setX(fig->getPosx() + 1);
				moves->setY(fig->getPosy());
				moves->setW(-conv->getWert(board->touchFigur((board->getField(fig->getPosx() + 1, fig->getPosy()) - 1),true)->getTyp()));
				aktuell->setNext(moves);
				aktuell = aktuell->getnext();
			}
		}
		if (board->getCastlKingside(true) && fig->getPosx()==0 && board->getField(fig->getPosx() + 1, fig->getPosy()) == 0 && board->getField(fig->getPosx() + 2, fig->getPosy()) == 0)
		{
			if (!this->testRochadeAngriffKS(board, fig))
			{
				moves = new Moving();
				moves->setX(fig->getPosx() + 2);
				moves->setY(fig->getPosy());
				moves->setW(ROCHADE);
				aktuell->setNext(moves);
				aktuell = aktuell->getnext();
			}
		}
		if (board->getCastlQueenside(true) && fig->getPosx() == 0 && board->getField(fig->getPosx() - 1, fig->getPosy()) == 0 && board->getField(fig->getPosx() - 2, fig->getPosy()) == 0 && board->getField(fig->getPosx() - 3, fig->getPosy()) == 0)
		{
			if (!this->testRochadeAngriffQS(board, fig))
			{
				moves = new Moving();
				moves->setX(fig->getPosx() - 2);
				moves->setY(fig->getPosy());
				moves->setW(ROCHADE);
				aktuell->setNext(moves);
				aktuell = aktuell->getnext();
			}
		}
		if (board->getCastlKingside(false) && fig->getPosx() == 7 && board->getField(fig->getPosx() + 1, fig->getPosy()) == 0 && board->getField(fig->getPosx() + 2, fig->getPosy()) == 0)
		{
			if (!this->testRochadeAngriffKS(board, fig))
			{
				moves = new Moving();
				moves->setX(fig->getPosx() + 2);
				moves->setY(fig->getPosy());
				moves->setW(ROCHADE);
				aktuell->setNext(moves);
				aktuell = aktuell->getnext();
			}
		}
		if (board->getCastlQueenside(false) && fig->getPosx() == 7 && board->getField(fig->getPosx() - 1, fig->getPosy()) == 0 && board->getField(fig->getPosx() - 2, fig->getPosy()) == 0 && board->getField(fig->getPosx() - 3, fig->getPosy()) == 0)
		{
			if (!this->testRochadeAngriffQS(board, fig))
			{
				moves = new Moving();
				moves->setX(fig->getPosx() - 2);
				moves->setY(fig->getPosy());
				moves->setW(ROCHADE);
				aktuell->setNext(moves);
				aktuell = aktuell->getnext();
			}
		}
	}
	return liste;
}

bool Movemennt::proveMove(int ** move, Figur * fig, Brett * board)
{
	if (board->getWhitetoMove() && !isupper(fig->getTyp()))
		return false;
	if (!board->getWhitetoMove() && isupper(fig->getTyp()))
		return false;
	// Felder für Pawn
	if (fig->getTyp() == 'P')
	{
		if ( (fig->getPosy() + 1) < 8 && board->getField(fig->getPosx(), (fig->getPosy() + 1)) == 0)
		{
			if (move[0][0] == move[1][0])
			{
				if (move[0][1] == (move[1][1] - 1))
				{
					return true;
				}
				else
				{
					if (fig->getPosy()==1 && board->getField(fig->getPosx(), (fig->getPosy() + 2)) == 0)
					{
						if (move[0][1] == (move[1][1] - 2))
						{
							return true;
						}
						else
						{
							return false;
						}
					}
					else
					{
						return false;
					}
				}
			}
			else
			{
				return false;
			}

		}
		else if ((fig->getPosx() + 1) < 8 &&  (fig->getPosy() + 1)< 8 && board->getField(fig->getPosx() + 1, (fig->getPosy() + 1)) < 0 && move[0][0] == (move[1][0] +1) && move[0][1]==(move[1][1]+1))
		{
			return true;
		}
		else if ((fig->getPosx() + 1) < 8 && (fig->getPosy() - 1) > -1 && board->getField(fig->getPosx() + 1, (fig->getPosy() - 1)) < 0 && move[0][0] == (move[1][0] + 1) && move[0][1] == (move[1][1] - 1))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else if (fig->getTyp() == 'p')
	{
		if ((fig->getPosy() - 1) > -1 && board->getField(fig->getPosx(), (fig->getPosy() - 1)) == 0)
		{
			if (move[0][0] == move[1][0])
			{
				if (move[0][1] == (move[1][1] + 1))
				{
					return true;
				}
				else
				{
					if (fig->getPosy() == 6 && board->getField(fig->getPosx(), (fig->getPosy() - 2)) == 0)
					{
						if (move[0][1] == (move[1][1] + 2))
						{
							return true;
						}
						else
						{
							return false;
						}
					}
					else
					{
						return false;
					}
				}
			}
			else if ((fig->getPosx() - 1) > -1 && (fig->getPosy() + 1) < 8 && board->getField(fig->getPosx() - 1, (fig->getPosy() + 1)) > 0 && move[0][0] == (move[1][0] - 1) && move[0][1] == (move[1][1] + 1))
			{
				return true;
			}
			else if ((fig->getPosx() - 1) > -1 && (fig->getPosy() - 1) > -1 && board->getField(fig->getPosx() - 1, (fig->getPosy() - 1)) > 0 && move[0][0] == (move[1][0] - 1) && move[0][1] == (move[1][1] - 1))
			{
				return true;
			}
			else
			{
				return false;
			}

		}

		else
		{
			return false;
		}
	}
	// Springer ------------------------------------------------------------------------------------------------------------
	// Weiss----------------------------------------------------------------------------------------------------------------
	else if (fig->getTyp() == 'N')
	{
		if (move[1][0] == (fig->getPosx() + 2) && (fig->getPosy() + 1) == move[1][1] && board->getField(fig->getPosx() + 2, fig->getPosy() + 1) <= 0)
		{
				return true;
		}
		if (move[1][0] == (fig->getPosx() + 2) && (fig->getPosy() - 1) == move[1][1] && board->getField(fig->getPosx() + 2, fig->getPosy() - 1) <= 0)
		{
				return true;
		}
		if (move[1][0] == (fig->getPosx() - 2) && (fig->getPosy() + 1) == move[1][1] && board->getField(fig->getPosx() - 2, fig->getPosy() + 1) <= 0)
		{
				return true;
		}
		if (move[1][0] == (fig->getPosx() - 2) && (fig->getPosy() - 1) == move[1][1] && board->getField(fig->getPosx() - 2, fig->getPosy() - 1) <= 0)
		{
				return true;
		}
		if (move[1][0] == (fig->getPosx() + 1) && (fig->getPosy() + 2) == move[1][1] && board->getField(fig->getPosx() + 1, fig->getPosy() + 2) <= 0)
		{
				return true;
		}
		if (move[1][0] == (fig->getPosx() - 1) && (fig->getPosy() + 2) == move[1][1] && board->getField(fig->getPosx() - 1, fig->getPosy() + 2) <= 0)
		{
				return true;
		}
		else if (move[1][0] == (fig->getPosx() + 1) && (fig->getPosy() - 2) == move[1][1] && board->getField(fig->getPosx() + 1, fig->getPosy() - 2) <= 0)
		{
				return true;
		}
		if (move[1][0] == (fig->getPosx() + 2) && (fig->getPosy() + 1) == move[1][1] && board->getField(fig->getPosx() - 1, fig->getPosy() - 2) <= 0)
		{
				return true;
		}
		return false;
	}
	// Schwarz--------------------------------------------------------------------------------------------------------------
	else if (fig->getTyp() == 'n')
	{
		if (move[1][0] == (fig->getPosx() + 2) && (fig->getPosy() + 1) == move[1][1] && board->getField(fig->getPosx() + 2, fig->getPosy() + 1) >= 0)
		{
				return true;
		}
		if (move[1][0] == (fig->getPosx() + 2) && (fig->getPosy() - 1) == move[1][1] && board->getField(fig->getPosx() + 2, fig->getPosy() - 1) >= 0)
		{
				return true;
		}
		if (move[1][0] == (fig->getPosx() - 2) && (fig->getPosy() + 1) == move[1][1] && board->getField(fig->getPosx() - 2, fig->getPosy() + 1) >= 0)
		{
				return true;
		}
		if (move[1][0] == (fig->getPosx() - 2) && (fig->getPosy() - 1) == move[1][1] && board->getField(fig->getPosx() - 2, fig->getPosy() - 1) >= 0)
		{
				return true;
		}
		if (move[1][0] == (fig->getPosx() + 1) && (fig->getPosy() + 2) == move[1][1] && board->getField(fig->getPosx() + 1, fig->getPosy() + 2) >= 0)
		{
				return true;
		}
		if (move[1][0] == (fig->getPosx() - 1) && (fig->getPosy() + 2) == move[1][1] && board->getField(fig->getPosx() - 1, fig->getPosy() + 2) >= 0)
		{
				return true;
		}
		if (move[1][0] == (fig->getPosx() + 1) && (fig->getPosy() - 2) == move[1][1] && board->getField(fig->getPosx() + 1, fig->getPosy() - 2) >= 0)
		{
				return true;
		}
		if (move[1][0] == (fig->getPosx() - 1) && (fig->getPosy() - 2) == move[1][1] && board->getField(fig->getPosx() - 1, fig->getPosy() - 2) >= 0)
		{
				return true;
		}
		return false;
	}
	// läufer,Rook und queen-----------------------------------------------------------------------------------------------------
	else if (toupper(fig->getTyp()) == 'B' || toupper(fig->getTyp()) == 'Q' || toupper(fig->getTyp()) == 'R')
	{
		// Läufer und Queen------------------------------------------------------------------------------------------------------
		if (toupper(fig->getTyp()) == 'B' || toupper(fig->getTyp()) == 'Q')
		{
			bool notend[4];
			notend[0] = true;
			notend[1] = true;
			notend[2] = true;
			notend[3] = true;
			for (int i = 1; i < 8; i++)
			{
				if (notend[0] && (fig->getPosx() + i) < 8 && (fig->getPosy() + i) < 8 )
				{
					if (move[1][0] == (fig->getPosx() + i) && (fig->getPosy() + i) == move[1][1] && board->getField(fig->getPosx() + i, fig->getPosy() + i) == 0)
						return true;
					if (isupper(fig->getTyp()) && board->getField(fig->getPosx() + i, fig->getPosy() + i) < 0)
					{
						notend[0] = false;
						if (move[1][0] == (fig->getPosx() + i) && (fig->getPosy() + i) == move[1][1])
							return true;
					}
					else if (!isupper(fig->getTyp()) && board->getField(fig->getPosx() + i, fig->getPosy() + i) > 0)
					{
						notend[0] = false;
						if (move[1][0] == (fig->getPosx() + i) && (fig->getPosy() + i) == move[1][1])
							return true;
					}
				}
				else
				{
					notend[0] = false;
				}
				if (notend[1] && (fig->getPosx() + i) < 8 && (fig->getPosy() - i) > -1 )
				{
					if (move[1][0] == (fig->getPosx() + i) && (fig->getPosy() - i) == move[1][1] && board->getField(fig->getPosx() + i, fig->getPosy() - i) == 0)
						return true;
					if (isupper(fig->getTyp()) && board->getField(fig->getPosx() + i, fig->getPosy() - i) < 0)
					{
						notend[1] = false;
						if (move[1][0] == (fig->getPosx() + i) && (fig->getPosy() - i) == move[1][1])
							return true;
					}
					else if (!isupper(fig->getTyp()) && board->getField(fig->getPosx() + i, fig->getPosy() - i) > 0)
					{
						notend[1] = false;
						if (move[1][0] == (fig->getPosx() + i) && (fig->getPosy() - i) == move[1][1])
							return true;
					}
				}
				else
				{
					notend[1] = false;
				}
				if (notend[2] && (fig->getPosx() - i) > -1 && (fig->getPosy() + i) < 8 )
				{
					if (move[1][0] == (fig->getPosx() - i) && (fig->getPosy() + i) == move[1][1] && board->getField(fig->getPosx() - i, fig->getPosy() + i) == 0)
						return true;
					if (isupper(fig->getTyp()) && board->getField(fig->getPosx() - i, fig->getPosy() + i) < 0)
					{
						notend[2] = false;
						if (move[1][0] == (fig->getPosx() - i) && (fig->getPosy() + i) == move[1][1])
							return true;
					}
					else if (!isupper(fig->getTyp()) && board->getField(fig->getPosx() - i, fig->getPosy() + i) > 0)
					{
						notend[2] = false;
						if (move[1][0] == (fig->getPosx() - i) && (fig->getPosy() + i) == move[1][1])
							return true;
					}
				}
				else
				{
					notend[2] = false;
				}
				if (notend[3] && (fig->getPosx() - i) > -1 && (fig->getPosy() - i) > -1 )
				{
					if (move[1][0] == (fig->getPosx() - i) && (fig->getPosy() - i) == move[1][1] && board->getField(fig->getPosx() - i, fig->getPosy() - i) == 0)
						return true;
					if (isupper(fig->getTyp()) && board->getField(fig->getPosx() - i, fig->getPosy() - i) < 0)
					{
						notend[3] = false;
						if (move[1][0] == (fig->getPosx() - i) && (fig->getPosy() - i) == move[1][1])
							return true;
					}
					else if (!isupper(fig->getTyp()) && board->getField(fig->getPosx() - i, fig->getPosy() - i) > 0)
					{
						notend[3] = false;
						if (move[1][0] == (fig->getPosx() - i) && (fig->getPosy() - i) == move[1][1])
							return true;
					}
				}
				else
				{
					notend[3] = false;
				}
			}
		}
		// Turm und Queen--------------------------------------------------------------------------------------------------------
		if (toupper(fig->getTyp()) == 'R' || toupper(fig->getTyp()) == 'Q')
		{
			bool notend[4];
			notend[0] = true;
			notend[1] = true;
			notend[2] = true;
			notend[3] = true;
			for (int i = 1; i < 8; i++)
			{
				if (notend[0] && (fig->getPosx() + i) < 8 )
				{
					if (move[1][0] == (fig->getPosx() + i) && fig->getPosy() == move[1][1] && board->getField(fig->getPosx() + i, fig->getPosy()) == 0)
						return true;
					if (isupper(fig->getTyp()) && board->getField(fig->getPosx() + i, fig->getPosy()) < 0)
					{
						notend[0] = false;
						if (move[1][0] == (fig->getPosx() + i) && fig->getPosy() == move[1][1])
							return true;
					}
					else if (!isupper(fig->getTyp()) && board->getField(fig->getPosx() + i, fig->getPosy()) > 0)
					{
						notend[0] = false;
						if (move[1][0] == (fig->getPosx() + i) && fig->getPosy() == move[1][1])
							return true;
					}
				}
				else
				{
					notend[0] = false;
				}
				if (notend[1] && (fig->getPosx() - i) > -1 )
				{
					if (move[1][0] == (fig->getPosx() - i) && fig->getPosy() == move[1][1] && board->getField(fig->getPosx() - i, fig->getPosy()) == 0)
						return true;
					if (isupper(fig->getTyp()) && board->getField(fig->getPosx() - i, fig->getPosy()) < 0)
					{
						notend[1] = false;
						if (move[1][0] == (fig->getPosx() - i) && fig->getPosy() == move[1][1])
							return true;
					}
					else if (!isupper(fig->getTyp()) && board->getField(fig->getPosx() - i, fig->getPosy()) > 0)
					{
						notend[1] = false;
						if (move[1][0] == (fig->getPosx() - i) && fig->getPosy() == move[1][1])
							return true;
					}
				}
				else
				{
					notend[1] = false;
				}
				if (notend[2] && (fig->getPosy() + i) < 8 )
				{
					if (move[1][0] == fig->getPosx() && (fig->getPosy()+1) == move[1][1] && board->getField(fig->getPosx(), fig->getPosy() + i) == 0)
						return true;
					if (isupper(fig->getTyp()) && board->getField(fig->getPosx(), fig->getPosy() + i) < 0)
					{
						notend[2] = false;
						if (move[1][0] == fig->getPosx() && (fig->getPosy() + 1) == move[1][1])
							return true;
					}
					else if (!isupper(fig->getTyp()) && board->getField(fig->getPosx() - i, fig->getPosy()) > 0)
					{
						notend[2] = false;
						if (move[1][0] == fig->getPosx() && (fig->getPosy() + 1) == move[1][1])
							return true;
					}
				}
				else
				{
					notend[2] = false;
				}
				if (notend[3] && (fig->getPosy() - i) > -1 )
				{
					if (move[1][0] == fig->getPosx() && (fig->getPosy() - 1) == move[1][1] && board->getField(fig->getPosx(), fig->getPosy() - i) == 0)
						return true;
					if (isupper(fig->getTyp()) && board->getField(fig->getPosx(), fig->getPosy() - i) < 0)
					{
						notend[3] = false;
						if (move[1][0] == fig->getPosx() && (fig->getPosy() - 1) == move[1][1])
							return true;
					}
					else if (!isupper(fig->getTyp()) && board->getField(fig->getPosx(), fig->getPosy() - i) > 0)
					{
						notend[3] = false;
						if (move[1][0] == fig->getPosx() && (fig->getPosy() - 1) == move[1][1])
							return true;
					}
				}
				else
				{
					notend[3] = false;
				}
			}
		}
		return false;
	}
	// König-------------------------------------------------------------------------------------------------------------------
	else if (fig->getTyp() == 'K' || fig->getTyp() == 'k')
	{
		std::cout << "test Kk\n";
		if ((fig->getPosx() + 1 < 8) && fig->getPosy() + 1 < 8 )
		{
			if (move[1][0] == (fig->getPosx() + 1) && (fig->getPosy() + 1) == move[1][1] && board->getField(fig->getPosx() + 1, fig->getPosy() + 1) == 0)
				return true;
			if (isupper(fig->getTyp()) && board->getField(fig->getPosx() + 1, fig->getPosy() + 1) < 0)
			{
				if (move[1][0] == (fig->getPosx() + 1) && (fig->getPosy() + 1) == move[1][1])
					return true;
			}
			else if (!isupper(fig->getTyp()) && board->getField(fig->getPosx() + 1, fig->getPosy() + 1) > 0)
			{
				if (move[1][0] == (fig->getPosx() + 1) && (fig->getPosy() + 1) == move[1][1])
					return true;
			}
		}
		else if ((fig->getPosx() + 1) < 8 && fig->getPosy() - 1 > -1 )
		{
			if (move[1][0] == (fig->getPosx() + 1) && (fig->getPosy() - 1) == move[1][1] && board->getField(fig->getPosx() + 1, fig->getPosy() - 1) == 0)
				return true;
			if (isupper(fig->getTyp()) && board->getField(fig->getPosx() + 1, fig->getPosy() - 1) < 0)
			{
				if (move[1][0] == (fig->getPosx() + 1) && (fig->getPosy() - 1) == move[1][1])
					return true;
			}
			else if (!isupper(fig->getTyp()) && board->getField(fig->getPosx() + 1, fig->getPosy() - 1) > 0)
			{
				if (move[1][0] == (fig->getPosx() + 1) && (fig->getPosy() - 1) == move[1][1])
					return true;
			}
		}
		else if ((fig->getPosx() - 1) > -1 )
		{
			if (move[1][0] == (fig->getPosx() - 1) && (fig->getPosy() + 1) == move[1][1] && fig->getPosy() + 1 < 8 && board->getField(fig->getPosx() - 1, fig->getPosy() + 1) == 0)
				return true;
			if (isupper(fig->getTyp()) && board->getField(fig->getPosx() - 1, fig->getPosy() + 1) < 0)
			{
				if (move[1][0] == (fig->getPosx() - 1) && (fig->getPosy() + 1) == move[1][1])
					return true;
			}
			else if (!isupper(fig->getTyp()) && board->getField(fig->getPosx() - 1, fig->getPosy() + 1) > 0)
			{
				if (move[1][0] == (fig->getPosx() - 1) && (fig->getPosy() + 1) == move[1][1])
					return true;
			}
		}
		else if (fig->getPosx() - 1 > -1 && fig->getPosy() - 1 > -1 )
		{
			if (move[1][0] == (fig->getPosx() - 1) && (fig->getPosy() - 1) == move[1][1] && board->getField(fig->getPosx() - 1, fig->getPosy() - 1) == 0)
				return true;
			if (isupper(fig->getTyp()) && board->getField(fig->getPosx() - 1, fig->getPosy() - 1) < 0)
			{
				if (move[1][0] == (fig->getPosx() - 1) && (fig->getPosy() - 1) == move[1][1])
					return true;
			}
			else if (!isupper(fig->getTyp()) && board->getField(fig->getPosx() - 1, fig->getPosy() - 1) > 0)
			{
				if (move[1][0] == (fig->getPosx() - 1) && (fig->getPosy() - 1) == move[1][1])
					return true;
			}
		}
		//---------------------------
		else if (fig->getPosy() + 1 < 8 )
		{
			if (move[1][0] == fig->getPosx()  && (fig->getPosy() + 1) == move[1][1] && board->getField(fig->getPosx(), fig->getPosy() + 1) == 0)
				return true;
			if (isupper(fig->getTyp()) && board->getField(fig->getPosx(), fig->getPosy() + 1) < 0)
			{
				if (move[1][0] == fig->getPosx() && (fig->getPosy() + 1) == move[1][1])
					return true;
			}
			else if (!isupper(fig->getTyp()) && board->getField(fig->getPosx(), fig->getPosy() + 1) > 0)
			{
				if (move[1][0] == fig->getPosx() && (fig->getPosy() + 1) == move[1][1])
					return true;
			}
		}
		else if (fig->getPosy() - 1 > -1)
		{
			if (move[1][0] == fig->getPosx() && (fig->getPosy() - 1) == move[1][1] && board->getField(fig->getPosx(), fig->getPosy() - 1) == 0)
				return true;
			if (isupper(fig->getTyp()) && board->getField(fig->getPosx(), fig->getPosy() - 1) < 0)
			{
				if (move[1][0] == fig->getPosx() && (fig->getPosy() - 1) == move[1][1])
					return true;
			}
			else if (!isupper(fig->getTyp()) && board->getField(fig->getPosx(), fig->getPosy() - 1) > 0)
			{
				if (move[1][0] == fig->getPosx() && (fig->getPosy() - 1) == move[1][1])
					return true;
			}
		}
		else if (fig->getPosx() - 1 > -1 )
		{
			if ((move[1][0] == fig->getPosx() - 1) && (fig->getPosy() - 1) == move[1][1] && board->getField(fig->getPosx() - 1, fig->getPosy()) == 0)
				return true;
			if (isupper(fig->getTyp()) && board->getField(fig->getPosx() - 1, fig->getPosy()) < 0)
			{
				if ((move[1][0] == fig->getPosx() - 1) && (fig->getPosy() - 1) == move[1][1])
					return true;
			}
			else if (!isupper(fig->getTyp()) && board->getField(fig->getPosx() - 1, fig->getPosy()) > 0)
			{
				if ((move[1][0] == fig->getPosx() - 1) && (fig->getPosy() - 1) == move[1][1])
					return true;
			}
		}
		else if (fig->getPosx() + 1 < 8 )
		{
			if ((move[1][0] == fig->getPosx() + 1) && (fig->getPosy() + 1) == move[1][1] && board->getField(fig->getPosx() + 1, fig->getPosy()) == 0)
				return true;
			if (isupper(fig->getTyp()) && board->getField(fig->getPosx() + 1, fig->getPosy()) < 0)
			{
				if ((move[1][0] == fig->getPosx() + 1) && (fig->getPosy() + 1) == move[1][1])
					return true;
			}
			else if (!isupper(fig->getTyp()) && board->getField(fig->getPosx() + 1, fig->getPosy()) > 0)
			{
				if ((move[1][0] == fig->getPosx() + 1) && (fig->getPosy() + 1) == move[1][1])
					return true;
			}
		}
		else if (board->getCastlKingside(true) && fig->getPosx() == 0 && board->getField(fig->getPosx() + 1, fig->getPosy()) == 0 && board->getField(fig->getPosx() + 2, fig->getPosy()) == 0)
		{
			if (!this->testRochadeAngriffKS(board, fig))
			{
				if ((move[1][0] == fig->getPosx() + 2) && fig->getPosy() == move[1][1])
					return true;
			}
		}
		else if (board->getCastlQueenside(true) && fig->getPosx() == 0 && board->getField(fig->getPosx() - 1, fig->getPosy()) == 0 && board->getField(fig->getPosx() - 2, fig->getPosy()) == 0 && board->getField(fig->getPosx() - 3, fig->getPosy()) == 0)
		{
			if (!this->testRochadeAngriffQS(board, fig))
			{
				if ((move[1][0] == fig->getPosx() - 2) && fig->getPosy() == move[1][1])
					return true;
			}
		}
		else if (board->getCastlKingside(false) && fig->getPosx() == 7 && board->getField(fig->getPosx() + 1, fig->getPosy()) == 0 && board->getField(fig->getPosx() + 2, fig->getPosy()) == 0)
		{
			if (!this->testRochadeAngriffKS(board, fig))
			{
				if ((move[1][0] == fig->getPosx() + 2) && fig->getPosy() == move[1][1])
					return true;
			}
		}
		else if (board->getCastlQueenside(false) && fig->getPosx() == 7 && board->getField(fig->getPosx() - 1, fig->getPosy()) == 0 && board->getField(fig->getPosx() - 2, fig->getPosy()) == 0 && board->getField(fig->getPosx() - 3, fig->getPosy()) == 0)
		{
			if (!this->testRochadeAngriffQS(board, fig))
			{
				if ((move[1][0] == fig->getPosx() - 2) && fig->getPosy() == move[1][1])
					return true;
			}
		}
	}
	return nullptr;
}

bool Movemennt::proveMove(Hashbrett * hash, std::string move)
{
	int **movemade;
	char promo = ' ';
	if (move.length() > 4)
	{
		promo = move.at(4);
	}
	movemade = conv->getMoveIntfromChar(move);
	Figur * fig;
	int z = hash->getBoard()->getField(movemade[0][0], movemade[0][1]);
	if (z == 0)
		return false;
	if (z > 0)
	{
		fig = hash->getBoard()->touchFigur(z - 1, true);
	}
	else
	{
		fig = hash->getBoard()->touchFigur(-(z + 1), false);
	}
	return proveMove(movemade, fig, hash->getBoard());
}

bool Movemennt::makeMove(Hashbrett * hash, std::string move)
{
	int **movemade;
	char promo = ' ';
	if (move.length() > 4)
	{
		promo = move.at(4);
	}
	movemade = conv->getMoveIntfromChar(move);
	Figur * fig;
	int z = hash->getBoard()->getField(movemade[0][0], movemade[0][1]);
	if (z == 0)
	return false;
	if (z > 0)
	{
		fig = hash->getBoard()->touchFigur(z - 1,true);
	}
	else
	{
		fig = hash->getBoard()->touchFigur(-(z + 1),false);
	}
	this->makeMove(fig,movemade[1][0], movemade[1][1],promo, hash);
	return true;
}
bool Movemennt::makeMove(Figur *fig, int nachx,int nachy, char promo, Hashbrett * hash)
{
	Brett * board = hash->getBoard();
	Figur *figk;
	hash->setZug(conv->getStringfromInt(fig->getPosx(), fig->getPosy(), nachx, nachy,promo));
	int wert;
	bool trade = false, rochKS = false, rochQS = false;
	int **movemade;
	movemade = new int*[2];
	movemade[0] = new int[2];
	movemade[1] = new int[2];
	movemade[0][0] = fig->getPosx();
	movemade[0][1] = fig->getPosy();
	movemade[1][0] = nachx;
	movemade[1][1] = nachy;
	//Figur *fig;
	int z,w=0;
	/*z = board->getField(vonx, vony);
	if (z == 0)
		return false;
	if (z > 0)
	{
		fig = board->touchFigur(z - 1,true);
	}
	else
	{
		fig = board->touchFigur(-(z + 1),false);
	}*/
	// (this->proveMove(movemade, fig, board))
	{
		if (fig->getTyp() == 'p' &&  promo != ' ' && fig->getPosy() == 1)
		{
			wert = conv->getWert(promo);
			if (wert > 0 && wert < 10)
			{
				wert = conv->getWert(fig->getTyp()) - wert;
				board->setFigurenwert(board->getFigurenwert() - wert);
				fig->setTyp(promo);
			}
		}
		if (fig->getTyp() == 'P' &&  promo != ' ' && fig->getPosy() == 6)
		{
			wert = conv->getWert(promo);
			if (wert > 0 && wert < 10)
			{
				wert = conv->getWert(fig->getTyp()) - wert;
				board->setFigurenwert(board->getFigurenwert() + wert);
				fig->setTyp(promo);
			}
		}
		//Figurenwert ändern
		//if (movemade[1][0] > -1 && movemade[1][0] < 8 && movemade[1][1] > -1 && movemade[1][1] < 8)
		{
			z = board->getField(movemade[1][0], movemade[1][1]);
			if (z != 0)
			{
				if (z > 0)
				{
					if (board->touchFigur(z - 1, true) != NULL)
						w = conv->getWert(board->touchFigur(z - 1, true)->getTyp());
					else
						w = 0;
					board->setFigurenwert(board->getFigurenwert() - w);
				}
				else if (z < 0)
				{
					if (board->touchFigur(z - 1, true) != NULL)
						w = conv->getWert(board->touchFigur(-(z + 1), false)->getTyp());
					else
						w = 0;
					board->setFigurenwert(board->getFigurenwert() + w);
				}
				board->deleteFigure(z);
			}
			board->makeMove(fig, movemade[1][0], movemade[1][1]);
			// König sonderzüge
			if ((toupper(fig->getTyp())) == 'K'  && movemade[0][0] == 4 && movemade[1][0] == 6)
			{
				z = board->getField(movemade[0][0], 7);
				if (z > 0)
				{
					figk = board->touchFigur(z - 1, true);
					board->makeMove(figk, movemade[0][0], 5);
				}
				else if (z < 0)
				{
					figk = board->touchFigur(-(z + 1), false);
					board->makeMove(figk, movemade[0][0], 5);
				}
			}
			if ((toupper(fig->getTyp())) == 'K'  && movemade[0][0] == 4 && movemade[1][0] == 2)
			{
				z = board->getField(movemade[0][0], 0);
				if (z > 0)
				{
					figk = board->touchFigur(z - 1, true);
					board->makeMove(figk, movemade[0][0], 3);
				}
				else if (z < 0)
				{
					figk = board->touchFigur(-(z + 1), false);
					board->makeMove(figk, movemade[0][0], 3);
				}
			}
			if (!board->getWhitetoMove())
				board->setZugNr(board->getZugNr() + 1);
			board->setWhitetoMove(!board->getWhitetoMove());
			return true;
		}
	}
	return false;
}

bool Movemennt::testRochadeAngriffKS(Brett * board, Figur * fig)
{
	return false;
}

bool Movemennt::testRochadeAngriffQS(Brett * board, Figur * fig)
{
	return false;
}

Brett * Movemennt::copyBoard(Brett * board)
{
	Brett *copy = new Brett();
	for (int i = 0; i < board->getFigurmax(true); i++)
	{
		copy->addnewFigur(true);
		copy->touchFigur(i, true)->setPosx(board->touchFigur(i, true)->getPosx());
		copy->touchFigur(i, true)->setPosy(board->touchFigur(i, true)->getPosy());
		copy->touchFigur(i, true)->setTyp(board->touchFigur(i, true)->getTyp());
	}
	for (int i = 0; i < board->getFigurmax(false); i++)
	{
		copy->addnewFigur(false);
		copy->touchFigur(i, false)->setPosx(board->touchFigur(i, false)->getPosx());
		copy->touchFigur(i, false)->setPosy(board->touchFigur(i, false)->getPosy());
		copy->touchFigur(i, false)->setTyp(board->touchFigur(i, false)->getTyp());
	}
	copy->setBewertung(board->getBewertung());
	copy->setCastlKingside(true, board->getCastlKingside(true));
	copy->setCastlKingside(false, board->getCastlKingside(false));
	copy->setCastlQueenside(true, board->getCastlQueenside(true));
	copy->setCastlQueenside(false, board->getCastlQueenside(false));
	copy->setEnPassant(board->getEnPassant());
	copy->setFigurenwert(board->getFigurenwert());
	copy->setHalbzug(board->getHalbzug());
	copy->setKingPos(true, board->getKingPos(true, true), board->getKingPos(true, false));
	copy->setKingPos(false, board->getKingPos(false, true), board->getKingPos(false, false));
	copy->setWhitetoMove(board->getWhitetoMove());
	copy->setZugNr(board->getZugNr());
	return copy;
}

void Movemennt::printHash(Hashbrett * hbrett)
{
	Hashbrett *hb,*hbs,*hbst;
	std::cout << "-------\n";
	std::cout << hbrett->getZug() << " Mom\n";
	hb = hbrett->getChild(true);
	if (hb)
	{
		while (hb = hb->getChild(true))
		{
			std::cout << hb->getZug() << " white\n";
			if (hb->getChild(false))
			{
				hbs = hb->getChild(false);
				while (hbs->getChild(false))
				{
					std::cout << "          "+hbs->getZug() << " black\n";
					if (hbst->getChild(true))
					{
						hbst = hbs->getChild(false);
						std::cout << "            " << hbst->getZug() << " white\n";
						while (hbst->getChild(false))
						{
							std::cout << "                   " + hbst->getZug() << " black\n";
							hbst = hbst->getChild(false);
						}
					}
					hbs = hbs->getChild(false);
				}
			}
		}
	}
	if (hbrett->getChild(false))
	{
		hbs = hbrett->getChild(false);
		while (hbs->getChild(false))
		{
			std::cout << "                   " + hbs->getZug() << " black\n";
			hbs = hbs->getChild(false);
		}
	}	std::cout << "\n--------------------\n";
}

Hashbrett * Movemennt::rekonfHash(Hashbrett * oldhash, std::string fenstring)
{
	// Begin Work
	Hashbrett *aktuell, *loschenA, *loschenB,*tree;
	aktuell = oldhash;
	int runde = 0;
	bool white = !aktuell->getBoard()->getWhitetoMove();
	while (aktuell->getChild(!white) != NULL)
	{
		std::cout << fenstring << " " << aktuell->getFenString() << aktuell->getZug() << "\n";
		runde++;
		if (aktuell->getFenString().compare(fenstring) == 0)
		{
			std::cout << "found in" << runde <<  "\n";
			
			tree = aktuell;
			tree->setChild(NULL, !white);
			//tree=aktuell->getChild(!white);
			//loschenB = aktuell->getChild(!white);
			//tree->setChild(NULL, !white);
			//delhash->delHash(loschenB);
			return tree;
		}
		//loschenA = aktuell;
		aktuell = aktuell->getChild(!white);
		//loschenA->setChild(NULL, !white);
		//delhash->delHash(loschenA);
	}
	if (aktuell->getFenString().compare(fenstring) == 0)
	{
		std::cout << "found in L" << runde << "\n";
		tree = aktuell;
		//tree=aktuell->getChild(!white);
		//loschenB = aktuell->getChild(!white);
		//tree->setChild(NULL, !white);
		//delhash->delHash(loschenB);
		return tree;
	}
	std::cout << "not found in" << runde << "\n";
	//delhash->delHash(aktuell);
	return NULL;
}

void Movemennt::showHash(Hashbrett * boards)
{
	if (boards)
	{
		if (boards->getChild(boards->getBoard()->getWhitetoMove()) != NULL)
		{
			std::cout << boards->getZug() << " ";
			showHash(boards->getChild(boards->getBoard()->getWhitetoMove()));
		}
		else
			std::cout << "\n";
		if (boards->getChild(!boards->getBoard()->getWhitetoMove()) != NULL)
		{
			std::cout << boards->getZug() << " ";
			showHash(boards->getChild(!boards->getBoard()->getWhitetoMove()));
			//if (boards->getChild(false) != NULL)
			//	traversSearch(boards->getChild(false), move, tiefe, godepth, zug, wertzug, bestmove, ponder, whitesearch);
		}
		else
			std::cout << "\n";
		/*if (boards->getChild(true) == NULL && boards->getChild(false) == NULL)
		{
			godepth = 2;
			tiefe = 0;
			this->deepSearch(boards, move, tiefe, godepth, zug, wertzug, bestmove, ponder, whitesearch);
		}*/
	}
}


