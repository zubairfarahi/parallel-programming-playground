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

# Executable file
MAIN = main

all:		$(MAIN)

$(MAIN): 	$(OBJECTS)
		$(CC) $(CFLAGS) $(OBJECTS) $(LIBS) -o $(MAIN)

.c.o:
		$(CC) $(CFLAGS) -c $< -o $@

clean:
		$(RM) *.o *~ $(MAIN)
