CXX = g++
CPPFLAGS = -g -Wall

all: copytest settest

copytest: llistint.o copytest.cpp
	$(CXX) $(CPPFLAGS) llistint.o copytest.cpp -o copytest

bin/llistint.o: llistint.cpp llistint.h
	$(CXX) $(CPPFLAGS) -c llistint.cpp -o llistint.o
    

settest: setint.o settest.cpp llistint.o
	$(CXX) $(CPPFLAGS) llistint.o setint.o settest.cpp -o settest

bin/setint.o: setint.cpp llistint.h setint.h
	$(CXX) $(CPPFLAGS) -c setint.cpp -o setint.o
