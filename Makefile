CXX := g++
FLAGS := -Wall -Wextra -Wpedantic -o 
EXEC := raytracing
DDL := -lm
SDL := $(shell pkg-config --cflags --libs sdl2)
DIR := src

all:  $(EXEC) 

$(EXEC): main.cc $(DIR)/*.cc 
	$(CXX) $(FLAGS) $@ $^ $(DDL) $(SDL)

.PHONY clean:
	@rm $(EXEC) 
