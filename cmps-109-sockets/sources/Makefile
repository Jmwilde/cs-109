SHELL = /bin/bash

SRCDIR = sources
DEPSDIR = headers

SRC := $(wildcard *.cpp)
DEPS := $(wildcard *.h)
OBJS := $(patsubst %.cpp, %.o, $(SRC))
NOMAIN := $(filter-out main.o, $(OBJS))
CLIENTOBJS := $(filter-out server_stream.o, $(NOMAIN))
SERVEROBJS := $(filter-out client_stream.o, $(NOMAIN))

CC = g++
DEBUG = -g
PTHREAD = -pthread
LPTHREAD = -lpthread
NOSIGN = -Wno-sign-compare
NOUNUSED = -Wno-unused-variable
CXXFLAGS = -Wall -pedantic -std=c++11 -c $(DEBUG) $(PTHREAD) $(NOSIGN) $(NOUNUSED)  
LFLAGS = -Wall -pedantic -std=c++11 $(DEBUG) $(LPTHREAD) $(DEBUG)

all: 

client: $(CLIENTOBJS)
	$(CC) $(LFLAGS) $^ -o $@

server: $(SERVEROBJS)
	$(CC) $(LFLAGS) $^ -o $@

%.o: %.cpp $(DEPS)
	$(CC) $(CXXFLAGS) $<

clean:
	rm *.o
	rm client
	rm server

run_client: client
	./client localhost

run_server: server
	./server

.PHONY: clean run