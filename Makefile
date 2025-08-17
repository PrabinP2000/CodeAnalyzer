#mingw32-make

# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -g 
#-Wall common mistakes like unused variables, uninitialized values, or missing return statements.
#identify even more subtle issues, like unused function parameters or signed/unsigned mismatches.

# Source and object files
SRCS = analyzer.c utils.c
OBJS = $(SRCS:.c=.o)

# Output executable
BIN_DIR = bin
TARGET = $(BIN_DIR)/my_program

# Default rule
all: $(BIN_DIR) $(TARGET)

# Build the target
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Compile .c to .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Create bin directory if it doesn't exist
$(BIN_DIR):
	mkdir -p $(BIN_DIR)	

# Clean up
clean:
	rm -f $(OBJS) $(TARGET)
	rm -rf $(BIN_DIR)