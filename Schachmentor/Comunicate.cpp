/*
		Liefert alle Funktionen zur Kommunikation mit der GUI
*/

#include "stdafx.h"
#include "Comunicate.h"


Comunicate::Comunicate()
{
	inputmethod = 0;
 	unsigned long dw;
	hstdin = GetStdHandle(STD_INPUT_HANDLE);
	pipe = !GetConsoleMode(hstdin, &dw);
	ponder = false;
	if (!pipe) {
		SetConsoleMode(hstdin, dw&~(ENABLE_MOUSE_INPUT | ENABLE_WINDOW_INPUT));
		FlushConsoleInputBuffer(hstdin);
	}
	else {
		setvbuf(stdin, NULL, _IONBF, 0);
		setvbuf(stdout, NULL, _IONBF, 0);
	}
}
/*
	Prüft ob im Inputbuffer eine eingabe vorliegt
*/
int Comunicate::input()
{
		unsigned long dw = 0;

		if (inputmethod == 0) return 1;

		//if (stdin->_cnt > 0) return 1; //Standartinput ?????? ausgeschalten...

		if (pipe) {
			if (!PeekNamedPipe(hstdin, 0, 0, 0, &dw, 0)) return 1;
			return dw;
		}
		else {
			GetNumberOfConsoleInputEvents(hstdin, &dw);
			if (dw > 1) inputmethod = 0;
		}

		return 0;
}

Comunicate::~Comunicate()
{
}
