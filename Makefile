# Compiler settings
CXX = g++
CXXFLAGS = -Wall -g -I./src

# Source files for the main executable
SRC = main.cpp  $(wildcard src/*.cpp) 

# Name of the main executable
EXEC = prog

# Source files for unit tests 
TESTSRC = test/test.cpp  $(wildcard src/*.cpp) 

TEST_EXEC = test_prog

# Default target: build the main executable
all: $(EXEC)

# Build the main executable
$(EXEC): $(SRC)
	$(CXX) $(CXXFLAGS) -o $@ $(SRC)

# Run the demonstration (make run)
Main: $(EXEC)
	./$(EXEC)

# Build the unit test executable
$(TEST_EXEC): $(TESTSRC)
	$(CXX) $(CXXFLAGS) -o $@ $(TESTSRC)

# Run unit tests
test: $(TEST_EXEC)
	./$(TEST_EXEC)

# Run valgrind on the main executable
valgrind: $(EXEC)
	valgrind --leak-check=full ./$(EXEC)

# Clean up all generated executables
clean:
	rm -f $(EXEC) $(TEST_EXEC)