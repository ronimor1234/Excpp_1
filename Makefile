# Compiler and flags for C++
CXX = g++  # Or g++
CXXFLAGS = -std=c++11 -Wall -Wextra -Werror -Wsign-conversion  # Basic C++ flags

# Valgrind settings for memory leak checks
VALGRIND_FLAGS = -v --leak-check=full --show-leak-kinds=all --error-exitcode=99

# Source files and object files
SOURCES = Graph.cpp Algorithms.cpp TestCounter.cpp Test.cpp Demo.cpp
OBJECTS = $(SOURCES:.cpp=.o)

# Build rules
.PHONY: all clean tidy valgrind

# Default target
all: demo test  # Build both demo and test by default

# Build the demo executable
demo: Demo.o $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Build the test executable
test: TestCounter.o Test.o $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Run clang-tidy with specific checks
tidy:
	clang-tidy $(SOURCES) -checks=bugprone-*,clang-analyzer-*,cppcoreguidelines-*,performance-*,portability-*,readability-* -warnings-as-errors=-* --

# Run Valgrind to check for memory leaks
valgrind: demo test
	valgrind --tool=memcheck $(VALGRIND_FLAGS) ./demo
	valgrind --tool=memcheck $(VALGRIND_FLAGS) ./test

# Compile individual object files from source files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up object files and executables
clean:
	rm -f *.o demo test

