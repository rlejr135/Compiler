#include "globals.h"
#include "util.h"

void printDataType(DataType dataType)
{
	switch(dataType)
	{
		case TYPE_VOID:
			fprintf(listing, "%4s", "void");
			break;
		case TYPE_INT:
			fprintf(listing, "%4s", "int");
			break;
		default:
			fprintf(listing, "%s", "Unknown Data Type");
	}
}

void printDeclType(DeclType declType)
{
	switch(declType)
	{
		case TYPE_VAR:
			fprintf(listing, "%8s", "variable");
			break;
		case TYPE_ARRAY:
			fprintf(listing, "%8s", "array");
			break;
		case TYPE_FUNC:
			fprintf(listing, "%8s", "function");
			break;
		default:
			fprintf(listing, "%s", "Unknown Declaration Type");
	}
}

void printOp(TokenType token)
{
	char buf[3] = {0};

	switch(token)
	{
		case PLUS:		buf[0] = '+'; break;
		case MINUS:		buf[0] = '-'; break;
		case TIMES:		buf[0] = '*'; break;
		case OVER:		buf[0] = '/'; break;
		case LT:		buf[0] = '<'; break;
		case GT:		buf[0] = '>'; break;
		case LE:		buf[0] = '<'; buf[1] = '='; break;
		case GE:		buf[0] = '>'; buf[1] = '='; break;
		case EQ:		buf[0] = '='; buf[1] = '='; break;
		case NE:		buf[0] = '!'; buf[1] = '='; break;
		case ASSIGN:	buf[0] = '='; break;
	}

	if(buf[0]) fprintf(listing, "%s\n", buf);
	else fprintf(listing, "Unknown Operator\n");
};

void printToken(TokenType token, const char *tokenString)
{
	int i, len = 8;
	char buffer[8] = {0};

	switch (token)
	{
		case IF:		case ELSE:		case WHILE:
		case RETURN:		case VOID:			case INT:
			for(i = 0; tokenString[i]; ++i) buffer[i] = (char)toupper(tokenString[i]);
			fprintf(listing, "%-*s\t%s\n", len, buffer, tokenString);
			break;
		case LPAREN:	case RPAREN:	case LBRACE:	case RBRACE:
		case LBRACKET:	case RBRACKET:	case SEMI:		case COMMA:
		case PLUS:		case MINUS:		case TIMES:		case OVER:
		case LT:		case LE:		case GT:		case GE:
		case EQ:		case NE:		case ASSIGN:
			fprintf(listing, "%-*s\t%s\n", len, tokenString, tokenString);
			break;
		case ENDFILE:
			fprintf(listing, "EOF\n");
			break;
		case NUM:
			fprintf(listing, "%-*s\t%s\n", len, "NUM", tokenString);
			break;
		case ID:
			fprintf(listing, "%-*s\t%s\n", len, "ID", tokenString);
			break;
		case COMMENTERROR:
			fprintf(listing, "%-*s\t%s\n", len, "ERROR", "Comment Error");
			break;
		case ERROR:
			fprintf(listing, "%-*s\t%s\n", len, "ERROR", tokenString);
			break;
		default: /* should never happen */
			fprintf(listing,"Unknown token: %d\n",token);
	}
}

TreeNode *newNode()
{
	int i;
	TreeNode *t = (TreeNode *)malloc(sizeof(TreeNode));

	if(!t) fprintf(listing, "Out of memory error at line %d\n", lineno);
	else
	{
		for(i = 0; i < MAXCHILDREN; ++i) t->child[i] = NULL;

		t->declType		= TYPE_NONE;
		t->dataType		= TYPE_VOID;
		t->parameter	= NULL;
		t->sibling		= NULL;
		t->lineno		= lineno;
	}
}

TreeNode *newStmtNode(StmtNodeKind detailKind)
{
	TreeNode *t = newNode();

	if(t)
	{
		t->nodeKind			= StmtNode;
		t->detailKind.stmt	= detailKind;
	}

	return t;
}

