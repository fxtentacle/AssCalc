
/*  A Bison parser, made from lexcalc.y with Bison version GNU Bison version 1.24
  */

#define YYBISON 1  /* Identify Bison output.  */

#define yyparse calc_parse
#define yylex calc_lex
#define yyerror calc_error
#define yylval calc_lval
#define yychar calc_char
#define yydebug calc_debug
#define yynerrs calc_nerrs
#define	NUMBER	258
#define	IDENTIFIER	259
#define	STRING	260
#define	EXIT	261
#define	TIMEOF	262
#define	TVALOF	263
#define	POSOF	264
#define	HEXOF	265
#define	COLOROF	266
#define	CHAROF	267
#define	INSERT	268
#define	TEXTLOCK	269
#define	TEXTFIND	270
#define	STYLELOCK	271
#define	FONTMATCHUSE	272
#define	SETFLAG	273
#define	RANDOM	274
#define	RANDOMINS	275
#define	LOOPFILE	276
#define	LOOPFILE2	277
#define	MIN	278
#define	MAX	279
#define	SIGN	280
#define	SIN	281
#define	COS	282
#define	INTROUND	283
#define	LOWKILL	284
#define	SWITCH	285
#define	TEXTFINDBOOL	286
#define	PIXBUF	287
#define	TRUNC	288
#define	KILLTHISLOOP	289
#define	COLORING_OFF	290
#define	TEXTINDEX	291
#define	STORE	292
#define	GET	293
#define	FINDINDEX	294
#define	PRINTS	295
#define	PRINTV	296
#define	BORDERLINE	297
#define	UMINUS	298

#line 1 "lexcalc.y"

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


#ifndef YYLTYPE
typedef
  struct yyltype
    {
      int timestamp;
      int first_line;
      int first_column;
      int last_line;
      int last_column;
      char *text;
   }
  yyltype;

#define YYLTYPE yyltype
#endif

#ifndef YYSTYPE
#define YYSTYPE int
#endif
#include <stdio.h>

#ifndef __cplusplus
#ifndef __STDC__
#define const
#endif
#endif



#define	YYFINAL		194
#define	YYFLAG		-32768
#define	YYNTBASE	57

#define YYTRANSLATE(x) ((unsigned)(x) <= 298 ? yytranslate[x] : 59)

static const char yytranslate[] = {     0,
     2,     2,     2,     2,     2,     2,     2,     2,     2,    49,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,    56,     2,     2,     2,     2,     2,     2,    50,
    51,    45,    43,    52,    44,     2,    46,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
    53,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
    54,     2,    55,    47,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     1,     2,     3,     4,     5,
     6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
    16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
    26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
    36,    37,    38,    39,    40,    41,    42,    48
};

#if YYDEBUG != 0
static const short yyprhs[] = {     0,
     0,     3,     7,    15,    23,    28,    33,    42,    51,    55,
    64,    70,    79,    84,    89,    94,    99,   104,   109,   114,
   119,   124,   130,   136,   146,   151,   156,   161,   167,   171,
   175,   176,   179,   183,   187,   191,   195,   199,   203,   208,
   213,   220,   225,   230,   237,   244,   253,   260,   263,   265,
   270,   277,   280
};

static const short yyrhs[] = {    57,
    49,     0,    57,    58,    49,     0,    57,    36,    37,    50,
    58,    51,    49,     0,    57,    36,    38,    50,    58,    51,
    49,     0,    57,    40,     5,    49,     0,    57,    41,    58,
    49,     0,    57,    35,    50,    58,    52,    58,    51,    49,
     0,    57,    42,    50,    58,    52,    58,    51,    49,     0,
    57,    34,    49,     0,    57,    29,    50,    58,    52,    58,
    51,    49,     0,    57,     4,    53,    58,    49,     0,    57,
     4,    54,    58,    55,    53,    58,    49,     0,    57,    17,
     5,    49,     0,    57,    18,     5,    49,     0,    57,     7,
    58,    49,     0,    57,     9,    58,    49,     0,    57,    10,
    58,    49,     0,    57,    12,    58,    49,     0,    57,    11,
    58,    49,     0,    57,     8,    58,    49,     0,    57,    13,
     4,    49,     0,    57,    20,     5,    58,    49,     0,    57,
    21,     5,    58,    49,     0,    57,    22,     5,    50,    58,
    52,    58,    51,    49,     0,    57,    14,     4,    49,     0,
    57,    16,     4,    49,     0,    57,    15,     4,    49,     0,
    57,    56,    15,     4,    49,     0,    57,     5,    49,     0,
    57,     6,    49,     0,     0,     1,    49,     0,    58,    43,
    58,     0,    58,    44,    58,     0,    58,    45,    58,     0,
    58,    46,    58,     0,    58,    47,    58,     0,    50,    58,
    51,     0,    26,    50,    58,    51,     0,    27,    50,    58,
    51,     0,    28,    50,    58,    52,    58,    51,     0,    33,
    50,    58,    51,     0,    25,    50,    58,    51,     0,    23,
    50,    58,    52,    58,    51,     0,    24,    50,    58,    52,
    58,    51,     0,    30,    50,    58,    52,    58,    52,    58,
    51,     0,    32,    50,    58,    52,    58,    51,     0,    44,
    58,     0,     4,     0,     4,    54,    58,    55,     0,    39,
    50,     4,    52,    58,    51,     0,    31,     4,     0,     3,
     0
};

#endif

