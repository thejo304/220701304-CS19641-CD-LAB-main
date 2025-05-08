%{
#include "expr.tab.h"
#include<stdio.h>
%}

%%

[0-9]+      { yylval = atoi(yytext); return NUMBER; }
[\t\n ]+    { /* ignore whitespace */ }
[+*()]      { return yytext[0]; }

.           { printf("Invalid character: %s\n", yytext); }

%%

int yywrap(void) {
    return 1;
}
