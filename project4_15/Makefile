TARGET = project4_15

CC = gcc
CFLAGS = -g -c

OBJECTS = main.o util.o lex.yy.o y.tab.o symtab.o analyze.o code.o cgen.o
SRCS = main.c util.c lex.yy.c y.tab.c symtab.c analyze.c code.c cgen.c

$(TARGET) : $(OBJECTS) lex.yy.c y.tab.c
		$(CC) -o $(TARGET) $(OBJECTS)

y.tab.c : cm.y
	yacc -d cm.y

lex.yy.c: cm.l
	flex cm.l



main.o : util.h globals.h parse.h symtab.h analyze.h $(SRCS)
	$(CC) $(CFLAGS) -c $(SRCS)



clean:
	-rm -rf *.tm *.o lex.yy.c y.tab.* project4_15
