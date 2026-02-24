%{
#include "ast.h"
#include <string.h>
#include <stdlib.h>

int yylex(void);
 void yyerror(program_t*, char const*);

static void append_constant(program_t *prog, constant_t *c) {
    c->next = prog->constanttbl;
    prog->constanttbl = c;
}

static void append_device(program_t *prog, device_t *d) {
    d->next = prog->devicetbl;
    prog->devicetbl = d;
}

void append_statement(program_t *p, statement_t *stmt) {
    stmt->next = NULL;

    if (!p->head) {
        p->head = p->tail = stmt;
    } else {
        p->tail->next = stmt;
        p->tail = stmt;
    }
}

void append_opcode(program_t *p, opcode_t* op) {
    statement_t *s = malloc(sizeof(statement_t));
    s->type = STMT_OPCODE;
    s->opcode = op;

    append_statement(p, s);
}

void append_label(program_t *p, char* lbl) {
    statement_t *s = malloc(sizeof(statement_t));
    s->type = STMT_LABEL;
    s->label = lbl;

    append_statement(p, s);
}

void append_variable(program_t *p, variable_t* var) {
    statement_t *s = malloc(sizeof(statement_t));
    s->type = STMT_VARIABLE;
    s->variable = var;

    append_statement(p, s);
}

/* void append_directive(program_t *p, directive_t dir) { */
/*     statement_t *s = malloc(sizeof(statement_t)); */
/*     s->type = STMT_DIRECTIVE; */
/*     s->directive = dir; */

/*     append_statement(p, s); */
/* } */
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
    operand_list_t* operand_list;
    opcode_t* opcode;
    operand_t* operand;
}
			
%token OPEN_SQUARE CLOSE_SQUARE COMMA AT DOT PLUS MINUS MULTIPLY DIVIDE AND OR NOT XOR COLON SECTION CONST VAR ORG DEV DOLLAR EOL IDENTIFIER STRING INTEGER LPAREN RPAREN EQUALS SKP SZC SNC SZR SNR SEZ SBN
			
%type	<str>	IDENTIFIER STRING
%type	<number>	INTEGER
%type	<constant>	constant_stmt;
%type	<device>	device_stmt;
%type	<variable>	var_stmt;
%type	<expression>	expression;
%type	<program>	program;
%type	<operand>	operand;
%type	<opcode>	opcode_stmt;
%type	<operand_list>	operand_list;
			
%left AND OR NOT XOR
%left PLUS MINUS
%left MULTIPLY DIVIDE

%%
program:
		{
		    prog->constanttbl = NULL;
		    prog->devicetbl = NULL;

		    prog->head = NULL;
		    prog->tail = NULL;
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
	|	program opcode_stmt {
		    append_opcode(prog, $2);
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

operand:
		expression {
		    $$ = malloc(sizeof(operand_t));
		    $$->kind = OPERAND_EXPR;
		    $$->u.expr = $1;
		}
	| 	AT expression {
		    $$ = malloc(sizeof(operand_t));
		    $$->kind = OPERAND_INDIRECT;
		    $$->u.expr = $2;
		}
	|       SKP {
		    $$ = malloc(sizeof(operand_t));
		    $$->kind = OPERAND_SKIP;
		    $$->u.skip = SKIP_SKP;
		}
	|       SZC {
		    $$ = malloc(sizeof(operand_t));
		    $$->kind = OPERAND_SKIP;
		    $$->u.skip = SKIP_SZC;
		}
	|       SNC {
		    $$ = malloc(sizeof(operand_t));
		    $$->kind = OPERAND_SKIP;
		    $$->u.skip = SKIP_SNC;
		}
	|       SZR {
		    $$ = malloc(sizeof(operand_t));
		    $$->kind = OPERAND_SKIP;
		    $$->u.skip = SKIP_SZR;
		}
	|	SNR {
		    $$ = malloc(sizeof(operand_t));
		    $$->kind = OPERAND_SKIP;
		    $$->u.skip = SKIP_SNR;
		}
	|       SEZ {
		    $$ = malloc(sizeof(operand_t));
		    $$->kind = OPERAND_SKIP;
		    $$->u.skip = SKIP_SEZ;
		}
	|       SBN {
		    $$ = malloc(sizeof(operand_t));
		    $$->kind = OPERAND_SKIP;
		    $$->u.skip = SKIP_SBN;
		}
;

operand_list:
		operand {
		    $$ = malloc(sizeof(operand_list_t));
		    $$->count = 1;
		    $$->items[0] = $1;
		}
	| 	operand_list COMMA operand {
		    if ($1->count >= MAX_OPERANDS) {
			yyerror(prog, "Too many operands");
		    } else {
			$1->items[$1->count++] = $3;
		    }

		    $$ = $1;
		}
;

opcode_stmt:
		IDENTIFIER EOL {
		    $$ = malloc(sizeof(opcode_t));
		    $$->mnemonic = strdup($1);
		    $$->operands = NULL;
		}
	| 	IDENTIFIER operand_list EOL {
		    $$ = malloc(sizeof(opcode_t));
		    $$->mnemonic = strdup($1);
		    $$->operands = $2;
		}
;
%%