#if YYDEBUG != 0
static const short yyrline[] = { 0,
    84,    85,    87,    88,    90,    91,    93,    95,    97,    98,
    99,   100,   101,   102,   103,   104,   105,   106,   107,   108,
   109,   110,   111,   112,   113,   114,   115,   116,   117,   118,
   119,   120,   123,   125,   126,   127,   128,   129,   130,   131,
   132,   133,   134,   135,   136,   137,   138,   139,   140,   141,
   142,   143,   144
};

static const char * const yytname[] = {   "$","error","$undefined.","NUMBER",
"IDENTIFIER","STRING","EXIT","TIMEOF","TVALOF","POSOF","HEXOF","COLOROF","CHAROF",
"INSERT","TEXTLOCK","TEXTFIND","STYLELOCK","FONTMATCHUSE","SETFLAG","RANDOM",
"RANDOMINS","LOOPFILE","LOOPFILE2","MIN","MAX","SIGN","SIN","COS","INTROUND",
"LOWKILL","SWITCH","TEXTFINDBOOL","PIXBUF","TRUNC","KILLTHISLOOP","COLORING_OFF",
"TEXTINDEX","STORE","GET","FINDINDEX","PRINTS","PRINTV","BORDERLINE","'+'","'-'",
"'*'","'/'","'^'","UMINUS","'\\n'","'('","')'","','","'='","'['","']'","'!'",
"lines","expr",""
};
#endif

static const short yyr1[] = {     0,
    57,    57,    57,    57,    57,    57,    57,    57,    57,    57,
    57,    57,    57,    57,    57,    57,    57,    57,    57,    57,
    57,    57,    57,    57,    57,    57,    57,    57,    57,    57,
    57,    57,    58,    58,    58,    58,    58,    58,    58,    58,
    58,    58,    58,    58,    58,    58,    58,    58,    58,    58,
    58,    58,    58
};

static const short yyr2[] = {     0,
     2,     3,     7,     7,     4,     4,     8,     8,     3,     8,
     5,     8,     4,     4,     4,     4,     4,     4,     4,     4,
     4,     5,     5,     9,     4,     4,     4,     5,     3,     3,
     0,     2,     3,     3,     3,     3,     3,     3,     4,     4,
     6,     4,     4,     6,     6,     8,     6,     2,     1,     4,
     6,     2,     1
};

static const short yydefact[] = {     0,
     0,     0,    32,    53,    49,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     1,     0,     0,     0,     0,     0,    29,    30,    49,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,    52,     0,     0,     9,     0,     0,     0,
     0,     0,     0,     0,    48,     0,     0,     0,     0,     0,
     0,     0,     2,     0,     0,     0,    15,    20,    16,    17,
    19,    18,    21,    25,    27,    26,    13,    14,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     5,     6,     0,    38,     0,
    33,    34,    35,    36,    37,    11,    50,     0,    22,    23,
     0,     0,     0,    43,    39,    40,     0,     0,     0,     0,
    42,     0,     0,     0,     0,     0,    28,     0,    50,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,    44,    45,    41,     0,     0,    47,     0,
     3,     4,    51,     0,    12,     0,    10,     0,     7,     8,
    24,    46,     0,     0
};

static const short yydefgoto[] = {     2,
    45
};

static const short yypact[] = {   168,
   -27,   222,-32768,-32768,   -17,   -25,   -19,    68,    68,    68,
    68,    68,    68,    28,    41,    42,    43,    45,    46,    47,
    48,    49,    -2,     7,    16,    19,    23,    24,    25,    27,
    74,    29,    35,    37,    39,   -21,    40,    82,    68,    52,
    68,-32768,    68,    89,   433,    68,    68,-32768,-32768,    51,
   440,   447,   454,   461,   468,   475,    57,    59,    60,    61,
    62,    64,    68,    68,    67,    68,    68,    68,    68,    68,
    68,    68,    68,-32768,    68,    68,-32768,    68,    75,    77,
    93,    65,   482,    68,-32768,   280,   120,    68,    68,    68,
    68,    68,-32768,   489,   -37,    68,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,   496,   503,
    68,   -18,    -3,   289,   298,   307,    76,    86,   110,   230,
   316,   240,    68,    68,    84,-32768,-32768,   250,-32768,    88,
   -26,   -26,    79,    79,    79,-32768,    90,   -32,-32768,-32768,
   260,    68,    68,-32768,-32768,-32768,    68,    68,    68,    68,
-32768,    68,   325,   334,    68,    68,-32768,    68,-32768,    68,
   343,   352,   361,   370,   270,   379,   388,    96,    97,   397,
   406,   510,   415,-32768,-32768,-32768,   100,    68,-32768,   102,
-32768,-32768,-32768,   109,-32768,   111,-32768,   424,-32768,-32768,
-32768,-32768,   159,-32768
};

static const short yypgoto[] = {-32768,
    -8
};


#define	YYLAST		559


