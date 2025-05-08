%{
#include <stdio.h>
#include <stdlib.h>

void yyerror(const char *s);
int yylex(void);
%}

%token IF ELSE WHILE FOR SWITCH CASE DEFAULT
%token ID NUM
%token LPAREN RPAREN LBRACE RBRACE SEMI COLON

%%

program:
    statement_list
;

statement_list:
    statement
  | statement_list statement
;

statement:
    if_stmt
  | if_else_stmt
  | while_stmt
  | for_stmt
  | switch_stmt
;

if_stmt:
    IF LPAREN ID RPAREN block   { printf("Valid if statement\n"); }
;

if_else_stmt:
    IF LPAREN ID RPAREN block ELSE block   { printf("Valid if-else statement\n"); }
;

while_stmt:
    WHILE LPAREN ID RPAREN block   { printf("Valid while loop\n"); }
;

for_stmt:
    FOR LPAREN ID SEMI ID SEMI ID RPAREN block   { printf("Valid for loop\n"); }
;

switch_stmt:
    SWITCH LPAREN ID RPAREN LBRACE case_blocks DEFAULT COLON block RBRACE { printf("Valid switch-case statement\n"); }
;

case_blocks:
    case_blocks CASE NUM COLON block
  | CASE NUM COLON block
;

block:
    LBRACE statement_list RBRACE
  | LBRACE RBRACE   // To support empty blocks
;

%%

void yyerror(const char *s) {
    printf("Syntax Error: %s\n", s);
}

int main() {
    printf("Enter control structure:\n");
    return yyparse();
}
