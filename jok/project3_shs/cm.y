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

#define debugMode FALSE

static char * savedName; /* for use in assignments */
static int savedLineNo;  /* ditto */
static TreeNode * savedTree; /* stores syntax tree for later return */
static int yylex();
static int scope = 0;
static int funcLine = 0;
YYSTYPE t;

%}

%token ENDFILE ERROR
%token ELSE IF INT RETURN VOID WHILE
%token PLUS MINUS TIMES DIV LT LTE GT GTE EQ NEQ ASSIGN SEMI COMMA LPAREN RPAREN LBRACKET RBRACKET LBRACE RBRACE
%token ID NUM

%left PLUS MINUS
%left TIMES DIV
%start program

%%
program 			: declaration_list { savedTree = $1; 
		   				if(debugMode)
							fprintf(listing,"%d:[%d] program [%s], [%s], [%d]\n",lineno, $$->nodeIndex, savedId, tokenString, savedNum);
		   };
declaration_list 	: declaration_list declaration 
				  		{
							t = $1;
							if(t)
							{
								t = findSibling(t);
								t->sibling = $2;
								$$ = $1;
							}
							else 
								$$ = $2;
		   				if(debugMode)
							fprintf(listing,"%d:[%d] declaration_list [%s], [%s], [%d]\n",lineno, $$->nodeIndex, savedId, tokenString, savedNum);
				  		}
					| declaration { $$ = $1; };
declaration 		: var_declaration { $$ = $1; }
					| fun_declaration { $$ = $1; };
var_declaration 	: type_specifier ID SEMI 
				 		{
							$$ = newDeclNode(VarK);
							$$->child[0] = $1;
							$$->attr.name = copyString(savedId);
							if(scope == 0) 
								$$->global = 1;
		   				if(debugMode)
							fprintf(listing,"%d:[%d] [[[%s]]]\n",lineno, $$->nodeIndex, $$->attr.name);
		   				if(debugMode)
							fprintf(listing,"%d:[%d] var_declaration1 [%s], [%s], [%d]\n",lineno, $$->nodeIndex, savedId, tokenString, savedNum);
						}
					| type_specifier ID LBRACKET NUM RBRACKET SEMI
						{
							$$ = newDeclNode(VarK);
							$$->child[0] = $1;
							$$->attr.name = copyString(savedId); 
							$$->type = IntegerArray;
							$$->arrayIndex = savedNum;
							if(scope == 0) 
								$$->global = 1;
		   				if(debugMode)
							fprintf(listing,"%d:[%d] [[[%s]]]\n",lineno, $$->nodeIndex, $$->attr.name);
		   				if(debugMode)
							fprintf(listing,"%d:[%d] var_declaration2 [%s], [%s], [%d]\n",lineno, $$->nodeIndex, savedId, tokenString, savedNum);
						};
type_specifier 		: INT
				 		{
							$$ = newDeclNode(TypeK);
							$$->type = Integer;
		   				if(debugMode)
							fprintf(listing,"%d:[%d] int [%s], [%s], [%d]\n",lineno, $$->nodeIndex, savedId, tokenString, savedNum);
						}
			 		| VOID
						{
							$$ = newDeclNode(TypeK);
							$$->type = Void;
		   				if(debugMode)
							fprintf(listing,"%d:[%d] void [%s], [%s], [%d]\n",lineno, $$->nodeIndex, savedId, tokenString, savedNum);
						};
fun_declaration 	: type_specifier ID { pushSavedId(savedId); scope++; funcLine=lineno; }
					  LPAREN params RPAREN compound_stmt 
				 		{
							$$ = newDeclNode(FunK);
							$$->lineno = funcLine;
							$$->child[0] = $1;
							$$->attr.name = popSavedId();
							$$->child[1] = $5;
							$$->child[2] = $7;
		   				if(debugMode)
							fprintf(listing,"%d:[%d] [[[%s]]]\n",lineno, $$->nodeIndex, $$->attr.name);
		   				if(debugMode)
							fprintf(listing,"%d:[%d] func_decl %s [%d]\n",lineno, $$->nodeIndex, savedId, $$->arrayIndex);
							scope--;
						};
params				: param_list { $$ = $1; }
					| VOID 
						{
							t = newDeclNode(TypeK);
							t->type = Void;

							$$ = newDeclNode(ParamK);
							$$->child[0] = t;
						};
param_list 			: param_list COMMA param
			  			{
							t = $3;
							if(t)
							{
								t = findSibling(t);
								t->sibling = $1;
								$$ = $3;
							}
							else
								$$ = $1;
		   				if(debugMode)
							fprintf(listing,"%d:[%d] param_list [%s], [%s], [%d]\n",lineno, $$->nodeIndex, savedId, tokenString, savedNum);
						}
		   			| param { $$ = $1; };
