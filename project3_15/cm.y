/****************************************************/
/* File: tiny.y                                     */
/* The TINY Yacc/Bison specification file           */
/* Compiler Construction: Principles and Practice   */
/* Kenneth C. Louden                                */
/****************************************************/
%{
#define YYPARSER /* distinguishes Yacc output from other code files */

#include "globals.h"
#include "util.h"
#include "scan.h"
#include "parse.h"

#define YYSTYPE TreeNode *
static char * savedName[5000]; /* for use in assignments */
static int savedLineNo[5000];  /* ditto */
static int savedSize;
static TreeNode * savedTree; /* stores syntax tree for later return */
static int now_level = 0;

%}

%token ERROR COMERROR
%token ELSE IF INT VOID WHILE RETURN
%token ID NUM
%token PLUS MINUS
%token TIMES OVER
%token LT LE GT GE EQ NE ASSIGN
%token SEMI COMMA
%token LPAREN RPAREN
%token LSQUAREB RSQUAREB
%token LCURLYB RCURLYB

%nonassoc LOWER_THEN_ELSE
%nonassoc ELSE

%% /* Grammar for C - */


program		   		  : declaration_list
        	        	{ savedTree = $1;} 
			            ;
declaration_list	: declaration_list declaration
										{
												TreeNode *t = $1;
												if (t != NULL){
															while (t->sibling != NULL)
																	t = t->sibling;
															t->sibling = $2;
															$$ = $1;
												}
												else {
															$$ = $2;
												}
										}
									|	declaration
										{	$$ = $1; }

									;
declaration				: var_declaration
										{	$$ = $1; }
									| fun_declaration
										{	$$ = $1; }
									;

var_declaration		: type_specifier ID 
										{ savedName[now_level] = copyString(beforeToken); 
											savedLineNo[now_level++] = lineno;
										}
										SEMI
										{ 
												TreeNode *new = newExpNode(IdK);

												$$ = newDecNode(IntK);
												$$->child[0] = $1;
												new->attr.name = savedName[--now_level];
												new->lineno = savedLineNo[now_level];
												$$->child[1] = new;
										}
									| type_specifier ID 
										{	savedName[now_level] = copyString(beforeToken); 
											savedLineNo[now_level++] = lineno;
										}
										LSQUAREB NUM 
									  { savedSize = atoi(tokenString); }
									  RSQUAREB SEMI
										{
												TreeNode *new = newExpNode (IdK);
												TreeNode *new2 = newExpNode(ConstK);

												$$ = newDecNode(ArrayK);
												$$->child[0] = $1;
												new->attr.name = savedName[--now_level];
												new->lineno = savedLineNo[now_level];
												new2->attr.val = savedSize;
												$$->child[1] = new;
												$$->child[2] = new2;
										}
									;

type_specifier		: INT
									 	{ $$ = newExpNode(TypeK);
										  $$->type = Integer;
									 	}
									| VOID
									 	{ $$ = newExpNode(TypeK);
											$$->type = Void;
										}
									;

fun_declaration		: type_specifier ID 
										{ 
													savedName[now_level] = copyString(beforeToken);
													savedLineNo[now_level++] = lineno;
										}
									LPAREN params RPAREN compound_stmt 
									 	{
													TreeNode * t;
													t = newExpNode(IdK);
													$$ = newDecNode(FunK);
													$$->child[0] = $1;
													$$->child[2] = $5;
													$$->child[3] = $7;
													t->attr.name = savedName[--now_level];
													t->lineno = savedLineNo[now_level];
													$$->child[1] = t;
										}								
									;

params						: param_list 
										{ $$ = $1; }
									| VOID 
										{
													$$ = newExpNode(ParamK);
													$$->type = Void;
										}
									;

