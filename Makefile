# CMPS 109
# Winter 2017

# John Wilde - jmwilde
# Nathaniel Suriawijaya - nsuriawi
# Tako Takeda - katakeda
# Noriaki Nakano - nnakano

# This Makefile assumes you keep .h and .cpp in one directory,
# and .o files in a seperate directory.

SHELL = /bin/bash

SRCDIR = source
OBJDIR = objects
TESTDIR = tests
TESTOBJDIR = test_obj

SRC := $(wildcard $(SRCDIR)/*.cpp)
DEPS := $(wildcard $(SRCDIR)/*.h)
OBJS := $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SRC))

TESTSRC := $(wildcard $(TESTDIR)/*.cpp)
TESTOBJ := $(patsubst $(TESTDIR)/%.cpp, $(TESTOBJDIR)/%.o, $(TESTSRC))

CC = g++
DEBUG = -g
PTHREAD = -pthread
NOSIGN = -Wno-sign-compare
CXXFLAGS = -W -Wall -pedantic -Wno-unused-parameter $(PTHREAD) $(NOSIGN) -std=c++14 -c $(DEBUG)
LFLAGS = -W -Wall -Werror -pedantic -std=c++14 $(DEBUG)

all: output

output: $(OBJS)
	$(CC) $(LFLAGS) $^ -o $@

test: $(TESTOBJDIR)/test.o $(OBJDIR)/rule.o $(OBJDIR)/fact.o $(OBJDIR)/rule_engine.o
	$(CC) $(LFLAGS) $^ -o $@

$(TESTOBJ): $(TESTOBJDIR)/%.o: $(TESTDIR)/%.cpp $(DEPS)
	mkdir -p $(@D)
	$(CC) $(CXXFLAGS) $< -o $@

$(OBJS): $(OBJDIR)/%.o: $(SRCDIR)/%.cpp $(DEPS)
	mkdir -p $(@D)
	$(CC) $(CXXFLAGS) $< -o $@

clean:
	rm objects/*.o
	rm test_obj/*.o
	rm output
	rm test

test_run: test
	./test

run: output
	./output

.PHONY: clean run
