DEPEND_FILE = depend_file
.SUFFIXES : .c .o

CC = gcc
CFLAGS = -g

SRCS = main.c util.c symbol.c type.c lex.yy.c y.tab.c
OBJS = $(SRCS:%.c=%.o)
TARGET = project3_12
LEX = flex
LEXFILE = cm.l
YACC = yacc -d -v
YACCFILE = cm.y
OPTION = -ly -ll
ANOTHER = lex.yy.c y.tab.c y.tab.h y.output

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $@ $(OBJS) $(OPTION)

lex.yy.c: $(LEXFILE)
	$(LEX) $(LEXFILE)

y.tab.c y.tab.h: $(YACCFILE)
	$(YACC) $(YACCFILE)

dep:
	$(LEX) $(LEXFILE)
	$(YACC) $(YACCFILE)
	$(CC) -MM $(SRCS) > $(DEPEND_FILE)
	$(CC) -MM lex.yy.c | sed 's/lex.yy.o: lex.yy.c/lex.yy.c:/g' >> $(DEPEND_FILE)
	$(CC) -MM y.tab.c | sed 's/y.tab.o: y.tab.c/y.tab.c:/g' | sed 's/y.tab.h//g' >> $(DEPEND_FILE)


clean:
	rm -f $(OBJS) $(TARGET) $(DEPENT_FILE)

cleanall: clean
	rm -f $(ANOTHER)

ifneq ($(MAKECMDGOALS), clean)
ifneq ($(MAKECMDGOALS), depend)
-include $(DEPEND_FILE)
endif
endif
