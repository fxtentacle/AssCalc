%{

#include "LexCalc.h"

#define yylval calc_lval

#include "LexCalc_tab.h"



%}

%option noyywrap

digit           [0-9]
number          {digit}+\.?|{digit}*\.{digit}+
identifier  [a-zA-Z_0-9.@]+
string  (\")[^\"]+(\")

%%

[ ]                      { /* Skip blanks. */ }
{number}         { sscanf(yytext, "%lf", &yylval.value); return NUMBER; }
"exit"           { return EXIT; }
"pos of"           { return POSOF; }
"hex of"           { return HEXOF; }
"char of"           { return CHAROF; }
"color of"           { return COLOROF; }
"time of"           { return TIMEOF; }
"tval of"           { return TVALOF; }
"fontmatch use"           { return FONTMATCHUSE; }
"MIN"           { return MIN; }
"MAX"           { return MAX; }
"INTROUND"           { return INTROUND; }
"SIN"           { return SIN; }
"COS"           { return COS; }
"SIGN"           { return SIGN; }
"TRUNC"           { return TRUNC; }
"LOWKILL"           { return LOWKILL; }
"SWITCH"           { return SWITCH; }
"KILLTHISLOOP"           { return KILLTHISLOOP; }
"pixbuf"           { return PIXBUF; }
"textfind"           { return TEXTFIND; }
"textfindbool"           { return TEXTFINDBOOL; }
"textlock"           { return TEXTLOCK; }
"stylelock"           { return STYLELOCK; }
"insert"			{ return INSERT; }
"insert random"		{ return RANDOMINS; }
"loopfile"			{ return LOOPFILE; }
"loopfile2"			{ return LOOPFILE2; }
"set flag"			{ return SETFLAG; }

"TEXTINDEX"           { return TEXTINDEX; }
"STORE"           { return STORE; }
"GET"           { return GET; }

"COLORING_OFF"           { return COLORING_OFF ; }

"PRINTS"           { return PRINTS; }
"PRINTV"           { return PRINTV; }

"FINDINDEX"           { return FINDINDEX; }

"BORDERLINE"           { return BORDERLINE; }

{identifier} { strcpy( yylval.name, yytext ); return IDENTIFIER; }
{string} { strcpy( yylval.name, yytext+1 ); yylval.name[strlen(yylval.name)-1]=0; return STRING; }
\n|.             { return yytext[0]; }

%%

