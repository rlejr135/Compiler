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
  { 
	preProc(t);
    { int i;
      for (i=0; i < MAXCHILDREN; i++)
        traverse(t->child[i],preProc,postProc);
    }
	if(t->nodekind == StmtK && t->kind.stmt == CompoundK){
		currentScope--;
		st_goback();
	}
	postProc(t); 
    traverse(t->sibling,preProc,postProc);
	
  }
}

static void freeProc(TreeNode * t) {
	if (t==NULL) 
		return;
	
	if(t->nodekind == StmtK && t->kind.stmt == CompoundK){
		;
		//st_goback();
	}
	return ;	
}

/* nullProc is a do-nothing procedure to 
 * generate preorder-only or postorder-only
 * traversals from traverse
 */
static void nullProc(TreeNode * t)
{ if (t==NULL) return;
  else return;
}


static void onlyScope( TreeNode * t)
{ 
	switch (t->nodekind)
  { 
		case StmtK:
      switch (t->kind.stmt){ 
				case CompoundK:
       		if(isFuncDecl) {
						isFuncDecl = 0;
					}
					else{
						currentScope++;
        		st_setCurrentScope();
					}
          break;
      
				default:
          break;
      }
      break;
    
		case ExpK:
      switch (t->kind.exp)
      { case IdK:
          if (st_lookup(t->attr.name) == -1)//not in tables
             ;
          else // in tables
          break;
        default:
          break;
      }
      break;
    
		case DeclK:
      switch (t->kind.decl)
      { 
          case FunK:
			  currentFuncName = t->attr.name;
              isFuncDecl = 1;
              currentScope++;
              st_setCurrentScope();
              break;

          case ParamK:
          break;
		  case VarK:
		  break;
        default:
          break;
      }
      break;
    default:
      break;
  }
}

/* Procedure insertNode inserts 
 * identifiers stored in t into 
 * the symbol table 
 */

