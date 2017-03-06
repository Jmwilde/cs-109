SHELL = /bin/bash

SRCDIR = sources
DEPSDIR = headers

SRC := $(wildcard *.cpp)
DEPS := $(wildcard *.h)
OBJS := $(patsubst %.cpp, %.o, $(SRC))

CC = g++
DEBUG = -g
PTHREAD = -pthread
NOSIGN = -Wno-sign-compare
NOUNUSED = -Wno-unused-variable
CXXFLAGS = -Wall $(NOSIGN) $(NOUNUSED) -std=c++11 -c $(DEBUG)
LFLAGS = -Wall -std=c++11 $(PTHREAD) $(DEBUG)

all: output

output: $(OBJS)
	$(CC) $(LFLAGS) $^ -o $@

%.o: %.cpp $(DEPS)
	$(CC) $(CXXFLAGS) $<

clean:
	rm *.o
	rm output

run: output
	./output

.PHONY: clean run