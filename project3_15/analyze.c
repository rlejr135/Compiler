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
extern int curr_scope_level;

static int location = 0;
static int location_up = 0;
static int location_down = -4;
static int location_func = -1;

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
		if (t->nodekind == StmtK && t->kind.stmt == CompoundK ){
				location_down = -4;
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

						if (func_flag == TRUE){
								func_flag = FALSE;
								first_param_flag = FALSE;
						}
						else{
								st_make_new_scope(0);
						}
						break;
							
        	case ExpressionK:					// do not use
	        	break;
						
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
						if (st_lookup(t->attr.name) == -1){
								typeError(t, "Error, No decl and used!\n");
						}
						else{
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
											typeError(t, "Error, No decl and used!\n");
									}
									else{
											st_insert((t->child[0])->attr.name, (t->child[0])->lineno, 0, 0, 0, 0, 0);
									}

						break;

					case TypeK:
						break;

					case ParamK:
						if (t->child[0] == NULL) break;
						if (first_param_flag == FALSE ){
								first_param_flag = TRUE;

								st_make_new_scope(0);
						}
					

						if (t->child[2] != NULL){ 		// array parameter
								st_insert((t->child[1])->attr.name, (t->child[1])->lineno, 0, PARAM, IS_ARRAY, 0, TYPE_ARRAY);
						}
						else{													//not array parameter
								st_insert((t->child[1])->attr.name, (t->child[1])->lineno, 0, PARAM, NOT_ARRAY, 0, TYPE_INT);
						}
						
						break;

					case CallK:
								if (st_lookup(t->attr.name) == -1){
											typeError(t, "Error, No decl and used!\n");
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
									if (st_lookup_curr_scope((t->child[1])->attr.name) == -1){

											if (t->child[2] == NULL){				// not array
														if(curr_scope_level == 0){
																location_up += 4;
																st_insert((t->child[1])->attr.name, (t->child[1])->lineno, location_up, VAR, NOT_ARRAY, 0, TYPE_INT);
														}
														else{
																location_down -= 4;
																st_insert((t->child[1])->attr.name, (t->child[1])->lineno, location_down, VAR, NOT_ARRAY, 0, TYPE_INT);
														}
											}
											else if (t->child[2] != NULL){	
														location_down -= 4 * t->child[2]->attr.val;
														st_insert((t->child[1])->attr.name, (t->child[1])->lineno, location_down , VAR, IS_ARRAY, (t->child[2])->attr.val, TYPE_ARRAY);
											}
									}
									else{
												typeError(t, "Already defined name!\n");
									}


									break;

							case ArrayK:
									if (st_lookup_curr_scope((t->child[1])->attr.name) == -1){
											if(curr_scope_level == 0){
												location_up += 4 * t->child[2]->attr.val;	//location for array (scope level == 0)
												st_insert((t->child[1])->attr.name, (t->child[1])->lineno, location_up, VAR, IS_ARRAY, (t->child[2])->attr.val, TYPE_ARRAY);
											}

											else{
												location_down -= 4 * t->child[2]->attr.val;	//location for array (scope level != 0)
												st_insert((t->child[1])->attr.name, (t->child[1])->lineno, location_down, VAR, IS_ARRAY, (t->child[2])->attr.val, TYPE_ARRAY);
											}
									}
									else{
												typeError(t, "Already defined name!\n");
									}
									break;

							case FunK:

									if (st_lookup_curr_scope((t->child[1])->attr.name) == -1){
											
											//location for function at scope level 0
											if(curr_scope_level == 0)
															location_func++;

											if (t->child[0]->type == Integer)
												st_insert((t->child[1])->attr.name, (t->child[1])->lineno, location_func, FUNC, NOT_ARRAY, 0, TYPE_INT);

											else if (t->child[0]->type == Void)
												st_insert((t->child[1])->attr.name, (t->child[1])->lineno, location_func, FUNC, NOT_ARRAY, 0, TYPE_VOID);
									}
									else{
												typeError(t, "Already defined name!\n");
									}

									if (t->child[2]->child[0] != NULL)
											func_flag = TRUE;

									break;

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
	func_flag = FALSE;
	first_param_flag = FALSE;

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
