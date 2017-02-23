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

SRC := $(wildcard $(SRCDIR)/*.cpp)
DEPS := $(wildcard $(SRCDIR)/*.h)
OBJS := $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SRC))

CC = g++
DEBUG = -g
CXXFLAGS = -Wall -std=c++14 -c $(DEBUG)
LFLAGS = -Wall -std=c++14 $(DEBUG)

all: output

output: $(OBJS)
	$(CC) $(LFLAGS) $^ -o $@

$(OBJS): $(OBJDIR)/%.o: $(SRCDIR)/%.cpp $(DEPS)
	mkdir -p $(@D)
	$(CC) $(CXXFLAGS) $< -o $@

clean:
	rm output
	rm objects/*.o

run:
	./output

.PHONY: clean run