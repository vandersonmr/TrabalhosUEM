
%{
using namespace std;
#include "y.h"
#include <stdio.h>
int vals[4];
int i = 1;
%}

%option c++
%option noyywrap
%%

" "       ;
"\n"      ; 
LOOP      {
            i = -1;
            return Parser::LOOP;
          }
DO        {return Parser::DO;}
END       {return Parser::END;}
"="       {return Parser::ATR;}
"+"       {return Parser::SOMA;}
"-"       {return Parser::SUB;}
x[0-9]+ {
         if(i == -1) { 
            vals[3]  = atoi(++yytext);
            i = 1;
         }
         else       vals[i++] = atoi(++yytext);
         if(i == 3) i = 1;
         return Parser::VAR;
        }
[0-9]+  {
         vals[0] = atoi(yytext);
         if(i == 3) i = 0;
         return Parser::CONST;
        }
";"     {
          return ';';
        }

PRINT   {
          i = -1;
          return Parser::PRINT;
        }
