%{
#include "ast.h"
#include <string.h>

int yylex(void);
 void yyerror(program_t*, char const*);

static void append_constant(program_t *prog, constant_t *c) {
    c->next = prog->constanttbl;
    prog->constanttbl = c;
}

static void append_variable(program_t *prog, variable_t *v) {
    v->next = prog->variabletbl;
    prog->variabletbl = v;
}

static void append_device(program_t *prog, device_t *d) {
    d->next = prog->devicetbl;
    prog->devicetbl = d;
}
%}

%parse-param { program_t* prog }
%define parse.error verbose

%union {
    char *str;
    long number;
    constant_t* constant;
    device_t* device;
    variable_t* variable;
    expression_t* expression;
}
			
%token OPEN_SQUARE CLOSE_SQUARE COMMA AT DOT PLUS MINUS MULTIPLY DIVIDE AND OR NOT XOR COLON SECTION CONST VAR ORG DEV DOLLAR EOL IDENTIFIER STRING INTEGER LPAREN RPAREN EQUALS
			
%type	<str>	IDENTIFIER STRING
%type	<number>	INTEGER
%type	<constant>	constant_stmt;
%type	<device>	device_stmt;
%type	<variable>	var_stmt;
%type	<expression>	expression;
%type	<program>	program;

%left AND OR NOT XOR
%left PLUS MINUS
%left MULTIPLY DIVIDE

%%
program:
		{
		    prog->constanttbl = NULL;
		    prog->variabletbl = NULL;
		    prog->devicetbl = NULL;
		}
	| 	program constant_stmt {
		    append_constant(prog, $2);
		}
	|	program device_stmt {
		    append_device(prog, $2);
		}
	|	program var_stmt {
		    append_variable(prog, $2);
		}
	|	program EOL {}
	;

constant_stmt:
		CONST IDENTIFIER EQUALS expression EOL {
		    $$ = malloc(sizeof(constant_t));
		    $$->name = strdup($2);
		    $$->value = $4;
		}
	;

device_stmt:
		DEV IDENTIFIER EQUALS INTEGER EOL {
		    $$ = malloc(sizeof(device_t));
		    $$->name = strdup($2);
		    $$->value = $4;
		}
	;

var_stmt:
		VAR IDENTIFIER EQUALS expression EOL {
		    $$ = malloc(sizeof(variable_t));
		    $$->type = VARIABLE_NUMBER;
		    $$->name = strdup($2);
		    $$->value = (variable_value_t){ .number = $4 };
		}
	|	VAR IDENTIFIER EQUALS STRING EOL {
		    $$ = malloc(sizeof(variable_t));
		    $$->type = VARIABLE_STRING;
		    $$->name = strdup($2);
		    $$->value = (variable_value_t){ .str = $4 };
		}
	;

expression:
		INTEGER {
		    $$ = malloc(sizeof(expression_t));
		    $$->kind = EXPR_INTEGER;
		    $$->u.number = $1;
		}
	| 	IDENTIFIER {
		    $$ = malloc(sizeof(expression_t));
		    $$->kind = EXPR_IDENTIFIER;
		    $$->u.identifier = strdup($1);
		}
	| 	expression PLUS expression {
		    $$ = malloc(sizeof(expression_t));
		    $$->kind = EXPR_BINARY;
		    $$->u.binary.op = OP_PLUS;
		    $$->u.binary.left = $1;
		    $$->u.binary.right = $3;
		}
	| 	expression MINUS expression {
		    $$ = malloc(sizeof(expression_t));
		    $$->kind = EXPR_BINARY;
		    $$->u.binary.op = OP_MINUS;
		    $$->u.binary.left = $1;
		    $$->u.binary.right = $3;
		}
	| 	expression MULTIPLY expression {
		    $$ = malloc(sizeof(expression_t));
		    $$->kind = EXPR_BINARY;
		    $$->u.binary.op = OP_MULTIPLY;
		    $$->u.binary.left = $1;
		    $$->u.binary.right = $3;
		}
	| 	expression DIVIDE expression {
		    $$ = malloc(sizeof(expression_t));
		    $$->kind = EXPR_BINARY;
		    $$->u.binary.op = OP_DIVIDE;
		    $$->u.binary.left = $1;
		    $$->u.binary.right = $3;
		}
	| 	expression AND expression {
		    $$ = malloc(sizeof(expression_t));
		    $$->kind = EXPR_BINARY;
		    $$->u.binary.op = OP_AND;
		    $$->u.binary.left = $1;
		    $$->u.binary.right = $3;
		}
	| 	expression OR expression {
		    $$ = malloc(sizeof(expression_t));
		    $$->kind = EXPR_BINARY;
		    $$->u.binary.op = OP_OR;
		    $$->u.binary.left = $1;
		    $$->u.binary.right = $3;
		}
	| 	expression XOR expression {
		    $$ = malloc(sizeof(expression_t));
		    $$->kind = EXPR_BINARY;
		    $$->u.binary.op = OP_XOR;
		    $$->u.binary.left = $1;
		    $$->u.binary.right = $3;
		}
	| 	NOT expression {
		    $$ = malloc(sizeof(expression_t));
		    $$->kind = EXPR_UNARY;
		    $$->u.unary.op = OP_NOT;
		    $$->u.unary.child = $2;
		}
	| 	LPAREN expression RPAREN {
		    $$ = $2;  /* just return the inner expression */
		}
	;
%%
