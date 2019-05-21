#ifndef _UTIL_H_ 
#define _UTIL_H_ 

/*
 *	Print Functions
 */
void printDataType(DataType dataType);
void printDeclType(DeclType declType);
void printOp(TokenType);
void printToken(TokenType, const char *); 
void printTree(TreeNode *); 

/*
 *	copy string to dynamic allocated memory and return it
 */
char *copyString(char *src); 

/*
 *	make new tree and return it
 */
TreeNode *newStmtNode(StmtNodeKind); 
TreeNode *newValNode(ValNodeKind);
TreeNode *newDeclNode(DeclNodeKind);
  
#endif 

