# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic -g

# Target executable
TARGET = graph_eulerian

# Source files (add all your source files here)
SRCS = main.cpp Graph.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)

ARGS = -v 1000 -e 10000 -s 31
ARGY = -v 5 -e 10 -s 31
# Default target
all: $(TARGET)

# Linking
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

# Compilation
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up
clean:
	rm -f $(OBJS) $(TARGET) gmon.out *.gcda *.gcno *.gcov callgrind.out.*

# Run the program with arguments
run: $(TARGET)
	./$(TARGET) $(ARGS)

# Profiling with gprof
gprof: CXXFLAGS += -pg
gprof: clean $(TARGET)
	./$(TARGET) $(ARGS)
	gprof $(TARGET) gmon.out > gprof_output.txt
	@echo "Gprof report generated in gprof_output.txt"

# Code coverage with gcov (targeted)
coverage: CXXFLAGS += -fprofile-arcs -ftest-coverage
coverage: clean $(TARGET)
	./$(TARGET) $(ARGS)
	./$(TARGET) $(ARGY)
	gcov -r $(SRCS)
	@echo "Code coverage reports generated for specified source files (*.gcov files)"

# Valgrind memcheck
memcheck: $(TARGET)
	valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all ./$(TARGET) $(ARGS) 2> memcheck_output.txt
	@echo "Valgrind memcheck report generated in memcheck_output.txt"

# Valgrind callgraph
callgraph: $(TARGET)
	valgrind --tool=callgrind ./$(TARGET) $(ARGS)
	callgrind_annotate callgrind.out.* > callgraph_output.txt
	@echo "Valgrind callgraph report generated in callgraph_output.txt"

.PHONY: all clean run gprof coverage memcheck callgraph