CPP       := g++
CPP_DEBUG_FLAGS := -W -Wall -Wextra -Wpedantic -ansi
CPP_OPTIMISE_FLAGS := -O2

BIN     := bin
SRC     := src
INCLUDE := include

LIBRARIES   := lib
EXEC  := main

optimise: neurons.obj cost.obj main.obj
		g++ $(BIN)/neurons.obj $(BIN)/cost.obj $(BIN)/main.obj -o main $(CPP_OPTIMISE_FLAGS)

neurons.obj: $(INCLUDE)/neurons.cpp $(INCLUDE)/neurons.hpp
		g++ -c $(INCLUDE)/neurons.cpp -o $(BIN)/neurons.obj $(CPP_OPTIMISE_FLAGS)

cost.obj: $(INCLUDE)/cost.cpp $(INCLUDE)/cost.hpp $(INCLUDE)/neurons.hpp
		g++ -c $(INCLUDE)/cost.cpp -o $(BIN)/cost.obj $(CPP_OPTIMISE_FLAGS)

main.obj: $(SRC)/main.cpp $(INCLUDE)/neurons.hpp $(INCLUDE)/cost.hpp
		g++ -c $(SRC)/main.cpp -o $(BIN)/main.obj $(CPP_OPTIMISE_FLAGS)


all: $(EXEC)

main: neurons.o cost.o main.o
		g++ $(BIN)/neurons.o $(BIN)/cost.o $(BIN)/main.o -o main $(CPP_DEBUG_FLAGS)

main.o: $(SRC)/main.cpp $(INCLUDE)/neurons.hpp $(INCLUDE)/cost.hpp
		g++ -c $(SRC)/main.cpp -o $(BIN)/main.o $(CPP_DEBUG_FLAGS)

neurons.o: $(INCLUDE)/neurons.cpp $(INCLUDE)/neurons.hpp
		g++ -c $(INCLUDE)/neurons.cpp -o $(BIN)/neurons.o $(CPP_DEBUG_FLAGS)

cost.o: $(INCLUDE)/cost.cpp $(INCLUDE)/cost.hpp $(INCLUDE)/neurons.hpp
		g++ -c $(INCLUDE)/cost.cpp -o $(BIN)/cost.o $(CPP_DEBUG_FLAGS)

clean: 
		rm -fv $(BIN)/*

debug: clean all
		./main --debug

val: clean all
		valgrind ./main --debug --leak-check=full

run: clean optimise
		./main