static const short yytable[] = {    51,
    52,    53,    54,    55,    56,    88,    89,    90,    91,    92,
    88,    89,    90,    91,    92,    79,    80,   137,    90,    91,
    92,     3,   159,    48,    88,    89,    90,    91,    92,    49,
    83,    57,    85,   142,    86,    46,    47,    94,    95,    88,
    89,    90,    91,    92,    58,    59,    60,    66,   143,    61,
    62,    63,    64,    65,   109,   110,    67,   112,   113,   114,
   115,   116,   117,   118,   119,    68,   120,   121,    69,   122,
     4,    50,    70,    71,    72,   128,    73,    74,    75,   131,
   132,   133,   134,   135,    76,    77,    82,   138,    78,    81,
    23,    24,    25,    26,    27,    28,   125,    30,    31,    32,
    33,    84,   141,    87,    96,   103,    37,   104,   105,   106,
   107,    41,   108,   126,   153,   154,   111,    43,    88,    89,
    90,    91,    92,   130,   123,    92,   124,   147,    88,    89,
    90,    91,    92,   161,   162,   155,   157,   148,   163,   164,
   165,   166,   158,   167,   181,   182,   170,   171,   187,   172,
   189,   173,    88,    89,    90,    91,    92,   190,   194,   191,
     0,   149,     0,     0,     0,     0,     0,   -31,     1,   188,
   -31,   -31,   -31,   -31,   -31,   -31,   -31,   -31,   -31,   -31,
   -31,   -31,   -31,   -31,   -31,   -31,     0,   -31,   -31,   -31,
   -31,   -31,   -31,   -31,   -31,   -31,   -31,   -31,   -31,   -31,
   -31,   -31,   -31,   -31,     0,     0,   -31,   -31,   -31,   -31,
     0,   -31,     0,     0,     0,     0,   -31,   -31,     0,     0,
     0,   193,     0,   -31,     4,     5,     6,     7,     8,     9,
    10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
     0,    20,    21,    22,    23,    24,    25,    26,    27,    28,
    29,    30,    31,    32,    33,    34,    35,    36,     0,     0,
    37,    38,    39,    40,     0,    41,     0,     0,     0,     0,
    42,    43,    88,    89,    90,    91,    92,    44,     0,     0,
     0,   150,    88,    89,    90,    91,    92,     0,     0,     0,
     0,   152,    88,    89,    90,    91,    92,     0,     0,     0,
     0,   156,    88,    89,    90,    91,    92,     0,     0,     0,
     0,   160,    88,    89,    90,    91,    92,     0,     0,     0,
     0,   178,    88,    89,    90,    91,    92,     0,     0,     0,
   129,    88,    89,    90,    91,    92,     0,     0,     0,   144,
    88,    89,    90,    91,    92,     0,     0,     0,   145,    88,
    89,    90,    91,    92,     0,     0,     0,   146,    88,    89,
    90,    91,    92,     0,     0,     0,   151,    88,    89,    90,
    91,    92,     0,     0,     0,   168,    88,    89,    90,    91,
    92,     0,     0,     0,   169,    88,    89,    90,    91,    92,
     0,     0,     0,   174,    88,    89,    90,    91,    92,     0,
     0,     0,   175,    88,    89,    90,    91,    92,     0,     0,
     0,   176,    88,    89,    90,    91,    92,     0,     0,     0,
   177,    88,    89,    90,    91,    92,     0,     0,     0,   179,
    88,    89,    90,    91,    92,     0,     0,     0,   180,    88,
    89,    90,    91,    92,     0,     0,     0,   183,    88,    89,
    90,    91,    92,     0,     0,     0,   184,    88,    89,    90,
    91,    92,     0,     0,     0,   186,    88,    89,    90,    91,
    92,     0,     0,     0,   192,    88,    89,    90,    91,    92,
     0,    93,    88,    89,    90,    91,    92,     0,    97,    88,
    89,    90,    91,    92,     0,    98,    88,    89,    90,    91,
    92,     0,    99,    88,    89,    90,    91,    92,     0,   100,
    88,    89,    90,    91,    92,     0,   101,    88,    89,    90,
    91,    92,     0,   102,    88,    89,    90,    91,    92,     0,
   127,    88,    89,    90,    91,    92,     0,   136,    88,    89,
    90,    91,    92,     0,   139,    88,    89,    90,    91,    92,
     0,   140,    88,    89,    90,    91,    92,     0,   185
};

