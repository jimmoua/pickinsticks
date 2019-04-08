CC=cc

SRC_DIR=src

SRC_EXT=cpp

INCLUDE_DIR=include

OBJ_DIR=obj

CFLAGS=-lstdc++ -lsfml-graphics -lsfml-system -lsfml-window -lsfml-audio -std=c++11

WFLAGS=-Wall -Wextra

EXE=pickinSticks

SOURCES := $(wildcard $(SRC_DIR)/*.$(SRC_EXT))
OBJECTS := $(SOURCES:$(SRC_DIR)/%.$(SRC_EXT)=$(OBJ_DIR)/%.o)

all: $(OBJECTS)
	$(CC) $(OBJECTS) $(CFLAGS) -o $(EXE)

$(OBJECTS): $(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp
	@mkdir -p obj
	$(CC) $(WFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

clean:
	rm $(OBJECTS) $(EXE) -v
