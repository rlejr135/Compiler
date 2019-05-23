/****************************************************/
/* File: analyze.c                                  */
/* Semantic analyzer implementation                 */
/* for the TINY compiler                            */
/* Compiler Construction: Principles and Practice   */
/* Kenneth C. Louden                                */
/****************************************************/

#include "globals.h"
#include "symtab.h"
#include "analyze.h"

/* counter for variable memory locations */
static int location = 0;

/* Procedure traverse is a generic recursive 
 * syntax tree traversal routine:
 * it applies preProc in preorder and postProc 
 * in postorder to tree pointed to by t
 */
static void traverse( TreeNode * t,
               void (* preProc) (TreeNode *),
               void (* postProc) (TreeNode *) )
{ if (t != NULL)
  { preProc(t);
    { int i;
      for (i=0; i < MAXCHILDREN; i++)
        traverse(t->child[i],preProc,postProc);
    }
		// **** If exit Compound stmt, scope level down **** //
		if (t->kind.stmt == CompoundK){
				st_scope_back();
		}
    postProc(t);
    traverse(t->sibling,preProc,postProc);
  }
}

/* nullProc is a do-nothing procedure to 
 * generate preorder-only or postorder-only
 * traversals from traverse
 */
static void nullProc(TreeNode * t)
{ if (t==NULL) return;
  else return;
}

/* Procedure insertNode inserts 
 * identifiers stored in t into 
 * the symbol table 
 */
static void insertNode( TreeNode * t)
{ 
	switch (t->nodekind){ 
		case StmtK:
      	switch (t->kind.stmt)
      	{ 
					case CompoundK:
						st_make_new_scope(0);
						break;
							
        	case ExpressionK:					
/*          	if (st_lookup(t->attr.name) == -1)
          		// not yet in table, so treat as new definition 
            	st_insert(t->attr.name,t->lineno,location++,);
          	else
          	// already in table, so ignore location, 
            // 	 add line number of use only 
            	st_insert(t->attr.name,t->lineno,0);
*/        	break;
						
					case SelectionK:					// do not use
						break;

					case IterationK:					// do not use
						break;

					case ReturnK:							// do not use
						break;

					case ElseK:								// do not use
						break;

        	default:
          	break;
      	}
    break;


    case ExpK:
      	switch (t->kind.exp)
      	{ 
					case IdK:
          	if (st_lookup(t->attr.name) != -1){
            		st_insert(t->attr.name,t->lineno,0, VAR, NOT_ARRAY, 0, TYPE_INT);
						}
          	break;

					case OpK:								// do not use
						break;

					case ConstK:						// do not use
						break;

					case AssignK:						// do not use
						break;

					case IdarrayK:
									if (st_lookup((t->child[0])->attr.name) == -1){
											printf ("error, no dec and use\n");
									}
									else{
											st_insert((t->child[0])->attr.name, (t->child[0])->lineno, 0, 0, 0, 0, 0);
									}

						break;

					case TypeK:
						break;

					case ParamK:

						break;

					case CallK:
								if (st_lookup(t->attr.name) == -1){
											printf("error, no dec and use\n");
								}
								else{
											st_insert(t->attr.name, t->lineno, 0, 0, 0, 0, 0);
								}
						break;

        	default:
          	break;
      	}
    break;
		

		case DecK:
				switch(t->kind.dec){
							case IntK:
							case LocalK:
									if (st_lookup((t->child[1])->attr.name) == -1){
											st_insert((t->child[1])->attr.name, (t->child[1])->lineno, location++, VAR, NOT_ARRAY, 0, TYPE_INT);
									}
									else{
											st_insert((t->child[1])->attr.name, (t->child[1])->lineno, 0, VAR, NOT_ARRAY, 0, TYPE_INT);
									}
									break;

							case ArrayK:
									if (st_lookup((t->child[1])->attr.name) == -1){
											st_insert((t->child[1])->attr.name, (t->child[1])->lineno, location++, VAR, IS_ARRAY, (t->child[2])->attr.val, TYPE_ARRAY);
									}
									else{
											st_insert((t->child[1])->attr.name, (t->child[1])->lineno, 0, VAR, IS_ARRAY, (t->child[2])->attr.val, TYPE_ARRAY);
									}
									break;

							case FunK:
									if (st_lookup((t->child[1])->attr.name) == -1){
											st_insert((t->child[1])->attr.name, (t->child[1])->lineno, location++, FUNC, NOT_ARRAY, 0, TYPE_INT);
									}
									else{
											st_insert((t->child[1])->attr.name, (t->child[1])->lineno, 0, FUNC, NOT_ARRAY, 0, TYPE_INT);
									}
									break;

//							case LocalK:
//									break;

							default:
									break;
			}
			break;
    

		default:
      break;
  }
}

/* Function buildSymtab constructs the symbol 
 * table by preorder traversal of the syntax tree
 */
void buildSymtab(TreeNode * syntaxTree)
{
	//**** add proj3 ****//
	
	st_scope_init();

	//////////////////////
	traverse(syntaxTree,insertNode,nullProc);
  if (TraceAnalyze)
  { fprintf(listing,"\nSymbol table:\n\n");
    printSymTab(listing);
  }
}

static void typeError(TreeNode * t, char * message)
{ fprintf(listing,"Type error at line %d: %s\n",t->lineno,message);
  Error = TRUE;
}

/* Procedure checkNode performs
 * type checking at a single tree node
 */
static void checkNode(TreeNode * t)
{ switch (t->nodekind)
  { 
    case StmtK:
      switch (t->kind.stmt)
      { 
				case CompoundK:
					break;

				case ExpressionK:
					break;

				case SelectionK:
					break;

				case IterationK:
					break;

				case ReturnK:
					break;

				case ElseK:
					break;

				default:
					break;

				/*
				case IfK:
          if (t->child[0]->type == Integer)
            typeError(t->child[0],"if test is not Boolean");
          break;
        case AssignK:
          if (t->child[0]->type != Integer)
            typeError(t->child[0],"assignment of non-integer value");
          break;
        case WriteK:
          if (t->child[0]->type != Integer)
            typeError(t->child[0],"write of non-integer value");
          break;
        case RepeatK:
          if (t->child[1]->type == Integer)
            typeError(t->child[1],"repeat test is not Boolean");
          break;
        default:
          break;
				*/
      }
      break;
			
		case ExpK:
      switch (t->kind.exp)
      { 
				case IdK:
          t->type = Integer;
          break;
				
				case OpK:
          if ((t->child[0]->type != Integer) ||
              (t->child[1]->type != Integer))
            typeError(t,"Op applied to non-integer");
          if ((t->attr.op == EQ) || (t->attr.op == LT))
            t->type = Boolean;
          else
            t->type = Integer;
          break;
        
				case ConstK:
					break;

				case AssignK:
					break;

				case IdarrayK:
					break;

				case TypeK:
					break;

				case CallK:
					break;

        default:
          break;
      }
      break;

		case DecK:
			switch(t->kind.dec){
					case IntK:
							break;

					case ArrayK:
							break;

					case FunK:
							break;

					case LocalK:
							break;

					default:
							break;
			}
			break;


    default:
      break;
  }
}

/* Procedure typeCheck performs type checking 
 * by a postorder syntax tree traversal
 */
void typeCheck(TreeNode * syntaxTree)
{ traverse(syntaxTree,nullProc,checkNode);
}
