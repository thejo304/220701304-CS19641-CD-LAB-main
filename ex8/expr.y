%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int temp_count = 0;

typedef struct Expression {
    char code[1000];
    char result[100];
} Expression;

void yyerror(const char *s);
int yylex(void);
%}

%union {
    char* str;
    struct Expression* expr;
}

%token <str> ID NUMBER OPERATOR
%token ASSIGN

%type <expr> expr

%left '+' '-'
%left '*' '/'

%%

statement:
    ID ASSIGN expr ';' {
        printf("%s = %s\n", $1, $3->result);
        printf("%s", $3->code);
    }
    ;

expr:
    ID {
        $$ = (Expression*)malloc(sizeof(Expression));
        strcpy($$->result, $1);
        strcpy($$->code, "");
    }
    |
    NUMBER {
        $$ = (Expression*)malloc(sizeof(Expression));
        strcpy($$->result, $1);
        strcpy($$->code, "");
    }
    |
    expr OPERATOR expr {
        $$ = (Expression*)malloc(sizeof(Expression));
        char temp[10];
        sprintf(temp, "t%d", temp_count++);
        sprintf($$->code, "%s%s%s = %s %s %s\n", 
                $1->code, $3->code,
                temp, $1->result, $2, $3->result);
        strcpy($$->result, temp);
    }
    |
    '(' expr ')' {
        $$ = $2;
    }
    ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Syntax error: %s\n", s);
}

int main() {
    printf("Enter expression (e.g., a = b + c * d;):\n");
    return yyparse();
}
