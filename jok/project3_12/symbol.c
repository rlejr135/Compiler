#include "globals.h"
#include "analyze.h"

void pushTable(struct symbolTable *point){

    struct symbolTable *newTb;
    int loop_Bucket;

    newTb=(struct symbolTable *)malloc(sizeof(struct symbolTable));

    for(loop_Bucket=0;loop_Bucket<BUCKET_SIZE;loop_Bucket++)
        newTb->bucket[loop_Bucket]=NULL;

    if (point->next !=NULL){
        newTb->scopeDepth = ( (point->next)->scopeDepth)+1;
        newTb->next = point->next;
        point->next = newTb;
    }
    else{
        point->next = newTb;
        newTb->next = NULL;
        newTb->scopeDepth = 0;
    }
}

void popTable(struct symbolTable *point){
    struct symbolTable *ptr;
    struct bucket   *ptr_B;
    int loop_B;
    if(point->next !=NULL){
        ptr=point->next;
        point->next=point->next->next;

        for(loop_B=0;loop_B<BUCKET_SIZE;loop_B++){

            while( ptr->bucket[loop_B] !=NULL ){
                    ptr_B = ptr->bucket[loop_B];
                    ptr->bucket[loop_B]=ptr->bucket[loop_B]->next;
                    free(ptr_B);
            }
        }
        free(ptr);

    }
    else{
        fprintf(listing,"Not popTable\n");
        Error=TRUE;

    }
}

#define LEN 10
int prime[7] = {2,3,5,7,11,13,17};

int hash(const char *str){
    int i = 0, key = 0;

    while(str[i] != '\0'){
        key += str[i]*prime[i%7];
        ++i;
    }

    key = key % BUCKET_SIZE;

    return key;
}

void printBoundary(){
    int i;

    for(i = 0 ; i < 8 ; i++)
        fprintf(listing,"----------");
    fprintf(listing,"\n");
}

void printSymTab(struct symbolTable * tab){
    int i;

    printBoundary();
    fprintf(listing,"scope depth : %d\n",tab -> scopeDepth);
    fprintf(listing,"%*s%*s%*s%*s""%*s%*s%*s%*s\n",
            LEN,"Name",LEN,"Addr",LEN,"Len",LEN,"V/P/F",
            LEN,"Array?",LEN,"ArrSize",LEN,"Type",LEN,"Line");
    printBoundary();

    for(i = 0 ; i < BUCKET_SIZE; i++){
        struct bucket *bucket = tab -> bucket[i];
        struct lineList *linelist;

        while(bucket != NULL){
            /*Name*/
            fprintf( listing , "%*s" , LEN , bucket -> name );

            /*Addr*/
            if(bucket->addrBase == BASE_FP){
                char buffer[14];
                sprintf(buffer, "%s%s%d", "FP", 0 <= bucket->addr ? "+" : "", bucket->addr);
                fprintf(listing, "%*s" , LEN, buffer);
            }
            else if(bucket -> addrBase == BASE_GLOBAL){
                fprintf( listing , "%*d" , LEN , bucket -> addr);
            }

            /*Len*/
            if(bucket->len) fprintf( listing , "%*d" , LEN , bucket -> len );
			else fprintf(listing, "%*s", LEN, ".");

            /*V/P/F*/
            if(bucket -> declType == TYPE_FUNC){
                fprintf( listing, "%*s" , LEN , "Func");
            }
            else if(bucket -> isParameter == TRUE){
                fprintf( listing, "%*s" , LEN , "Par");
            }
            else{
                fprintf( listing, "%*s" , LEN , "Var");
            }

            /*Array? */
            if(bucket -> declType == TYPE_ARRAY)
                fprintf( listing, "%*s" , LEN , "Yes");
            else
                fprintf( listing, "%*s" , LEN , "No");

            /*ArrSize*/
            fprintf( listing , "%*d" , LEN , bucket -> arrayCount );

            /*Type*/
            fprintf( listing , "%*s" , LEN , bucket -> dataType == TYPE_INT ? "Int" : "Void");

            /*Line*/
            linelist = bucket -> lineList;
            fprintf(listing, "%*s", LEN, "( ");

            while(linelist != NULL){
                fprintf(listing, "%d ", linelist->line);
                linelist = linelist -> next;
            }

            fprintf(listing, ")\n");

            bucket = bucket -> next;
        }
    }

    printBoundary();
    fprintf(listing, "\n");
}

