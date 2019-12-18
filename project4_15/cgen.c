/****************************************************/
/* File: cgen.c                                     */
/* The code generator implementation                */
/* for the TINY compiler                            */
/* (generates code for the TM machine)              */
/* Compiler Construction: Principles and Practice   */
/* Kenneth C. Louden                                */
/****************************************************/

#include <stdio.h>
#include "globals.h"
#include "symtab.h"
#include "code.h"
#include "cgen.h"

/* tmpOffset is the memory offset for temps
   It is decremented each time a temp is
   stored, and incremeted when loaded again
*/
static int tmpOffset = 0;

/* prototype for internal recursive code generator */
static void cGen (TreeNode * tree);

/* Procedure genStmt generates code at a statement node */
static void genStmt( TreeNode * tree)
{ TreeNode * p1, * p2, * p3;
  int savedLoc1,savedLoc2,currentLoc;
  int loc;
  switch (tree->kind.stmt) {

		case CompoundK:
			if (TraceCode) emitComment("-> Compound");
		
			st_gen_down();

			p1 = tree->child[0];
			p2 = tree->child[1];
			cGen(p1);
			cGen(p2);

			st_gen_up();
				
			if (TraceCode) emitComment("<- Compound");
	  		break;

		case ExpressionK:
	//		if (TraceCode) emitComment("-> Expression");

	//		if (TraceCode) emitComment("<- Expression");
	 	    break;

		case SelectionK:
			if (TraceCode) emitComment("-> If");

			p1 = tree->child[0];
			p2 = tree->child[1];
			p3 = tree->child[2];

			cGen(p1); 										// E1

			savedLoc1 = emitSkip(1);
			emitComment("if condition is true, go down");	// for fjp L1

			cGen(p2);										// S1


			if (p3 != NULL){
				savedLoc2 = emitSkip(1);				
				emitComment("else part is exist");			// for ujp L2
			}

			currentLoc = emitSkip(0);						// Lab L1
			emitBackup(savedLoc1);
			emitRM_Abs("JEQ", ac, currentLoc, "if, jump to finish or else");	//fjp L1
			emitRestore();


			if (p3 != NULL){
				cGen(p3);									// S2
				
				currentLoc = emitSkip(0);					// Lab L2
				emitBackup(savedLoc2);
				emitRM_Abs("LDA", pc, currentLoc, "Else, jump to finish");		//ujp L2
				emitRestore();
			}



			if (TraceCode) emitComment("<- If");
			break;

		case ElseK:
			if (TraceCode) emitComment("-> Else");
			
			p1 = tree->child[0];
			cGen(p1);

			if (TraceCode) emitComment("<- Else");
			break;

		case IterationK:
			if (TraceCode) emitComment("-> While");

			p1 = tree->child[0];
			p2 = tree->child[1];
			

			/* While (E) S;*/
			savedLoc1 = emitSkip(0);			// save L1 location
			
			cGen(p1);							// E;
			
			savedLoc2 = emitSkip(1);			// for later

			cGen(p2);							// S;
			emitRM_Abs("LDA", pc, savedLoc1, "while : go to while loop");		//ujp L1
			currentLoc = emitSkip(0);			// for save now loc 			save L2 location

			emitBackup(savedLoc2);				// insert E's next
			emitRM_Abs("JEQ", ac, currentLoc, "while : go back to body" );		// fjp L2
			emitRestore();





			if (TraceCode) emitComment("<- While");
			break;

		case ReturnK:
			if (TraceCode) emitComment("-> Return");
//			fprintf(listing, "In return stmt\n");	
			p1 = tree->child[0];
			cGen(p1);

//			fprintf(listing, "[%d]\n", p1);
			emitRM("LD", pc, -1, fp, "jmp to return addr");

			if (TraceCode) emitComment("<- Return");
			break;

		
      default:
         break;
    }
} /* genStmt */


int isAddr;
int Addr_level[100];
int addr_lev = 0;
void store_addr_lev(){
	Addr_level[addr_lev++] = isAddr;
}
void restore_addr_lev(){
	isAddr = Addr_level[--addr_lev];
}

