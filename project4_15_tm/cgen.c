/****************************************************/
/* File: cgen.c                                     */
/* The code generator implementation                */
/* for the TINY compiler                            */
/* (generates code for the TM machine)              */
/* Compiler Construction: Principles and Practice   */
/* Kenneth C. Louden                                */
/****************************************************/

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
			cgen(p1);
			cgen(p2);

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
				emitRM_Abs("LDA", ac, currentLoc, "Else, jump to finish");		//ujp L2
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

		ReturnK:
			if (TraceCode) emitComment("-> Return");
				
			p1 = tree->child[0];
			cGen(p1);
			emitRM("LD", pc, -1, fp, "jmp to return addr");

			if (TraceCode) emitComment("<- Return");
			break;

		
      default:
         break;
    }
} /* genStmt */

/* Procedure genExp generates code at an expression node */
static void genExp( TreeNode * tree)
{ int loc;

  int flag;
  TreeNode * p1, * p2;
  switch (tree->kind.exp) {

    case ConstK :
      if (TraceCode) emitComment("-> Const") ;
      /* gen code to load integer constant using LDC */
      emitRM("LDC",ac,tree->attr.val,0,"load const");
      if (TraceCode)  emitComment("<- Const") ;
      break; /* ConstK */
    
    case IdK :
      if (TraceCode) emitComment("-> Id") ;
//      loc = st_lookup(tree->attr.name);
	  loc = st_get_target_loc(tree->attr.name, &flag);
      emitRM("LD",ac,loc,gp,"load id value");
      if (TraceCode)  emitComment("<- Id") ;
      break; /* IdK */

	case IdarrayK:
		break;



    case OpK :
         if (TraceCode) emitComment("-> Op") ;
         p1 = tree->child[0];
         p2 = tree->child[1];
         /* gen code for ac = left arg */
         cGen(p1);
         /* gen code to push left operand */
         emitRM("ST",ac,tmpOffset--,mp,"op: push left");
         /* gen code for ac = right operand */
         cGen(p2);
         /* now load left operand */
         emitRM("LD",ac1,++tmpOffset,mp,"op: load left");
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
				emitRM("JGP",ac,2,pc,"br if true");
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
		
		if (TraceCode) emitComment("<- Assign");
		break;


	case CallK:
		if (TraceCode) emitComment("-> Call");

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

static void getDec(TreeNode *tree){
 int loc;
  TreeNode * p1, * p2;
  switch (tree->kind.exp) {

    case IntK :			/* global variable */
	  //added
	  emitRM("LDA",sp,-1,sp,"Decl(Decrease sp : not array");
      //
	  break; /* IntK */
    
    case ArrayK :
      //added
	  int i;
	  for(i=0;i<(tree->child[1])->attr.val;i++)
	  	emitRM("LDA",sp,-1,sp,"Decl (Decrease sp : array)");
      //
	  break; /* ArrayK */

    case FunK :
	 
      break; /* FunK */

    case LocalK:		/* Local variable */
	  //added
	  emitRM("LDA",sp,-1,sp,"Decl(Decrease sp : not array)");
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

   cGen(syntaxTree);
   /* finish */
   emitComment("End of execution.");
   emitRO("HALT",0,0,0,"");
}
