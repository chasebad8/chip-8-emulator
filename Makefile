# Compiler
CC = g++

# Directories
SRC_DIR = src
INC_DIR = include
OBJ_DIR = obj
LIB_DIR = libs
SPDLOG_PATH=./libs/spdlog/build

# Compiler flags
CXXFLAGS = -c -Wall -g
INCLUDES = -I$(INC_DIR) -I./libs/spdlog/include/
LDFLAGS = -L$(SPDLOG_PATH)/spdlog

# Source files
SRCS = $(wildcard $(SRC_DIR)/*.cpp)

# Object files
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))

# Executable file
TARGET = chip-8

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) $^ -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	mkdir -p $(OBJ_DIR)
	$(CC) $(CXXFLAGS) $(INCLUDES) $< -o $@

clean:
	rm -f $(OBJ_DIR)/*.o $(TARGET)