/*
 *  Calculate a value for fast comparison
 */
static int getFastCheckValue(const char *str)
{
    const int M = 19;
    const int Kind = 510511;

    int i;
    int t = 0;

    for(i = 0; str[i]; ++i)
    {
        t *= M;
        t += str[i];
        t %= Kind;
    }

    return t;
}

/*
 *  Search a symbol from symbol table
 *  Found       : return depth of the symbol's scope
 *  Not Found   : -1
 *
 *  if ppOut isn't NULL, it will be the bucket's pointer
 */
static int searchFromSymbolTable(struct bucket **ppOut, struct symbolTable *symbolTable, const char *name)
{
    struct symbolTable *table = symbolTable->next;
    int fastCheck = getFastCheckValue(name);
    int idx = hash(name);

    while(table)
    {
        struct bucket *bucket = table->bucket[idx];

        while(bucket)
        {
            if(bucket->fastCheck == fastCheck && strcmp(bucket->name, name) == 0)
            {
                if(ppOut) *ppOut = bucket;
                return table->scopeDepth;
            }

            bucket = bucket->next;
        }

        table = table->next;
    }

    if(ppOut) *ppOut = NULL;
    return -1;
}

/*
 *  Allocate a line list node
 */
static struct lineList *getNewLineNode(int line)
{
    struct lineList *lineList = (struct lineList *)malloc(sizeof(struct lineList));

    lineList->line = line;
    lineList->next = NULL;

    return lineList;
}

/*
 *  Calculate Address and length of symbol
 */
static void calculateAddress(struct bucket *bucket, struct addrCounter *counter)
{
    int baseSize = bucket->dataType == TYPE_INT ? SIZE_INT : SIZE_VOID;

    switch(bucket->declType)
    {
        case TYPE_VAR:
            bucket->len = baseSize;
            break;
        case TYPE_ARRAY:
            if(bucket->arrayCount) bucket->len = bucket->arrayCount * baseSize;
            else bucket->len = SIZE_ARRAY_ADDR;
            break;
        case TYPE_FUNC:
            bucket->len = 0;
            break;
        default:
            fprintf(listing, "Wrong Declaration Type\n");
            Error = TRUE;
    }

    if(bucket->declType == TYPE_FUNC)
    {
        bucket->addr = counter->function++;
    }
    else if(bucket->addrBase == BASE_GLOBAL)
    {
        bucket->addr = counter->global;
        counter->global += bucket->len;
    }
    else if(bucket->addrBase == BASE_FP)
    {
        counter->local -= bucket->len;
        bucket->addr = counter->local;
    }
    else
    {
        fprintf(listing, "Wrong Address Base\n");
        Error = TRUE;
    }
}

/*
 *  Insert new symbol into symbol table
 */
static struct bucket *insertToSymbolTable(
    struct symbolTable *symbolTable, const char *name, DataType dataType, DeclType declType,
    AddrBase addrBase, int line, int arrayCount, struct addrCounter *counter
)
{
    int idx = hash(name);
    struct bucket *bucket = (struct bucket *)malloc(sizeof(struct bucket));

    bucket->parameter   = NULL;

    bucket->fastCheck   = getFastCheckValue(name);
    bucket->arrayCount  = arrayCount;
    strcpy(bucket->name, name);

    bucket->isParameter = FALSE;
    bucket->dataType    = dataType;
    bucket->declType    = declType;

    bucket->lineList    = getNewLineNode(line);
    bucket->lineTail    = bucket->lineList;
    bucket->next        = NULL;

    bucket->addrBase    = addrBase;
    calculateAddress(bucket, counter);

    bucket->next = symbolTable->next->bucket[idx];
    symbolTable->next->bucket[idx] = bucket;

    return bucket;
}

/*
 *  Recaculate Address for parameter
 */
static void recalcParameterAddr(struct symbolTable *symbolTable, struct addrCounter *counter)
{
    struct symbolTable *table = symbolTable->next;
    int i;

    counter->local -= SIZE_INT;

    for(i = 0; i < BUCKET_SIZE; ++i)
    {
        struct bucket *bucket = table->bucket[i];

        while(bucket)
        {
            bucket->addr -= counter->local;
            bucket->isParameter = TRUE;
            bucket = bucket->next;
        }
    }

    counter->local = 0;
}
/*
 *  traverse tree and find error with symbol table
 */