static const short yycheck[] = {     8,
     9,    10,    11,    12,    13,    43,    44,    45,    46,    47,
    43,    44,    45,    46,    47,    37,    38,    55,    45,    46,
    47,    49,    55,    49,    43,    44,    45,    46,    47,    49,
    39,     4,    41,    52,    43,    53,    54,    46,    47,    43,
    44,    45,    46,    47,     4,     4,     4,    50,    52,     5,
     5,     5,     5,     5,    63,    64,    50,    66,    67,    68,
    69,    70,    71,    72,    73,    50,    75,    76,    50,    78,
     3,     4,    50,    50,    50,    84,    50,     4,    50,    88,
    89,    90,    91,    92,    50,    49,     5,    96,    50,    50,
    23,    24,    25,    26,    27,    28,     4,    30,    31,    32,
    33,    50,   111,    15,    54,    49,    39,    49,    49,    49,
    49,    44,    49,    49,   123,   124,    50,    50,    43,    44,
    45,    46,    47,     4,    50,    47,    50,    52,    43,    44,
    45,    46,    47,   142,   143,    52,    49,    52,   147,   148,
   149,   150,    53,   152,    49,    49,   155,   156,    49,   158,
    49,   160,    43,    44,    45,    46,    47,    49,     0,    49,
    -1,    52,    -1,    -1,    -1,    -1,    -1,     0,     1,   178,
     3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
    13,    14,    15,    16,    17,    18,    -1,    20,    21,    22,
    23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
    33,    34,    35,    36,    -1,    -1,    39,    40,    41,    42,
    -1,    44,    -1,    -1,    -1,    -1,    49,    50,    -1,    -1,
    -1,     0,    -1,    56,     3,     4,     5,     6,     7,     8,
     9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
    -1,    20,    21,    22,    23,    24,    25,    26,    27,    28,
    29,    30,    31,    32,    33,    34,    35,    36,    -1,    -1,
    39,    40,    41,    42,    -1,    44,    -1,    -1,    -1,    -1,
    49,    50,    43,    44,    45,    46,    47,    56,    -1,    -1,
    -1,    52,    43,    44,    45,    46,    47,    -1,    -1,    -1,
    -1,    52,    43,    44,    45,    46,    47,    -1,    -1,    -1,
    -1,    52,    43,    44,    45,    46,    47,    -1,    -1,    -1,
    -1,    52,    43,    44,    45,    46,    47,    -1,    -1,    -1,
    -1,    52,    43,    44,    45,    46,    47,    -1,    -1,    -1,
    51,    43,    44,    45,    46,    47,    -1,    -1,    -1,    51,
    43,    44,    45,    46,    47,    -1,    -1,    -1,    51,    43,
    44,    45,    46,    47,    -1,    -1,    -1,    51,    43,    44,
    45,    46,    47,    -1,    -1,    -1,    51,    43,    44,    45,
    46,    47,    -1,    -1,    -1,    51,    43,    44,    45,    46,
    47,    -1,    -1,    -1,    51,    43,    44,    45,    46,    47,
    -1,    -1,    -1,    51,    43,    44,    45,    46,    47,    -1,
    -1,    -1,    51,    43,    44,    45,    46,    47,    -1,    -1,
    -1,    51,    43,    44,    45,    46,    47,    -1,    -1,    -1,
    51,    43,    44,    45,    46,    47,    -1,    -1,    -1,    51,
    43,    44,    45,    46,    47,    -1,    -1,    -1,    51,    43,
    44,    45,    46,    47,    -1,    -1,    -1,    51,    43,    44,
    45,    46,    47,    -1,    -1,    -1,    51,    43,    44,    45,
    46,    47,    -1,    -1,    -1,    51,    43,    44,    45,    46,
    47,    -1,    -1,    -1,    51,    43,    44,    45,    46,    47,
    -1,    49,    43,    44,    45,    46,    47,    -1,    49,    43,
    44,    45,    46,    47,    -1,    49,    43,    44,    45,    46,
    47,    -1,    49,    43,    44,    45,    46,    47,    -1,    49,
    43,    44,    45,    46,    47,    -1,    49,    43,    44,    45,
    46,    47,    -1,    49,    43,    44,    45,    46,    47,    -1,
    49,    43,    44,    45,    46,    47,    -1,    49,    43,    44,
    45,    46,    47,    -1,    49,    43,    44,    45,    46,    47,
    -1,    49,    43,    44,    45,    46,    47,    -1,    49
};
/* -*-C-*-  Note some compilers choke on comments on `#line' lines.  */
#line 3 "bison.simple"

/* Skeleton output parser for bison,
   Copyright (C) 1984, 1989, 1990 Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.  */

/* As a special exception, when this file is copied by Bison into a
   Bison output file, you may use that output file without restriction.
   This special exception was added by the Free Software Foundation
   in version 1.24 of Bison.  */

#ifndef alloca
#ifdef __GNUC__
#define alloca __builtin_alloca
#else /* not GNU C.  */
#if (!defined (__STDC__) && defined (sparc)) || defined (__sparc__) || defined (__sparc) || defined (__sgi)
#include <alloca.h>
#else /* not sparc */
#if defined (MSDOS) && !defined (__TURBOC__)
#include <malloc.h>
#else /* not MSDOS, or __TURBOC__ */
#if defined(_AIX)
#include <malloc.h>
 #pragma alloca
#else /* not MSDOS, __TURBOC__, or _AIX */
#ifdef __hpux
#ifdef __cplusplus
extern "C" {
void *alloca (unsigned int);
};
#else /* not __cplusplus */
void *alloca ();
#endif /* not __cplusplus */
#endif /* __hpux */
#endif /* not _AIX */
#endif /* not MSDOS, or __TURBOC__ */
#endif /* not sparc.  */
#endif /* not GNU C.  */
#endif /* alloca not defined.  */

/* This is the parser code that is written into each bison parser
  when the %semantic_parser declaration is not specified in the grammar.
  It was written by Richard Stallman by simplifying the hairy parser
  used when %semantic_parser is specified.  */

/* Note: there must be only one dollar sign in this file.
   It is replaced by the list of actions, each action
   as one case of the switch.  */

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		-2
#define YYEOF		0
#define YYACCEPT	return(0)
#define YYABORT 	return(1)
#define YYERROR		goto yyerrlab1
/* Like YYERROR except do call yyerror.
   This remains here temporarily to ease the
   transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */
#define YYFAIL		goto yyerrlab
#define YYRECOVERING()  (!!yyerrstatus)
#define YYBACKUP(token, value) \
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    { yychar = (token), yylval = (value);			\
      yychar1 = YYTRANSLATE (yychar);				\
      YYPOPSTACK;						\
      goto yybackup;						\
    }								\
  else								\
    { yyerror ("syntax error: cannot back up"); YYERROR; }	\
while (0)

#define YYTERROR	1
#define YYERRCODE	256

#ifndef YYPURE
#define YYLEX		yylex()
#endif

#ifdef YYPURE
#ifdef YYLSP_NEEDED
#ifdef YYLEX_PARAM
#define YYLEX		yylex(&yylval, &yylloc, YYLEX_PARAM)
#else
#define YYLEX		yylex(&yylval, &yylloc)
#endif
#else /* not YYLSP_NEEDED */
#ifdef YYLEX_PARAM
#define YYLEX		yylex(&yylval, YYLEX_PARAM)
#else
#define YYLEX		yylex(&yylval)
#endif
#endif /* not YYLSP_NEEDED */
#endif

