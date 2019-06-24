* TINY Compilation to TM Code
* File: test2.tm
* Standard prelude:
  0:     LD  5,0(0) 	load maxaddress from location 0
  1:     LD  2,0(0) 	load maxaddress from location 0
  2:     LD  3,0(0) 	load maxaddress from location 0
  3:     ST  0,0(0) 	load maxaddress from location 0
  4:    LDA  3,1(3) 	INITIALIZE
* End of standard prelude.
* -> compound
* -> if
* -> Op
* -> Id
  6:     LD  0,1(2) 	store IdK value fp
* <- Id
  7:     ST  0,0(6) 	op: push left
  8:    LDA  6,1(6) 	mp increase
* -> Const
  9:    LDC  0,1(0) 	load const
* <- Const
 10:    LDA  6,-1(6) 	mp decrease
 11:     LD  1,0(6) 	op: load left
 12:    SUB  0,1,0 	op >
 13:    JGT  0,2(7) 	br if true
 14:    LDC  0,0(0) 	false case
 15:    LDA  7,1(7) 	unconditional jmp
 16:    LDC  0,1(0) 	true case
* <- Op
* if: jump to else belongs here
* -> return
* -> Op
* -> Id
 18:     LD  0,1(2) 	store IdK value fp
* <- Id
 19:     ST  0,0(6) 	op: push left
 20:    LDA  6,1(6) 	mp increase
* -> Call
* -> Op
* -> Id
 21:     LD  0,1(2) 	store IdK value fp
* <- Id
 22:     ST  0,0(6) 	op: push left
 23:    LDA  6,1(6) 	mp increase
* -> Const
 24:    LDC  0,1(0) 	load const
* <- Const
 25:    LDA  6,-1(6) 	mp decrease
 26:     LD  1,0(6) 	op: load left
 27:    SUB  0,1,0 	op -
* <- Op
 28:     ST  0,-1(3) 	store argument
 29:    LDA  3,-1(3) 	adjust SP
 30:    LDA  3,-2(3) 	allocate cntl link and ret addr
 31:     ST  2,1(3) 	store cntl link
 32:    LDA  2,1(3) 	store current FP
 33:    LDC  1,3(0) 	TEST
 34:    LDA  4,0(7) 	TEST
 35:    ADD  4,1,4 	TEST
 36:     ST  4,0(3) 	save return 
 37:    LDA  7,-32(7) 	jump to function
 38:    LDA  3,2(2) 	restore SP
 39:     LD  2,0(2) 	restore FP
* <- Call
 40:    LDA  6,-1(6) 	mp decrease
 41:     LD  1,0(6) 	op: load left
 42:    MUL  0,1,0 	op *
* <- Op
 43:     LD  7,-1(2) 	Jump to return address
* <- return
* if: jump to end belongs here
 17:    JEQ  0,27(7) 	if: jmp to else
* -> return
* -> Const
 45:    LDC  0,1(0) 	load const
* <- Const
 46:     LD  7,-1(2) 	Jump to return address
* <- return
 44:    LDA  7,2(7) 	jmp to end
* <- if
* -> return
* -> Const
 47:    LDC  0,1(0) 	load const
* <- Const
 48:     LD  7,-1(2) 	Jump to return address
* <- return
* <- compound
 49:     LD  7,-1(2) 	Jump to return address
 50:    LDA  2,0(3) 	fp adjust
  5:    LDA  7,44(7) 	Jump to main function
* -> compound
 51:    LDA  3,1(3) 	adjust SP
* -> Call
 52:     IN  0,0,0 	read integer value
 53:     ST  0,-1(3) 	store argument
 54:    LDA  3,-1(3) 	adjust SP
 55:    LDA  3,-2(3) 	allocate cntl link and ret addr
 56:     ST  2,1(3) 	store cntl link
 57:    LDA  2,1(3) 	store current FP
 58:    LDC  1,3(0) 	TEST
 59:    LDA  4,0(7) 	TEST
 60:    ADD  4,1,4 	TEST
 61:     ST  4,0(3) 	save return 
 62:    LDA  7,-57(7) 	jump to function
 63:    LDA  3,2(2) 	restore SP
 64:     LD  2,0(2) 	restore FP
* <- Call
 65:    OUT  0,0,0 	write integer value
* <- compound
* End of execution.
 66:   HALT  0,0,0 	