int isArg = FALSE;
/* Procedure genExp generates code at an expression node */
static void genExp( TreeNode * tree)
{ int loc;

  int global_flag;
  TreeNode * p1, * p2;
  switch (tree->kind.exp) {

    case ConstK :
      if (TraceCode) emitComment("-> Const") ;
      /* gen code to load integer constant using LDC */
      emitRM("LDC",ac,tree->attr.val,0,"load const val");
      if (TraceCode)  emitComment("<- Const") ;
      break; /* ConstK */
    
    case IdK :
      if (TraceCode) emitComment("-> Id") ;
//      loc = st_lookup(tree->attr.name);

	  global_flag = FALSE;
	  loc = st_get_target_loc(tree->attr.name, &global_flag);

		if (isAddr == FALSE){  			// when it is r-value
			  if (global_flag == TRUE){			// variable is global
				  emitRM("LD", ac, -1 * loc, gp, "store global variable");
			  }
			  else if (global_flag == FALSE){	// variable is local
				  emitRM("LD", ac, loc, fp, "store local variable");
			  }
		}
		else if (isAddr == TRUE){		// when it is l-value
			  if (global_flag == TRUE){			// variable is global
				  emitRM("LDA", ac, -1 * loc, gp, "store global variable");
			  }
			  else if (global_flag == FALSE){	// variable is local
				  emitRM("LDA", ac, loc, fp, "store local variable");
			  }
		}
      if (TraceCode)  emitComment("<- Id") ;
      break; /* IdK */

	case IdarrayK:
		if (TraceCode) emitComment("-> Idarray");

		store_addr_lev();
		isAddr = FALSE;
		cGen(tree->child[1]);				// index is stored in ac register
		restore_addr_lev();


		global_flag = FALSE;
		loc = st_get_target_loc(tree->child[0]->attr.name, &global_flag);


		if (isAddr == FALSE){				//when it is r-value
				if (global_flag == TRUE){
					emitRM("LDA", ac1, -1*loc, gp, "rvalue var gp");
				}
				else if (global_flag == FALSE){
					emitRM("LDA", ac1, loc, fp, "rvalue var fp");
				}

				emitRO("ADD", ac, ac1, ac, "calculate rvalue addr");
				emitRM("LD", ac, 0, ac, "store IdK arr value");
		}
		else if (isAddr == TRUE){			// when it is l-value
				if (global_flag == TRUE){
					emitRM("LDA", ac1, -1*loc, gp, "lvalue var gp");
				}
				else if (global_flag == FALSE){
					emitRM("LDA", ac1, loc, fp, "lvalue var fp");
				}

				emitRO("ADD", ac, ac1, ac, "calculate lvalue addr");
		}

		if (TraceCode) emitComment("<- Idarray");
		break;



    case OpK :
         if (TraceCode) emitComment("-> Op") ;
         p1 = tree->child[0];
         p2 = tree->child[1];
         /* gen code for ac = left arg */
         cGen(p1);
         /* gen code to push left operand */
         emitRM("ST",ac,0,mp,"op: push left");
		 emitRM("LDA", mp, 1, mp, "mp increase");

         /* gen code for ac = right operand */
         cGen(p2);
         /* now load left operand */
		 emitRM("LDA", mp, -1, mp, "mp decrease");
         emitRM("LD",ac1, 0,mp,"op: load left");

         switch (tree->attr.op) {
            case PLUS :
               emitRO("ADD",ac,ac1,ac,"op +");
               break;
            case MINUS :
               emitRO("SUB",ac,ac1,ac,"op -");
               break;
            case TIMES :
               emitRO("MUL",ac,ac1,ac,"op *");
               break;
            case OVER :
               emitRO("DIV",ac,ac1,ac,"op /");
               break;
            case LT :
               emitRO("SUB",ac,ac1,ac,"op <") ;
               emitRM("JLT",ac,2,pc,"br if true") ;
               emitRM("LDC",ac,0,ac,"false case") ;
               emitRM("LDA",pc,1,pc,"unconditional jmp") ;
               emitRM("LDC",ac,1,ac,"true case") ;
               break;
            case EQ :
               emitRO("SUB",ac,ac1,ac,"op ==") ;
               emitRM("JEQ",ac,2,pc,"br if true");
               emitRM("LDC",ac,0,ac,"false case") ;
               emitRM("LDA",pc,1,pc,"unconditional jmp") ;
               emitRM("LDC",ac,1,ac,"true case") ;
               break;

			case NE :
				emitRO("SUB",ac,ac1,ac,"op !=");
				emitRM("JNE",ac,2,pc,"br if true");
				emitRM("LDC",ac,0,pc,"false case");
				emitRM("LDA",pc,1,pc,"unconditional jmp");
				emitRM("LDC",ac,1,ac,"true cae");
				break;
			
			case LE :
				emitRO("SUB",ac,ac1,ac,"op <=");
				emitRM("JLE",ac,2,pc,"br if true");
				emitRM("LDC",ac,0,pc,"false case");
				emitRM("LDA",pc,1,pc,"unconditional jmp");
				emitRM("LDC",ac,1,ac,"true case");
				break;

			case GT:
				emitRO("SUB",ac,ac1,ac,"op >");
				emitRM("JGT",ac,2,pc,"br if true");
				emitRM("LDC",ac,0,ac,"false case");
				emitRM("LDA",pc,1,pc,"unconditional jmp");
				emitRM("LDC",ac,1,ac,"true case");
				break;

			case GE:
				emitRO("SUB",ac,ac1,ac,"op >=");
				emitRM("JGE",ac,2,pc,"br if true");
				emitRM("LDC",ac,0,ac,"false case");
				emitRM("LDA",pc,1,pc,"unconditional jmp");
				emitRM("LDC",ac,1,ac,"true case");
				break;

			
            default:
               emitComment("BUG: Unknown operator");
               break;
         } /* case op */
         if (TraceCode)  emitComment("<- Op") ;
         break; /* OpK */

	case AssignK:
		if (TraceCode) emitComment("-> Assign");

		p1 = tree->child[0];
		p2 = tree->child[1];
		store_addr_lev();

		isAddr = FALSE;
		cGen(p2);

		emitRM("ST", ac, 0, mp, "temporary store at mp");
		emitRM("LDA", mp, 1, mp, "mp stack increase");
		
		isAddr = TRUE;
		cGen(p1);

		emitRM("LDA", mp, -1, mp, "mp stack decrease");
		emitRM("LD", ac1, 0, mp, "temporary store at ac1");

		emitRM("ST", ac1, 0, ac, "store rvalue to lvalue's addr");


		restore_addr_lev();
		if (TraceCode) emitComment("<- Assign");
		break;


	case CallK:
		if (TraceCode) emitComment("-> Call");
		
		
		
		if (strcmp(tree->attr.name, "input") == 0 ){			// when it is input function
			emitRO("IN", ac, 0, 0, "input from user");
		}
		else if (strcmp(tree->attr.name, "output") == 0){		// when it is output function
			emitRM("LDA", sp, 1, sp, "adjust SP");	
			cGen(tree->child[0]);
			emitRO("OUT", ac, 0, 0, "output to user");
		}
		else{
			p1 = tree->child[0];  							// args list
			
			int args = 1;
			store_addr_lev();
			isArg = TRUE;
			while(p1 != NULL){
				isAddr = FALSE;
				cGen(p1);
				emitRM("ST", ac, -1, sp, "store argument");
				emitRM("LDA", sp, -1, sp, "sp decrease (for another argument)");

				args+=1;
				p1 = p1->sibling;
			}
			isArg = FALSE;
			restore_addr_lev();

			emitRM("LDA", sp, -2, sp, "sp decrease 2 (for control link and return address)");
			emitRM("ST", fp, 1, sp, "store fp in control link");
			emitRM("LDA", fp, 1, sp, "store new fp");

			emitRM("LDC", ac1, 3, 0, "calculate return addr");
			emitRM("LDA", ac2, 0, pc, "calculate return addr");
			emitRO("ADD", ac2, ac1, ac2, "calculate return addr");

			emitRM("ST", ac2, 0, sp, "store return address");
			emitRM_Abs("LDA", pc, st_get_emit_loc(tree->attr.name) + 1, "jump to user function");

			emitRM("LDA", sp, args, fp, "restore SP");
			emitRM("LD", fp, 0, fp, "restore FP");

		}

		if (TraceCode) emitComment("<- Call");
		break;

 	case TypeK:
		break;	
	case ParamK:
		break;
    default:
      break;
  }
} /* genExp */


