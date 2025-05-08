%{
#include "ctrl.tab.h"
#include <stdio.h>
%}

%%
"if"        { return IF; }
"else"      { return ELSE; }
"while"     { return WHILE; }
"for"       { return FOR; }
"switch"    { return SWITCH; }
"case"      { return CASE; }
"default"   { return DEFAULT; }

"("         { return LPAREN; }
")"         { return RPAREN; }
"{"         { return LBRACE; }
"}"         { return RBRACE; }
";"         { return SEMI; }
":"         { return COLON; }

[0-9]+      { return NUM; }
[a-zA-Z_][a-zA-Z0-9_]*   { return ID; }

[ \t\n]+    ;   // Ignore whitespace
.           ;   // Ignore unknown characters
%%

int yywrap() { return 1; }
