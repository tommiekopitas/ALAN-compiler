# Makefile for creating alan_lib.a from library.cpp

# Compiler and flags
CXX = g++
CXXFLAGS = -w -O2 -std=c++11  # -w flag suppresses all warnings

# Targets and files
TARGET = alan_lib.a
SRC = library.cpp
OBJ = library.o

# Default target
all: $(TARGET)

# Create the static library
$(TARGET): $(OBJ)
	@echo "Creating static library $(TARGET)..."
	ar rcs $(TARGET) $(OBJ)
	@echo "Static library $(TARGET) created successfully."

# Compile the object file
$(OBJ): $(SRC)
	@echo "Compiling $(SRC)..."
	$(CXX) $(CXXFLAGS) -c $(SRC) -o $(OBJ)

# Clean up build files
clean:
	@echo "Cleaning

