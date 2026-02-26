%{
#include "ast.h"
#include "parser.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_STRING 4096

static char string_buf[MAX_STRING];
static char *string_buf_ptr;

%}

%x string
%option yylineno

%%

"/*".*"*/"                   ;
[ \t]                        ;

\"                           { string_buf_ptr = string_buf; BEGIN(string); }

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
                               int result;

                               (void) sscanf( yytext + 1, "%o", &result );

                               if (result > 0xff) {
                                 fprintf(stderr, "Escape sequence is out of bounds\n");
                                 exit(1);
                               }

                               *string_buf_ptr++ = result;
                             }

<string>\\[0-9]+             {
                               fprintf(stderr, "Bad escape sequence\n");
                               exit(1);
                             }

<string>\\n                  *string_buf_ptr++ = '\n';
<string>\\t                  *string_buf_ptr++ = '\t';
<string>\\r                  *string_buf_ptr++ = '\r';
<string>\\b                  *string_buf_ptr++ = '\b';
<string>\\f                  *string_buf_ptr++ = '\f';

<string>\\(.|\n)             *string_buf_ptr++ = yytext[1];

<string>[^\\\n\"]+           {
                               char *yptr = yytext;

                               while (*yptr)
                                 *string_buf_ptr++ = *yptr++;
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
const                        { return CONST; }
var                          { return VAR; }
org                          { return ORG; }
dev                          { return DEV; }
section                      { return SECTION; }
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

. {
    fprintf(stderr, "Unexpected character: '%s' at line %d\n", yytext, yylineno);
    exit(1);
}

%%

int yywrap() {
	return 1;
}

int yyerror(program_t* prog, char *s) {
	fprintf(stderr,
            "Parse error at line %d near '%s': %s\n", yylineno, yytext, s);
}

