%{
#include <stdio.h>

int yylex(void);
void yyerror(char const*);
%}

%union {
    char *str;
    long number;
}

%token OPEN_SQUARE CLOSE_SQUARE COMMA AT DOT PLUS MINUS MULTIPLY DIVIDE AND OR NOT XOR COLON STRING HASH CONST VAR ORG DEV DOLLAR INTEGER IDENTIFIER EOL

%type	<str>	IDENTIFIER STRING

%left AND OR NOT XOR
%left PLUS MINUS
%left MULTIPLY DIVIDE

%%
program:
			statement  {}
			| program statement  {}

statement:
			directive EOL {}

directive:
			HASH CONST IDENTIFIER expression { printf("Defined const %s\n", $3); }

expression:
			STRING   { printf("Got expression %s\n", $1); }
%%
