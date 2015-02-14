CXX = g++
CPPFLAGS = -g -Wall

all: copytest settest

copytest: llistint.o copytest.cpp
	$(CXX) $(CPPFLAGS) llistint.o copytest.cpp -o copytest

bin/llistint.o: llistint.cpp llistint.h
	$(CXX) $(CPPFLAGS) -c llistint.cpp -o llistint.o
    

