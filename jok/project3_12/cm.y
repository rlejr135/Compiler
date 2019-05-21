%{ 
#define YYPARSER /* distinguishes Yacc output from other code files */ 
 
#include "globals.h" 
#include "util.h" 
#include "scan.h" 

static TreeNode *savedTree; /* stores syntax */ 
static int yylex(void);

%} 
 
%token IF ELSE INT RETURN VOID WHILE 
%token ID NUM
%token PLUS MINUS TIMES OVER
%token LT LE GT GE EQ NE ASSIGN
%token SEMI COMMA LPAREN RPAREN LBRACKET RBRACKET LBRACE RBRACE 
%token ERROR ENDFILE COMMENTERROR

%nonassoc NO_ELSE
%nonassoc ELSE


%% /* Grammar for C- */

program				: declaration_list		{ savedTree = $1; }
					;
declaration_list	: declaration_list declaration
						{
							struct treeNode *t = $1;
							while(t->sibling) t = t->sibling;

							t->sibling = $2;
							$$ = $1;
						}
					| declaration			{ $$ = $1; }
					;
declaration			: var_declaration		{ $$ = $1; }
					| fun_declaration		{ $$ = $1; }
					;
var_declaration		: type_specifier ID
						{
							$$ = newDeclNode(KindVar);
							$$->child[0] = $1;
							$$->child[1] = newValNode(KindId);

							$$->child[1]->attr.name = copyString(tokenBefore);
						}
					  SEMI
						{
							$$ = $3;
						}
					| type_specifier ID
						{
							$$ = newDeclNode(KindArray);
							$$->child[0] = $1;
							$$->child[1] = newValNode(KindId);
							$$->child[2] = newValNode(KindConst);

							$$->child[1]->attr.name = copyString(tokenBefore);
						}
					  LBRACKET NUM
						{
							$$ = $3;
							$$->child[2]->attr.val = atoi(tokenString);
						}
					  RBRACKET SEMI
						{
							$$ = $6;
						}
					;
type_specifier		: INT
						{
							$$ = newValNode(KindType);
							$$->dataType = TYPE_INT;
						}
					| VOID
						{
							$$ = newValNode(KindType);
							$$->dataType = TYPE_VOID;
						}
					;
fun_declaration		: type_specifier ID
						{
							$$ = newDeclNode(KindFunc);
							$$->child[0] = $1;
							$$->child[1] = newValNode(KindId);

							$$->child[1]->attr.name = copyString(tokenBefore);
						}
					  LPAREN params RPAREN compound_stmt
						{
							$$ = $3; 
							$$->child[2] = $5;
							$$->child[3] = $7;
						}
					;
params				: param_list
						{
							$$ = newStmtNode(KindParam);
							$$->child[0] = $1;
						}
					| VOID
						{
							$$ = newStmtNode(KindParam);
						}
					;
param_list			: param_list COMMA param
						{
							struct treeNode *t = $1;
							while(t->sibling) t = t->sibling;

							t->sibling = $3;
							$$ = $1;
						}
					| param					{ $$ = $1; }
					;
param				: type_specifier ID
						{
							$$ = newDeclNode(KindVar);
							$$->child[0] = $1;
							$$->child[1] = newValNode(KindId);

							$$->child[1]->attr.name = copyString(tokenBefore);
						}
					| type_specifier ID
						{
							$$ = newDeclNode(KindArray);
							$$->child[0] = $1;
							$$->child[1] = newValNode(KindId);
							$$->child[2] = newValNode(KindConst);

							$$->child[1]->attr.name	= copyString(tokenBefore);
							$$->child[2]->attr.val	= 0;
						}
					  LBRACKET RBRACKET
						{
							$$ = $3;
						}
					;
compound_stmt		: LBRACE local_declarations statement_list RBRACE
						{
							$$ = newStmtNode(KindCompound);

							if($2)
							{
								$$->child[0] = $2;
								$$->child[1] = $3;
							}
							else $$->child[0] = $3;
						}
					;
local_declarations	: local_declarations var_declaration
						{
							if($1)
							{
								struct treeNode *t = $1;
								while(t->sibling) t = t->sibling;

								t->sibling = $2;
								$$ = $1;
							}
							else $$ = $2;
						}
					|	{ $$ = NULL; }
					;
statement_list		: statement_list statement
						{
							if($1)
							{
								struct treeNode *t = $1;
								while(t->sibling) t = t->sibling;

								t->sibling = $2;
								$$ = $1;
							}
							else $$ = $2;
						}
					|	{ $$ = NULL; }
					;
statement			: expression_stmt		{ $$ = $1; }
					| compound_stmt			{ $$ = $1; }
					| selection_stmt		{ $$ = $1; }
					| iteration_stmt		{ $$ = $1; }
					| return_stmt			{ $$ = $1; }
					;