int is_first_func = TRUE;
int globalDec_to_main = -1;

static void genDec(TreeNode *tree){
 int loc;
  TreeNode * p1, * p2;
  switch (tree->kind.exp) {

    case IntK :			/* global variable */
	  //added
	  emitRM("LDA",sp,-1,sp,"global Dec (decrease sp , not array");
      //
	  break; /* IntK */
    
    case ArrayK :
      //added
//	  for(int i=0;i<(tree->child[2])->attr.val;i++)
//	  	emitRM("LDA",sp,-1,sp,"Decl (Decrease sp : array)");

		emitRM("LDA", sp, -1 * tree->child[2]->attr.val, sp, "Dec (decrease sp, array)");
      
	  break; /* ArrayK */

    case FunK :
		if (TraceCode) emitComment("<- Function");
	 	
		p1 = tree->child[3];
		st_set_emit_loc(tree->child[1]->attr.name, emitSkip(0));


		if ((strcmp(tree->child[1]->attr.name, "main") == 0) && globalDec_to_main > -1){		// it is main function and there is at least one user defined function
			emitRM("LDA", fp, 0, sp, "main function start, fp and sp is start same location");

			emitBackup(globalDec_to_main);
			emitRM("LDA", pc, st_get_emit_loc(tree->child[1]->attr.name) - globalDec_to_main - 1, pc, "Jump to main function and start");
			emitRestore();
			
			cGen(p1);
		}
		else if (strcmp(tree->child[1]->attr.name, "main") == 0){
			cGen(p1);
		}
		else {												// user define function
			if (is_first_func == TRUE){
				globalDec_to_main = emitSkip(1);
				is_first_func = FALSE;
			}
			
			emitComment("user define function start");
			
			cGen(p1);
			emitRM("LD", pc, -1, fp, "jump to return address");

			emitComment("user define function finish");
		}

	 	if (TraceCode) emitComment("-> Function");
      break; /* FunK */

    case LocalK:		/* Local variable */
	  //added
	  emitRM("LDA",sp,-1,sp,"Dec(decrease sp , not array)");
	  //
	  break; /*LocalK */

    default:
      break;
  }

}

