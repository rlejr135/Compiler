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


ParamList check_paramlist, walk;


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
			int isarr_flag, paramcheck_flag, VPF_flag;
			static int main_location=-1, main_flag=0;
			char err_msg[50];
			char *func_name;
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
								typeError(t, "Error, No decl and used!");
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
									
									st_lookup_data((t->child[0])->attr.name, &isarr_flag, &VPF_flag);
									if (st_lookup((t->child[0])->attr.name) == -1){
											typeError(t->child[0], "Error, No decl and used!");
									}
									else if (isarr_flag == NOT_ARRAY){
											sprintf(err_msg, "[%s] is not array variable.", t->child[0]->attr.name);
											typeError(t->child[0], err_msg);
									}
									else{
											st_insert((t->child[0])->attr.name, (t->child[0])->lineno, 0, 0, 0, 0, 0);
									}

						break;

					case TypeK:
						break;

					case ParamK:
						if (t->child[0] == NULL) { break;}
//						printf("[%s]\n", glo_func_name);
						if (first_param_flag == FALSE ){
								first_param_flag = TRUE;

								if (t->child[2] == NULL){
										st_make_new_scope(PARAM_INT);
								}
								else if (t->child[2] != NULL){
										st_make_new_scope(PARAM_ARRAY);
								}
						}
						else{
								if (t->child[2] == NULL){
										st_attach_param(PARAM_INT);
								}
								else if (t->child[2] != NULL){
										st_attach_param(PARAM_ARRAY);
								}
						}
					

						if (t->child[2] != NULL){ 		// array parameter
								st_insert((t->child[1])->attr.name, (t->child[1])->lineno, 0, PARAM, IS_ARRAY, 0, TYPE_ARRAY);
						}
						else{													//not array parameter
								st_insert((t->child[1])->attr.name, (t->child[1])->lineno, 0, PARAM, NOT_ARRAY, 0, TYPE_INT);
						}
						
						break;

					case CallK:
								st_lookup_data(t->attr.name, &isarr_flag, &VPF_flag);
								if (st_lookup(t->attr.name) == -1){
											typeError(t, "Error, No decl and used!");
								}
								else if (VPF_flag != FUNC){
											typeError(t, "Error, you can only call function!");
								}
								else{
											st_insert(t->attr.name, t->lineno, 0, FUNC, NOT_ARRAY, 0, 0);
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
												typeError(t->child[1], "Already defined name!");
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
												typeError(t->child[1], "Already defined name!");
									}
									break;

							case FunK:

									func_name = (char*)malloc(sizeof(char) * strlen(t->child[1]->attr.name));
									strcpy(func_name, t->child[1]->attr.name);

									glo_func_name = func_name;
//									printf("[%s]\n", glo_func_name);
									if (st_lookup_curr_scope((t->child[1])->attr.name) == -1){
											
											
											//location for function at scope level 0
											if(curr_scope_level == 0){
													
													//main function declaration
													if(strcmp(t->child[1]->attr.name, "main") == 0){		  
															
															//main function must not be Void type
															if(t->child[0]->type == Integer){
																	typeError(t->child[1], "main function must be Void type");
															}

															//main function should not have parameters
															else if(t->child[2]->child[0] != NULL){
																	typeError(t->child[1], "main function should not have parameters");
															}


															else{
																	main_flag = 1;
																	main_location = location_func;
															}
													}
													
													//main function should be defined last
													if(main_flag && (location_func > main_location))
															typeError(t->child[1], "main function is not declared last");

													else
															location_func++;
											}

											if (t->child[0]->type == Integer)
												st_insert((t->child[1])->attr.name, (t->child[1])->lineno, location_func, FUNC, NOT_ARRAY, 0, TYPE_INT);

											else if (t->child[0]->type == Void)
												st_insert((t->child[1])->attr.name, (t->child[1])->lineno, location_func, FUNC, NOT_ARRAY, 0, TYPE_VOID);
									}
									else{
												typeError(t, "Already defined name!");
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
/*  
	if(!Error){
		if (TraceAnalyze)
  	{ fprintf(listing,"\nSymbol table:\n\n");
    	printSymTab(listing);
  	}
	}*/
}

static void typeError(TreeNode * t, char * message)
{ fprintf(listing,"Type error at line %d: %s\n",t->lineno,message);
  Error = TRUE;
}

/* Procedure checkNode performs
 * type checking at a single tree node
 */
