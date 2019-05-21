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

typedef int BOOL;
struct treeNode;
#define YYSTYPE struct treeNode *

#include "y.tab.h"
typedef enum yytokentype TokenType;

/* defined in main.c */
extern FILE	*source;	/* source code text file */
extern FILE	*listing;	/* listing output text file */
extern int	lineno;		/* source line number for listing */


/*
 *	Syntax Tree
 */
typedef enum {DeclNode, ValNode, StmtNode} NodeKind;

typedef enum {KindConst, KindId, KindType} ValNodeKind;
typedef enum {KindVar, KindArray, KindFunc} DeclNodeKind;
typedef enum {
	KindCompound, KindIf, KindWhile, KindReturn, KindNop, KindSubscript, KindCall, KindOp, KindParam
} StmtNodeKind;

typedef enum {TYPE_INT, TYPE_VOID} DataType;
typedef enum {TYPE_VAR, TYPE_FUNC, TYPE_ARRAY, TYPE_RVALUE, TYPE_SUBSCRIPTED, TYPE_NONE} DeclType;

typedef enum {BASE_FP, BASE_GLOBAL} AddrBase;


#define MAXCHILDREN 4

typedef struct treeNode
{
	struct treeNode* child[MAXCHILDREN];
	struct treeNode* sibling;
	int lineno;

	NodeKind nodeKind;

	DeclType declType;
	DataType dataType;
	AddrBase addrBase;
	int addr;

	struct treeNode *parameter;

	union
	{
		ValNodeKind val;
		DeclNodeKind decl;
		StmtNodeKind stmt;
	} detailKind;

	union
	{
		TokenType op;
		int val;
		char *name;
	} attr;
} TreeNode;

/*
 *	Tracing and Error Flag
 */
extern int TraceScan;
extern int TraceParse;
extern int TraceAnalyze;
extern int TraceCode;

extern int Error;

#endif

