# Compiler and flags
CC = gcc
CFLAGS = -g

# Source and object files
SOURCES = hello.c
OBJECTS = $(SOURCES:.c=.o)

# Executable name
EXECUTABLE = my_program

# Valgrind memcheck target
MEMCHECK = valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(EXECUTABLE)

memcheck: $(EXECUTABLE)
	$(MEMCHECK) ./$(EXECUTABLE) 2> memcheck_output.txt
	@echo "Valgrind output written to memcheck_output.txt"