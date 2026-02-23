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
    device_t device;
    variable_t variable;
}
			
%token OPEN_SQUARE CLOSE_SQUARE COMMA AT DOT PLUS MINUS MULTIPLY DIVIDE AND OR NOT XOR COLON SECTION CONST VAR ORG DEV DOLLAR EOL IDENTIFIER STRING INTEGER LPAREN RPAREN EQUALS
			
%type	<str>	IDENTIFIER STRING
%type	<number>	INTEGER expression
%type	<constant>	constant_stmt;
%type	<device>	device_stmt;
%type	<variable>	var_stmt;

%left AND OR NOT XOR
%left PLUS MINUS
%left MULTIPLY DIVIDE

%%
program:
		{}
	| 	program constant_stmt  { printf("Const %s=%d\n", $2.name, $2.value); }
	|	program device_stmt  { printf("Device %s=%d\n", $2.name, $2.value); }
	|	program var_stmt  {{
			if ($2.type == VARIABLE_STRING) {
			    printf("String var %s=%s\n", $2.name, $2.value.str);
			} else {
			    printf("Int var %s=%d\n", $2.name, $2.value.number);
			}
		}}
	|	program EOL  {}

constant_stmt:
		CONST IDENTIFIER EQUALS expression EOL { $$ = (constant_t){
			$2, $4,
		}; }

device_stmt:	DEV IDENTIFIER EQUALS INTEGER EOL { $$ = (device_t){
			$2, $4,
		}; }
	;

var_stmt:	VAR IDENTIFIER EQUALS expression EOL { $$ = (variable_t){
			.type = VARIABLE_NUMBER,
			.name = $2,
			.value = (variable_value_t){ .number = $4},
		}; }
	|	VAR IDENTIFIER EQUALS STRING EOL { $$ = (variable_t){
			.type = VARIABLE_STRING,
			.name = $2,
			.value = (variable_value_t){ .str = $4},
		}; }
	;

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
