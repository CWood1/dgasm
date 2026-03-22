%{
#include "ast.h"
#include "parser.h"
#include "error.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_STRING 4096
#define YY_USER_ACTION append_to_line(yytext, yyleng);

#define APPEND_CHAR(c) do {                           \
    if ((size_t)(string_buf_ptr - string_buf) >= MAX_STRING - 1) { \
        fprintf(stderr, "String too long\n");         \
        exit(1);                                     \
    }                                                \
    *string_buf_ptr++ = (c);                         \
} while (0)

static char string_buf[MAX_STRING];
static char *string_buf_ptr;

static char* current_line = NULL;
static size_t current_line_len = 0;

#define MAX_INCLUDE_DEPTH 10

typedef struct {
    YY_BUFFER_STATE buffer;
    char* fn;
    int lineno;
} include_frame_t;

include_frame_t include_stack[MAX_INCLUDE_DEPTH];
int include_stack_ptr = 0;

void append_to_line(const char* text, int len) {
    for(int i = 0; i < len; i++) {
	if (text[i] == '\n') {
	    source_add_line(include_stack[include_stack_ptr].fn, current_line ? current_line : "");
	    free(current_line);
	    current_line = strdup("");
	    current_line_len = 0;
        } else {
	    current_line = realloc(current_line, current_line_len + 2);
	    if (current_line == NULL) {
		fprintf(stderr, "Realloc returned NULL\n");
		exit(1);
            }
	    current_line[current_line_len++] = text[i];
	    current_line[current_line_len] = '\0';
	}
    }
}

%}

%x string
%x incl
%option yylineno
%option noinput
%option nounput

%%

"/*".*"*/"                   ;
[ \t]                        ;

\"                           { string_buf_ptr = string_buf; BEGIN(string); }

include                      BEGIN(incl);
<incl>[ \t]*                 ;
<incl>\"[^ \t\n]+\"          {
                               if (include_stack_ptr >= MAX_INCLUDE_DEPTH) {
				   fprintf(stderr, "Includes nest too deeply");
                                   exit(1);
                               }

                               include_stack[include_stack_ptr].buffer = YY_CURRENT_BUFFER;
                               char* fn = strpbrk(yytext, "\"") + 1;
                               *(strpbrk(fn, "\"")) = '\0';

                               include_stack[++include_stack_ptr].fn = strdup(fn);
                               include_stack[include_stack_ptr].lineno = yylineno;

                               yyin = fopen(fn, "r");

                               if (!yyin) {
                                   fprintf(stderr, "Cannot include %s - no such file\n", fn);
                                   exit(1);
                               }

                               yy_switch_to_buffer(yy_create_buffer(yyin, YY_BUF_SIZE));
                               BEGIN(INITIAL);
                             }

<string>\"                   { /* saw closing quote - all done */
                               BEGIN(INITIAL);
                               *string_buf_ptr = '\0';
                               yylval.str = strdup(string_buf);
                               return STRING;
                             }

<string>\n                   {
                               fprintf(stderr, "Unterminated string constant. String cannot end in a newline.\n");
                               exit(1);
                             }

<string>\\[0-7]{1,3}         {
                               /* octal escape sequence */
                               unsigned int result;

                               (void) sscanf( yytext + 1, "%o", &result );

                               if (result > 0xff) {
                                 fprintf(stderr, "Escape sequence is out of bounds\n");
                                 exit(1);
                               }

                               APPEND_CHAR(result);
                             }

<string>\\[0-9]+             {
                               fprintf(stderr, "Bad escape sequence\n");
                               exit(1);
                             }

<string>\\n                  { APPEND_CHAR('\n'); }
<string>\\t                  { APPEND_CHAR('\t'); }
<string>\\r                  { APPEND_CHAR('\r'); }
<string>\\b                  { APPEND_CHAR('\b'); }
<string>\\f                  { APPEND_CHAR('\f'); }

<string>\\(.|\n)             { APPEND_CHAR(yytext[1]); }

<string>[^\\\n\"]+           {
                               char *yptr = yytext;

                               while (*yptr) {
                                   APPEND_CHAR(*yptr++);
                               }
                             }

":"                          { return COLON; }
"["                          { return OPEN_SQUARE; }
"]"                          { return CLOSE_SQUARE; }
"("                          { return LPAREN; }
")"                          { return RPAREN; }
","                          { return COMMA; }
"="                          { return EQUALS; }
"@"                          { return AT; }
"."                          { return DOT; }
"+"                          { return PLUS; }
"-"                          { return MINUS; }
"*"                          { return MULTIPLY; }
"/"                          { return DIVIDE; }
"&"                          { return AND; }
"|"                          { return OR; }
"~"                          { return NOT; }
"^"                          { return XOR; }
"#"                          { return HASH; }
const                        { return CONST; }
var                          { return VAR; }
org                          { return ORG; }
dev                          { return DEV; }
section                      { return SECTION; }
resv                         { return RESV; }
dw                           { return DW; }
packed                       { return PACKED; }
"$"                          { return DOLLAR; }
SKP                          { return SKP; }
SZC                          { return SZC; }
SNC                          { return SNC; }
SZR                          { return SZR; }
SNR                          { return SNR; }
SEZ                          { return SEZ; }
SBN                          { return SBN; }

[0-9]+                       { yylval.number = strtol(yytext, NULL, 0); return INTEGER; }
0x[0-9A-Fa-f]+               { yylval.number = strtol(yytext, NULL, 0); return INTEGER; }
[a-zA-Z_][a-zA-Z_0-9]*       { yylval.str = strdup(yytext); return IDENTIFIER; }

"//".*\n                     { return EOL; }
\n                           { return EOL; }

<<EOF>>                      {
                               if (yyin != stdin)
                                   fclose(yyin);

                               source_add_line(include_stack[include_stack_ptr].fn, current_line ? current_line : "");
                               free(current_line);
                               free(include_stack[include_stack_ptr].fn);
                               current_line = NULL;

                               yy_delete_buffer(YY_CURRENT_BUFFER);

                               if (--include_stack_ptr < 0) {
                                   yyterminate();
                               } else {
                                   yy_switch_to_buffer(include_stack[include_stack_ptr].buffer);
                                   include_stack[include_stack_ptr].lineno = yylineno;
                               }
                             }

. {
    fprintf(stderr, "Unexpected character: '%s' at line %d\n", yytext, yylineno);
    exit(1);
}

%%

int yywrap() {
	return 1;
}

void yyerror(program_t* p, char *s) {
    if (include_stack_ptr >= 0) {
	source_add_line(include_stack[include_stack_ptr].fn, current_line ? current_line : "");
	report_syntax_error(include_stack[include_stack_ptr].fn, yylineno,
			    "Syntax error near %s: %s", yytext, s);
    } else {
	// At this point, it's going to exit anyhow, might as well exit here
	fprintf(stderr, "Error in root file around EOF: %s\n", s);
	exit(1);
    }

    while(false) {
	*p = *p;
    }
}
