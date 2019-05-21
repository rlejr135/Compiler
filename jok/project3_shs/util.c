/****************************************************/
/* File: util.c                                     */
/* Utility function implementation                  */
/* for the TINY compiler                            */
/* Compiler Construction: Principles and Practice   */
/* Kenneth C. Louden                                */
/*                                                  */
/* modified by HYEONSOO SHIN, 20111636 (March, 2016)*/
/****************************************************/

#include "globals.h"
#include "util.h"
#include "scan.h"

/* Procedure printToken prints a token 
 * and its lexeme to the listing file
 */
void printToken( TokenType token, const char* tokenString )
{ 
  /* For printing operand of proj2*/
  fprintf(listing,"%s", TokenTypeLabel[token-ERROR+1]);

  return;
}

/* Function findSibling finds last sibling of input TreeNode
 * and return the sibling TreeNode
 */
TreeNode * findSibling(TreeNode * node)
{
	if(node == NULL)
	    fprintf(listing,"findSibling NULL\n");

	TreeNode * t = node;
	while(t->sibling != NULL)
		t = t->sibling;
	return t;
}

/* Function newStmtNode creates a new statement
 * node for syntax tree construction
 */
TreeNode * newStmtNode(StmtKind kind)
{ TreeNode * t = (TreeNode *) malloc(sizeof(TreeNode));
  int i;
  if (t==NULL)
    fprintf(listing,"Out of memory error at line %d\n",lineno);
  else {
    for (i=0;i<MAXCHILDREN;i++) t->child[i] = NULL;
    t->sibling = NULL;
    t->nodekind = StmtK;
    t->kind.stmt = kind;
    t->lineno = lineno;
	t->nodeIndex = nodeIndex++;
  }
  return t;
}

/* Function newExpNode creates a new expression 
 * node for syntax tree construction
 */
TreeNode * newExpNode(ExpKind kind)
{ TreeNode * t = (TreeNode *) malloc(sizeof(TreeNode));
  int i;
  if (t==NULL)
    fprintf(listing,"Out of memory error at line %d\n",lineno);
  else {
    for (i=0;i<MAXCHILDREN;i++) t->child[i] = NULL;
    t->sibling = NULL;
    t->nodekind = ExpK;
    t->kind.exp = kind;
    t->lineno = lineno;
    t->type = Void;
	t->nodeIndex = nodeIndex++;
  }
  return t;
}

/* Function newDeclNode creates a new statement
 * node for syntax tree construction
 */
TreeNode * newDeclNode(DeclKind kind)
{ TreeNode * t = (TreeNode *) malloc(sizeof(TreeNode));
  int i;
  if (t==NULL)
    fprintf(listing,"Out of memory error at line %d\n",lineno);
  else {
    for (i=0;i<MAXCHILDREN;i++) t->child[i] = NULL;
    t->sibling = NULL;
    t->nodekind = DeclK;
    t->kind.decl = kind;
    t->lineno = lineno;
	t->type = 0;
	t->arrayIndex = -1;
	t->global = 0;
	t->nodeIndex = nodeIndex++;
  }
  return t;
}

/* Function copyString allocates and makes a new
 * copy of an existing string
 */
char * copyString(char * s)
{ int n;
  char * t;
  if (s==NULL) return NULL;
  n = strlen(s)+1;
  t = malloc(n);
  if (t==NULL)
    fprintf(listing,"Out of memory error at line %d\n",lineno);
  else strcpy(t,s);
  return t;
}

/* Variable indentno is used by printTree to
 * store current number of spaces to indent
 */
static indentno = 0;
/* macros to increase/decrease indentation */
#define INDENT indentno+=4
#define UNINDENT indentno-=4
#define NEWLINE fprintf(listing, "\n");

/* printSpaces indents by printing spaces */
static void printSpaces(void)
{ int i;
  for (i=0;i<indentno;i++)
    fprintf(listing," ");
}

/* procedure printTree prints a syntax tree to the 
 * listing file using indentation to indicate subtrees
 */
