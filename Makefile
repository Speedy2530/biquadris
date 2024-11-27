# Makefile for the biquadris project

# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++20 -Wall -Wextra -MMD

# Linker flags
LDFLAGS = -lX11

# Executable name
EXEC = biquadris

# Source directories
SRC_DIR = .
BLOCKS_DIR = blocks
LEVELS_DIR = levels

# Source files
SOURCES = $(wildcard $(SRC_DIR)/*.cc) \
          $(wildcard $(BLOCKS_DIR)/*.cc) \
          $(wildcard $(LEVELS_DIR)/*.cc)

# Object files
OBJECTS = $(SOURCES:.cc=.o)

# Dependency files
DEPENDS = $(OBJECTS:.o=.d)

# Default target
all: $(EXEC)

# Link the executable
$(EXEC): $(OBJECTS)
	$(CXX) $(OBJECTS) $(LDFLAGS) -o $@

# Compile source files into object files
%.o: %.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Include dependency files
-include $(DEPENDS)

# Clean target to remove generated files
clean:
	rm -f $(OBJECTS) $(DEPENDS) $(EXEC)

# Phony targets
.PHONY: all clean

