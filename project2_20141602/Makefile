TARGET = 20141602

CC = gcc
CFLAGS = -g -c

OBJECTS = main.o util.o lex.yy.o y.tab.o
SRCS = main.c util.c lex.yy.c y.tab.c

$(TARGET) : $(OBJECTS) lex.yy.c y.tab.c
		$(CC) -o $(TARGET) $(OBJECTS)

y.tab.c : cm.y
	yacc -d cm.y

lex.yy.c: cm.l
	flex cm.l



main.o : util.h globals.h parse.h $(SRCS)
	$(CC) $(CFLAGS) -c $(SRCS)



clean:
	-rm -rf *.o lex.yy.c y.tab.* 20141602