param_list				: param_list COMMA param 
										{
													TreeNode *t = $1;
													if (t != NULL){
																while (t->sibling !=NULL){
																			t = t->sibling;
																}
																t->sibling = $3;
																$$ = $1;
													}
													else{
																$$ = $3;
													}
										}
									| param
										{ 
													$$ = $1;
										}
									;

param 						: type_specifier ID
										{
													TreeNode *new = newExpNode(IdK);
													$$ = newExpNode(ParamK);
													$$->child[0] = $1;
													$$->child[1] = new;
													new->attr.name = copyString(beforeToken);
										}
									| type_specifier ID 
										{
													savedName[now_level] = copyString(beforeToken);
													savedLineNo[now_level++] = lineno;
										}
									LSQUAREB RSQUAREB
										{
													TreeNode *new = newExpNode(IdK);
													TreeNode *new2 = newExpNode(ConstK);
													$$ = newExpNode(ParamK);
													$$->child[0] = $1;
													$$->child[1] = new;
													$$->child[2] = new2;
													new->attr.name = savedName[--now_level];
													new->lineno = savedLineNo[now_level];
													new2->attr.val = 0;
										}
									;

compound_stmt 		: LCURLYB local_declarations statement_list RCURLYB
										{
													$$ = newStmtNode(CompoundK);
													$$->child[0] = $2;
													$$->child[1] = $3;
										}
									;

local_declarations	: local_declarations var_declaration
											{
													TreeNode *t = $1;
													$2->kind.dec = LocalK;
													if (t != NULL){
																while (t->sibling != NULL){
																			t = t->sibling;
																}
																t->sibling = $2;
																$$ = $1;
													}
													else{
																$$ = $2;
													}
											}
										| 
											{ $$ = NULL; }
										;

statement_list			: statement_list statement
											{ 
													TreeNode *t = $1;
													if (t != NULL){
																while (t->sibling != NULL){
																			t = t->sibling;
																}
																t->sibling = $2;
																$$ = $1;
													}
													else{
																$$ = $2;
													}
											}
										|
											{ $$ = NULL; }
										;

statement						: expression_stmt
											{	$$ = $1; }
										| compound_stmt
											{	$$ = $1; }
										| selection_stmt
											{	$$ = $1; }
										| iteration_stmt
											{	$$ = $1; }
										| return_stmt
											{	$$ = $1; }
										;

expression_stmt			: expression SEMI
											{	$$ = $1; }
										| SEMI
											{ $$ = NULL; }
										;

selection_stmt			: IF LPAREN expression RPAREN statement %prec LOWER_THEN_ELSE 
											{
														$$ = newStmtNode(SelectionK);
														$$->child[0] = $3;
														$$->child[1] = $5;
											}
										| IF LPAREN expression RPAREN statement ELSE statement
											{
														TreeNode *new = newStmtNode(ElseK);
														$$ = newStmtNode(SelectionK);
														$$->child[0] = $3;
														$$->child[1] = $5;
														$$->child[2] = new;
														new->child[0] = $7;
											}
										;

iteration_stmt			: WHILE LPAREN expression RPAREN statement
											{
														$$ = newStmtNode(IterationK);
														$$->child[0] = $3;
														$$->child[1] = $5;
											}
										;

return_stmt					: RETURN SEMI
											{	$$ = newStmtNode(ReturnK); }	
										| RETURN expression SEMI
											{
														$$ = newStmtNode(ReturnK);
														$$->child[0] = $2;
											}
										;

expression					: var ASSIGN expression
											{ 
														$$ = newExpNode(AssignK);
														$$->child[0] = $1;
														$$->child[1] = $3;
														$$->attr.op = ASSIGN;
											}
										| simple_expression
											{ $$ = $1; }
										;

