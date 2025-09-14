#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "parser.h"

/*
 * Interpreter for the Mini C Compiler
 * 
 * Responsibilities:
 * - Traverse the AST
 * - Evaluate expressions (numbers, variables, binary operations)
 * - Execute statements (assignments, print, etc.)
 * - Manage a symbol table (variable storage)
 */

// Represents a single entry (a variable) in the symbol table
// Each Symbol is a name–value pair (like x = 5)
typedef struct {
    char name[32];  // variable name
    int value;      // variable value
} Symbol;

// Represents the entire symbol table
typedef struct {
    Symbol symbols[128]; // fixed-size array of symbols (max 128 variables)
    int count;           // number of symbols currently stored in the table; also indicates the next free position in 'symbols'
} SymbolTable;

/* Function prototypes */
void init_symbol_table(SymbolTable* table);
int lookup_symbol(SymbolTable* table, const char* name);
void set_symbol(SymbolTable* table, const char* name, int value);

int eval_expression(ASTNode* node, SymbolTable* table);
void exec_statement(ASTNode* node, SymbolTable* table);
void interpret(ASTNode* root);

#endif