CC = gcc
CXX = g++
INC = -I/usr/local/include
CPPFLAGS = -std=c++11 ${INC}
LIB = -L/usr/local/lib
RM = rm -f

SRCS = main.cc cell.cc board.cc solver.cc 
OBJS = $(subst .cc,.o,$(SRCS))

all: sudokusolver

sudokusolver: main.cc $(OBJS)
	$(CXX) $(CPPFLAGS) -o sudokusolver $(OBJS)

test: test.cc $(OBJS)
	$(CXX) $(CPPFLAGS) $(LIB) -o test test.o $(OBJS) -lgtest

clean:
	$(RM) $(OBJS) main.o test.o sudokusolver test

dist-clean: clean
	$(RM) tool