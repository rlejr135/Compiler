/****************************************************/
/* File: symtab.c                                   */
/* Symbol table implementation for the TINY compiler*/
/* (allows only one symbol table)                   */
/* Symbol table is implemented as a chained         */
/* hash table                                       */
/* Compiler Construction: Principles and Practice   */
/* Kenneth C. Louden                                */
/****************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symtab.h"

/* SIZE is the size of the hash table */
#define SIZE 211

/* SHIFT is the power of two used as multiplier
   in hash function  */
#define SHIFT 4

/* the hash function */
static int hash ( char * key )
{ int temp = 0;
  int i = 0;
  while (key[i] != '\0')
  { temp = ((temp << SHIFT) + key[i]) % SIZE;
    ++i;
  }
  return temp;
}


   
/* the list of line numbers of the source 
 * code in which a variable is referenced
 */
typedef struct LineListRec
   { int lineno;
     struct LineListRec * next;
   } * LineList;

/* The record in the bucket lists for
 * each variable, including name, 
 * assigned memory location, and
 * the list of line numbers in which
 * it appears in the source code
 */
typedef struct BucketListRec
   { char * name;
     LineList lines;
     int memloc ; /* memory location for variable */
     struct BucketListRec * next;
	 int scope ; 
	 char * VPF ;
	 int arraySize;
	 ExpKind type;
   } * BucketList;

/* the list of parameter numbers of the source 
 * code in which a variable is referenced
 */
typedef struct ParamListRec
   { int paramNum;
     ExpKind type;
     struct ParamListRec * next;
   } * ParamList;

typedef struct ScopeListRec
   {
	 BucketList hashTable[SIZE];
	 int scope;
	 int upLocation;
	 int downLocation;
	 int funcLocation;
   struct ScopeListRec * scopeChild;
	 struct ScopeListRec * scopeSibling;
	 struct ScopeListRec * scopeParent;
	 char * funcName;
	 int isSearched;
	 ParamList params;
   } * ScopeList;

// /* the hash table */
// static BucketList hashTable[SIZE];

// head
static ScopeList headScopeList;
static ScopeList currentScopeList;

void st_init(){
	currentScopeList = headScopeList->scopeChild;
	currentScope = 0;
}
	
void st_setCurrentScope(){
	
	// fprintf(listing, "st_setCurrentScope currentFunction [%s] [%d] [%d]\n", currentScopeList->funcName, currentScope, currentScopeList->scope);
	 ScopeList t = currentScopeList->scopeChild;
	 while(t->isSearched != FALSE){
		//  fprintf(listing, "function[%s] is already Searched [%d] t=[%d], next=[%s]\n", t->funcName, currentScope, t->scope, t->scopeSibling->funcName);
		 t = t->scopeSibling;
	 }
     currentScopeList = t;
	 currentScopeList->isSearched = TRUE;
	 // fprintf(listing, "set scope  [%d][%s] is Searched \n", currentScopeList->scope, currentScopeList->funcName);
	 // fprintf(listing,"----------\n");
}

void st_make(int isFuncDeclaration){

   ScopeList temp = (ScopeList) malloc(sizeof(struct ScopeListRec));
	 temp->scope = currentScope;

	 // set location 
	 if(currentScope == 1){
		 temp->upLocation = 0;
		 temp->downLocation = -4;
		 temp->funcLocation = 0;
	 }
	 else{	 
		 temp->upLocation = currentScopeList->upLocation;
		 temp->downLocation = currentScopeList->downLocation;
		 if(isFuncDeclaration)
			 temp->downLocation -= 4;
		 temp->funcLocation = currentScopeList->funcLocation;
	 }
	 
	 temp->scopeChild = NULL;
	 temp->scopeParent = currentScopeList;
	 temp->funcName = currentFuncName;
	 temp->isSearched = FALSE;
	 
	 temp->params = (ParamList) malloc(sizeof(struct ParamListRec));
	 temp->params->paramNum = 0;
	 temp->params->next = NULL;
	 
	 // parent has no child scope, then temp will be child of parent
	 if(currentScopeList->scopeChild == NULL)
		currentScopeList->scopeChild = temp;
	 else{	 
		 // parent has other scope, then temp will be sibling of last
		 ScopeList t, firstChild = currentScopeList->scopeChild;
		 t = firstChild;
		 while(t->scopeSibling != NULL){
			 t = t->scopeSibling;
		 }	
		 t->scopeSibling = temp;
	 }
	 
	 currentScopeList = temp;
}