/* Procedure cGen recursively generates code by
 * tree traversal
 */
static void cGen( TreeNode * tree)
{ if (tree != NULL)
  { switch (tree->nodekind) {
      case StmtK:
        genStmt(tree);
        break;
      case ExpK:
        genExp(tree);
        break;
	  case DecK:
		genDec(tree);
		break;
      default:
        break;
    }
	if (isArg == FALSE)
	    cGen(tree->sibling);
  }
}

/**********************************************/
/* the primary function of the code generator */
/**********************************************/
/* Procedure codeGen generates code to a code
 * file by traversal of the syntax tree. The
 * second parameter (codefile) is the file name
 * of the code file, and is used to print the
 * file name as a comment in the code file
 */
void codeGen(TreeNode * syntaxTree, char * codefile)
{  char * s = malloc(strlen(codefile)+7);
   strcpy(s,"File: ");
   strcat(s,codefile);
   emitComment("TINY Compilation to TM Code");
   emitComment(s);
   /* generate standard prelude */
   emitComment("Standard prelude:");
//   emitRM("LD",mp,0,ac,"load maxaddress from location 0");

   emitRM("LD", gp, 0, ac, "load maxaddr from location 0");
   emitRM("LD", fp, 0, ac, "load maxaddr from location 0");
   emitRM("LD", sp, 0, ac, "load maxaddr from location 0");
   emitRM("ST", ac, 0, ac, "clear location 0");
   emitRM("LDA", sp, 1, sp, "Initialize");
   emitComment("End of standard prelude.");
   /* generate code for TINY program */

	st_gen_start();
	isAddr = FALSE;
   cGen(syntaxTree);
   /* finish */
   emitComment("End of execution.");
   emitRO("HALT",0,0,0,"");
}
