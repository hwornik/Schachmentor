#pragma once

static const char NUMBERTOCHAR[8] = { 'a','b','c','d','e','f','g','h' };

#define STARTFEN "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"


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
#define SHOWFEN 12
#define WAITING -1
#define RESETGAME 13
#define SETBOARDWITHFEN 90
#define MAKEMOVES	91
#define MAKEMOVE 80
#define STARTCOMPUTING 10

//interne Befehle für Compute
#define NAKED 0
#define UCI 1
#define UCISTARTUP 11
#define WHITE 0
#define BLACK 1
#define VERSION_STRING "1.1"
#define COMPILE_STRING " compiled 23.03.2016"

// Werte für Spiel
#define MAX_THREADS 3
#define BUF_SIZE 255

//Anweisung für Roched in zugarray auf pos 3
#define ROCHADE 100

//deppsearch const
#define THREADCOUNT 12