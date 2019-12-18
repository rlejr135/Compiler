/****************************************************/
/* File: code.h                                     */
/* Code emitting utilities for the TINY compiler    */
/* and interface to the TM machine                  */
/* Compiler Construction: Principles and Practice   */
/* Kenneth C. Louden                                */
/****************************************************/

#ifndef _CODE_H_
#define _CODE_H_


#define BUFFER_SIZE 1024
#define SYM_LEN -13
#define CODE_LEN -70

/* op rg, rg, rg  */
void SyntaxType1(const char* op, const char *r1, const char *r2, const char *r3);

/* op rg, rg, val */
void SyntaxType2(const char* op, const char *r1, const char *r2, int val);

/* op rg, rg */
void SyntaxType3(const char* op, const char *r1, const char *r2);

/* op rg */
void SyntaxType4(const char* op, const char *r1);

/* emit -> comment's postion is center*/
/* print -> comment follows code */
void emitComment(const char* comment);
void printComment(const char* comment);



void emitAdd(const char* r1, const char* r2, const char* r3, const char * comment);
void emitAddi(const char * r1, const char * r2, int val, const char * comment);
void emitSub(const char *r1, const char *r2, const char *r3, const char * comment);
void emitMul(const char *r1, const char *r2, const char *r3, const char * comment);
void emitDiv(const char *r1, const char *r2, const char *r3, const char * comment);


void emitXori(const char *r1, const char *r2, int value, const char * comment);
void emitOr(const char *r1, const char *r2, const char *r3, const char * comment);

void emitMove(const char *r1, const char *r2, const char * comment);
void emitLi(const char *r, int value, const char * comment);

void emitLw(const char *r1, const char *r2, int offset, const char * comment);
void emitSw(const char *r1, const char *r2, int offset, const char * comment);

void emitLa(const char *r, const char *name, const char * comment);
void emitSlt(const char *r1, const char *r2, const char* r3, const char * comment);
void emitBeqz(const char *r, const char *labelname, int labelnum, const char * comment);

void emitJ(const char *labelname, int labelnum, const char * comment);
void emitJr(const char *r, const char * comment);
void emitJal(const char *name, const char * comment);


void emitPush(const char *reg);
void emitPop(const char *reg);



#endif