/* If nonreentrant, generate the variables here */

#ifndef YYPURE

int	yychar;			/*  the lookahead symbol		*/
YYSTYPE	yylval;			/*  the semantic value of the		*/
				/*  lookahead symbol			*/

#ifdef YYLSP_NEEDED
YYLTYPE yylloc;			/*  location data for the lookahead	*/
				/*  symbol				*/
#endif

int yynerrs;			/*  number of parse errors so far       */
#endif  /* not YYPURE */

#if YYDEBUG != 0
int yydebug;			/*  nonzero means print parse trace	*/
/* Since this is uninitialized, it does not stop multiple parsers
   from coexisting.  */
#endif

/*  YYINITDEPTH indicates the initial size of the parser's stacks	*/

#ifndef	YYINITDEPTH
#define YYINITDEPTH 200
#endif

/*  YYMAXDEPTH is the maximum size the stacks can grow to
    (effective only if the built-in stack extension method is used).  */

#if YYMAXDEPTH == 0
#undef YYMAXDEPTH
#endif

#ifndef YYMAXDEPTH
#define YYMAXDEPTH 10000
#endif

/* Prevent warning if -Wstrict-prototypes.  */
#ifdef __GNUC__
int yyparse (void);
#endif

#if __GNUC__ > 1		/* GNU C and GNU C++ define this.  */
#define __yy_memcpy(FROM,TO,COUNT)	__builtin_memcpy(TO,FROM,COUNT)
#else				/* not GNU C or C++ */
#ifndef __cplusplus

/* This is the most reliable way to avoid incompatibilities
   in available built-in functions on various systems.  */
static void
__yy_memcpy (from, to, count)
     char *from;
     char *to;
     int count;
{
  register char *f = from;
  register char *t = to;
  register int i = count;

  while (i-- > 0)
    *t++ = *f++;
}

#else /* __cplusplus */

/* This is the most reliable way to avoid incompatibilities
   in available built-in functions on various systems.  */
static void
__yy_memcpy (char *from, char *to, int count)
{
  register char *f = from;
  register char *t = to;
  register int i = count;

  while (i-- > 0)
    *t++ = *f++;
}

#endif
#endif

#line 192 "bison.simple"

/* The user can define YYPARSE_PARAM as the name of an argument to be passed
   into yyparse.  The argument should have type void *.
   It should actually point to an object.
   Grammar actions can access the variable by casting it
   to the proper pointer type.  */

#ifdef YYPARSE_PARAM
#define YYPARSE_PARAM_DECL void *YYPARSE_PARAM;
#else
#define YYPARSE_PARAM
#define YYPARSE_PARAM_DECL
#endif

