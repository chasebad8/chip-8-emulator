# Compiler
CC = g++

# Compiler flags
CFLAGS = -c -Wall
LFLAGS = 

# Directories
SRC_DIR = src
INC_DIR = include
OBJ_DIR = obj

# Source files
SRCS = $(wildcard $(SRC_DIR)/*.cpp)

# Object files
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))

# Executable file
TARGET = chip-8

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(LFLAGS) $^ -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -I$(INC_DIR) $< -o $@

clean:
	rm -f $(OBJ_DIR)/*.o $(TARGET)