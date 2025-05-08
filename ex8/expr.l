%{
#include "expr.tab.h"
#include <string.h>
%}

%%

[a-zA-Z_][a-zA-Z0-9_]*  { yylval.str = strdup(yytext); return ID; }
[0-9]+                 { yylval.str = strdup(yytext); return NUMBER; }
"="                    { return ASSIGN; }
[\+\-\*/]              { yylval.str = strdup(yytext); return OPERATOR; }
[();]                  { return *yytext; }
[ \t\n]                ; // Skip whitespace

.                      ; // Skip other unknown characters

%%
int yywrap() { return 1; }
