

#ifndef LexCalc_h
#define LexCalc_h


#include <math.h>


typedef union calc_type {
        double value;
        wchar_t name[2048];
 //       int length;
} calc_type;

#define YYSTYPE calc_type

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

#endif
