# Compiler and flags for C++
CXX = g++  # Or g++
CXXFLAGS = -std=c++11 -Wall -Wextra -Werror -Wsign-conversion  # Default flags

# Valgrind settings for memory leak checks
VALGRIND_FLAGS = -v --leak-check=full --show-leak-kinds=all --error-exitcode=99

# Source files and object files
DEMO_SOURCES = Demo.cpp Graph.cpp Algorithms.cpp
TEST_SOURCES = TestCounter.cpp Test.cpp Graph.cpp Algorithms.cpp

# Object files derived from source files
DEMO_OBJECTS = $(DEMO_SOURCES:.cpp=.o)
TEST_OBJECTS = $(TEST_SOURCES:.cpp=.o)

# Build rules
.PHONY: all clean tidy valgrind  # Targets that don't create files

# Default target builds both demo and test
all: demo test

# Build the demo executable
demo: $(DEMO_OBJECTS)
	$(CXX) $(CXXFLAGS) -o demo $(DEMO_OBJECTS)

# Build the test executable, using different flags for TestCounter
test: TestCounter.o Test.o Graph.o Algorithms.o
	$(CXX) $(CXXFLAGS) -o test TestCounter.o Test.o Graph.o Algorithms.o

# Compile individual object files from source files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compile TestCounter with a modified flag to ignore unused parameter warnings
TestCounter.o: TestCounter.cpp
	$(CXX) $(CXXFLAGS) -Wno-unused-parameter -c TestCounter.cpp -o TestCounter.o

# Clean up object files and executables
clean:
	rm -f *.o demo test
