%{
#include "globals.h" 
#include "y.tab.h"
#include "util.h" 
#include "scan.h"

/* lexeme of identifier or reserved word */ 
char tokenString[MAXTOKENLEN+1]; 
char tokenBefore[MAXTOKENLEN+1];
%} 
 
digit       [0-9] 
number      {digit}+ 
letter      [a-zA-Z] 
identifier  {letter}+ 
newline     \n 
whitespace  [ \t]+ 
 
%% 
 
"/*"			{
					char c1, c2;
					c1 = 0;
					c2 = input();
				 	
					while(1)
			 	 	{ 
						if(c2 == EOF) return COMMENTERROR;
						if(c2 == '\n') lineno++;
						if(c1 == '*' && c2 == '/') break;

						c1 = c2;
						c2 = input();
					}
				}
"if"            {return IF;}
"else"			{return ELSE;}
"int"			{return INT;}
"return"		{return RETURN;}
"void"			{return VOID;}
"while"			{return WHILE;}
"+"				{return PLUS;}
"-"				{return MINUS;}
"*"				{return TIMES;}
"/"				{return OVER;}
"<"				{return LT;}
"<="			{return LE;}
">"				{return GT;}
">="			{return GE;}
"=="			{return EQ;}
"!="			{return NE;}
"="				{return ASSIGN;}
";"				{return SEMI;}
","				{return COMMA;}
"("				{return LPAREN;}
")"				{return RPAREN;}
"["				{return LBRACKET;}
"]"				{return RBRACKET;}
"{"				{return LBRACE;}
"}"				{return RBRACE;}
{number}        {return NUM;} 
{identifier}    {return ID;} 
{newline}       {lineno++;} 
{whitespace}    {/* skip whitespace */} 
.               {return ERROR;} 
 
%% 

TokenType getToken(void) 
{
  static int firstTime = TRUE; 
  TokenType currentToken;
 
  if(firstTime) 
  {
	tokenBefore[0] = 0;
	tokenString[0] = 0;
    firstTime = FALSE; 
    lineno++; 
    yyin = source; 
    yyout = listing; 
  }

  currentToken = yylex();
  strncpy(tokenBefore, tokenString, MAXTOKENLEN);
  strncpy(tokenString, yytext, MAXTOKENLEN); 

  if (TraceScan)
  {
    fprintf(listing,"\t%-8d\t",lineno); 
    printToken(currentToken, tokenString); 
  }

  return currentToken; 
}
