CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra
TARGET = singleton_guard_demo

all: $(TARGET)

$(TARGET): singleton_guard_demo.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: all run clean