static void checkSymbolTable(struct symbolTable *table, struct treeNode *node, struct treeNode *parent, struct addrCounter *counter)
{
	static DataType funcDataType = TYPE_VOID;

	while(node)
	{
	    if(node && node->nodeKind == ValNode && node->detailKind.val == KindId)
	    {
	        struct bucket *bucket;
	
	        if(parent->nodeKind == DeclNode)
	        {
	            int depth       = table->next->scopeDepth;
	            int result      = searchFromSymbolTable(NULL, table, node->attr.name);
	            int arrCount    = parent->declType == TYPE_ARRAY ? parent->child[2]->attr.val: 0;
	
	            if(result != depth)
	            {
	                bucket = insertToSymbolTable(
	                    table, node->attr.name, parent->child[0]->dataType, parent->declType,
	                    depth ? BASE_FP : BASE_GLOBAL, node->lineno, arrCount, counter
	                );
	
	                if(parent->detailKind.decl == KindFunc)
	                {
	                    bucket->parameter	= parent->child[2];
	                    parent->parameter	= parent->child[2];
						funcDataType		= parent->child[0]->dataType;
	                }
	            }
	            else
	            {
	                fprintf(listing, "<%s> redefinition in line %d\n", node->attr.name, node->lineno);
	                Error = TRUE;
	            }
	        }
	        else if(searchFromSymbolTable(&bucket, table, node->attr.name) != -1)
	        {
	            node->declType          = bucket->declType;
	            node->dataType          = bucket->dataType;
	            node->addrBase          = bucket->addrBase;
	            node->addr              = bucket->addr;
	
	            bucket->lineTail->next  = getNewLineNode(node->lineno);
	            bucket->lineTail        = bucket->lineTail->next;
	
				if(parent->nodeKind == StmtNode && parent->detailKind.stmt == KindCall &&
					parent->child[0] == node)
				{
					parent->parameter = bucket->parameter;
				}
	        }
	        else
	        {
	            fprintf(listing, "Undefined Variable <%s> in line %d\n", node->attr.name, node->lineno);
	            Error = TRUE;
	        }
	    }
	    else
	    {
            int i;
            int isParentFunc    = parent && parent->nodeKind == DeclNode && parent->detailKind.decl == KindFunc;
            int isCompoundNode  = node->nodeKind == StmtNode && node->detailKind.stmt == KindCompound;
            int isParameter     = node->nodeKind == StmtNode && node->detailKind.stmt == KindParam;

			if(node->nodeKind == StmtNode && node->detailKind.stmt == KindReturn)
			{
				node->dataType = funcDataType;
			}

            if((isCompoundNode && !isParentFunc) || isParameter) pushTable(table);
            for(i = 0; i < MAXCHILDREN; ++i) checkSymbolTable(table, node->child[i], node, counter);
            if(isParameter) recalcParameterAddr(table, counter);
            if(isCompoundNode)
            {
                if(!Error)
                {
                    printSymTab(table->next);
                }

                popTable(table);
            }
		}

		node = node->sibling;
    }
}


static void checkMain(struct symbolTable *table, struct addrCounter *counter)
{
    struct bucket *bucket;

    if(searchFromSymbolTable(&bucket, table, "main") == -1)
    {
        fprintf(listing, "\nCannot find main function!\n");
        Error = TRUE;
    }
    else if(bucket->declType != TYPE_FUNC)
    {
        fprintf(listing, "\nCannot find main function!\n");
        Error = TRUE;
    }
    else if(bucket->addr + 1 != counter->function)
    {
        fprintf(listing, "\nmain function should be last function! : line %d\n", bucket->lineList->line);
        Error = TRUE;
    }
    else if(bucket->dataType != TYPE_VOID)
    {
        fprintf(listing, "\nmain function should be void type! : line %d\n", bucket->lineList->line);
        Error = TRUE;
    }
    else if(bucket->parameter->child[0])
    {
        fprintf(listing, "\nmain function should not have parameter! : line %d\n", bucket->lineList->line);
        Error = TRUE;
    }
}

void buildSymtab(struct treeNode *syntaxTree)
{
	struct addrCounter counter;
	struct symbolTable symbolTable;
	symbolTable.next = NULL;

	counter.function	= 0;
	counter.global		= 0;
	counter.local		= 0;

	pushTable(&symbolTable);
	checkSymbolTable(&symbolTable, syntaxTree, NULL, &counter);
	
	if(!Error) checkMain(&symbolTable, &counter);
    if(!Error) printSymTab(symbolTable.next);

	popTable(&symbolTable);
}

