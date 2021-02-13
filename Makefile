C := clang

CXX	:= clang++
CXX_FLAGS := -ggdb

BIN		:= bin
SRC		:= src
INCLUDE	:= include
STANDARD := c++11
OBJECT := object

LIBRARIES	:= lib
EXECUTABLE	:= main


all: $(BIN)/$(EXECUTABLE)

run: clean all
	clear
	./$(BIN)/$(EXECUTABLE)

$(BIN)/$(EXECUTABLE): $(SRC)/*.cpp
	$(CXX) $(CXX_FLAGS) -I$(INCLUDE) -std=$(STANDARD) $(OBJECT)/*.o -x c++ $^ -o $@ -lglfw

clean:
	-rm $(BIN)/*