TreeNode *newDeclNode(DeclNodeKind detailKind)
{
	TreeNode *t = newNode();

	if(t)
	{
		t->nodeKind			= DeclNode;
		t->detailKind.decl	= detailKind;
	}

	switch(detailKind)
	{
		case KindVar:
			t->declType = TYPE_VAR;
			break;
		case KindArray:
			t->declType = TYPE_ARRAY;
			break;
		case KindFunc:
			t->declType = TYPE_FUNC;
			break;
	}

	return t;
}

TreeNode *newValNode(ValNodeKind detailKind)
{
	TreeNode *t = newNode();

	if(t)
	{
		t->nodeKind			= ValNode;
		t->detailKind.val	= detailKind;
	}

	if(detailKind == KindConst)
	{
		t->declType = TYPE_RVALUE;
		t->dataType = TYPE_INT;
	}

	return t;
}


char *copyString(char * s)
{
	int n;
	char *t;

	if(!s) return NULL;

	n = strlen(s) + 1;
	t = malloc(n);

	if(!t) fprintf(listing, "Out of memory error at line %d\n", lineno);
	else strcpy(t,s);

	return t;
}

/*
 *	utility macro function for indentation
 */
static indentno = 0;

#define INDENT_STEP	2
#define INDENT		indentno += INDENT_STEP
#define UNINDENT	indentno -= INDENT_STEP

/*
 *	utility function for print space
 */
static void printSpaces(void)
{
	int i;
	for (i = 0; i < indentno; ++i) fprintf(listing," ");
}

void printTree(TreeNode * tree)
{
	int i;
	int hasSibling = FALSE;

	INDENT;

	if(tree && tree->sibling)
	{
		hasSibling = TRUE;
		printSpaces();
		fprintf(listing, "(\n");

		INDENT;
	}

	while(tree)
	{
		printSpaces();

		if(tree->nodeKind == StmtNode)
		{
			switch(tree->detailKind.stmt)
			{
				case KindCompound:
					fprintf(listing, "Compound\n");
					break;
				case KindIf:
					fprintf(listing, "If\n");
					break;
				case KindWhile:
					fprintf(listing, "While\n");
					break;
				case KindReturn:
					fprintf(listing, "Return\n");
					break;
				case KindNop:
					fprintf(listing, "Nop\n");
					break;
				case KindSubscript:
					fprintf(listing, "Array Subscript\n");
					break;
				case KindCall:
					fprintf(listing, "Call\n");
					break;
				case KindOp:
					fprintf(listing, "Op: ");
					printOp(tree->attr.op);
					break;
				case KindParam:
					fprintf(listing, "Parameter: ");
				default:
					fprintf(listing, "Unknown Statement Node detailKind\n");
			}
		}
		else if(tree->nodeKind == ValNode)
		{
			switch(tree->detailKind.val)
			{
				case KindConst:
					fprintf(listing, "Const: %d\n", tree->attr.val);
					break;
				case KindId:
					fprintf(listing, "ID: %s\n", tree->attr.name);
					break;
				case KindType:
					if(tree->dataType == TYPE_INT) fprintf(listing, "Type: int\n");
					else if(tree->dataType == TYPE_VOID) fprintf(listing, "Type: void\n");
					else fprintf(listing, "Unknown Type\n");
					break;
				default:
					fprintf(listing, "Unknown Value Node detailKind\n");
			}
		}
		else if(tree->nodeKind == DeclNode)
		{
			switch(tree->detailKind.decl)
			{
				case KindVar:
					fprintf(listing, "Variable Declaration\n");
					break;
				case KindArray:
					fprintf(listing, "Array Declaration\n");
					break;
				case KindFunc:
					fprintf(listing, "Function Declaration\n");
					break;
				default:
					fprintf(listing, "Unknown Function Node detailKind\n");
			}
		}
		else fprintf(listing,"Unknown node detailKind\n");

		for (i = 0;i < MAXCHILDREN; ++i) printTree(tree->child[i]);
		tree = tree->sibling;
	}

	if(hasSibling)
	{
		UNINDENT;

		printSpaces();
		fprintf(listing, ")\n");
	}

	UNINDENT;
}

