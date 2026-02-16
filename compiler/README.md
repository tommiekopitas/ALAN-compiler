# Compiler of Alan Language

This project is meant as a submission to the **Compilers** subject of the **School of Electrical and Computer Engineering** at **NTUA** for the academic year **2023-2024**. The project is a compiler for a programming language named **Alan**, the specifications of which were given at the start of the semester.
This repository contains the source code, examples by the students, and testcases from the professor's repository for the language.


## Authors
- **Spyridon Loukovitis** (spyrosloukovitis@gmail.com)
- **Chrysostomos Kopitas** (chrisostomoskopitas@gmail.com)


## Repo Structure
The tree structure of the repository is the following:

```
├── examples/         # Example Alan programs
├── src/              # Core compiler implementation
│   ├── ast/          # Abstract Syntax Tree (AST) and semantic analysis
│   ├── implementations/ # Intermediate representation (LLVM IR) and printing functions
│   ├── lexer/        # Lexical analysis using Flex
│   ├── lib/          # Runtime library for Alan
│   ├── parser/       # Syntax analysis using Bison
│   ├── compiler_executable  # The compiled Alan compiler
│   ├── Makefile      # Build process definition
├── testfolder/       # Folder for additional test cases
├── alanc             # The executable we run to use the compiler
```
The `examples` directory contains alan programs we made for troubleshooting.
The `testfolder` directory contains alan programs provided by the course's github repo.
The `src` directory contains all the code of the project as described below:
- The `ast` dir contains the files:
    - ast.cpp: Implementation of helper functions for the AST.
    - ast.hpp: Declarations of the classes for the different types of nodes.
    - llvmsymbol.hpp: Declarations and Implementations of classes used for the Symbol Table used during code generation.
    - symbol.hpp: Declarations and Implementations of classes used for the Symbol Table used during semantic checking.
- The `implementations` dir contains the files:
    - igen.cpp: Implementations of the code generation for all nodes.
    - print.cpp: Implementations of the printing functions for all nodes (not used by user, useful for programmer).
    - sem.cpp: Implementations of the sem function for all nodes and helper functions for type checking
- The `lexer` dir contains the files for the lexer: lexer.hpp and lexer.l (all others are made automatically).
- The `lib` dir contains the files needed for the static library.
- The `parser` dir contains the parser.y file (all others are made automatically).

## Installation


### Requirements

The project was created using
- **Bison** (version 3.5.1)
- **Flex** (version 2.6.4)
- **G++** for compiling the C++ source code and linking
- **LLMV** (version 15)
- **Make** for building the project

### How to download

1. Clone the repository:
    ```bash
    git clone https://github.com/ntua-el20120/compiler.git

    ```
2. Navigate to the project directory:
    ```bash
    cd compiler
    ```
3. The compiler and library are already compiled but if not we can make them as follows:
    ```bash
    cd src
    make
    cd lib
    make
    ```
   This will compile the compiler (`compiler_executable`) inside `src/` and create the static library (`lib.a`) inside `src/lib/`.

4. Clean up (optional):
    ```bash
    cd src
    make clean
    ```




### How to use from anywhere

We will add the project's directory to the `PATH`, so that `alanc` can be used from anywhere.


1. Open your shell configuration file in a text editor:
    ```bash
    vim ~/.bashrc
    ```

2. Add the path to alanc to the end of the file:
    ```bash
    export PATH="/path/to/alan_compiler:$PATH"
    ```

    The `path/to/alan_compiler` should be whaterver `pwd` outputs when called in the folder the file `alanc` is.

3. Save the file and reload the shell configuration:
    ```bash
    source ~/.bashrc
    ```

4. Verify that the `alanc` compiler is accessible:
    ```bash
    which alanc
    ```
   This should output the path to the `alanc` binary.


This should output the path to the alanc binary.

## Usage
We assume that the alanc path has been added to the `PATH` and the compiler can be used from anywhere. The basic usage of the compiler is the following:
```bash
alanc <path>/<name>.alan
```
Which will try to create in the current directory the files:
- `<name>.imm`: for the intermediate llvm code
- `<name>.asm`: for the assembly code
- `<name>.o`: for the object file
- `<name>`: for the executable

The different options that can be used are the following:
- `-O`: Enable code optimization.
- `-f`: Output the final assembly code to standard output.
- `-i`: Output the intermediate LLVM IR to standard output.

If -f or -i are used then the code is read from the standard input and no file argument is given. The final executable isn't produced.

An example for enabling optimizations is:
```bash
alanc -O testfolder/answer.alan
```


## Assumptions

- A variable or function is described by it's name. That means that while there can be multiple definitions with the same name, there can only be one per scope, and it'll hide previous declarations even if the types don't much. In practice that means that if a function foo() was declared in a previous scope, and I declare an int foo in this scope, the function foo() can not be called and the compiler will result in a semantic error.
- Nested functions exist and an inner function has access to all the variables of the outer function, as if they were passed by reference.
- Functions that don't have a return statement in every possible path, will return with a default value (0) if they reach the end of the function.
- The `int` type is 32 bits and the `byte` type is 8 bits.
- The main function can have any name. It is called by the main function generated by LLVM. If the main function's name was "main", in the llvm code it'll change to "alan_main" to avoid confusion.
