SRC = ./src
UTILS = ./src/utils
BUILD = ./build

check: $(SRC)/check.cpp $(UTILS)/input.cpp
	g++ $(SRC)/check.cpp $(UTILS)/input.cpp $(UTILS)/cmp.cpp -o $(BUILD)/check

SOR: $(SRC)/SOR.cpp
	g++ $(SRC)/SOR.cpp $(UTILS)/input.cpp $(UTILS)/cmp.cpp -o $(BUILD)/SOR
