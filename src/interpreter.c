#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/interpreter.h"

/*
 * Initializes the symbol table by setting count = 0
 */
void init_symbol_table(SymbolTable* table) {
    table->count = 0;
}

/*
 * Looks up a variable in the symbol table.
 * If found, returns its value.
 * If not found, prints an error and exits.
 */
int lookup_symbol(SymbolTable* table, const char* name) {
    for (int i = 0; i < table->count; i++) {
        if (strcmp(table->symbols[i].name, name) == 0) {
            return table->symbols[i].value;
        }
    }
    printf("Runtime error: undefined variable '%s'\n", name);
    exit(1);
}

/*
 * Inserts or updates a variable in the symbol table.
 * If variable already exists, updates its value.
 * If new, adds it to the table.
 */
void set_symbol(SymbolTable* table, const char* name, int value) {
    for (int i = 0; i < table->count; i++) {
        if (strcmp(table->symbols[i].name, name) == 0) {
            table->symbols[i].value = value;
            return;
        }
    }
    if (table->count < 128) {
        strncpy(table->symbols[table->count].name, name, 31);
        table->symbols[table->count].name[31] = '\0';
        table->symbols[table->count].value = value;
        table->count++;
    } else {
        printf("Runtime error: symbol table overflow\n");
        exit(1);
    }
}

/*
 * Recursively evaluates an expression node
 */
int eval_expression(ASTNode* node, SymbolTable* table) {
    switch (node->type) {
        // --- Case 1: Number ---
        case AST_NUMBER:
            // If the node represents a number, simply return its value
            // Example: AST_NUMBER(5)  => returns 5
            return node->value;

        // --- Case 2: Variable ---
        case AST_VAR:
            // If the node represents a variable, look up its value in the symbol table
            // Example: AST_VAR("x") with table containing x = 10 => returns 10
            return lookup_symbol(table, node->name);

        // --- Case 3: Binary operation (+, -, *, /) ---
        case AST_BINARY_OP: {
            // Recursively evaluate the left-hand side of the binary operation.
            // Example: if the expression is "5 + 3", node->left points to AST_NUMBER(5),
            // so this call returns 5 and stores it in left_val.
            int left_val = eval_expression(node->left, table);

            // Recursively evaluate the right-hand side of the binary operation.
            // Continuing the example: node->right points to AST_NUMBER(3),
            // so this call returns 3 and stores it in right_val.
            int right_val = eval_expression(node->right, table);

            // Perform the operation indicated by node->value
            switch (node->value) {
                case '+': return left_val + right_val;
                case '-': return left_val - right_val;
                case '*': return left_val * right_val;
                case '/':
                    if (right_val == 0) { // protect against division by zero
                        printf("Runtime error: division by zero\n");
                        exit(1);
                    }
                    return left_val / right_val; // integer division
                default:
                    printf("Runtime error: unknown operator '%c'\n", node->value);
                    exit(1);
            }
        }

        default:
            printf("Runtime error: invalid expression node\n");
            exit(1);
    }
}

/*
 * Executes a statement node
 */
void exec_statement(ASTNode* node, SymbolTable* table) {
    switch (node->type) {
        case AST_ASSIGN: {
            // Evaluate the expression on the left-hand side of the assignment node.
            // For example, in "let x = 5 + 3;", node->left represents "5 + 3".
            int value = eval_expression(node->left, table);
            // Store the computed value in the symbol table using the variable name.
            // 'node->name' contains the variable being assigned (e.g., "x").
            int value = eval_expression(node->left, table);
            set_symbol(table, node->name, value);
            break;
        }

        case AST_PRINT: {
            // Evaluate the expression to be printed, which is the left child of the AST_PRINT node.
            // For example, in "print(x);", node->left represents "x".
            int value = eval_expression(node->left, table);
            printf("%d\n", value);
            break;
        }

        case AST_NUMBER:
        case AST_VAR:
        case AST_BINARY_OP:
            // These cases handle standalone expressions that are not part of an assignment or print statement.
            // Examples: just writing "5;", "x;", or "3 + 4;" in the code.
            // The expression is evaluated for its side effects (if any), but the result is not stored or printed.
            eval_expression(node, table);
            break;

        default:
            printf("Runtime error: invalid statement node\n");
            exit(1);
    }
}

/*
 * Main interpreter entry point
 * Traverses the AST (linked list of statements)
 */
void interpret(ASTNode* root) {
    SymbolTable table;
    init_symbol_table(&table);

    ASTNode* current = root;
    while (current != NULL) {
        exec_statement(current, &table);
        current = current->right; // move to next statement
    }
}
