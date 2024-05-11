#//ID: 208018028, Mail: ronimordechai70@gmail.com
#**note : when i do the commend 'make tidy' i get warnings only on magic number on the numbers in the matrixs in the demo and in the test, so its fine becouse it is need to be a number and not a const. 
# Another importent thing is that the valgrind not install correctly to me computer so its not working when i am wirte- 'make valdgind', but in this task there is no need to be a memoery leak becouse there is no dynamic allocation.

# Compiler and flags for C++
CXX = g++  
CXXFLAGS = -std=c++11 -Wall -Wextra -Werror -Wsign-conversion  # Default flags

# Valgrind settings for memory leak checks
VALGRIND_FLAGS = -v --leak-check=full --show-leak-kinds=all --error-exitcode=99

# Clang-tidy flags for code analysis
CLANG_TIDY_FLAGS = -checks='*' -warnings-as-errors='*'  # Enable all checks, treat warnings as errors

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

# Tidy up the codebase using clang-tidy
tidy:
	@echo "Running clang-tidy..."
	clang-tidy $(DEMO_SOURCES) $(TEST_SOURCES) $(CLANG_TIDY_FLAGS) --fix --quiet

# Run Valgrind to check for memory leaks
valgrind:
	valgrind $(VALGRIND_FLAGS) ./demo
