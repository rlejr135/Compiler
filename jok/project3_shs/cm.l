/****************************************************/
/* File: cm.l                                       */
/* Lex specification for TINY                       */
/* Compiler Construction: Principles and Practice   */
/* Kenneth C. Louden                                */
/*                                                  */
/* modified by HYEONSOO SHIN, 20111636 (March, 2016)*/
/****************************************************/

%{
#include "globals.h"
#include "util.h"
#include "scan.h"

/* lexeme of identifier or reserved word */
char tokenString[MAXTOKENLEN+1];
char savedId[MAXTOKENLEN+1];
int savedNum;
%}

digit       [0-9]
number      {digit}+
letter      [a-zA-Z]
identifier  {letter}+
newline     \n
whitespace  [ \t\r]+

%%

 /* KEYWORDS of C- 
	(by Appendix A: Compiler Project (p491)) */
"else"          {return ELSE;}
"if"            {return IF;}
"int"           {return INT;}
"return"        {return RETURN;}
"void"          {return VOID;}
"while"         {return WHILE;}

 /* SPECIAL SYMBOLS OF C-
	(by Appendix A: Compiler Project (p491)) */
"+"             {return PLUS;}
"-"             {return MINUS;}
"*"             {return TIMES;}
"/"             {return DIV;}
"<"             {return LT;}
"<="            {return LTE;}
">"             {return GT;}
">="            {return GTE;}
"=="            {return EQ;}
"!="            {return NEQ;}
"="             {return ASSIGN;}
";"             {return SEMI;}
","             {return COMMA;}
"("             {return LPAREN;}
")"             {return RPAREN;}
"["             {return LBRACKET;}
"]"             {return RBRACKET;}
"{"             {return LBRACE;}
"}"             {return RBRACE;}

{number}        {	
					savedNum = atoi(yytext);
					return NUM;
				}
{identifier}    {
					strcpy(savedId, yytext);
					return ID;
				}
{newline}       {lineno++;}
{whitespace}    {/* skip whitespace */}


 /* COMMENT */

"/*"             { register int c, expectingSlashMark=0;
                   while(1)
                   {
              			c = input();
              
             			if(c == EOF)
			            	return ERROR;
                       	if(c == '/' && expectingSlashMark == 1)
              				break;
             			expectingSlashMark = 0;
            			if(c == '\n')
             				lineno++;
            			if(c == '*')
			            	expectingSlashMark = 1;
            		}
                 }
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
  /*
  if (TraceScan) {
    fprintf(listing,"\t%-10d\t",lineno);     // to-be : shs
    printToken(currentToken,tokenString);
  }
  */
  return currentToken;
}
