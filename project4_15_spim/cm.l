/****************************************************/
/* File: tiny.l                                     */
/* Lex specification for TINY                       */
/* Compiler Construction: Principles and Practice   */
/* Kenneth C. Louden                                */
/****************************************************/

%{
#include "globals.h"
#include "util.h"
#include "scan.h"
/* lexeme of identifier or reserved word */
char tokenString[MAXTOKENLEN+1];
char beforeToken[MAXTOKENLEN+1];
%}

digit       [0-9]
number      {digit}+
letter      [a-zA-Z]
identifier  {letter}+
newline     \n
whitespace  [ \t]+

%%

"if"            {return IF;}
"else"          {return ELSE;}
"while"					{return WHILE;}
"int"						{return INT;}
"void"					{return VOID;}
"return"				{return RETURN;}

"=="            {return EQ;}
"!="						{return NE;}
"="             {return ASSIGN;}
"<"             {return LT;}
"<="						{return LE;}
">"							{return GT;}
">="						{return GE;}
"+"             {return PLUS;}
"-"             {return MINUS;}
"*"             {return TIMES;}
"/*"             { char c;
									int prelast = 0;
									int errflag;
									do{
										c = input();
										if (c == '\n') {lineno++; continue;}
										if (c == '*'){
												prelast = 1;
										}
										else if (c == '/' && prelast == 1){
												break;
										}
										else if (prelast == 1 && c != '/'){
												prelast = 0;
										}
										if (c == EOF){
												errflag = 1;
												break;
										}
									}while (1);
									if (errflag == 1)
													return COMERROR;

								}
"/"							{return OVER;}
"("             {return LPAREN;}
")"             {return RPAREN;}
";"             {return SEMI;}
{number}        {return NUM;}
{identifier}    {return ID;}
{newline}       {lineno++;}
{whitespace}    {/* skip whitespace */}
"{"             {return LCURLYB;}
"}"							{return RCURLYB;}
"["							{return LSQUAREB;}
"]"							{return RSQUAREB;}
","							{return COMMA;}
.               {return ERROR;}

%%

TokenType getToken(void)
{ static int firstTime = TRUE;
  TokenType currentToken;
  if (firstTime)
  { firstTime = FALSE;
    lineno++;
    yyin = source;
    yyout = listing;
  }
	if (tokenString != NULL){
				strncpy(beforeToken,tokenString,MAXTOKENLEN);
	}
  currentToken = yylex();
  strncpy(tokenString,yytext,MAXTOKENLEN);
  if (TraceScan) {
    fprintf(listing,"\t%d  ",lineno);
    printToken(currentToken,tokenString);
  }
  return currentToken;
}

int yywrap(void){
		return 1;
}
