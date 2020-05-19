HEADDIR = head
SRCDIR = src
BUILDDIR = build

MAIN = main
MT = mt
LCG = lcg
TESTS = tests

CC = gcc
FLAGS = -g -Wall -std=c99 -I$(HEADDIR)

.PHONY: all clean

all: before $(MAIN)

before:
	@[ -d $(BUILDDIR) ] || mkdir $(BUILDDIR)

$(MAIN): $(BUILDDIR)/$(MAIN).o $(BUILDDIR)/$(MT).o $(BUILDDIR)/$(LCG).o $(BUILDDIR)/$(TESTS).o
	@echo Enlazando $@: $^
	$(CC) -o $@ $^ $(FLAGS)

$(BUILDDIR)/%.o: $(SRCDIR)/%.c
	@echo Compilando $@: $^
	$(CC) -o $@ -c $^ $(FLAGS)

clean:
	@rm -f ./$(BUILDDIR)/* $(MAIN)