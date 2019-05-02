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
%}

digit       [0-9]
number      {digit}+
letter      [a-zA-Z]
identifier  {letter}+
newline     \n
whitespace  [ \t]+

%%

"if"            {return IF;}
"then"          {return THEN;}
"else"          {return ELSE;}
"end"           {return END;}
"repeat"        {return REPEAT;}
"until"         {return UNTIL;}
"while"					{return WHILE;}
"read"          {return READ;}
"write"         {return WRITE;}
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
									int first = 0;
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
"{"             { /*char c;
                  do
                  { c = input();
                    if (c == EOF) break;
                    if (c == '\n') lineno++;
                  } while (c != '}');*/
									return LCURLYB;
                }
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
  currentToken = yylex();
  strncpy(tokenString,yytext,MAXTOKENLEN);
  if (TraceScan) {
    fprintf(listing,"\t%d  ",lineno);
    printToken(currentToken,tokenString);
  }
  return currentToken;
}

