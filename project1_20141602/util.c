/****************************************************/
/* File: util.c                                     */
/* Utility function implementation                  */
/* for the TINY compiler                            */
/* Compiler Construction: Principles and Practice   */
/* Kenneth C. Louden                                */
/****************************************************/

#include "globals.h"
#include "util.h"

/* Procedure printToken prints a token 
 * and its lexeme to the listing file
 */
void printToken( TokenType token, const char* tokenString )
{ 
	fprintf(listing, "\t\t");
	switch (token)
  { case IF:
      fprintf(listing,"IF"); break;
    case THEN:
      fprintf(listing,"THEN"); break;
    case ELSE:
      fprintf(listing,"ELSE"); break;
    case END:
      fprintf(listing,"END"); break;
    case REPEAT:
      fprintf(listing,"REPEAT"); break;
    case UNTIL:
      fprintf(listing,"UNTIL"); break;
    case READ:
      fprintf(listing,"READ"); break;
    case WRITE:
      fprintf(listing,"WRITE"); break;
    case WHILE:
      fprintf(listing,"WHILE"); break;
		case VOID:
			fprintf(listing, "VOID"); break;
    case ASSIGN: fprintf(listing,"="); break;
    case LT: fprintf(listing,"<"); break;
    case EQ: fprintf(listing,"=="); break;
    case LPAREN: fprintf(listing,"("); break;
    case RPAREN: fprintf(listing,")"); break;
    case SEMI: fprintf(listing,";"); break;
    case PLUS: fprintf(listing,"+"); break;
    case MINUS: fprintf(listing,"-"); break;
    case TIMES: fprintf(listing,"*"); break;
    case OVER: fprintf(listing,"/"); break;
    case ENDFILE: fprintf(listing,"EOF"); break;
		case LCURLYB: fprintf(listing,"{"); break;
		case RCURLYB: fprintf(listing, "}"); break;
  	case LSQUAREB: fprintf(listing,"["); break;
		case RSQUAREB: fprintf(listing, "]"); break;
		case LE: fprintf(listing, "<="); break;
		case GT: fprintf(listing, ">"); break;
		case GE: fprintf(listing, ">="); break;
		case NE: fprintf(listing, "!="); break;
		case COMMA: fprintf(listing, ","); break;
   case NUM:
			fprintf(listing, "NUM");
      break;
    case ID:
			fprintf(listing, "ID");
      break;
    case ERROR:
			fprintf(listing, "ERROR");
      break;
		case COMERROR:
			fprintf(listing, "ERROR"); break;
		case INT: fprintf(listing, "INT"); break;
		case RETURN: fprintf(listing, "RETURN"); break;
    default: /* should never happen */
      fprintf(listing,"Unknown token: %d\n",token);
  }

	if (token == COMERROR)
			fprintf(listing, "\t\tComment Error\n");
	else
			fprintf(listing, "\t\t%s\n", tokenString);
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

// modify 
// static indentno=0 ; to static int indentno=0
static int indentno = 0;

/* macros to increase/decrease indentation */
#define INDENT indentno+=2
#define UNINDENT indentno-=2

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
{ int i;
  INDENT;
  while (tree != NULL) {
    printSpaces();
    if (tree->nodekind==StmtK)
    { switch (tree->kind.stmt) {
        case IfK:
          fprintf(listing,"If\n");
          break;
        case RepeatK:
          fprintf(listing,"Repeat\n");
          break;
        case AssignK:
          fprintf(listing,"Assign to: %s\n",tree->attr.name);
          break;
        case ReadK:
          fprintf(listing,"Read: %s\n",tree->attr.name);
          break;
        case WriteK:
          fprintf(listing,"Write\n");
          break;
        default:
          fprintf(listing,"Unknown ExpNode kind\n");
          break;
      }
    }
    else if (tree->nodekind==ExpK)
    { switch (tree->kind.exp) {
        case OpK:
          fprintf(listing,"Op: ");
          printToken(tree->attr.op,"\0");
          break;
        case ConstK:
          fprintf(listing,"Const: %d\n",tree->attr.val);
          break;
        case IdK:
          fprintf(listing,"Id: %s\n",tree->attr.name);
          break;
        default:
          fprintf(listing,"Unknown ExpNode kind\n");
          break;
      }
    }
    else fprintf(listing,"Unknown node kind\n");
    for (i=0;i<MAXCHILDREN;i++)
         printTree(tree->child[i]);
    tree = tree->sibling;
  }
  UNINDENT;
}
