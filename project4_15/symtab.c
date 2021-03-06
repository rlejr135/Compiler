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

typedef struct ScopeListRec{
			int scope_level;

			BucketList hashTable[SIZE];

			struct ScopeListRec * parent;
			struct ScopeListRec * sibling;
			struct ScopeListRec * child;
			
			ParamList params;
			char * name;
			int visited;

			int func_emit_loc;
			int gen_visited;
} * ScopeList;

ScopeList head_scope;
ScopeList curr_scope;

ScopeList gen_current;

ScopeList for_call_scope[100];
static int now_call_save_level = 0;
static int now_call_get_level = 0;

int curr_scope_level = 0;
int check_is_global;


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

// **** lookup my, and my parent scope **** //
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
			else {
				if (search->parent == NULL)
					check_is_global = 1;
				return l->memloc; 
			}
	}
}

// **** lookup only current scope **** //
int st_lookup_curr_scope( char * name){
	int h = hash(name);
	BucketList l = curr_scope->hashTable[h];

	while((l != NULL) && (strcmp(name, l->name) != 0)){
				l = l->next;
	}

	if (l == NULL) return -1;
	else return l->memloc;
}

int st_lookup_data( char *name, int *isarray, int *VPF){
	int h = hash(name);
	
	ScopeList search = curr_scope;

	// **** find scope and check it's data type and array **** //
	while(1){
				BucketList l = search->hashTable[h];

		while((l != NULL) && (strcmp(name, l->name) != 0)){
				l = l->next;		
		}
		if(l == NULL && search->parent != NULL) { search = search->parent;}
		else if (l == NULL && search->parent == NULL) { return -1; }
		else {
				*isarray = l->is_array;
				*VPF = l->vpf;
				return l->type;
		}	
	}	
}


// **** proj 3 add **** //

void st_make_new_scope(int csflag){
	ScopeList temp, search_t;
	

	// **** flag == 1 function compound **** //
	// **** flag == 0 ignore **** //
	temp = (ScopeList)malloc(sizeof(struct ScopeListRec));

	// **** Increase scope level **** //

	temp->scope_level = ++curr_scope_level;
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
	temp->visited = FALSE;

	if (glo_func_name != NULL){
			temp->name = glo_func_name;
			glo_func_name = NULL;
	}
	else{
			temp->name = NULL;
	}

	// **** for parameter type checking. **** //
	if(csflag >= 1){
			temp->params = (ParamList)malloc(sizeof(struct ParamListRec));
			temp->params->param_num = 1;
			temp->params->type = csflag; 
			temp->params->next = NULL;
	}
	else{
			temp->params = NULL;
	}
	

	temp->func_emit_loc = 0;
	temp->gen_visited = 0;
	curr_scope = temp;
}

// **** for parameter check, attach parameter **** //
void st_attach_param(int csflag){
	ParamList walk, tmp = (ParamList)malloc(sizeof(struct ParamListRec));
	
	walk = curr_scope->params;
	while(walk->next != NULL){
				walk = walk->next;
	}

	tmp->type = csflag;
	tmp->param_num = walk->param_num + 1;
	tmp->next = NULL;
	walk->next = tmp;
}


void st_scope_init(){
	ScopeList head = (ScopeList)malloc(sizeof(struct ScopeListRec));
	head->parent = NULL;
	head->child = NULL;
	head->sibling = NULL;
	head->scope_level = curr_scope_level;
	head_scope = head;
	curr_scope = head_scope;
}

// **** go parent scope **** //
void st_scope_back(){
	if (curr_scope->parent != NULL){
			curr_scope = curr_scope->parent;
			curr_scope_level -= 1;
	}
}

void st_scope_go_child(){
	if (curr_scope->child != NULL){
			curr_scope = curr_scope->child;
			while (curr_scope->visited == TRUE){
						curr_scope = curr_scope->sibling;
			}
			curr_scope->visited = TRUE;
			curr_scope_level += 1;
	}
}

ParamList st_find_func_data(char * name, int *type){
		ScopeList search = head_scope;
 int h = hash(name);

 // **** find what function type is **** //
	while(1){
			BucketList l =  search->hashTable[h];

			while ((l != NULL) && (strcmp(name,l->name) != 0)){
					l = l->next;
			}
			
			if (l == NULL && search->child != NULL) { search = search->child; }
			else {
					*type = l->type;
					break;
			}
	}

	// **** find where function scope is **** //
	search = head_scope->child;
	while (strcmp(search->name, name) != 0){
		if ( search->sibling != NULL){
				search = search->sibling;
		}

	}
	curr_scope = search;
	while(curr_scope ->child != NULL){
				curr_scope = curr_scope->child;
	}


	return search->params;
}

void set_call_scope(){
	for_call_scope[now_call_save_level++] = curr_scope;	
}

void get_call_scope(){
		curr_scope = for_call_scope[now_call_get_level++];
}

void st_param_loc_up(){
	BucketList l;
	int i;

	for (i = 0 ; i < SIZE ; i++){
			l = curr_scope->hashTable[i];
			while (l!= NULL){
						l->memloc += 4;
						l = l->next;
			}
	}

}

// **** do not use **** //
void st_set_head(){
		curr_scope = head_scope;
}




void st_set_emit_loc(char *name, int emitLoc){
	ScopeList curr = head_scope ->child;

	while(strcmp(curr->name, name) != 0){
		if (curr->sibling == NULL){
			break;
		}
		curr = curr->sibling;
	}

	curr->func_emit_loc = emitLoc;
}

int st_get_emit_loc(char *name){
	ScopeList curr = head_scope -> child;

	while (strcmp(curr->name, name) != 0){
		if (curr->sibling == NULL){
			break;
		}
		curr = curr->sibling;
	}

	return curr->func_emit_loc;
}
int st_get_target_loc(char *name, int *flag){

	int res_loc ;
	curr_scope = gen_current;

	// check find variable is global
	check_is_global = 0;
	res_loc = st_lookup(name);

	if (check_is_global == 1){
		*flag = 1;
	}
	return res_loc / 4;
}

void st_gen_start(){
	gen_current = head_scope;
}

void st_gen_down(){
	gen_current = gen_current->child;

	while(gen_current->gen_visited == 1){
		gen_current = gen_current->sibling;
	}
	gen_current->gen_visited = 1;
}

void st_gen_up(){
	gen_current = gen_current->parent;
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
						else if(l->vpf == PARAM)	fprintf(listing,"%-7s ", "Par");
						else fprintf(listing,"%-7s ", "Func");
						
						if(l->is_array == IS_ARRAY){
							fprintf(listing,"%-7s ", "Array");
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