int
yyparse(YYPARSE_PARAM)
     YYPARSE_PARAM_DECL
{
  register int yystate;
  register int yyn;
  register short *yyssp;
  register YYSTYPE *yyvsp;
  int yyerrstatus;	/*  number of tokens to shift before error messages enabled */
  int yychar1 = 0;		/*  lookahead token as an internal (translated) token number */

  short	yyssa[YYINITDEPTH];	/*  the state stack			*/
  YYSTYPE yyvsa[YYINITDEPTH];	/*  the semantic value stack		*/

  short *yyss = yyssa;		/*  refer to the stacks thru separate pointers */
  YYSTYPE *yyvs = yyvsa;	/*  to allow yyoverflow to reallocate them elsewhere */

#ifdef YYLSP_NEEDED
  YYLTYPE yylsa[YYINITDEPTH];	/*  the location stack			*/
  YYLTYPE *yyls = yylsa;
  YYLTYPE *yylsp;

#define YYPOPSTACK   (yyvsp--, yyssp--, yylsp--)
#else
#define YYPOPSTACK   (yyvsp--, yyssp--)
#endif

  int yystacksize = YYINITDEPTH;

#ifdef YYPURE
  int yychar;
  YYSTYPE yylval;
  int yynerrs;
#ifdef YYLSP_NEEDED
  YYLTYPE yylloc;
#endif
#endif

  YYSTYPE yyval;		/*  the variable used to return		*/
				/*  semantic values from the action	*/
				/*  routines				*/

  int yylen;

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Starting parse\n");
#endif

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss - 1;
  yyvsp = yyvs;
#ifdef YYLSP_NEEDED
  yylsp = yyls;
#endif

/* Push a new state, which is found in  yystate  .  */
/* In all cases, when you get here, the value and location stacks
   have just been pushed. so pushing a state here evens the stacks.  */
yynewstate:

  *++yyssp = yystate;

  if (yyssp >= yyss + yystacksize - 1)
    {
      /* Give user a chance to reallocate the stack */
      /* Use copies of these so that the &'s don't force the real ones into memory. */
      YYSTYPE *yyvs1 = yyvs;
      short *yyss1 = yyss;
#ifdef YYLSP_NEEDED
      YYLTYPE *yyls1 = yyls;
#endif

      /* Get the current used size of the three stacks, in elements.  */
      int size = yyssp - yyss + 1;

#ifdef yyoverflow
      /* Each stack pointer address is followed by the size of
	 the data in use in that stack, in bytes.  */
#ifdef YYLSP_NEEDED
      /* This used to be a conditional around just the two extra args,
	 but that might be undefined if yyoverflow is a macro.  */
      yyoverflow("parser stack overflow",
		 &yyss1, size * sizeof (*yyssp),
		 &yyvs1, size * sizeof (*yyvsp),
		 &yyls1, size * sizeof (*yylsp),
		 &yystacksize);
#else
      yyoverflow("parser stack overflow",
		 &yyss1, size * sizeof (*yyssp),
		 &yyvs1, size * sizeof (*yyvsp),
		 &yystacksize);
#endif

      yyss = yyss1; yyvs = yyvs1;
#ifdef YYLSP_NEEDED
      yyls = yyls1;
#endif
#else /* no yyoverflow */
      /* Extend the stack our own way.  */
      if (yystacksize >= YYMAXDEPTH)
	{
	  yyerror("parser stack overflow");
	  return 2;
	}
      yystacksize *= 2;
      if (yystacksize > YYMAXDEPTH)
	yystacksize = YYMAXDEPTH;
      yyss = (short *) alloca (yystacksize * sizeof (*yyssp));
      __yy_memcpy ((char *)yyss1, (char *)yyss, size * sizeof (*yyssp));
      yyvs = (YYSTYPE *) alloca (yystacksize * sizeof (*yyvsp));
      __yy_memcpy ((char *)yyvs1, (char *)yyvs, size * sizeof (*yyvsp));
#ifdef YYLSP_NEEDED
      yyls = (YYLTYPE *) alloca (yystacksize * sizeof (*yylsp));
      __yy_memcpy ((char *)yyls1, (char *)yyls, size * sizeof (*yylsp));
#endif
#endif /* no yyoverflow */

      yyssp = yyss + size - 1;
      yyvsp = yyvs + size - 1;
#ifdef YYLSP_NEEDED
      yylsp = yyls + size - 1;
#endif

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Stack size increased to %d\n", yystacksize);
#endif

      if (yyssp >= yyss + yystacksize - 1)
	YYABORT;
    }

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Entering state %d\n", yystate);
#endif

  goto yybackup;
 yybackup:

/* Do appropriate processing given the current state.  */
/* Read a lookahead token if we need one and don't already have one.  */
/* yyresume: */

  /* First try to decide what to do without reference to lookahead token.  */

  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* yychar is either YYEMPTY or YYEOF
     or a valid token in external form.  */

  if (yychar == YYEMPTY)
    {
#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Reading a token: ");
#endif
      yychar = YYLEX;
    }

  /* Convert token to internal form (in yychar1) for indexing tables with */

  if (yychar <= 0)		/* This means end of input. */
    {
      yychar1 = 0;
      yychar = YYEOF;		/* Don't call YYLEX any more */

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Now at end of input.\n");
#endif
    }
  else
    {
      yychar1 = YYTRANSLATE(yychar);

#if YYDEBUG != 0
      if (yydebug)
	{
	  fprintf (stderr, "Next token is %d (%s", yychar, yytname[yychar1]);
	  /* Give the individual parser a way to print the precise meaning
	     of a token, for further debugging info.  */
#ifdef YYPRINT
	  YYPRINT (stderr, yychar, yylval);
#endif
	  fprintf (stderr, ")\n");
	}
#endif
    }

  yyn += yychar1;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != yychar1)
    goto yydefault;

  yyn = yytable[yyn];

  /* yyn is what to do for this token type in this state.
     Negative => reduce, -yyn is rule number.
     Positive => shift, yyn is new state.
       New state is final state => don't bother to shift,
       just return success.
     0, or most negative number => error.  */

  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrlab;

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Shift the lookahead token.  */

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Shifting token %d (%s), ", yychar, yytname[yychar1]);
#endif

  /* Discard the token being shifted unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  *++yyvsp = yylval;
#ifdef YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

  /* count tokens shifted since error; after three, turn off error status.  */
  if (yyerrstatus) yyerrstatus--;

  yystate = yyn;
  goto yynewstate;

/* Do the default action for the current state.  */
yydefault:

  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;

/* Do a reduction.  yyn is the number of a rule to reduce with.  */
yyreduce:
  yylen = yyr2[yyn];
  if (yylen > 0)
    yyval = yyvsp[1-yylen]; /* implement default value of the action */

#if YYDEBUG != 0
  if (yydebug)
    {
      int i;

      fprintf (stderr, "Reducing via rule %d (line %d), ",
	       yyn, yyrline[yyn]);

      /* Print the symbols being reduced, and their result.  */
      for (i = yyprhs[yyn]; yyrhs[i] > 0; i++)
	fprintf (stderr, "%s ", yytname[yyrhs[i]]);
      fprintf (stderr, " -> %s\n", yytname[yyr1[yyn]]);
    }
