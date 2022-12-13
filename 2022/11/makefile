# Commands and compiler settings
CC = g++
CXXFLAGS = -std=c++17 -fdiagnostics-color=always -g3 -Wall -Wpedantic 
RM = rm -rf

# Directories
SRC = src
INC = include
OBJ = obj
BIN = bin

# Source files, objects, target
TARGET = 11
SOURCES = $(TARGET).cpp troop.cpp monkey.cpp utils.cpp
OBJS = $(patsubst %, $(OBJ)/%, $(SOURCES:.cpp=.o))

# Build rules
.PHONY: all
all : $(TARGET)
$(TARGET) : $(OBJS) | $(BIN)
	$(CC) -o $(BIN)/$@ $^ 
$(OBJ)/%.o : $(SRC)/%.cpp | $(OBJ)
	$(CC) -c -I$(INC) $(CXXFLAGS) -o $@ $<

# Ensure that the build directories exist
$(BIN) $(OBJ):
	mkdir -p $@

# Clean
clean :
	$(RM) $(OBJ)
	$(RM) $(BIN)
