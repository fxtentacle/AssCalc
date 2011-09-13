%{

#include "LexCalc.h"

#define yylval src_lval

#include "srcread_tab.h"
/*

[ ]                      {   }// Skip blanks.   Dialogue: 1,0:00:38.53,0:00:41.62,OpKHM,OP,0000,0000,0000,,bla
{number}         { sscanf(yytext, "%lf", &yylval.value); return NUMBER; }

*/

extern int bMayBeTextWC;

%}

%option noyywrap

text	[^\{\}\n]+
text_sure	\§[^§]+\§
digit           [0-9]
number          {digit}+\.?|{digit}*\.{digit}+

%%



\{\\[Kkf]+{number}\}		{ yytext+=3; if( yytext[0]<'0' || yytext[0]>'9' )yytext++; sscanf(yytext, "%lf", &yylval.value); yylval.value*=0.01; return KTHINGY; }

{text_sure}			{ strcpy( yylval.name, yytext+1 );yylval.name[strlen(yylval.name)-1]=0;return TEXT; }
{text}			{ strcpy( yylval.name, yytext );return TEXT; }
\{{text}\}			{ strcpy( yylval.name, yytext );return COMMENT; }

\n|.             {  return yytext[0]; }


%%
