%{
 
#include <stdio.h>
#include "calc.tab.h"
int c;
//extern int yylval;
%}
 
%%

" "         {}

\n          { return '\n'; }

"def"       { return FUN; }

[a-zA-Z][a-zA-Z0-9]* {
              yylval.cval = strdup(yytext);
              return VAR;
            }

[0-9]+"."[0-9]*  {
                    yylval.fval = atof(yytext);
                    return FLOAT; 
                 }


[0-9]+      {
              yylval.nval = atoi(yytext);
              return INT;
            }

[+-/*%=:]   {
             c = yytext[0];
             return c;
            }

\(          {
              return '(';
            }

\)          {
              return ')';
            }

%%

YY_BUFFER_STATE getCurrentBuffer() {
  return YY_CURRENT_BUFFER;
}

