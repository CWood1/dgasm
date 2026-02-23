%{
#include "ast.h"
#include <stdio.h>

int yylex(void);
void yyerror(char const*);
%}

%union {
    char *str;
    long number;
    constant_t constant;
}
			
%token OPEN_SQUARE CLOSE_SQUARE COMMA AT DOT PLUS MINUS MULTIPLY DIVIDE AND OR NOT XOR COLON SECTION CONST VAR ORG DEV DOLLAR EOL IDENTIFIER STRING INTEGER LPAREN RPAREN EQUALS
			
%type	<str>	IDENTIFIER STRING
%type	<number>	INTEGER expression
%type	<constant>	constant_stmt;

%left AND OR NOT XOR
%left PLUS MINUS
%left MULTIPLY DIVIDE

%%
program:
		{}
	| 	program constant_stmt  { printf("Const %s=%d", $2.name, $2.value); }
	|	program EOL  {}

constant_stmt:
		CONST IDENTIFIER EQUALS expression EOL { $$ = (constant_t){
			$2, $4,
		}; }

expression:
		INTEGER   { $$ = $1; }
	|	expression PLUS expression  { $$ = $1 + $3; }
	|	expression MINUS expression  { $$ = $1 - $3; }
	|	expression MULTIPLY expression  { $$ = $1 * $3; }
	|	expression DIVIDE expression  { $$ = $1 / $3; }
	|	LPAREN expression RPAREN  { $$ = $2; }
	|	expression AND expression  { $$ = $1 & $3; }
	|	expression OR expression  { $$ = $1 | $3; }
	|       NOT expression  { $$ = ~$2; }
	|	expression XOR expression  { $$ = $1 ^ $3; }
%%
