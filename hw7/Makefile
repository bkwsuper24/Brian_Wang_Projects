CXX=g++
CXXFLAGS=-g -Wall 
BIN_DIR = bin

rbbst: rbbst.cpp rbbst.h bst.h
	$(CXX) $(CXXFLAGS) rbbst.cpp -o $@

bst: bst.cpp bst.h
	$(CXX) $(CXXFLAGS) bst.cpp -o $@ 

$(BIN_DIR)/rbbst.o: rbbst.h rbbst.cpp $(BIN_DIR)/.dirstamp
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ -c rbbst.cpp
$(BIN_DIR)/bst.o: bst.h bst.cpp $(BIN_DIR)/.dirstamp
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ -c bst.cpp

$(BIN_DIR)/.dirstamp:
	mkdir -p $(BIN_DIR)
	touch $(BIN_DIR)/.dirstamp

clean: 
	rm -rf $(BIN_DIR)