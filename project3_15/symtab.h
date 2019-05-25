/****************************************************/
/* File: symtab.h                                   */
/* Symbol table interface for the TINY compiler     */
/* (allows only one symbol table)                   */
/* Compiler Construction: Principles and Practice   */
/* Kenneth C. Louden                                */
/****************************************************/

#ifndef _SYMTAB_H_
#define _SYMTAB_H_

/* Procedure st_insert inserts line numbers and
 * memory locations into the symbol table
 * loc = memory location is inserted only the
 * first time, otherwise ignored
 */
void st_insert( char * name, int lineno, int loc, int VPF, int is_array, int arrsize, int type );

/* Function st_lookup returns the memory 
 * location of a variable or -1 if not found
 */
int st_lookup ( char * name );

/* Procedure printSymTab prints a formatted 
 * listing of the symbol table contents 
 * to the listing file
 */
void printSymTab(FILE * listing);


// **** proj3 add **** //

// **** csflag -> make child scope or make sibling scope **** //
// **** make new scope list and change curr_scope.				**** //

void st_make_new_scope(int csflag);		 	
					

// make head scope
void st_scope_init();


// **** scope go back(go now scope's parent) **** //
void st_scope_back();

// **** go now scope's child **** //
void st_scope_go_child();

int st_lookup_curr_scope(char * name);


#define VAR 0
#define PARAM 1
#define FUNC 2

#define IS_ARRAY 1
#define NOT_ARRAY 0

#define TYPE_INT 0
#define TYPE_VOID 1
#define TYPE_ARRAY 2


extern char* func_name;

/////////////////////////

#endif
