COMPILER=gcc
FLAGS=-lncurses -ltinfo
SOURCE=src/*.c
INCLUDE=-Iinclude
BUILD=build/game

all: install compile

compile:
	@$(COMPILER) -o $(BUILD) $(SOURCE) $(INCLUDE) $(FLAGS)

run:
	@$(BUILD)

install:
	@mkdir -p build
