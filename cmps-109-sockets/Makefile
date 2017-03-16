SHELL = /bin/bash

SRCDIR = sources
DEPSDIR = headers

SRC := $(wildcard *.cpp)
DEPS := $(wildcard *.h)
OBJS := $(patsubst %.cpp, %.o, $(SRC))
CLIENTOBJS := 
SERVEROBJS :=

CC = g++
DEBUG = -g
PTHREAD = -pthread
LPTHREAD = -lpthread
NOSIGN = -Wno-sign-compare
NOUNUSED = -Wno-unused-variable
CXXFLAGS = -Wall -pedantic $(PTHREAD)$(NOSIGN) $(NOUNUSED) -std=c++11 -c $(DEBUG)
LFLAGS = -Wall -std=c++11 $(LPTHREAD) $(DEBUG)

all: 

client: $(CLIENTOBJS)
	$(CC) $(LFLAGS) $^ -o $@

server: $(SERVEROBJS)
	$(CC) $(LFLAGS) $^ -o $@

%.o: %.cpp $(DEPS)
	$(CC) $(CXXFLAGS) $<

clean:
	rm *.o
	rm output

run: output
	./output

.PHONY: clean run