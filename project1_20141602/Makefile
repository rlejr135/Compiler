CC = gcc

CFLAGS = 

OBJS = main.o util.o lex.yy.o

20141602: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o 20141602 -lfl

main.o: main.c globals.h util.h scan.h 
	$(CC) $(CFLAGS) -c main.c

util.o: util.c util.h globals.h
	$(CC) $(CFLAGS) -c util.c

lex.yy.o: lex.yy.c util.h globals.h scan.h
	$(CC) $(CFLAGS) -c lex.yy.c

lex.yy.c: tiny.l
	flex tiny.l

clean:
	-rm 20141602
	-rm $(OBJS)
	-rm lex.yy.c

all: 20141602

