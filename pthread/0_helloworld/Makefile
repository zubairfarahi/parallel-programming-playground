# Compiler to use
CC = gcc

# Options
CFLAGS = -Wall -Werror -g

# Libraries
LIBS = -pthread

# Source files
SOURCES = main.c

# C Object files
OBJECTS = $(SOURCES:.c=.o)

# Build directory
BUILD_DIR = build

# Builds results
BUILDS = $(addprefix $(BUILD_DIR)/,$(notdir $(OBJECTS)))

# Executable file
MAIN = main

all:		dir $(MAIN)

$(MAIN): 	$(OBJECTS)
			$(CC) $(CFLAGS) $(BUILDS) $(LIBS) -o $(BUILD_DIR)/$(MAIN)

%.o: %.c
			$(CC) $(CFLAGS) -c $< -o $(BUILD_DIR)/$(notdir $@)

dir:
			mkdir -p $(BUILD_DIR)

clean:
			$(RM) -r $(BUILD_DIR)
