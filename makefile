SRCDIR=src
LIBDIR=lib
BINDIR=bin
INCLUDEDIR=include
TESTSRCDIR=$(SRCDIR)/tests
TESTDIR=tests
DOCDIR=doc
CC = gcc
YACC=yacc
LEX=lex
CFLAGS=-Wall -pedantic -g -std=gnu99
#CFLAGS=-g
LDFLAGS=-lm

FICHIER_LEX=analyseurLexical
FICHIER_YACC=analyseurSyntaxique
HEADER_LEX_YACC=constantes

LIB_OBJECTS=$(SRCDIR)/erreur.o $(SRCDIR)/expression.o $(SRCDIR)/instruction.o $(SRCDIR)/listeChainee.o $(SRCDIR)/memoire.o $(SRCDIR)/valeur.o  $(SRCDIR)/variable.o $(SRCDIR)/label.o $(SRCDIR)/tableDeLabels.o $(SRCDIR)/programme.o $(SRCDIR)/$(FICHIER_LEX).o $(SRCDIR)/$(FICHIER_YACC).o 


all : bASIc 

bASIc :  $(BINDIR)/bASIc

doc: $(DOCDIR)/html

$(BINDIR)/bASIc : $(LIB_OBJECTS) $(SRCDIR)/main.o
	gcc -o $@ $(LIB_OBJECTS) $(SRCDIR)/main.o

$(LIBDIR)/lib$(LIB).a : $(LIB_OBJECTS)
	$(AR)  r $(LIBDIR)/lib$(LIB).a  $^

$(SRCDIR)/%.o : $(SRCDIR)/%.c
	$(CC) -o $@ -c $< $(CFLAGS) -I$(INCLUDEDIR)  

$(LIBDIR)/%.so : $(SRCDIR)/%.c
	$(CC) -shared -o $@ -c $< $(CFLAGS) -I$(INCLUDEDIR)  

$(SRCDIR)/$(FICHIER_YACC).c : $(SRCDIR)/$(FICHIER_YACC).y
	$(YACC) -o $(SRCDIR)/$(FICHIER_YACC).c $^

$(SRCDIR)/$(FICHIER_LEX).c : $(SRCDIR)/$(FICHIER_LEX).l $(INCLUDEDIR)/$(HEADER_LEX_YACC).h
	$(LEX) -o $(SRCDIR)/$(FICHIER_LEX).c $<

$(INCLUDEDIR)/$(HEADER_LEX_YACC).h : $(SRCDIR)/$(FICHIER_YACC).y
	$(YACC) --defines=$(INCLUDEDIR)/$(HEADER_LEX_YACC).h -o $(SRCDIR)/$(FICHIER_YACC).c $<	

$(DOCDIR)/html: $(INCLUDEDIR)/erreur.h $(INCLUDEDIR)/expression.h $(INCLUDEDIR)/instruction.h $(INCLUDEDIR)/listeChainee.h $(INCLUDEDIR)/memoire.h $(INCLUDEDIR)/valeur.h  $(INCLUDEDIR)/variable.h $(INCLUDEDIR)/label.h $(INCLUDEDIR)/tableDeLabels.h $(INCLUDEDIR)/programme.h
	doxygen

clean :
	rm -f $(BINDIR)/*
	rm -f $(LIBDIR)/*
	rm -f $(TESTDIR)/*
	rm -f $(SRCDIR)/*.o
	rm -f $(TESTSRCDIR)/*.o
	rm -f $(SRCDIR)/$(FICHIER_LEX).c
	rm -f $(SRCDIR)/$(FICHIER_YACC).c
	rm -f $(INCLUDEDIR)/$(FICHIER_YACC).h
	rm -rf $(DOCDIR)/*