expression_stmt		: expression SEMI		{ $$ = $1; }
					| SEMI
						{
							$$ = newStmtNode(KindNop);
						}
					;
selection_stmt		: IF LPAREN expression RPAREN statement %prec NO_ELSE
						{
							$$ = newStmtNode(KindIf);
							$$->child[0] = $3;
							$$->child[1] = $5;
						}
					| IF LPAREN expression RPAREN statement ELSE statement
						{
							$$ = newStmtNode(KindIf);
							$$->child[0] = $3;
							$$->child[1] = $5;
							$$->child[2] = $7;
						}
					;
iteration_stmt		: WHILE LPAREN expression RPAREN statement
						{
							$$ = newStmtNode(KindWhile);
							$$->child[0] = $3;
							$$->child[1] = $5;
						}
					;
return_stmt			: RETURN SEMI
						{
							$$ = newStmtNode(KindReturn);
						}
					| RETURN expression SEMI
						{
							$$ = newStmtNode(KindReturn);
							$$->child[0] = $2;
						}
					;
expression			: var ASSIGN expression
						{
							$$ = newStmtNode(KindOp);
							$$->child[0] = $1;
							$$->child[1] = $3;

							$$->attr.op = ASSIGN;
						}
					| simple_expression		{ $$ = $1; }
					;
var					: ID
						{
							$$ = newValNode(KindId);
							$$->attr.name = copyString(tokenBefore);
						}
					| ID
						{
							$$ = newStmtNode(KindSubscript);
							$$->child[0] = newValNode(KindId);

							$$->child[0]->attr.name = copyString(tokenBefore);
						}
					  LBRACKET expression RBRACKET
						{
							$$ = $2;
							$$->child[1] = $4;
						}
					;
simple_expression	: additive_expression relop additive_expression
						{
							$$ = $2;
							$$->child[0] = $1;
							$$->child[1] = $3;
						}
					| additive_expression	{ $$ = $1; }
					;
relop				: LE
						{
							$$ = newStmtNode(KindOp);
							$$->attr.op = LE;
						}
					| LT
						{
							$$ = newStmtNode(KindOp);
							$$->attr.op = LT;
						}
					| GT
						{
							$$ = newStmtNode(KindOp);
							$$->attr.op = GT;
						}
					| GE
						{
							$$ = newStmtNode(KindOp);
							$$->attr.op = GE;
						}
					| EQ
						{
							$$ = newStmtNode(KindOp);
							$$->attr.op = EQ;
						}
					| NE
						{
							$$ = newStmtNode(KindOp);
							$$->attr.op = NE;
						}
					;
additive_expression	: additive_expression addop term
						{
							$$ = $2;
							$$->child[0] = $1;
							$$->child[1] = $3;
						}
					| term					{ $$ = $1; }
					;
addop				: PLUS
						{
							$$ = newStmtNode(KindOp);
							$$->attr.op = PLUS;
						}
					| MINUS
						{
							$$ = newStmtNode(KindOp);
							$$->attr.op = MINUS;
						}
					;
term				: term mulop factor
						{
							$$ = $2;
							$$->child[0] = $1;
							$$->child[1] = $3;
						}
					| factor				{ $$ = $1; }
					;
mulop				: TIMES
						{
							$$ = newStmtNode(KindOp);
							$$->attr.op = TIMES;
						}
					| OVER
						{
							$$ = newStmtNode(KindOp);
							$$->attr.op = OVER;
						}
					;
factor				: LPAREN expression RPAREN
						{
							$$ = $2;
						}
					| var					{ $$ = $1; }
					| call					{ $$ = $1; }
					| NUM
						{
							$$ = newValNode(KindConst);
							$$->attr.val = atoi(tokenString);
						}
					;
call				: ID
						{
							$$ = newStmtNode(KindCall);
							$$->child[0] = newValNode(KindId);
							
							$$->child[0]->attr.name = copyString(tokenBefore);
						}
					  LPAREN args RPAREN
						{
							$$ = $2;
							$$->child[1] = $4;
						}
					;
args				: arg_list				{ $$ = $1; }
					|	{ $$ = NULL; }
					;
arg_list			: arg_list COMMA expression
						{
							struct treeNode *t = $1;
							while(t->sibling) t = t->sibling;

							t->sibling = $3;
							$$ = $1;
						}
					| expression			{ $$ = $1; }
					;

%% 
 
int yyerror(char * message) 
{
  int len = 8;

  fprintf(listing,"Syntax error at line %d: %s\n", lineno, message); 
  fprintf(listing, "\t%-*s\t%s\n", 8, "token kind", "token string");
  fprintf(listing, "\t");

  printToken(yychar, tokenString); 
  Error = TRUE;

  return 0; 
} 


static int yylex(void) 
{
	return getToken();
}


TreeNode * parse(void) 
{
	yyparse(); 
	return savedTree; 
}


