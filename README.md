# Mini C Compiler

## Overview

This project is a **minimal compiler** implemented in **C** for a small, toy programming language. The goal is **educational**: to understand the inner workings of a compiler from scratch. Even if you have experience with web development, scripting, or standard application programming, this project will guide you through the core concepts that transform **plain text code** into something a computer can execute.  

This repository is designed so that each part is **understandable and modular**, making it easy to extend with new features like conditionals, loops, and more complex operations.  

---

## Project Status

⚠️ **Work in Progress (WIP)**

This project is **currently under development**. Features are incomplete, and the compiler is evolving.  
Some parts (like the interpreter, semantic analysis, and optional extensions) are still being implemented.

- The lexer and parser are functional for simple expressions and variable assignments.
- More complex statements, loops, and error handling are **not yet supported**.
- Expect **frequent updates** and possible **breaking changes**.

![status](https://img.shields.io/badge/status-in%20progress-yellow)

---

## Tools and Language

The project is written entirely in **C**, chosen for its clarity and direct mapping to low-level programming concepts.  

No external libraries are required – the entire compiler is implemented using **plain C**, including:  
- Data structures for tokens, AST nodes, and symbol tables  
- String parsing and manipulation  
- Recursive functions for parsing and interpreting code

You will only need a **C compiler** (e.g., GCC or Clang) to build and run the project.

---

## Compiler Phases

The compiler is divided into several key **phases**, each responsible for a specific task. Understanding these phases is essential to grasp how modern compilers work:

1. **Lexical Analysis (Lexer / Tokenizer)**  
   - Converts raw text code into **tokens**, the smallest meaningful elements in a program (numbers, operators, keywords, identifiers).  
   - Example: the code `let x = 5 + 3;` is transformed into tokens: `[LET] [IDENTIFIER:x] [EQUAL] [NUMBER:5] [PLUS] [NUMBER:3] [SEMICOLON]`.

2. **Parsing**  
   - Organizes tokens into a **structured representation** called an **Abstract Syntax Tree (AST)**.  
   - The AST captures the **hierarchy and order of operations** in the program.  
   - Example: `5 + 3` becomes a tree node `PLUS` with children `5` and `3`.

3. **Semantic Analysis**  
   - Checks that the program makes sense: variables are declared before use, operations are valid, etc.  
   - Builds a **symbol table** to track variable names and their values.

4. **Code Generation / Interpretation**  
   - Converts the AST into something executable.  
   - In this project, we use an **interpreter** approach: the AST is traversed and executed directly, computing results and printing output.

5. **(Optional Extensions)**  
   - Future phases may include optimization, bytecode generation, or outputting assembly code.  

---

## Why This Project?

This project is perfect for developers who want to:  
- Understand **what happens under the hood** when code is compiled or interpreted.  
- Learn **core concepts of programming languages** and their execution.  
- Gain experience in **low-level programming** while still producing working, visible results.  

Even if your background is in web development, Python, or app programming, completing this project will give you insights into **how your code is transformed into machine-readable instructions**.

---

## Requirements

To compile and run the project, you need:

- A **C compiler** (GCC, Clang, or compatible).  
- A terminal or command prompt to execute compiled binaries.  
- No additional libraries are required.

---

## How to Build and Run

The compiler reads **source code from a file**, which must be specified as a **command-line argument** when executing the program.  

1. Open a terminal in the project directory.  
2. Compile the source files:
```bash
gcc src/main.c src/lexer.c src/parser.c src/interpreter.c src/utils.c -Iinclude -o mini-c.exe
```
3. Run the compiler/interpreter with a source file:
```bash
./mini-c.exe examples/test.txt
```
- Replace examples/test.txt with the path to your own source code file.
- The program will read the file, tokenize, parse, and interpret it.
4. Input code directly (or modify main.c to read a source file) to see results.
Example code supported currently **(examples/test.txt)**:
```c
let x = 5 + 3;
let y = 1 + 1;
print(x + y);
```
Output:
```plaintext
10
```
> ⚠️ Note: The function that reads the source file is implemented in `src/utils.c`.
![triangle](https://upload.wikimedia.org/wikipedia/commons/4/4f/Triangle_equilateral.svg)

---

## Notes

- Only simple expressions and variable assignments are supported.  
- Statements must end with a semicolon `;`.  
- Parentheses `(` and `)` can be used for grouping expressions.  
- Accessing undefined variables or dividing by zero will terminate execution with an error message.
