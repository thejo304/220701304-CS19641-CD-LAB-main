%{
#include <stdio.h>
#include <stdlib.h>
int yylex(void);
void yyerror(const char *s);
%}

%token NUMBER
%left '+' 
%left '*' 

%%

S : E              { printf("Result: %d\n", $1); return 0; }
  ;

E : E '+' E        { $$ = $1 + $3; }
  | E '*' E        { $$ = $1 * $3; }
  | '(' E ')'      { $$ = $2; }
  | NUMBER         { $$ = $1; }
  ;

%%

int main() {
    printf("Enter an expression: ");
    return yyparse();
}

void yyerror(const char* s) {
    fprintf(stderr, "Error: %s\n", s);
}
