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
	//fprintf(listing, "\t\t");
	switch (token)
  { case IF: fprintf(listing,"IF"); break;
    case ELSE: fprintf(listing,"ELSE"); break;
    case WHILE: fprintf(listing,"WHILE"); break;
		case VOID: fprintf(listing, "VOID"); break;
		case INT: fprintf(listing, "INT"); break;
		case RETURN: fprintf(listing, "RETURN"); break;
    
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
	  case NUM:	fprintf(listing, "NUM"); break;
    case ID: fprintf(listing, "ID"); break;
    case ERROR:	fprintf(listing, "ERROR"); break;
		case COMERROR: fprintf(listing, "ERROR"); break;
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

// **** add proj2 **** //

TreeNode * newDecNode(DecKind kind)
{ TreeNode * t = (TreeNode *) malloc(sizeof(TreeNode));
  int i;
  if (t==NULL)
    fprintf(listing,"Out of memory error at line %d\n",lineno);
  else {
    for (i=0;i<MAXCHILDREN;i++) t->child[i] = NULL;
    t->sibling = NULL;
    t->nodekind = DecK;
    t->kind.dec = kind;
    t->lineno = lineno;
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
        case CompoundK:
          fprintf(listing,"Compound statement\n");
          break;
        case ExpressionK:
          fprintf(listing,"Expression statement\n");
          break;
        case SelectionK:
          fprintf(listing,"Selection statement\n");
          break;
        case IterationK:
          fprintf(listing,"Iteration statement\n");
          break;
        case ReturnK:
          fprintf(listing,"Return statement\n");
          break;
				case ElseK:
					fprintf(listing,"Else statement\n");
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
        case AssignK:
          fprintf(listing,"Assign statement\n");
          break;
				case IdK:
          fprintf(listing,"ID: %s\n",tree->attr.name);
          break;
				case IdarrayK:
					fprintf(listing, "Array\n");
					break;
				case TypeK:
					fprintf(listing, "Type: ");
					if (tree->type == Integer){
								fprintf(listing, "Int\n");
					}
					else if (tree->type == Void){
								fprintf(listing, "Void\n");
					}
					break;
				case ParamK:
					if (tree->child[0] == NULL){
								fprintf(listing, "Parameter: VOID\n");
					}
					else{
								fprintf(listing, "Parameter\n");
					}
					break;
				case CallK:
					fprintf(listing, "Call Func : %s\n", tree->attr.name);
					break;

        default:
          fprintf(listing,"Unknown ExpNode kind\n");
          break;
      }
    }
		//**** add proj2 ****//
		else if (tree->nodekind == DecK){
				switch (tree->kind.dec){
					case IntK:
						fprintf(listing, "Variable declaration\n");
						break;
					case ArrayK:
						fprintf(listing, "Array declaration\n");
						break;
					case FunK:
						fprintf(listing, "Function declaration\n");
						break;
					case LocalK:
						fprintf(listing, "Variable declaration (LOCAL)\n");
						break;

					default:
						fprintf(listing, "Unknown DecNode kind\n");
						break;
				}
		}
    else fprintf(listing,"Unknown node kind\n");
    for (i=0;i<MAXCHILDREN;i++){
         printTree(tree->child[i]);
		}
    tree = tree->sibling;
  }
  UNINDENT;
}
