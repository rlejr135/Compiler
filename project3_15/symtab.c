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
		 int vpf;
		 int is_array;
		 int arrsize;
		 int type;
   } * BucketList;

/* the hash table */
//static BucketList hashTable[SIZE];





//**** add for proj3 ****//

typedef struct ScopeListRec{
			int scope_level;
			char *func_name;

			BucketList hashTable[SIZE];

			struct ScopeListRec * parent;
			struct ScopeListRec * sibling;
			struct ScopeListRec * child;
} * ScopeList;

ScopeList head_scope;
ScopeList curr_scope;

int curr_scope_level = 0;

///////////////////////////







/* Procedure st_insert inserts line numbers and
 * memory locations into the symbol table
 * loc = memory location is inserted only the
 * first time, otherwise ignored
 */
void st_insert( char * name, int lineno, int loc, int VPF, int is_array, int arrsize, int type )
{ int h = hash(name);
  BucketList l =  curr_scope->hashTable[h];
	ScopeList walk = curr_scope;

	printf("[%s] [%d]\n", name, lineno);

	if (loc == 0){
	while (1){
		  while ((l != NULL) && (strcmp(name,l->name) != 0))
		    l = l->next;

			// **** If not exist in this scope, find parent **** //
			if (l == NULL && walk->parent != NULL){
					walk = walk->parent;
					l = walk->hashTable[h];
					continue;
			}
			break;
	}
	}
	else{
		l = NULL;
	}
  if (l == NULL) /* variable not yet in table */
  { l = (BucketList) malloc(sizeof(struct BucketListRec));
    l->name = name;
    l->lines = (LineList) malloc(sizeof(struct LineListRec));
    l->lines->lineno = lineno;
    l->memloc = loc;
    l->lines->next = NULL;
    l->next = curr_scope->hashTable[h];

		// **** add proj3 **** //
		l->vpf = VPF;
		l->is_array = is_array;
		l->arrsize = arrsize;
		l->type = type;
		////////////////////////

    curr_scope->hashTable[h] = l; }
  else /* found in table, so just add line number */
  { LineList t = l->lines, tmp;

		// **** If lineno is already exist, ignore **** //
		if (t->lineno == lineno) return;
    while (t->next != NULL){ 
				if (t->next->lineno == lineno) return;
				if (t->next->lineno > lineno){
							tmp = (LineList) malloc(sizeof(struct LineListRec));
							tmp->lineno = lineno;
							tmp->next = t->next;
							t->next = tmp;
							return;
				}

				t = t->next;
		}
    t->next = (LineList) malloc(sizeof(struct LineListRec));
    t->next->lineno = lineno;
    t->next->next = NULL;
  }
} /* st_insert */

/* Function st_lookup returns the memory 
 * location of a variable or -1 if not found
 */
int st_lookup ( char * name )
{ int h = hash(name);


	ScopeList search = curr_scope;

	// **** lookup name, if not exist, go parent scope and re - find **** //

	while(1){
			BucketList l =  search->hashTable[h];

			while ((l != NULL) && (strcmp(name,l->name) != 0)){
					l = l->next;
			}
			
			if (l == NULL && search->parent != NULL) { search = search->parent; }
			else if (l == NULL && search->parent == NULL) { return -1; }
			else { return l->memloc; }
	}
}
int st_lookup_curr_scope( char * name){
	int h = hash(name);
	BucketList l = curr_scope->hashTable[h];

	while((l != NULL) && (strcmp(name, l->name) != 0)){
				l = l->next;
	}

	if (l == NULL) return -1;
	else return l->memloc;
}



// **** proj 3 add **** //

