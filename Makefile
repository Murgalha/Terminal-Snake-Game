COMPILER=gcc
FLAGS=-lncurses -ltinfo
SOURCE=src/*.c
INCLUDE=-Iinclude
BUILD=snake

all: compile

compile:
	@$(COMPILER) -o $(BUILD) $(SOURCE) $(INCLUDE) $(FLAGS)

run:
	@./$(BUILD)
