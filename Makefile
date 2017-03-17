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
DEPSDIR = headers
TESTDIR = tests
TESTOBJDIR = test_obj

SRC := $(wildcard $(SRCDIR)/*.cpp)
DEPS := $(wildcard $(DEPSDIR)/*.h)
OBJS := $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SRC))
MAINS := $(OBJDIR)/client.o $(OBJDIR)/main.o $(OBJDIR)/server.o
NOMAINS := $(filter-out $(MAINS), $(OBJS))
TESTSRC := $(wildcard $(TESTDIR)/*.cpp)

CC = g++
DEBUG = -g
PTHREAD = -pthread
LPTHREAD = -lpthread
NOSIGN = -Wno-sign-compare
UNUSED = -Wno-unused-parameter
CXXFLAGS = -W -Wall -Werror -pedantic -std=c++14 -c $(DEBUG) $(PTHREAD) $(UNUSED) $(NOSIGN)
LFLAGS = -W -Wall -Werror -pedantic -std=c++14 $(DEBUG) $(LPTHREAD) 

all: output

client: $(OBJDIR)/client.o $(NOMAINS)
	$(CC) $(LFLAGS) $^ -o $@

server: $(OBJDIR)/server.o $(NOMAINS)
	$(CC) $(LFLAGS) $^ -o $@ 

output: $(OBJDIR)/main.o $(NOMAINS)
	$(CC) $(LFLAGS) $^ -o $@

test: $(TESTOBJDIR)/test.o $(NOMAINS)
	$(CC) $(LFLAGS) $^ -o $@

$(TESTOBJDIR)/test.o: tests/test.cpp $(DEPS)
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

print:
	@echo $(NOMAINS)

test_run: test
	./test

run: output
	./output

run_client: client
	./client localhost

run_server: server
	./server

.PHONY: clean run