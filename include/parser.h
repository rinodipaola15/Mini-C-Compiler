#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"

/*
 * AST node types
 * Represents different elements of the program syntax
 */
typedef enum {
    AST_NUMBER,   // numeric literal
    AST_BINOP,    // binary operation (+, -, *, /)
    AST_VAR,      // variable usage
    AST_ASSIGN,   // variable assignment
    AST_PRINT     // print statement
} ASTNodeType;

/*
 * AST node structure
 * Represents one node in the abstract syntax tree
 */
typedef struct ASTNode {
    ASTNodeType type;        // node type
    int value;               // used if node is a number
    char name[32];           // used if node is a variable
    struct ASTNode* left;    // left child (for binary operations)
    struct ASTNode* right;   // right child (for binary operations)
} ASTNode;

/* Function declarations */

/*
 *   Takes a list of tokens (produced by the lexer) and builds an Abstract Syntax Tree (AST).
 *   The AST represents the hierarchical structure of the program and the order of operations.
 *   Example: "5 + 3" becomes a node of type AST_BINOP with two children nodes (5 and 3).
 */
ASTNode* parse(TokenList* tokens);

/*
 *   Recursively prints the AST to the console, showing the structure of the program.
 *   The 'indent' parameter is used to visually format the tree (increase indentation for child nodes).
 *   Useful for debugging and understanding how the parser interprets the code.
 *   Example output with indent levels:
 *     ASSIGN
 *       VAR x
 *       BINOP +
 *         NUMBER 5
 *         NUMBER 3
 */
void print_ast(ASTNode* node, int indent);


#endif