#endif


  switch (yyn) {

case 2:
#line 85 "lexcalc.y"
{ print_tval_of( yyvsp[-1].value );/*fprintf( foutt, "%.12g", $2.value) */;
    break;}
case 3:
#line 87 "lexcalc.y"
{ TextindexStore( yyvsp[-2].value ); ;
    break;}
case 4:
#line 88 "lexcalc.y"
{ TextindexGet( yyvsp[-2].value ); ;
    break;}
case 5:
#line 90 "lexcalc.y"
{ printf( "%s", yyvsp[-1].name ); ;
    break;}
case 6:
#line 91 "lexcalc.y"
{ printf( "%f", yyvsp[-1].value ); ;
    break;}
case 7:
#line 93 "lexcalc.y"
{ ColoringOff( yyvsp[-4].value, yyvsp[-2].value );  ;
    break;}
case 8:
#line 95 "lexcalc.y"
{ PrintBorderline( yyvsp[-4].value, yyvsp[-2].value );  ;
    break;}
case 9:
#line 97 "lexcalc.y"
{ KillThisLoop(); ;
    break;}
case 10:
#line 98 "lexcalc.y"
{ if( yyvsp[-4].value<yyvsp[-2].value ){printf( "lowkill yes %f<%f\n",yyvsp[-4].value,yyvsp[-2].value);return EXIT_SUCCESS;}else printf( "lowkill no %f>=%f\n",yyvsp[-4].value,yyvsp[-2].value); ;
    break;}
case 11:
#line 99 "lexcalc.y"
{ set_identifier( yyvsp[-3], yyvsp[-1].value ); ;
    break;}
case 12:
#line 100 "lexcalc.y"
{ set_identifier_arr( yyvsp[-6], yyvsp[-1].value, yyvsp[-4].value ); ;
    break;}
case 13:
#line 101 "lexcalc.y"
{ fontmatchuse( yyvsp[-1].name ); ;
    break;}
case 14:
#line 102 "lexcalc.y"
{ set_flag( yyvsp[-1].name ); ;
    break;}
case 15:
#line 103 "lexcalc.y"
{ print_time_of( yyvsp[-1].value ); ;
    break;}
case 16:
#line 104 "lexcalc.y"
{ print_pos_of( yyvsp[-1].value ); ;
    break;}
case 17:
#line 105 "lexcalc.y"
{ print_hex_of( yyvsp[-1].value ); ;
    break;}
case 18:
#line 106 "lexcalc.y"
{ print_char_of( yyvsp[-1].value ); ;
    break;}
case 19:
#line 107 "lexcalc.y"
{ print_color_of( yyvsp[-1].value ); ;
    break;}
case 20:
#line 108 "lexcalc.y"
{ print_tval_of( yyvsp[-1].value ); ;
    break;}
case 21:
#line 109 "lexcalc.y"
{ print_identifier( yyvsp[-1].name ); ;
    break;}
case 22:
#line 110 "lexcalc.y"
{ rand_ins( yyvsp[-2].name, yyvsp[-1].value ); ;
    break;}
case 23:
#line 111 "lexcalc.y"
{ loop_file( yyvsp[-2].name, yyvsp[-1].value, 1 ); ;
    break;}
case 24:
#line 112 "lexcalc.y"
{ loop_file( yyvsp[-6].name, yyvsp[-4].value, yyvsp[-2].value ); ;
    break;}
case 25:
#line 113 "lexcalc.y"
{ if( !textlock_identifier( yyvsp[-1].name ) )return EXIT_SUCCESS; ;
    break;}
case 26:
#line 114 "lexcalc.y"
{ if( !stylelock_identifier( yyvsp[-1].name ) )return EXIT_SUCCESS; ;
    break;}
case 27:
#line 115 "lexcalc.y"
{ if( !textfind_identifier( yyvsp[-1].name ) )return EXIT_SUCCESS; ;
    break;}
case 28:
#line 116 "lexcalc.y"
{ if( textfind_identifier( yyvsp[-1].name ) )return EXIT_SUCCESS; ;
    break;}
case 29:
#line 117 "lexcalc.y"
{ fprintf( foutt, "%s", yyvsp[-1].name) ;
    break;}
case 30:
#line 118 "lexcalc.y"
{ return EXIT_SUCCESS; ;
    break;}
case 32:
#line 120 "lexcalc.y"
{ printf("\n error \n"); yyerrok; ;
    break;}
case 33:
#line 124 "lexcalc.y"
{ yyval.value = yyvsp[-2].value + yyvsp[0].value ;
    break;}
case 34:
#line 125 "lexcalc.y"
{ yyval.value = yyvsp[-2].value - yyvsp[0].value ;
    break;}
case 35:
#line 126 "lexcalc.y"
{ yyval.value = yyvsp[-2].value * yyvsp[0].value ;
    break;}
case 36:
#line 127 "lexcalc.y"
{ yyval.value = yyvsp[-2].value / yyvsp[0].value ;
    break;}
case 37:
#line 128 "lexcalc.y"
{ yyval.value = pow(yyvsp[-2].value, yyvsp[0].value) ;
    break;}
case 38:
#line 129 "lexcalc.y"
{ yyval.value = yyvsp[-1].value ;
    break;}
case 39:
#line 130 "lexcalc.y"
{ yyval.value = sin(yyvsp[-1].value); ;
    break;}
case 40:
#line 131 "lexcalc.y"
{ yyval.value = cos(yyvsp[-1].value); ;
    break;}
case 41:
#line 132 "lexcalc.y"
{ yyval.value = (double)(((int)(yyvsp[-3].value+0.5)) % ((int)(yyvsp[-1].value+0.5))); ;
    break;}
case 42:
#line 133 "lexcalc.y"
{ yyval.value = floor(yyvsp[-1].value); ;
    break;}
case 43:
#line 134 "lexcalc.y"
{ yyval.value = yyvsp[-1].value/(abs(yyvsp[-1].value)+0.0001); ;
    break;}
case 44:
#line 135 "lexcalc.y"
{ if( yyvsp[-3].value<yyvsp[-1].value )yyval.value = yyvsp[-3].value; else yyval.value = yyvsp[-1].value; ;
    break;}
case 45:
#line 136 "lexcalc.y"
{ if( yyvsp[-3].value>yyvsp[-1].value )yyval.value = yyvsp[-3].value; else yyval.value = yyvsp[-1].value; ;
    break;}
case 46:
#line 137 "lexcalc.y"
{ if( yyvsp[-5].value<0.5 )yyval.value = yyvsp[-3].value; else yyval.value = yyvsp[-1].value; ;
    break;}
case 47:
#line 138 "lexcalc.y"
{ yyval.value = get_pixbuf( yyvsp[-3].value, yyvsp[-1].value ); ;
    break;}
case 48:
#line 139 "lexcalc.y"
{ yyval.value = -yyvsp[0].value ;
    break;}
case 49:
#line 140 "lexcalc.y"
{ yyval.value = get_identifier( yyvsp[0] ); ;
    break;}
case 50:
#line 141 "lexcalc.y"
{ yyval.value = get_identifier_arr( yyvsp[-3], yyvsp[-1].value ); ;
    break;}
case 51:
#line 142 "lexcalc.y"
{ yyval.value = find_index_arr( yyvsp[-3], yyvsp[-1].value ); ;
    break;}
case 52:
#line 143 "lexcalc.y"
{ yyval.value = textfind_identifier( yyvsp[0].name ); ;
    break;}
}
   /* the action file gets copied in in place of this dollarsign */
