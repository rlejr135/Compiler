#include "globals.h"

/*data type check*/
/*1. array index */
BOOL ArrayIndexCheck(struct treeNode * node){
    return ( node -> child[1] -> dataType == TYPE_INT );
}
/*2. if,while condition */
BOOL IfWhileCheck(struct treeNode * node){
    return ( node -> child[0] -> dataType == TYPE_INT );
}
/*3. operator left right*/
BOOL OpLeftRightCheck(struct treeNode * left, struct treeNode * right){
    return ( left -> dataType == TYPE_INT && right -> dataType == TYPE_INT);
}

/*Call check 시 argument 비교*/
BOOL CalledParCheck(struct treeNode * param, struct treeNode * arg){

    param = param -> child[0];

    while(arg != NULL){
        if(param == NULL){
            return FALSE;
        }
        else if(arg -> dataType != param -> dataType){
            return FALSE;
        }
		else if(arg->declType == TYPE_ARRAY && param->declType != TYPE_ARRAY) return FALSE;
		else if(arg->declType != TYPE_ARRAY && param->declType == TYPE_ARRAY) return FALSE;

        arg = arg -> sibling;
        param = param -> sibling;
    }

    return (param == NULL);
}

BOOL returnTypeCheck(struct treeNode *node)
{
    if(!node->child[0]) return node->dataType == TYPE_VOID;
    else return node->dataType == node->child[0]->dataType;
}

void checkDataType(struct treeNode * node){

    switch( node -> nodeKind){
        case StmtNode:
            switch( node -> detailKind.stmt){
                case KindIf:
                case KindWhile:
                    if(!IfWhileCheck(node))
                    {
                        Error = TRUE;
                        fprintf(listing, "Condition of if/while statement isn't integer! line %d\n",
							 node->child[0]->lineno);
                    }
                    break;
                case KindCall:
					if(!node->parameter)
					{
						Error = TRUE;
					}
                    else if(!CalledParCheck(node->parameter, node->child[1]))
                    {
						struct treeNode *par = node->parameter->child[0], *arg = node->child[1];
                        Error = TRUE;

                        fprintf(listing, "Called parameters are wrong! line %d\n", node->lineno);
						fprintf(listing, "\tDecl : ");
						while(par)
						{
							fprintf(listing, "%s", par->dataType == TYPE_INT ? "int" : "void");
							if(par->declType == TYPE_ARRAY) fprintf(listing, "[]");
							fprintf(listing, " ");
							par = par->sibling;
						}
						fprintf(listing, "\n");

						fprintf(listing, "\tCall : ");
						while(arg)
						{
							fprintf(listing, "%s", arg->dataType == TYPE_INT ? "int" : "void");
							if(arg->declType == TYPE_ARRAY) fprintf(listing, "[]");
							fprintf(listing, " ");
							arg = arg->sibling;
						}
						fprintf(listing, "\n");					
                    }
                    break;
                case KindOp:
                    if(!OpLeftRightCheck(node -> child[0], node -> child[1]))
                    {
                        Error = TRUE;
                        fprintf(listing, "Factors of %s statement are not integer! line %d\n",
							node->attr.op == ASSIGN ? "assignment" : "operator", node->lineno);
                    }
                    break;
                case KindSubscript:
                    if(!ArrayIndexCheck(node))
                    {
                        Error = TRUE;
                        fprintf(listing, "Index of Array is not integer! line %d\n", node->lineno);
                    }
                    break;
                case KindReturn:
                    if(!returnTypeCheck(node))
                    {
                        Error = TRUE;
                        fprintf(listing, "return type is wrong! line : %d\n", node->lineno);
                    }
                    break;
            }
    }
}

void checkUnindexedArray(struct treeNode *node)
{
    int i;

    for(i = 0; i < MAXCHILDREN; ++i)
    {
        struct treeNode *child = node->child[i];

		while(child)
		{
			if(
				(child->declType == TYPE_ARRAY && child->nodeKind != DeclNode) &&
				!(node->declType == TYPE_SUBSCRIPTED && i == 0) &&
				!(node->nodeKind == StmtNode && node->detailKind.stmt == KindCall)
			)
	        {
	            Error = TRUE;
	            fprintf(listing, "Array <%s> should be subscripted! line : %d\n",
					child->attr.name, node->lineno);
	        }

			child = child->sibling;
		}
    }
}

void checkDeclarationType(struct treeNode *node)
{
    if(node->nodeKind == StmtNode)
    {
        switch(node->detailKind.stmt)
        {
            case KindSubscript:
                if(node->child[0]->declType != TYPE_ARRAY)
                {
                    Error = TRUE;
                    fprintf(listing, "<%s> is not array! It cannot be subscripted! line : %d\n",
                        node->child[0]->attr.name, node->lineno);
                }
                break;
            case KindCall:
                if(node->declType != TYPE_FUNC)
                {
                    Error = TRUE;
                    fprintf(listing, "<%s> is not function! It cannot be called! line : %d\n",
                        node->child[0]->attr.name, node->lineno);
                }
                break;
            case KindOp:
                if(node->attr.op == ASSIGN)
                {
                    struct treeNode *left = node->child[0];
                    BOOL isLeftValue = left->declType == TYPE_VAR ||
                        (left->nodeKind == StmtNode && left->detailKind.stmt == KindSubscript);

                    if(!isLeftValue)
                    {
                        Error = TRUE;
                        fprintf(listing, "Left hand side of assign should be L-Value! line : %d\n",
                            node->lineno);
                    }
                }
                break;
        }

		checkUnindexedArray(node);
    }
}


void typeCheck(struct treeNode *node)
{
	while(node)
	{
		int i;

		for(i = 0; i < MAXCHILDREN; ++i)
		{
			if(node->child[i]) typeCheck(node->child[i]);
			else break;
		}
	
		if(node->nodeKind == DeclNode)
		{
			if(node->detailKind.decl != KindFunc && node->child[0]->dataType == TYPE_VOID)
			{
				fprintf(listing, "Variable can't be void type! <%s> line %d\n",
					node->child[1]->attr.name, node->lineno);
				Error = TRUE;
			}

			node->dataType = node->child[0]->dataType;
			if(node->detailKind.decl == KindVar)	node->declType = TYPE_VAR;
			if(node->detailKind.decl == KindArray)	node->declType = TYPE_ARRAY;
			if(node->detailKind.decl == KindFunc)	node->declType = TYPE_FUNC;
		}
		else if(node->nodeKind == ValNode)
		{
			if(node->detailKind.val == KindConst)
			{
				node->declType = TYPE_RVALUE;
				node->dataType = TYPE_INT;
			}
		}
		else if(node->nodeKind == StmtNode)
		{
			if(node->detailKind.stmt == KindSubscript)
			{
				node->declType = TYPE_SUBSCRIPTED;
				node->dataType = node->child[0]->dataType;
			}
			else if(node->detailKind.stmt == KindCall)
			{
				node->declType = node->child[0]->declType;
				node->dataType = node->child[0]->dataType;
			}
			else if(node->detailKind.stmt == KindOp)
			{
				if(node->attr.op != ASSIGN) node->declType = TYPE_RVALUE;
				else node->declType = node->child[0]->declType;
				node->dataType = node->child[0]->dataType;
			}
		}
		else
		{
			fprintf(listing, "Unknown Node Kind! line %d\n", node->lineno);
			Error = TRUE;
		}

		checkDataType(node);
		checkDeclarationType(node);

		node = node->sibling;
	}
}

