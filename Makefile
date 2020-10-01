CXX	:= clang++
CXX_FLAGS := -ggdb

BIN		:= bin
SRC		:= src
INCLUDE	:= include
STANDARD := c++11

LIBRARIES	:= lib
EXECUTABLE	:= main


all: $(BIN)/$(EXECUTABLE)

run: clean all
	clear
	./$(BIN)/$(EXECUTABLE)

$(BIN)/$(EXECUTABLE): $(SRC)/*.cpp
	$(CXX) $(CXX_FLAGS) -I$(INCLUDE) -x c src/glad.c -x c++ $^ -o $@ -lglfw

clean:
	-rm $(BIN)/*