static void checkNode(TreeNode * t)
{ 
	int isarr_flag, func_type, ret_err, VPF_flag;
	int paramcheck_flag = 0;
	char err_msg[50];
	TreeNode *tmp;
	switch (t->nodekind)
  { 
    case StmtK:
      switch (t->kind.stmt)
      { 
				case CompoundK:
					break;

				case ExpressionK:
					break;

				case SelectionK:
		/*			if (t->child[0]->type != Boolean){
								typeError(t, "Selection condition must have Boolean type.");
					}*/
					if (t->child[0]->type == Void || t->child[0]->type == Array){
								typeError(t, "Selection condition must have Boolean or Integer type.");
					}


					break;

				case IterationK:
					if (t->child[0]->type == Void || t->child[0]->type == Array){
								typeError(t, "Iteration condition must have Boolean or Integer type.");
					}
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

					if (t->child[0] == NULL) break;

					if (t->child[0]->type != t->child[1]->type){
								typeError(t, "Op applied to non-integer.");
					}

					if (t->attr.op == LE || t->attr.op == LT || t->attr.op == GT || t->attr.op == GE || t->attr.op == EQ || t->attr.op == NE){
								t->type = Boolean;
					}
					else{
								t->type = Integer;
					}
					
          break;
        
				case ConstK:
					t->type = Integer;
					break;

				case AssignK:
					if (t->child[0]->type == Boolean && t->child[1]->type == Integer){			// assign type check
								typeError(t->child[0], "Unmatched type between l-value and r-value.");
					}

					t->type = t->child[0]->type;

					break;

				case IdarrayK:
					t->type = Integer;
					if (t->child[1]->type != Integer){								// array index type check
								typeError(t->child[0], "Array index error.");
					}
		/*			
					st_lookup_data(t->child[0]->attr.name, &isarr_flag);
					if (isarr_flag == NOT_ARRAY){
								sprintf(err_msg, "[%s] is not array variable.", t->child[0]->attr.name);
								typeError(t->child[0], err_msg);
					}*/
					break;

				case TypeK:
					break;

				case ParamK:
					if (t->type == Void) break;
					if (t->child[0]->type == Void){									// Void type check.
								typeError(t->child[1], "Unvalid Parameter type. Parameter must not have void type.");
					}

					if (t->child[2] == NULL){
								t->type = Integer;
					}
					else if (t->child[2] != NULL){
								t->type = Array;
					}

					break;

				case CallK:

					check_paramlist = st_find_func_data(t->attr.name, &func_type);
					tmp = t->child[0];
				

					while (1){

//							printf("[%s %d %d] ", tmp->attr.name, tmp->nodekind, tmp->kind.exp);
							if (tmp->nodekind == ExpK && tmp->kind.exp == ConstK){
										if (tmp->sibling == NULL)
														break;
										
										tmp = tmp->sibling;
										continue;
							}
							st_lookup_data(tmp->attr.name, &isarr_flag, &VPF_flag);

							if (isarr_flag == IS_ARRAY){
										tmp->type = Array;
							}
							else{
										tmp->type = Integer;
							}
							if (tmp->sibling == NULL){
									break;
							}

							tmp = tmp->sibling;
					}
					tmp = t->child[0];
					while (1){
//									printf("%d %d\n", tmp->type, check_paramlist->type);
							if (tmp->type != check_paramlist->type){		// type error
											paramcheck_flag = 1;
											break;
							}

							if (tmp->sibling != NULL && check_paramlist->next != NULL){
										tmp = tmp->sibling;
										check_paramlist = check_paramlist->next;
							}
							else if (tmp->sibling == NULL && check_paramlist->next == NULL){
										break;
							}
							else{																				// count error
										paramcheck_flag = 2;
										break;
							}
							t->type = func_type;
					}
					
					if (paramcheck_flag == 1){				// When parameter type is dirrerent.
								typeError(t, "Parameter type is different");
					}
					else if (paramcheck_flag == 2){		// When parameter count is different.
								typeError(t, "Parameter count is different");
					}


					break;

        default:
          break;
      }
      break;

		case DecK:
			switch(t->kind.dec){
					case IntK:
							if(t->child[0]->type == Void){								// Void type check.
										typeError(t->child[1], "Unvalid variable type. Variable must not have void type.");
							}
							break;

					case ArrayK:
							if(t->child[0]->type == Void){								// Void type check.
										typeError(t->child[1], "Unvalid variable type. Array Variable must not have void type.");
							}
							break;

					case FunK:
							tmp = t->child[3]->child[1];
							func_type = 0;
							while(tmp!= NULL){
										if (tmp->nodekind == StmtK && tmp->kind.stmt == ReturnK){
												ret_err = 1;
												if (tmp->child[0] != NULL){
														if (tmp->child[0]->kind.exp == ConstK){
																	func_type = Integer;
														}
														else if (tmp->child[0]->attr.name == NULL){
																	func_type = tmp->child[0]->type;
														}
														else{
																	st_lookup_data(tmp->child[0]->attr.name, &isarr_flag, &VPF_flag);
																	func_type = isarr_flag;
														}
												}
												else{
														func_type = Void;
												}

										}
										if (tmp->sibling == NULL)
														break;
										else{
														tmp = tmp->sibling;
										}
							}
							if (t->child[0]->type == Void && ret_err == 1){
										typeError(t, "Function type is void, but it have return");
							}
	
							if (t->child[0]->type != func_type){
										typeError(t, "Function type and return type unmatched");
							}
							break;

					case LocalK:
							if(t->child[0]->type == Void){								// Void type check.
										typeError(t->child[1], "Unvalid variable type. Variable must not have void type.");
							}
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
{
			st_set_head();
			traverse(syntaxTree,nullProc,checkNode);

  
	if(!Error){
		if (TraceAnalyze)
  	{ fprintf(listing,"\nSymbol table:\n\n");
    	printSymTab(listing);
  	}
	}
}
