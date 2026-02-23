%{
#include "parser.h"
#include <stdlib.h>
%}


%%

"/*".*"*/"                   ;
[ \t]                        ;

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
\"([^\\\"]|\\.)*\"           { yylval.str = strdup(yytext); return STRING; }
const                        { return CONST; }
var                          { return VAR; }
org                          { return ORG; }
dev                          { return DEV; }
section                      { return SECTION; }
"$"                          { return DOLLAR; }

[0-9]+                       { yylval.number = strtol(yytext, NULL, 0); return INTEGER; }
0x[0-9A-Fa-f]+               { yylval.number = strtol(yytext, NULL, 0); return INTEGER; }
[a-zA-Z_][a-zA-Z_0-9]*       { yylval.str = strdup(yytext); return IDENTIFIER; }

"//".*"\n"                   { return EOL; }
"\n"                         { return EOL; }

%%

int yywrap() {
	return 1;
}

int yyerror(char *s) {
	fprintf(stderr,"error: %s\n", s);
}

