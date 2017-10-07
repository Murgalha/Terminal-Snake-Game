COMPILER=gcc
FLAGS=-lncurses
SOURCE=src/*.c
INCLUDE=-Iinclude
BUILD=build/snake

all: compile run

compile:
	@$(COMPILER) -o $(BUILD) $(SOURCE) $(INCLUDE) $(FLAGS)

run:
	@$(BUILD)
