CXX = g++
CPPFLAGS = -g -Wall
BIN_DIR = bin

all: copytest settest

copytest: $(BIN_DIR)/llistint.o copytest.cpp
	$(CXX) $(CPPFLAGS) $(BIN_DIR)/llistint.o copytest.cpp -o copytest

llistint.o: $(BIN_DIR)/llistint.o: llistint.cpp llistint.h $(BIN_DIR)/.dirstamp
	$(CXX) $(CPPFLAGS) -c llistint.cpp -o $(BIN_DIR)/llistint.o

settest: $(BIN_DIR)/setint.o settest.cpp $(BIN_DIR)/llistint.o
	$(CXX) $(CPPFLAGS) $(BIN_DIR)/setint.o  $(BIN_DIR)/llistint.o settest.cpp -o settest

	$(BIN_DIR)/setint.o: setint.h setint.cpp llistint.h llistint.cpp $(BIN_DIR)/.dirstamp
	$(CXX) $(CPPFLAGS) -c setint.cpp -o $(BIN_DIR)/setint.o

%.o: %.cpp

$(BIN_DIR)/.dirstamp:
	mkdir -p $(BIN_DIR)
	touch $(BIN_DIR)/.dirstamp

clean:
	rm -rf $(BIN_DIR)