ScopeList findParents(char * name){
	int h = hash(name);
	ScopeList s = currentScopeList;
	while(s!= NULL){
		BucketList l =  s->hashTable[h];
		while ((l != NULL) && (strcmp(name,l->name) != 0))
			l = l->next;
		if (l == NULL) 
			s = s->scopeParent;
		else 
			return s;
	}
	return NULL;
}

ScopeList getInsertScopeList(char *name, int isDeclaration ){
//	fprintf(listing, "getInsertScopeList %s\n", name);

	if(headScopeList == NULL) {
		// making head
		headScopeList = (ScopeList) malloc(sizeof(struct ScopeListRec));
		
		// making head->scopeChild
		headScopeList->scopeChild = (ScopeList) malloc(sizeof(struct ScopeListRec));
		headScopeList->scopeChild->scope = 0;
		headScopeList->scopeChild->upLocation = 0;
		headScopeList->scopeChild->downLocation = 0;
		headScopeList->scopeChild->funcLocation = 0;
		headScopeList->scopeChild->scopeChild = NULL;
		headScopeList->scopeChild->scopeParent = NULL;
		headScopeList->scopeChild->scopeSibling = NULL;
		headScopeList->scopeChild->funcName = NULL;
		// set current
		currentScopeList = headScopeList->scopeChild;
	}

	//	isDeclaration ? 
	//  true -> insert only currentScope 
	if(isDeclaration) 
		return currentScopeList;

	//  false -->  search all scope 
	return findParents(name);
}

int calculateLocation (ScopeList s,int loc, int arraySize){

	if(arraySize == -1 || arraySize == 0 ) // not array or param array
		arraySize = 1;

	if(loc > 0)
		return s->upLocation += loc * arraySize;
	else if(loc < 0)
		return s->downLocation += loc * arraySize;
	else if(loc == 0)
		return s->funcLocation ++;
	else
		return 0;
}

/* Procedure st_insert inserts line numbers and
 * memory locations into the symbol table
 * loc = memory location is inserted only the
 * first time, otherwise ignored
 */
void st_insert( char * name, int lineno, int loc , char *vpf, int arraySize, ExpKind type, int isDeclaration)
{ 
	int h = hash(name);

//	fprintf(listing, "st_insert %s\n", name);

	ScopeList s = getInsertScopeList(name, isDeclaration);
  BucketList l =  s->hashTable[h];

  while ((l != NULL) && (strcmp(name,l->name) != 0))
    l = l->next;
  if (l == NULL) /* variable not yet in table */
  { l = (BucketList) malloc(sizeof(struct BucketListRec));
    l->name = name;
    l->lines = (LineList) malloc(sizeof(struct LineListRec));
    l->lines->lineno = lineno;
		l->scope = s->scope;
    l->memloc = calculateLocation(s, loc, arraySize);
		l->VPF = vpf;
		l->arraySize = arraySize;
		l->type = type;
    l->lines->next = NULL;
    l->next = s->hashTable[h];
    s->hashTable[h] = l; 
	
	if(strcmp(l->VPF, "Param") == 0){
		ParamList p = s->params;
		while(p->next != NULL){
		    p = p->next;
		}
		p->next = (ParamList) malloc(sizeof(struct ParamListRec));
		p->next->paramNum = p->paramNum + 1; 
		p->next->type = l->type;
		p->next->next = NULL;
	}
  }
  else /* found in table, so just add line number */
  { LineList t = l->lines;
    while (t->next != NULL) 
	{
		if(t->next->lineno == lineno)
			return ;
		t = t->next;
	}
    t->next = (LineList) malloc(sizeof(struct LineListRec));
    t->next->lineno = lineno;
    t->next->next = NULL;
  }
	
//  fprintf(listing, "st_insert end %s\n", name);

} /* st_insert */

/* Function st_lookup returns the memory 
 * location of a variable or -1 if not found
 */
int st_lookup ( char * name )
{ 
	int h = hash(name);
	
//	fprintf(listing, "st_lookup %s\n", name);

	if(headScopeList == NULL) 
        return -1;
	
	if(currentScopeList == NULL) 
        return -1;
	
	ScopeList s = findParents(name);
	if(s == NULL)
		return -1;
	return s->scope;
}

void st_goback(){ 
	currentScopeList = currentScopeList->scopeParent;
}
//ssg
int st_hasNoSibling(char *name){
    int h = hash(name);
    int i;
    // 0 scope
    ScopeList s = findParents(name);

    if(s == NULL)
        return FALSE;
    
    //ERROR

    s = s->scopeChild;
	while(s != NULL){
		if(strcmp(s->funcName, name) == 0){
			if(s->scopeSibling == NULL)
				return TRUE;
			else 
				return FALSE;
				
		}
		
		s = s->scopeSibling;
	}
	
	return FALSE;
}
//ssg
char * st_getVPF(char *name){
    int h = hash(name);

    ScopeList s = findParents(name);

    if(s == NULL){
        return NULL;
    }
    //ERROR

    BucketList l = s->hashTable[h];	
    while ((l != NULL) && (strcmp(name,l->name) != 0))
        l = l->next;
    // fprintf(listing, "l type = [%d]\n", l->type);
    return l->VPF;

}

