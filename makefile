CC=cc

SRC_DIR=src
INCLUDE_DIR=include

EXE=pickinSticks.out

CFLAGS=-lstdc++ \
			 -std=c++17 \
			 -lsfml-graphics \
			 -lsfml-system \
			 -lsfml-window \
			 -lsfml-audio \
			 -I$(INCLUDE_DIR)/

TARGETS=main.o \
				window.o \
				character.o \
				map.o \
				game.o

all: main

main: $(TARGETS)
	$(CC) $(TARGETS) $(CFLAGS) -o $(EXE)

$(TARGETS): $(wildcard $(SRC_DIR)/*.cpp)
	$(CC) -c $(wildcard $(SRC_DIR)/*.cpp) -I$(INCLUDE_DIR)/


clean:
	rm -v $(TARGETS) *.out
