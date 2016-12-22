# Compiler to use
CC = mpicc

# Options
CFLAGS = -Wall -Werror -g

# Source files
SOURCES = main.c

# Executable file
OUTPUT = main

.PHONY:		clean

all:		clean hello

hello:
			$(CC) $(SOURCES) $(CFLAGS) -o $(OUTPUT)

clean:
			$(RM) -r $(OUTPUT)