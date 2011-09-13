%{
        /* From Aho, Seti, Ullman, fig. 4.59, p. 266. */

#include <stdio.h>
#include <string.h>
#include "LexCalc.h"

double get_identifier( calc_type name );
void set_identifier( calc_type name, double v );

double get_identifier_arr( calc_type name, double ind );
void set_identifier_arr( calc_type name, double v, double ind );
double find_index_arr( calc_type name, double vx );

int textlock_identifier( char* name );
int textfind_identifier( char* name );
int stylelock_identifier( char* name );
void print_identifier( char* name );
void print_time_of( double t );
void print_pos_of( double t );
void print_hex_of( double t );
void print_char_of( double t );
void print_color_of( double t );
void print_tval_of( double t );

void loop_file( char* name, double t, double t2 );

void rand_ins( char* name, double t );
double get_rand();

void fontmatchuse( char* name );
void set_flag( char* name );

double get_pixbuf( double vx, double vy );

void KillThisLoop();

void TextindexStore( double ind );
void TextindexGet( double ind );

void ColoringOff( double col, double ind );

void PrintBorderline( double a1, double a2 );

extern FILE *foutt;

%}

%token NUMBER
%token IDENTIFIER
%token STRING
%token EXIT
%token TIMEOF TVALOF POSOF HEXOF COLOROF CHAROF
%token INSERT TEXTLOCK TEXTFIND STYLELOCK
%token FONTMATCHUSE SETFLAG
%token RANDOM RANDOMINS
%token LOOPFILE LOOPFILE2

%token MIN
%token MAX
%token SIGN
%token SIN COS INTROUND
%token LOWKILL SWITCH
%token TEXTFINDBOOL PIXBUF
%token TRUNC
%token KILLTHISLOOP

%token COLORING_OFF

%token TEXTINDEX STORE GET
%token FINDINDEX

%token PRINTS PRINTV

%token BORDERLINE

%left '+' '-'
%left '*' '/'
%right '^'
%right IDENTIFIER STRING
%right UMINUS

%%
lines:        lines '\n'
        |       lines expr '\n'         { print_tval_of( $2.value );/*fprintf( foutt, "%.12g", $2.value) */}

        |       lines TEXTINDEX STORE '(' expr ')' '\n'         { TextindexStore( $5.value ); }
        |       lines TEXTINDEX GET '(' expr ')' '\n'         { TextindexGet( $5.value ); }

        |       lines PRINTS STRING '\n'         { printf( "%s", $3.name ); }
        |       lines PRINTV expr '\n'         { printf( "%f", $3.value ); }

        |       lines COLORING_OFF '(' expr ',' expr ')' '\n'         { ColoringOff( $4.value, $6.value );  }

        |       lines BORDERLINE '(' expr ',' expr ')' '\n'         { PrintBorderline( $4.value, $6.value );  }

        |       lines KILLTHISLOOP '\n'    { KillThisLoop(); }
        |       lines LOWKILL '(' expr ',' expr ')' '\n'    { if( $4.value<$6.value ){printf( "lowkill yes %f<%f\n",$4.value,$6.value);return EXIT_SUCCESS;}else printf( "lowkill no %f>=%f\n",$4.value,$6.value); }
        |       lines IDENTIFIER '=' expr '\n'         { set_identifier( $2, $4.value ); }
        |       lines IDENTIFIER '[' expr ']' '=' expr '\n'         { set_identifier_arr( $2, $7.value, $4.value ); }
        |       lines FONTMATCHUSE STRING '\n'         { fontmatchuse( $3.name ); }
        |       lines SETFLAG STRING '\n'         { set_flag( $3.name ); }
        |       lines TIMEOF expr '\n'         { print_time_of( $3.value ); }
        |       lines POSOF expr '\n'         { print_pos_of( $3.value ); }
        |       lines HEXOF expr '\n'         { print_hex_of( $3.value ); }
        |       lines CHAROF expr '\n'         { print_char_of( $3.value ); }
        |       lines COLOROF expr '\n'         { print_color_of( $3.value ); }
        |       lines TVALOF expr '\n'         { print_tval_of( $3.value ); }
        |       lines INSERT IDENTIFIER '\n'         { print_identifier( $3.name ); }
        |       lines RANDOMINS STRING expr '\n'         { rand_ins( $3.name, $4.value ); }
        |       lines LOOPFILE STRING expr '\n'         { loop_file( $3.name, $4.value, 1 ); }
        |       lines LOOPFILE2 STRING '(' expr ',' expr ')' '\n'         { loop_file( $3.name, $5.value, $7.value ); }
        |       lines TEXTLOCK IDENTIFIER '\n'         { if( !textlock_identifier( $3.name ) )return EXIT_SUCCESS; }
        |       lines STYLELOCK IDENTIFIER '\n'         { if( !stylelock_identifier( $3.name ) )return EXIT_SUCCESS; }
        |       lines TEXTFIND IDENTIFIER '\n'         { if( !textfind_identifier( $3.name ) )return EXIT_SUCCESS; }
        |       lines '!' TEXTFIND IDENTIFIER '\n'         { if( textfind_identifier( $4.name ) )return EXIT_SUCCESS; }
        |       lines STRING '\n'         { fprintf( foutt, "%s", $2.name) }
        |       lines EXIT '\n'         { return EXIT_SUCCESS; }
        |       /* empty */
        |       error '\n'              { printf("\n error \n"); yyerrok; }
        ;

expr:   
				expr '+' expr   { $$.value = $1.value + $3.value }
        |       expr '-' expr   { $$.value = $1.value - $3.value }
        |       expr '*' expr   { $$.value = $1.value * $3.value }
        |       expr '/' expr   { $$.value = $1.value / $3.value }
        |       expr '^' expr   { $$.value = pow($1.value, $3.value) }
        |       '(' expr ')'    { $$.value = $2.value }
        |       SIN '(' expr ')'    { $$.value = sin($3.value); }
        |       COS '(' expr ')'    { $$.value = cos($3.value); }
        |       INTROUND '(' expr ',' expr ')'    { $$.value = (double)(((int)($3.value+0.5)) % ((int)($5.value+0.5))); }
        |       TRUNC '(' expr ')'    { $$.value = floor($3.value); }
        |       SIGN '(' expr ')'    { $$.value = $3.value/(abs($3.value)+0.0001); }
        |       MIN '(' expr ',' expr ')'    { if( $3.value<$5.value )$$.value = $3.value; else $$.value = $5.value; }
        |       MAX '(' expr ',' expr ')'    { if( $3.value>$5.value )$$.value = $3.value; else $$.value = $5.value; }
        |       SWITCH '(' expr ',' expr ',' expr ')'    { if( $3.value<0.5 )$$.value = $5.value; else $$.value = $7.value; }
        |       PIXBUF '(' expr ',' expr ')'    { $$.value = get_pixbuf( $3.value, $5.value ); }
        |       '-' expr  %prec UMINUS { $$.value = -$2.value }
        |       IDENTIFIER { $$.value = get_identifier( $1 ); }
        |       IDENTIFIER '[' expr ']' { $$.value = get_identifier_arr( $1, $3.value ); }
        |       FINDINDEX '(' IDENTIFIER ',' expr ')' { $$.value = find_index_arr( $3, $5.value ); }
        |       TEXTFINDBOOL IDENTIFIER { $$.value = textfind_identifier( $2.name ); }
        |       NUMBER
        ;

%%