ExpKind st_getType(char * name){
    int h = hash(name);
	
	// fprintf(listing, "name = %s scope = [%d] curScopeList =[%d]\n", name, currentScope, currentScopeList->scope);
	ScopeList s = findParents(name);
	
	if(s == NULL){
		// fprintf(listing, "name  = [%s]\n", name);
		return -1;
	}
		//ERROR
	
	BucketList l = s->hashTable[h];	
	while ((l != NULL) && (strcmp(name,l->name) != 0))
			l = l->next;
	// fprintf(listing, "l type = [%d]\n", l->type);
	return l->type;
}

ScopeList st_getScopeByFuncName(char * funcName){
	ScopeList s = headScopeList->scopeChild->scopeChild;
	while(s->scopeSibling != NULL){
		if(strcmp(s->funcName, funcName)==0)
			return s;
		s=s->scopeSibling;
	}
	return NULL;
}

int st_checkFuncParamCnt(char * funcName, int cnt){
	ScopeList s = st_getScopeByFuncName(funcName);
	ParamList p; 
	
	if(s == NULL)
		return FALSE;
		
	p = s->params;
	
	while(p->next != NULL){
		p = p->next;
	}
	
	if(cnt == p->paramNum)
		return TRUE;
	return FALSE;
}

int st_checkFuncParamType(char * funcName, int idx, ExpKind type){
	ScopeList s = st_getScopeByFuncName(funcName);
	ParamList p; 
	
	if(s == NULL)
		return FALSE;
		
	p = s->params;
		
	while(idx != 0){
		p = p->next;
		idx--;
	}
	
	
	if(p->type == Void || type == Void)
		return FALSE;
	return TRUE;
}

void printFormat(FILE * listing, ScopeList s)
{ 

	int i;
	int COLUMN_SIZE = 8;
  	
	//fprintf(listing,"[%d - %d] ", s->scope, currentScope);
  char *columnName[] = {"Name", "Scope", "Loc", "V/P/F", "Array?", "ArrSize", "Type", "Line Numbers"};
  char *type; 
  for(i=0; i< COLUMN_SIZE; i++){
	  fprintf(listing, "%-8s ", columnName[i]);
  }
  fprintf(listing,"\n");

  for(i=0; i< COLUMN_SIZE; i++){
	  fprintf(listing, "%-8s-", "--------");
	  if(i == COLUMN_SIZE -1 )
	  	fprintf(listing, "%-8s-", "--------");
  }
  fprintf(listing,"\n");

  for (i=0;i<SIZE;++i)
  { if (s->hashTable[i] != NULL)
    { BucketList l = s->hashTable[i];
      while (l != NULL)
      { 
	  	fprintf(listing, "%-8s ", l->name);
	  	fprintf(listing, "%-8d ", l->scope);
	  	fprintf(listing, "%-8d ", l->memloc);
	  	fprintf(listing, "%-8s ", l->VPF);
	  	fprintf(listing, "%-8s ", l->arraySize == -1 ? "No" : "Yes");
		if(l->arraySize == -1 )
		 	fprintf(listing, "%-8s ", "-");
		else
		 	fprintf(listing, "%-8d ", l->arraySize);
	  	
		switch(l->type){
			case Void:
				type = "Void";
				break;
			case Integer:
				type = "Integer";
				break;
			case IntegerArray:
				type = "Array";
				break;
			default:
				type = NULL;
				break;
		}
		fprintf(listing, "%-8s ", type);
		
		LineList t = l->lines;
        while (t != NULL)
        { fprintf(listing,"%4d ",t->lineno);
          t = t->next;
        }
        fprintf(listing,"\n");
        l = l->next;
      }
    }
  }
  fprintf(listing,"\n");
} /* printSymTab */


void printScopeList(FILE * listing, ScopeList s)
{ 
  if (s != NULL)
  { 
    printScopeList(listing, s->scopeChild);
    printFormat(listing, s);
	printScopeList(listing, s->scopeSibling);
  }
}

/* Procedure printSymTab prints a formatted 
 * listing of the symbol table contents 
 * to the listing file
 */
void printSymTab(FILE * listing){
		printScopeList(listing, headScopeList->scopeChild);
}
