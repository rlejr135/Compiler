/****************************************************/
/* File: globals.h                                  */
/* Global types and vars for TINY compiler          */
/* must come before other include files             */
/* Compiler Construction: Principles and Practice   */
/* Kenneth C. Louden                                */
/****************************************************/

#ifndef _GLOBALS_H_
#define _GLOBALS_H_

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#ifndef FALSE
#define FALSE 0
#endif

#ifndef TRUE
#define TRUE 1
#endif

#ifndef YYPARSER
#include "y.tab.h"

#define ENDFILE 0

#endif

/* MAXRESERVED = the number of reserved words */
#define MAXRESERVED 8
/*
typedef enum 
 book-keeping tokens 
   {ENDFILE,ERROR, COMERROR,
   * reserved words 
    IF,THEN,ELSE,END,REPEAT,UNTIL,READ,WRITE, INT, RETURN, WHILE, VOID, 
    multicharacter tokens 
    ID,NUM,
     special symbols 
    ASSIGN,EQ,LT,PLUS,MINUS,TIMES,OVER,LPAREN,RPAREN,SEMI,
		LCURLYB, RCURLYB, LSQUAREB, RSQUAREB,
		COMMA, LE, GT, GE, NE
   } TokenType;
*/
typedef int TokenType;
extern FILE* source; /* source code text file */
extern FILE* listing; /* listing output text file */
extern FILE* code; /* code text file for TM simulator */

extern int lineno; /* source line number for listing */

/**************************************************/
/***********   Syntax tree for parsing ************/
/**************************************************/


// **** add proj2 **** //
// **** DecKind, Dec **** //
typedef enum {StmtK,ExpK, DecK} NodeKind;

typedef enum {CompoundK,ExpressionK,SelectionK,IterationK,ReturnK, ElseK} StmtKind;
typedef enum {OpK,ConstK, AssignK, IdK, IdarrayK, TypeK, ParamK, CallK} ExpKind;
//**** add proj2 ****//
typedef enum {IntK, ArrayK, FunK, LocalK} DecKind;

/* ExpType is used for type checking */
typedef enum {Void,Integer,Boolean} ExpType;

#define MAXCHILDREN 5

typedef struct treeNode
   { struct treeNode * child[MAXCHILDREN];
     struct treeNode * sibling;
     int lineno;
     NodeKind nodekind;
     union { StmtKind stmt; ExpKind exp; DecKind dec;} kind;
     union { TokenType op;
             int val;
             char * name; } attr;
     ExpType type; /* for type checking of exps */
   } TreeNode;

/**************************************************/
/***********   Flags for tracing       ************/
/**************************************************/

/* EchoSource = TRUE causes the source program to
 * be echoed to the listing file with line numbers
 * during parsing
 */
extern int EchoSource;

/* TraceScan = TRUE causes token information to be
 * printed to the listing file as each token is
 * recognized by the scanner
 */
extern int TraceScan;

/* TraceParse = TRUE causes the syntax tree to be
 * printed to the listing file in linearized form
 * (using indents for children)
 */
extern int TraceParse;

/* TraceAnalyze = TRUE causes symbol table inserts
 * and lookups to be reported to the listing file
 */
extern int TraceAnalyze;

/* TraceCode = TRUE causes comments to be written
 * to the TM code file as code is generated
 */
extern int TraceCode;

/* Error = TRUE prevents further passes if an error occurs */
extern int Error; 
#endif