//ssg
static void scopeError(TreeNode * t, char * message)
{ 
  fprintf(listing,"Error at line %d: %s\n",t->lineno,message);
  Error = TRUE;
}
static void insertNode( TreeNode * t)
{ 
	switch (t->nodekind)
  { 
			case StmtK:
      		switch (t->kind.stmt){ 
							case CompoundK:
       						if(isFuncDecl) {
										isFuncDecl = 0;
									}
									else{
										currentScope++;
                		st_make(FALSE);
									}
          				break;

      				// ssg
							case CallK:
          				if( st_lookup(t->attr.name) == -1 )
              			scopeError(t, "Func not exist");
          				else if( strcmp(st_getVPF(t->attr.name) , "Func") != 0 )
              			scopeError(t, "Call not function");
        					break;
        	
							default:
          				break;
      		}
      		break;
    
			case ExpK:
      		switch (t->kind.exp){ 
							case IdK:
								//ssh
          			if (st_lookup(t->attr.name) == -1)
			  					scopeError(t, "Variable not exist");
          			else if( t->type == IntegerArray && st_getType(t->attr.name) != IntegerArray) {
              		scopeError(t,"Not array variable");
            			st_insert(t->attr.name,t->lineno,-1, NULL, -1, Void, FALSE);
          			}
          		break;
        
							default:
          		break;
      		}
      break;
    case DeclK:
      switch (t->kind.decl)
      { 
          case FunK:
              //ssg
              if( st_lookup(t->attr.name) == 0 )
                  scopeError(t, "Function declaration of a duplicated");
              if( strcmp(t->attr.name,"main") == 0){
                  if(t->child[0]->type != Void )
                      scopeError(t, "The main func is not Void type");
                  if(t->child[1]->child[0]->type != Void )
                      scopeError(t, "The param type of main func is not Void type");
              }
			  			currentFuncName = t->attr.name;
              st_insert(t->attr.name,t->lineno,0, "Func", -1, t->child[0]->type, TRUE);
              isFuncDecl = 1;
              currentScope++;
              st_make(TRUE);
              break;

          case ParamK: // int a
              if(t->attr.name != NULL){
                  //ssg 
                  if( st_lookup(t->attr.name) == currentScope )
                      scopeError(t, "Parameter declaration of a duplicated");
                  if( st_lookup(t->attr.name) == 0 && strcmp( st_getVPF(t->attr.name), "Func") == 0 )
                      scopeError( t, "The parameter id is already in use (as func id)");
                  if( t->child[0]->type == Void )
                      scopeError(t, "Void parameter type");

                  if( t->type == IntegerArray )
                    st_insert(t->attr.name,t->lineno,+4,"Param", 0,  t->type, TRUE);
                  else
                    st_insert(t->attr.name,t->lineno,+4,"Param", -1,  t->child[0]->type, TRUE);
              }
          break;
          case VarK:
          //ssg
            if( st_lookup(t->attr.name) == currentScope )
                  scopeError(t, "Variable declaration of a duplicated");
            if( st_lookup(t->attr.name) == 0 && strcmp( st_getVPF(t->attr.name), "Func") == 0 )
                scopeError( t, "The variable id is already in use (as func id)");
            if( t->child[0]->type == Void )
                  scopeError(t, "Void variable type");

          	st_insert(t->attr.name,t->lineno, currentScope == 0 ? +4 : -4 , "Var", t->arrayIndex, t->type == IntegerArray ? t->type : t->child[0]->type, TRUE);
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
	traverse(syntaxTree,insertNode,freeProc);
    //ssg
	/*if (TraceAnalyze)
		printSymTab(listing);*/
}

static void typeError(TreeNode * t, char * message)
{ fprintf(listing,"Error at line %d: %s\n",t->lineno,message);
  Error = TRUE;
}

/* Procedure checkNode performs
 * type checking at a single tree node
 */
static void checkNode(TreeNode * t)
// 현재에서
// t의 child들에 대한 type은 이미 게산이 완료되어있다.
// 이 함수에서, t에 대한 type을 계산하여 저장한다.

{ switch (t->nodekind)
  { case ExpK:
      switch (t->kind.exp)
      { case OpK:
		break;
        case ConstK:
		  t->type = Integer;
		  break;
        case IdK:
          // ssg
          if( t->type == IntegerArray && t->child[0]->type == Void)
              typeError(t,"Void array index");
          t->type = st_getType(t->attr.name);
          break;
		case FactorK:
		  break;
        default:
          break;
      }
      break;
    case StmtK:
      switch (t->kind.stmt)
      { 
	    case ExpStmtK:
			if((t->child[0]->type == Void) || (t->child[2]->type == Void))
				typeError(t,"Expression Statement is invalid");
			else
				t->type = Integer;
		  break;
	    case CompoundK:
          break;
        case IfK:
          if (t->child[0]->type == Void)
            typeError(t->child[0],"if test is not Integer");
          break;
		case WhileK:
		  if (t->child[0]->type == Void)
            typeError(t->child[0],"while test is not Integer");
		  break;
        case ReturnK:
          if(t->child[0] != NULL) // return asdf ;
              t->type = t->child[0]->type;
          else // return ;
              t->type = Void;
          // equal return type?
		  
		  if(t->type == Void && st_getType(currentFuncName) != Void)
					typeError(t,"return type is not equal to function type");
		  else if(t->type == Integer && st_getType(currentFuncName) == Void)
					typeError(t,"return type is not equal to function type");
		  else if(t->type == IntegerArray && st_getType(currentFuncName) == Void)
					typeError(t,"return type is not equal to function type");		
		  break;
		case CallK:
			if(checkParamCnt(t->child[0], t->attr.name) == FALSE)
				typeError(t,"the number of parameters is not matched");
			else if(checkParamType(t->child[0], t->attr.name) == FALSE)
				typeError(t,"the type of parameter is not matched");
			t->type = st_getType(t->attr.name);
		  break;
        case AssignK:
          if (t->child[0]->type == Void)
            typeError(t->child[0],"assignment of Void left-side value");
		  else if(t->child[1]->type == Void)
			  typeError(t->child[1],"assignment of Void right-side value");
		  else
			t->type = Integer;
          break;
        default:
          break;
      }
      break;
      //ssg
    case DeclK:
      switch (t->kind.decl)
      { 
          case FunK:
              if( strcmp( t->attr.name , "main" ) == 0 && st_hasNoSibling(t->attr.name ) == FALSE){
                    typeError(t,"The main func should be decl at the end");
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

int checkParamCnt(TreeNode * args, char * funcName){
	TreeNode * t;
	t = args;
	int cnt=0;	
		
	if(args != NULL){
		cnt = 1;
		while(t->sibling != NULL){
				t=t->sibling;
				cnt++;
		}
	}
	
	return st_checkFuncParamCnt(funcName, cnt);
}
  
int checkParamType(TreeNode * args, char * funcName){
	TreeNode * t;
	int idx=0;
	t = args;
	
	if(args != NULL) {
		while(t->sibling != NULL){
			if(st_checkFuncParamType(funcName, ++idx, t->type) == FALSE){
				return FALSE;
			}
			t=t->sibling;
		}
	}
	return 1;
}
  

/* Procedure typeCheck performs type checking 
 * by a postorder syntax tree traversal
 */
void typeCheck(TreeNode * syntaxTree)
{ 
	st_init();
	traverse(syntaxTree,onlyScope,checkNode);
}