void printTree( TreeNode * tree )
{ 
	int i;
   	
	if(tree == NULL)
		return;

	// first indent
    fprintf(listing, "    ");
	printSpaces();

	//line no
//	fprintf(listing, "%3d:", tree->nodeIndex);

	switch(tree->nodekind){
		case StmtK:
			printStmtK(tree);
			break;
		case ExpK:
			printExpK(tree);
			break;
		case DeclK:
			printDeclK(tree);
			break;
		default:
			break;
	}

	INDENT;
	for(i=0; i<MAXCHILDREN; i++) {
		if(tree->child[i] != NULL)
			printTree(tree->child[i]);
	}
	UNINDENT;
	if(tree->sibling != NULL) 
		printTree(tree->sibling);
}
void printStmtK( TreeNode * tree )
{
	switch (tree->kind.stmt) {
		case IfK:
				fprintf(listing, "IF Statement");
			break;
		case ElseK:
				fprintf(listing, "ELSE Statement");
			break;
		case WhileK:
				fprintf(listing, "WHILE Statement");
			break;
		case ReturnK:
				fprintf(listing, "RETURN Statement");
			break;
		case CompoundK:
				fprintf(listing, "Compound Statement");
			break;
		case AssignK:
				fprintf(listing, "Assign Statement");
			break;
		case ExpStmtK:
				fprintf(listing, "Expression Statement");
			break;
		case CallK:
				fprintf(listing, "Call Statement.   Id: %s", tree->attr.name);
			break;
		default :
			break;
	}
	NEWLINE;
}
void printExpK( TreeNode * tree )
{
	switch (tree->kind.exp) {
		case OpK:
				fprintf(listing, "Op: ");
				printToken(tree->attr.op, NULL);
			break;
		case ConstK:
				fprintf(listing, "Const: %d", tree->attr.val);
			break;
		case IdK:
				fprintf(listing, "Id: %s", tree->attr.name);
				if(tree->type == IntegerArray)
					fprintf(listing, "  Array");
			break;
		case TermK:
				fprintf(listing, "Term");
			break;
		case FactorK:
				fprintf(listing, "Factor");
			break;
		default :
			break;
	}
	NEWLINE;
}

void printDeclK( TreeNode * tree )
{
	switch (tree->kind.decl) {
		case VarK:
				if (tree->type == IntegerArray && tree->arrayIndex != -1)
					fprintf(listing, "Variable Declaration.   Id: %s   Array Size: %d", tree->attr.name, tree->arrayIndex);
				else
					fprintf(listing, "Variable Declaration.   Id: %s", tree->attr.name);
				if(tree->global == 1)
					fprintf(listing, "    (GLOBAL)");
			break;
		case FunK:
				fprintf(listing, "Function Declaration.   Id: %s", tree->attr.name);
			break;
		case ParamListK:
					fprintf(listing, "Parameter.");
			break;
		case ParamK:
					fprintf(listing, "Parameter.   Id: %s", tree->attr.name);
					if(tree->type == IntegerArray)
						fprintf(listing, "  Array");
			break;
		case TypeK:
				if(tree->type == Void) 
					fprintf(listing, "Type : %s", "void");
				else if(tree->type == Integer)
					fprintf(listing, "Type : %s", "int");
				else
					fprintf(listing, "Type : %s", "array");
			break;
		default :
			break;
	}
	NEWLINE;
}


void pushSavedId(char savedId[])
{
	stackId * item = (stackId *) malloc(sizeof(stackId));
	
	if(top == NULL){
		top =  (stackId *) malloc(sizeof(stackId));
		top->head = NULL;
	}

	item->savedId = copyString(savedId);
	item->head = top->head;
	top->head = item;
}
char* popSavedId(){
	stackId *item = top->head;
	char *retId;

	if(item == NULL)
		return NULL;

	top->head = item->head;
	retId = item->savedId;
	free(item);
	
	return retId;
}