param 				: type_specifier ID
		  				{
							$$ = newDeclNode(ParamK);
							$$->child[0] = $1;
							$$->attr.name = copyString(savedId);
		   				if(debugMode)
							fprintf(listing,"%d:[%d] [[[%s]]]\n",lineno, $$->nodeIndex, $$->attr.name);
		   				if(debugMode)
							fprintf(listing,"%d:[%d] param [%s], [%s], [%d]\n",lineno, $$->nodeIndex, savedId, tokenString, savedNum);
						}
					| type_specifier ID LBRACKET RBRACKET
						{
							$$ = newDeclNode(ParamK);
							$$->child[0] = $1;
							$$->attr.name = copyString(savedId);
							$$->type = IntegerArray;
		   				if(debugMode)
							fprintf(listing,"%d:[%d] [[[%s]]]\n",lineno, $$->nodeIndex, $$->attr.name);
		   				if(debugMode)
							fprintf(listing,"%d:[%d] param2 [%s], [%s], [%d]\n",lineno, $$->nodeIndex, savedId, tokenString, savedNum);
						};
compound_stmt 		: LBRACE local_declarations statement_list RBRACE
						{
							$$ = newStmtNode(CompoundK);
							$$->child[0] = $2;
							$$->child[1] = $3;
		   				if(debugMode)
							fprintf(listing,"%d:[%d] compound_stmt [%s], [%s], [%d]\n",lineno, $$->nodeIndex, savedId, tokenString, savedNum);
						}
local_declarations 	: local_declarations var_declaration
						{
							t = $1;
							if(t)
							{
								t = findSibling(t);
								t->sibling = $2;
								$$ = $1;
							}
							else
								$$ = $2;
		   				if(debugMode)
							fprintf(listing,"%d:[%d] local_declarations [%s], [%s], [%d]\n",lineno, $$->nodeIndex, savedId, tokenString, savedNum);
						}
				   	| /* empty */ { $$ = NULL; };
statement_list 		: statement_list statement
				 		{
							t = $1;
							if(t)
							{
								t = findSibling(t);
								t->sibling = $2;
								$$ = $1;
							}
							else
								$$ = $2;
		   				if(debugMode)
							fprintf(listing,"%d:[%d] statement_list [%s], [%s], [%d]\n",lineno, $$->nodeIndex, savedId, tokenString, savedNum);
						}
		  			|  /* empty */ { $$ = NULL; };
statement 			: expression_stmt { $$ = $1; }
					| compound_stmt { $$ = $1; }
					| selection_stmt { $$ = $1; }
					| iteration_stmt { $$ = $1; }
					| return_stmt { $$ = $1; };
expression_stmt 	: expression SEMI { $$ = $1; }
					| SEMI { $$ = NULL; };
selection_stmt 		: IF LPAREN expression RPAREN statement
				 		{
							$$ = newStmtNode(IfK);
							$$->child[0] = $3;
							$$->child[1] = $5;
						}
					| IF LPAREN expression RPAREN statement ELSE statement
						{
							$$ = newStmtNode(IfK);
							$$->child[0] = $3;
							$$->child[1] = $5;
							$$->child[2] = $7;
						};
iteration_stmt		: WHILE LPAREN expression RPAREN statement 
						{
							$$ = newStmtNode(WhileK);
							$$->child[0] = $3;
							$$->child[1] = $5;
						};
return_stmt 		: RETURN SEMI
			  			{
							$$ = newStmtNode(ReturnK);
						}
					| RETURN expression SEMI
						{
							$$ = newStmtNode(ReturnK);
							$$->child[0] = $2;
						};
expression  		: var ASSIGN expression 
			  			{
							$$ = newStmtNode(AssignK);
							$$->child[0] = $1;
							$$->child[1] = $3;
							$$->attr.op = ASSIGN;
		   				if(debugMode)
							fprintf(listing,"%d:[%d] expression1 [%s], [%s], [%d]\n",lineno, $$->nodeIndex, savedId, tokenString, savedNum);
						}
					| simple_expression { $$ = $1; };
var 				: ID 
						{
							$$ = newExpNode(IdK); 
							$$->attr.name = copyString(savedId);
		   				if(debugMode)
							fprintf(listing,"%d:[%d] [[[%s]]]\n",lineno, $$->nodeIndex, $$->attr.name);
		   				if(debugMode)
							fprintf(listing,"%d:[%d] var [%s], [%s], [%d]\n",lineno, $$->nodeIndex, savedId, tokenString, savedNum);
						}
					| ID { pushSavedId(savedId); }
					  LBRACKET expression RBRACKET
						{
							$$ = newExpNode(IdK);
							$$->attr.name = popSavedId();
							$$->type = IntegerArray;
							$$->child[0] = $4;
						};