var									: ID
											{ 
														$$ = newExpNode(IdK);
														$$->attr.name = copyString(beforeToken);
											}
										| ID 
											{
														savedName[now_level] = copyString(beforeToken);
														savedLineNo[now_level++] = lineno;
											}
											LSQUAREB expression RSQUAREB
											{
														TreeNode *new = newExpNode(IdK);
														$$ = newExpNode(IdarrayK);
														new->attr.name = savedName[--now_level];
														new->lineno = savedLineNo[now_level];
														$$->child[0] = new;
														$$->child[1] = $4;
											}
										;

simple_expression		: additive_expression relop additive_expression
											{
														$$ = newExpNode(OpK);
														$$->child[0] = $1;
														$$->child[1] = $3;
														$$->attr.op = $2->attr.op;
											}
										| additive_expression
											{ $$ = $1; }
										;

relop								: LE 
											{ $$ = newExpNode(OpK); $$->attr.op = LE; }
										| LT
											{ $$ = newExpNode(OpK); $$->attr.op = LT; }
										| GT
											{ $$ = newExpNode(OpK); $$->attr.op = GT; }
										| GE
											{ $$ = newExpNode(OpK); $$->attr.op = GE; }
										| EQ
											{ $$ = newExpNode(OpK); $$->attr.op = EQ; }
										| NE
											{ $$ = newExpNode(OpK); $$->attr.op = NE; }
										;

additive_expression : additive_expression addop term
											{ 
														$$ = newExpNode(OpK);
														$$->child[0] = $1;
														$$->child[1] = $3;
														$$->attr.op = $2->attr.op;
											}
										| term
											{ $$ = $1; }
										;

addop								: PLUS
											{ $$ = newExpNode(OpK); $$->attr.op = PLUS; }
										| MINUS
											{ $$ = newExpNode(OpK); $$->attr.op = MINUS; }
										;

term								: term mulop factor
											{ 
														$$ = newExpNode(OpK);
														$$->child[0] = $1;
														$$->child[1] = $3;
														$$->attr.op = $2->attr.op;
											}
										| factor
											{ $$ = $1; }
										;

mulop								: TIMES
											{ $$ = newExpNode(OpK); $$->attr.op = TIMES; }
										| OVER
											{ $$ = newExpNode(OpK); $$->attr.op = OVER; }
										;

factor							: LPAREN expression RPAREN
											{ $$ = $2; }
										| var
											{ $$ = $1; }
										| call
											{ $$ = $1; }
										| NUM
											{ 
														$$ = newExpNode(ConstK);
														$$->attr.val = atoi(tokenString);
											}
										;

call								: ID 
											{
														savedName[now_level] = copyString(beforeToken);
														savedLineNo[now_level++] = lineno;
											}
											LPAREN args RPAREN
											{
														$$ = newExpNode(CallK);
														$$->attr.name = savedName[--now_level];
														$$->lineno = savedLineNo[now_level];
														$$->child[0] = $4;
											}
										;

args								: arg_list
											{ $$ = $1; }
										|
											{ $$ = NULL; }
										;

arg_list						: arg_list COMMA expression
											{
														TreeNode *t = $1;
														if (t != NULL){
																	while(t->sibling != NULL){
																				t = t->sibling;
																	}
																	t->sibling = $3;
																	$$ = $1;
														}
														else{
																	$$ = $3;
														}
											}
										| expression
											{ $$ = $1; }
										;


%%

int yyerror(char * message)
{ fprintf(listing,"Syntax error at line %d: %s\n",lineno,message);
	fprintf(listing, "before token : %s\n", beforeToken);
  fprintf(listing,"Current token: ");
  printToken(yychar,tokenString);
  Error = TRUE;
  return 0;
}

/* yylex calls getToken to make Yacc/Bison output
 * compatible with ealier versions of the TINY scanner
 */
static int yylex(void)
{
			TokenType token = getToken();

			if (token == ERROR){
						fprintf(listing,"Lexical anaylze error at line %d: %s", lineno, tokenString);
						Error = TRUE;
						return 0;
			}

			return token; 
}

TreeNode * parse(void)
{ yyparse();
  return savedTree;
}

