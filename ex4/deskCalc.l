%{
#include <stdio.h>
#include <stdlib.h>
%}

DIGIT      [0-9]
NUMBER     {DIGIT}+\.?{DIGIT}*
OPERATOR   [\+\-\*/]
WHITESPACE [ \t]

%%
{NUMBER}      { printf("NUMBER (%s)\n", yytext); }
{OPERATOR}    { printf("OPERATOR (%s)\n", yytext); }
"("           { printf("LEFT PARENTHESIS (%s)\n", yytext); }
")"           { printf("RIGHT PARENTHESIS (%s)\n", yytext); }
{WHITESPACE}+ { /* Ignore whitespace */ }
.             { printf("Error: Invalid token (%s)\n", yytext); exit(1); }
%%

int main() {
    printf("Enter an arithmetic expression: ");
    yylex();
    printf("Valid arithmetic expression.\n");
    return 0;
}

int yywrap() {
    return 1;
}
