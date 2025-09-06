# Project Setup and Initial Structure

This document explains step by step how we are setting up the Mini C Compiler project and the reasoning behind the structure.

---

## 1. Repository Creation

We started by creating a GitHub repository for the project.  
At this stage, the repository contains only the `README.md`.

---

## 2. Project Structure

To organize the compiler code properly, we create the following folders:

mini-c-compiler/
├── src/ # C source files (.c)
├── include/ # Header files (.h)
├── tests/ # Example programs and test cases
└── docs/ # Documentation files


- `src/` → contains the main program and source files for the lexer, parser, and interpreter.  
- `include/` → contains header files with function declarations and data structures.  
- `tests/` → will contain text files with small programs for testing the compiler.  
- `docs/` → contains additional documentation, like module explanations or development notes.

---

## 3. Initial Files

We also create three essential files:

1. `src/main.c` → main program that will run the compiler pipeline  
2. `include/lexer.h` → header for the lexer module  
3. `include/parser.h` → header for the parser module

These files contain **basic structure and placeholders** for functions that will be implemented step by step.

---

## 4. Next Steps

The next step is to implement the **lexer**, which will read source code and convert it into tokens.  
We will document the lexer separately in `docs/lexer.md` once implemented.
