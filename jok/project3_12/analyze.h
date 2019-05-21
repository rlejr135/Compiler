#ifndef _ANALYZE_H
#define _ANALYZE_H

#include "globals.h"
#include "scan.h"

enum
{
	BUCKET_SIZE		= 61,
	SIZE_VOID		= 0,
	SIZE_INT		= 4,
	SIZE_ARRAY_ADDR	= SIZE_INT,
};

struct addrCounter
{
	int function;
	int global;
	int local;
};

struct lineList
{
	int line;
	struct lineList *next;
};

struct bucket
{
	struct treeNode *parameter;

	int fastCheck;
	int arrayCount;
	char name[MAXTOKENLEN + 1];

	AddrBase addrBase;
	int addr;
	int len;

	BOOL isParameter;
	DataType dataType;
	DeclType declType;

	struct lineList *lineList;
	struct lineList *lineTail;
	struct bucket *next;
};

//first table is sentinel
struct symbolTable
{
	int scopeDepth;
	struct bucket *bucket[BUCKET_SIZE];
	struct symbolTable *next;
};

struct treeNode;
void buildSymtab(struct treeNode *syntaxTree);
void typeCheck(struct treeNode *syntaxTree);

#endif
