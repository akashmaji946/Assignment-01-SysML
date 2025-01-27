# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17

# List all .cpp files
SOURCES = $(wildcard *.cpp)

# Generate executables (replace .cpp with nothing for the name)
EXECUTABLES = $(SOURCES:.cpp=)

# Default target: Build all executables
all: $(EXECUTABLES)

# Rule to build each executable from its corresponding .cpp file
%: %.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

# Clean up .txt, .out, and executables
clean:
	rm -f *.txt *.out *.o $(EXECUTABLES)

# Phony targets
.PHONY: all clean
