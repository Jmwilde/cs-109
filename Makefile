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

SRC := $(wildcard $(SRCDIR)/*.cpp)
DEPS := $(wildcard $(SRCDIR)/*.h)
OBJS := $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SRC))

TESTSRC := $(wildcard $(TSTDIR)/*.cpp)
TESTOBJ := $(patsubst $(TESTDIR)/%.cpp, $(TESTDIR)/%.o, $(TESTSRC))

CC = g++
DEBUG = -g
CXXFLAGS = -Wall -std=c++14 -c $(DEBUG)
LFLAGS = -Wall -std=c++14 $(DEBUG)

all: output

output: $(OBJS)
	$(CC) $(LFLAGS) $^ -o $@

test: $(TESTDIR)/test.o $(OBJDIR)/rule.o $(OBJDIR)/fact.o $(OBJDIR)/rule_engine.o
	$(CC) $(LFLAGS) $^ -o $@

test.o: $(TESTDIR)/test.cpp $(DEPS)
	$(CC) $(CXXFLAGS) $< -o $@

$(OBJS): $(OBJDIR)/%.o: $(SRCDIR)/%.cpp $(DEPS)
	mkdir -p $(@D)
	$(CC) $(CXXFLAGS) $< -o $@

clean:
	rm objects/*.o
	rm output
	rm test

test_run: test
	./test

run: output
	./output

.PHONY: clean run
