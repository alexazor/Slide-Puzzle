### Variables declaration

## Name of the compiler
CXX = g++

## Executable path
EXEC = ./bin/Slide-Puzzle

## Include paths
INCLUDE_PATHS = -I D:/cpp_libraries/SDL2/include

## Library paths
LIBRARY_PATHS = -L D:/cpp_libraries/SDL2/lib

## Source files path
SRC_PATH = ./src/

## Object files path
OBJ_PATH = ./obj/

## List of source files
SRC_FILES = $(wildcard $(SRC_PATH)*.cpp)
# We select all files in the source files folders with the .cpp extension

## List of object files
OBJ_FILES = $(SRC_FILES:$(SRC_PATH)%.cpp=$(OBJ_PATH)%.o)
# We take the list of source files and, for each name, 
# we replace the source files path by the object files path
# and the extension

## Linker flags
LINKER_FLAGS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf


### Rules
## Main rule
all: $(EXEC)

## Creation of the object files
$(OBJ_PATH)%.o : $(SRC_PATH)%.cpp
	$(CXX) -c $^ -o $@ $(INCLUDE_PATHS)

## Creation of the executable
$(EXEC): $(OBJ_FILES)
	$(CXX) $^ -o $@ $(LINKER_FLAGS) $(LIBRARY_PATHS)

##
clear:
	rm $(OBJ_FILES);
	rm $(EXEC)
