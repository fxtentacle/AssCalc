%{
        /* From Aho, Seti, Ullman, fig. 4.59, p. 266. */

#include "LexCalc.h"

void DoIt1( double t1, double t2 );
void DoIt2( double t1 );
void DoIt3( char *txt );
void CheckComment( char *txt );

int bMayBeTextWC=0;



%}

%token TEXT
%token NUMBER

%token KTHINGY

%token COMMENT


%%
//Dialogue: 8,0:00:34.12,0:00:38.13,OpKHM,OP,0000,0000,0000,,

DIALOGUE_TEXT:
		 TEXT	{ DoIt3( $1.name ); }	
		| KTHINGY2 DIALOGUE_TEXT
		| DIALOGUE_TEXT DIALOGUE_TEXT
		| COMMENT  { CheckComment( $1.name ); }	 
		| /* empty */
		;

KTHINGY2:
		KTHINGY { DoIt2( $1.value ); }	
		;


%%