simple_expression 	: additive_expression relop additive_expression
				   		{
							$$ = newStmtNode(ExpStmtK);
							$$->child[0] = $1;
							$$->child[1] = $2;
							$$->child[2] = $3;
		   				if(debugMode)
							fprintf(listing,"%d:[%d] simple_exp1 [%s], [%s], [%d]\n",lineno, $$->nodeIndex, savedId, tokenString, savedNum);
						}
					| additive_expression { $$ = $1; };
relop 				: LTE 
		  				{
							$$ = newExpNode(OpK);
							$$->attr.op = LTE;
						}
					| LT 
						{
							$$ = newExpNode(OpK);
							$$->attr.op = LT;
						}
					| GT
						{
							$$ = newExpNode(OpK);
							$$->attr.op = GT;
						}
					| GTE 
						{
							$$ = newExpNode(OpK);
							$$->attr.op = GTE;
						}
					| EQ
						{
							$$ = newExpNode(OpK);
							$$->attr.op = EQ;
		   				if(debugMode)
							fprintf(listing,"%d:[%d] relop [%s], [%s], [%d]\n",lineno, $$->nodeIndex, savedId, tokenString, savedNum);
						}
					| NEQ
						{
							$$ = newExpNode(OpK);
							$$->attr.op = NEQ;
						}
additive_expression : additive_expression addop term
						{
							$$ = newStmtNode(ExpStmtK);
							$$->child[0] = $1;
							$$->child[1] = $2;
							$$->child[2] = $3;
		   				if(debugMode)
							fprintf(listing,"%d:[%d] addtive_exp [%s], [%s], [%d]\n",lineno, $$->nodeIndex, savedId, tokenString, savedNum);
						}
					| term	{ $$ = $1; };
addop 				: PLUS
		  				{
							$$ = newExpNode(OpK);
							$$->attr.op = PLUS;
		   				if(debugMode)
							fprintf(listing,"%d:[%d] addop [%s], [%s], [%d]\n",lineno, $$->nodeIndex, savedId, tokenString, savedNum);
						}
					| MINUS
		  				{
							$$ = newExpNode(OpK);
							$$->attr.op = MINUS;
						}
term 				: term mulop factor
		 				{
							$$ = newStmtNode(ExpStmtK);
							$$->child[0] = $1;
							$$->child[1] = $2;
							$$->child[2] = $3;
		   				if(debugMode)
							fprintf(listing,"%d:[%d] term [%s], [%s], [%d]\n",lineno, $$->nodeIndex, savedId, tokenString, savedNum);
						}
					| factor { $$ = $1; };
mulop 				: TIMES 
		  				{
							$$ = newExpNode(OpK);
							$$->attr.op = TIMES;
						}
					| DIV
		  				{
							$$ = newExpNode(OpK);
							$$->attr.op = DIV;
						};
factor 				: LPAREN expression RPAREN { $$ = $2; }
					| var { $$ = $1; }
					| call { $$ = $1; }
					| NUM
						{
						 	$$ = newExpNode(ConstK);
							$$->attr.val = savedNum;
		   				if(debugMode)
							fprintf(listing,"%d:[%d] factor4 [%s], [%s], [%d]\n",lineno, $$->nodeIndex, savedId, tokenString, savedNum);
						};
call 				: ID { pushSavedId(savedId); }
		 			  LPAREN args RPAREN
		 				{
							$$ = newStmtNode(CallK);
							$$->attr.name = popSavedId();
							$$->child[0] = $4;
		   				if(debugMode)
							fprintf(listing,"%d:[%d] [[[%s]]]\n",lineno, $$->nodeIndex, $$->attr.name);
		   				if(debugMode)
							fprintf(listing,"%d:[%d] call [%s], [%s], [%d]\n",lineno, $$->nodeIndex, savedId, tokenString, savedNum);
						}
args 				: arg_list { $$ = $1; }
					|  /* empty */ { $$ = NULL; };
arg_list 			: arg_list COMMA expression 
						{
							t = $3;
							if(t)
							{
								t = findSibling(t);
								t->sibling = $1;
                                $$ = $3;
							}
							else
								$$ = $1;
						}
					| expression { $$ = $1;	};
%%
int yyerror(char * message)
{ fprintf(listing,"Syntax error at line %d: %s\n",lineno,message);
  fprintf(listing,"Current token: " );
  printToken(yychar,tokenString);
  Error = TRUE;
  return 0;
}

/* yylex calls getToken to make Yacc/Bison output
 * compatible with ealier versions of the TINY scanner
 */
static int yylex(void)
{ return getToken(); }

TreeNode * parse(void)
{ yyparse();
  return savedTree;
}