void st_make_new_scope(int csflag){
	ScopeList temp, search_t;
	

	// **** flag == 1 function compound **** //
	// **** flag == 0 ignore **** //
	temp = (ScopeList)malloc(sizeof(struct ScopeListRec));

	// **** Increase scope level **** //

	temp->scope_level = ++curr_scope_level;
	printf("%d\n", curr_scope_level);
	// **** If now scope's child is NULL, simple connect **** //
	if (curr_scope->child == NULL){
			curr_scope->child = temp;
			temp->parent = curr_scope;
			temp->sibling = NULL;
			temp->child = NULL;
	}
	// **** If now scope's child is exist, find this child's last sibling **** //
	else{
			search_t = curr_scope->child;

			while (search_t->sibling != NULL){
						search_t = search_t->sibling;
			}
			search_t->sibling = temp;
			temp->parent = curr_scope;
			temp->child = NULL;
			temp->sibling = NULL;
	}

	if (csflag == 1){
			temp->func_name = func_name;		
	}
	else{
			temp->func_name = NULL;
	}

	curr_scope = temp;
}


void st_scope_init(){
	ScopeList head = (ScopeList)malloc(sizeof(struct ScopeListRec));
	head->parent = NULL;
	head->child = NULL;
	head->sibling = NULL;
	head->scope_level = curr_scope_level;
	head->func_name = NULL;
	head_scope = head;
	curr_scope = head_scope;
}


void st_scope_back(){
	if (curr_scope->parent != NULL){
			curr_scope = curr_scope->parent;
			curr_scope_level -= 1;
	}
}

void st_scope_go_child(){
	ScopeList walk;
	if (curr_scope->child != NULL){
			// func_name 
			walk = curr_scope->child;

			while (strcmp(walk->func_name, func_name) != 0){
						walk = walk->sibling;
			}
			curr_scope = walk;
			curr_scope_level += 1;
	}
}

//////////////////////////
/* Procedure printSymTab prints a formatted 
 * listing of the symbol table contents 
 * to the listing file
 */
void printSymTab(FILE * listing)
{ int i;
	ScopeList walk = head_scope, temp;
	
	// **** Find head scope's last child **** //
	while (walk->child != NULL){
			walk = walk->child;
	}

	// **** Print symtab repetition **** //
	while(1){
			fprintf(listing,"Name    Scope   Loc     V/P/F   Array?  ArrSize Type    Line Numbers\n");
			fprintf(listing,"--------------------------------------------------------------------\n");
			for (i=0;i<SIZE;++i)
			{ if (walk->hashTable[i] != NULL)
				{ BucketList l = walk->hashTable[i];
					while (l != NULL)
					{ LineList t = l->lines;
						fprintf(listing,"%-7s ",l->name);
						fprintf(listing,"%-7d ",walk->scope_level);
						fprintf(listing,"%-7d ",l->memloc);

						if(l->vpf == VAR)	fprintf(listing,"%-7s ", "Var");
						else if(l->vpf == PARAM)	fprintf(listing,"%-7s ", "Param");
						else fprintf(listing,"%-7s ", "Func");
						
						if(l->is_array == IS_ARRAY){
							fprintf(listing,"%-7s ", "YES");
							fprintf(listing,"%-7d ", l->arrsize);
						}
						else {
							fprintf(listing,"%-7s ", "NO");
							fprintf(listing,"%-7s ", "-");
						}
						
						if(l->type == TYPE_INT)	fprintf(listing,"%-7s ", "int");
						else if(l->type == TYPE_VOID)	fprintf(listing,"%-7s ", "void");
						else fprintf(listing,"%-7s ", "array");

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

			// **** If sibling is exist, go this scope's sibling and find last child ****//
			if (walk->sibling != NULL){
					temp = walk->sibling;
					while(temp->child != NULL){
							temp = temp->child;
					}
					walk = temp;
			}
			// **** If sibling is non-exist, go parent. **** //
			else if (walk->parent != NULL){
					walk = walk->parent;
			}
			// **** If parent is NULL, it is head scope, so finish **** //
			else if (walk->parent == NULL){
					break;
			}
	}
} /* printSymTab */