#line 487 "bison.simple"

  yyvsp -= yylen;
  yyssp -= yylen;
#ifdef YYLSP_NEEDED
  yylsp -= yylen;
#endif

#if YYDEBUG != 0
  if (yydebug)
    {
      short *ssp1 = yyss - 1;
      fprintf (stderr, "state stack now");
      while (ssp1 != yyssp)
	fprintf (stderr, " %d", *++ssp1);
      fprintf (stderr, "\n");
    }
#endif

  *++yyvsp = yyval;

#ifdef YYLSP_NEEDED
  yylsp++;
  if (yylen == 0)
    {
      yylsp->first_line = yylloc.first_line;
      yylsp->first_column = yylloc.first_column;
      yylsp->last_line = (yylsp-1)->last_line;
      yylsp->last_column = (yylsp-1)->last_column;
      yylsp->text = 0;
    }
  else
    {
      yylsp->last_line = (yylsp+yylen-1)->last_line;
      yylsp->last_column = (yylsp+yylen-1)->last_column;
    }
#endif

  /* Now "shift" the result of the reduction.
     Determine what state that goes to,
     based on the state we popped back to
     and the rule number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTBASE] + *yyssp;
  if (yystate >= 0 && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTBASE];

  goto yynewstate;

yyerrlab:   /* here on detecting error */

  if (! yyerrstatus)
    /* If not already recovering from an error, report this error.  */
    {
      ++yynerrs;

#ifdef YYERROR_VERBOSE
      yyn = yypact[yystate];

      if (yyn > YYFLAG && yyn < YYLAST)
	{
	  int size = 0;
	  char *msg;
	  int x, count;

	  count = 0;
	  /* Start X at -yyn if nec to avoid negative indexes in yycheck.  */
	  for (x = (yyn < 0 ? -yyn : 0);
	       x < (sizeof(yytname) / sizeof(char *)); x++)
	    if (yycheck[x + yyn] == x)
	      size += strlen(yytname[x]) + 15, count++;
	  msg = (char *) malloc(size + 15);
	  if (msg != 0)
	    {
	      strcpy(msg, "parse error");

	      if (count < 5)
		{
		  count = 0;
		  for (x = (yyn < 0 ? -yyn : 0);
		       x < (sizeof(yytname) / sizeof(char *)); x++)
		    if (yycheck[x + yyn] == x)
		      {
			strcat(msg, count == 0 ? ", expecting `" : " or `");
			strcat(msg, yytname[x]);
			strcat(msg, "'");
			count++;
		      }
		}
	      yyerror(msg);
	      free(msg);
	    }
	  else
	    yyerror ("parse error; also virtual memory exceeded");
	}
      else
#endif /* YYERROR_VERBOSE */
	yyerror("parse error");
    }

  goto yyerrlab1;
yyerrlab1:   /* here on error raised explicitly by an action */

  if (yyerrstatus == 3)
    {
      /* if just tried and failed to reuse lookahead token after an error, discard it.  */

      /* return failure if at end of input */
      if (yychar == YYEOF)
	YYABORT;

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Discarding token %d (%s).\n", yychar, yytname[yychar1]);
#endif

      yychar = YYEMPTY;
    }

  /* Else will try to reuse lookahead token
     after shifting the error token.  */

  yyerrstatus = 3;		/* Each real token shifted decrements this */

  goto yyerrhandle;

yyerrdefault:  /* current state does not do anything special for the error token. */

#if 0
  /* This is wrong; only states that explicitly want error tokens
     should shift them.  */
  yyn = yydefact[yystate];  /* If its default is to accept any token, ok.  Otherwise pop it.*/
  if (yyn) goto yydefault;
#endif

yyerrpop:   /* pop the current state because it cannot handle the error token */

  if (yyssp == yyss) YYABORT;
  yyvsp--;
  yystate = *--yyssp;
#ifdef YYLSP_NEEDED
  yylsp--;
#endif

#if YYDEBUG != 0
  if (yydebug)
    {
      short *ssp1 = yyss - 1;
      fprintf (stderr, "Error: state stack now");
      while (ssp1 != yyssp)
	fprintf (stderr, " %d", *++ssp1);
      fprintf (stderr, "\n");
    }
#endif

yyerrhandle:

  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    goto yyerrdefault;

  yyn += YYTERROR;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != YYTERROR)
    goto yyerrdefault;

  yyn = yytable[yyn];
  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	goto yyerrpop;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrpop;

  if (yyn == YYFINAL)
    YYACCEPT;

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Shifting error token, ");
#endif

  *++yyvsp = yylval;
#ifdef YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

  yystate = yyn;
  goto yynewstate;
}
#line 147 "lexcalc.y"

