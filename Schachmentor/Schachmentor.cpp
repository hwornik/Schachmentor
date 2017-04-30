// Schachmentor.cpp : Definiert den Einstiegspunkt für die Konsolenanwendung.
//

#include "stdafx.h"
#include "Compute.h"

int main()
{
	Compute *komm;
	komm = new Compute();
	komm->start();
    return 0;
}
