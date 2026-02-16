.PHONY: clean distclean default

CXX=g++
CXXFLAGS=-Wall -std=c++11 `llvm-config --cxxflags`
LDFLAGS=`llvm-config --ldflags --system-libs --libs all`

SRC_DIR=.
AST_DIR=$(SRC_DIR)/ast
IMPL_DIR=$(SRC_DIR)/implementations
LEXER_DIR=$(SRC_DIR)/lexer
PARSER_DIR=$(SRC_DIR)/parser

OBJS = $(PARSER_DIR)/parser.o $(LEXER_DIR)/lexer.o \
       $(AST_DIR)/ast.o $(IMPL_DIR)/igen.o \
       $(IMPL_DIR)/print.o $(IMPL_DIR)/sem.o

default: compiler_executable

# Generate lexer.cpp
$(LEXER_DIR)/lexer.cpp: $(LEXER_DIR)/lexer.l
	flex -s -o $@ $<

# Compile lexer.o
$(LEXER_DIR)/lexer.o: $(LEXER_DIR)/lexer.cpp $(LEXER_DIR)/lexer.hpp $(PARSER_DIR)/parser.hpp $(AST_DIR)/ast.hpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# Generate parser.cpp and parser.hpp
$(PARSER_DIR)/parser.cpp $(PARSER_DIR)/parser.hpp: $(PARSER_DIR)/parser.y
	bison -dv -o $(PARSER_DIR)/parser.cpp $(PARSER_DIR)/parser.y

# Compile parser.o
$(PARSER_DIR)/parser.o: $(PARSER_DIR)/parser.cpp $(LEXER_DIR)/lexer.hpp $(AST_DIR)/ast.hpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# Compile AST object
$(AST_DIR)/ast.o: $(AST_DIR)/ast.cpp $(AST_DIR)/ast.hpp $(AST_DIR)/symbol.hpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# Compile semantic analysis object
$(IMPL_DIR)/sem.o: $(IMPL_DIR)/sem.cpp $(AST_DIR)/ast.hpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# Compile code generation object
$(IMPL_DIR)/igen.o: $(IMPL_DIR)/igen.cpp $(AST_DIR)/ast.hpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# Compile printing object
$(IMPL_DIR)/print.o: $(IMPL_DIR)/print.cpp $(AST_DIR)/ast.hpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# Link the final executable
compiler_executable: $(OBJS)
	$(CXX) $(CXXFLAGS) -o compiler_executable $(OBJS) $(LDFLAGS)

# Clean up generated and temporary files
clean:
	$(RM) $(LEXER_DIR)/lexer.cpp $(PARSER_DIR)/parser.cpp $(PARSER_DIR)/parser.hpp $(PARSER_DIR)/parser.output $(OBJS)

distclean: clean
	$(RM) compiler_executable
