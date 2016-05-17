CC = gcc
CXX = g++
INC = -I/usr/local/include
CPPFLAGS = -std=c++11 ${INC}
LIB = -L/usr/local/lib
RM = rm -f

SRCS = test.cc
OBJS = $(subst .cc,.o,$(SRCS))

all: sudokusolver

test: $(OBJS)
	$(CXX) $(CPPFLAGS) $(LIB) -o test $(OBJS) -lgtest

sudokusolver: $(OBJS)
	$(CXX) $(CPPFLAGS) $(LIB) -o sudokusolver $(OBJS) -lgtest

clean:
	$(RM) $(OBJS)

dist-clean: clean
	$(RM) tool