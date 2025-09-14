#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/parser.h"

/* 
 * Helper function to create a new AST node
 */
ASTNode* create_node(ASTNodeType type, int value, const char* name, ASTNode* left, ASTNode* right) {
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    node->type = type;
    node->value = value;
    if (name != NULL) {
        strncpy(node->name, name, 31);
        node->name[31] = '\0';
    } else {
        node->name[0] = '\0';
    }
    node->left = left;
    node->right = right;
    return node;
}

/* Forward declaration of parse_expression for recursive calls */
ASTNode* parse_expression(TokenList* tokens, int* pos);

/* 
 * Parses a statement (variable assignment, print, etc.)
 */
ASTNode* parse_statement(TokenList* tokens, int* pos) {
    Token current = tokens->tokens[*pos];

    if (current.type == T_LET) { // if statement starts with 'let' -> e.g. let x = 5 + 3;
        (*pos)++; // move past 'let' keyword
        Token var = tokens->tokens[*pos]; // capture the variable name ('x')
        (*pos)++; // move past variable token

        if (tokens->tokens[*pos].type != T_EQUAL) { // check for '='
            printf("Syntax error: expected '=' at pos=%d\n", *pos);
            exit(1);
        }
        (*pos)++; // skip '='

        /* 
         * parse the expression "5 + 3" 
         * returns AST_BINARY_OP(+) with left = AST_NUMBER(5), right = AST_NUMBER(3)
         */
        ASTNode* expr = parse_expression(tokens, pos);

        if (tokens->tokens[*pos].type != T_SEMICOLON) { // expect ';' at the end of the statement
            printf("Syntax error: expected ';' at pos=%d\n", *pos);
            exit(1);
        }
        (*pos)++; // skip ';'

        /*
         * Resulting AST structure for "let x = 5 + 3;"
         * AST_ASSIGN(x)
         *   └── AST_BINARY_OP(+)
         *        ├── AST_NUMBER(5)
         *        └── AST_NUMBER(3)
         *
         * - The assigned variable (x) is stored in the 'name' field of the AST_ASSIGN node.
         * - The computed expression (5 + 3) is the left child of the assignment node.
         * - The right child is NULL because it is not needed for assignments.
         */
        return create_node(AST_ASSIGN, 0, var.name, expr, NULL);

    } else if (current.type == T_PRINT) { // if statement starts with 'print'
        (*pos)++; // move past 'print' keyword

        /*
         * parse the expression inside print, e.g. print(x); -> parses 'x'
         */
        ASTNode* expr = parse_expression(tokens, pos);

        if (tokens->tokens[*pos].type != T_SEMICOLON) { // expect ';' at the end of the statement
            printf("Syntax error: expected ';' at pos=%d\n", *pos);
            exit(1);
        }
        (*pos)++; // skip ';'

        /*
         * Resulting AST structure for "print(x);"
         * AST_PRINT
         *   └── AST_VAR(x)
         *
         * - The variable to print (i.e., x) is the left child of the AST_PRINT node.
         * - The right child is NULL because it is not needed for print statements.
         */
        return create_node(AST_PRINT, 0, NULL, expr, NULL);

    } else if (current.type == T_LPAREN) { // if statement starts with '(' -> e.g. print(x);
        (*pos)++; // skip '('
        ASTNode* expr = parse_expression(tokens, pos);
        if (tokens->tokens[*pos].type != T_RPAREN) {
            printf("Syntax error: expected ')' at pos=%d\n", *pos);
            exit(1);
        }
        (*pos)++; // skip ')'
        return expr;
    } else { // handles standalone expressions that are not 'let' or 'print' statements (for example: "5 + 3;" or "x;")
        /* 
         * The parser creates an AST node representing the expression itself.
         * The left child contains the expression (e.g., AST_BINARY_OP)
         */
        ASTNode* expr = parse_expression(tokens, pos);
        if (tokens->tokens[*pos].type == T_SEMICOLON) (*pos)++;
        return expr;
    }
}

/* 
 * Parses simple binary expressions (numbers, variables, +, -, *, /)
 */
ASTNode* parse_expression(TokenList* tokens, int* pos) {
    Token current = tokens->tokens[*pos];
    ASTNode* left = NULL;

    if (current.type == T_NUMBER) { // if token is a number (e.g. '5' in "5 + 3")
        // left is a pointer to an AST node of type = AST_NUMBER; value contains the numeeric value read from the token (e.g. '5')
        left = create_node(AST_NUMBER, current.value, NULL, NULL, NULL);
        (*pos)++;
    } else if (current.type == T_IDENTIFIER) { // if token is a variable (e.g. 'x' in "x * 2") (it means that the expression contains a variable instead of a number)
        left = create_node(AST_VAR, 0, current.name, NULL, NULL);
        (*pos)++;
    } else if (current.type == T_LPAREN) {  // if token is '('
        (*pos)++; // skip the '(' token and move to the next one

        // Recursively parse the expression inside the parentheses.
        // This handles any valid sub-expression, including numbers, variables,
        // binary operations, or even nested parentheses.
        // The result is stored in 'left' as a subtree of the AST.
        left = parse_expression(tokens, pos);

        // After parsing the sub-expression, we expect a closing parenthesis ')'
        // If the next token is not ')', it's a syntax error
        if (tokens->tokens[*pos].type != T_RPAREN) {
            printf("Syntax error: expected ')' at pos=%d\n", *pos);
            exit(1);
        }

        (*pos)++;  // Skip the ')' token and continue parsing
    } else {
        printf("Syntax error: unexpected token at pos=%d\n", *pos);
        exit(1);
    }

    current = tokens->tokens[*pos];
    while (current.type == T_PLUS || current.type == T_MINUS ||
        current.type == T_MULT || current.type == T_DIV) {

        char op = 0;
        switch (current.type) {
            case T_PLUS: op = '+'; break;
            case T_MINUS: op = '-'; break;
            case T_MULT: op = '*'; break;
            case T_DIV: op = '/'; break;
        }
        (*pos)++;
        ASTNode* right = parse_expression(tokens, pos);
        left = create_node(AST_BINARY_OP, op, NULL, left, right);
        current = tokens->tokens[*pos];
    }

    /* If no binary operator follows the current token, simply return the left node
     * Example: a standalone number "5" will return AST_NUMBER(5) without further recursion
     */
    return left;
}

/* 
 * Entry point: parses the entire token list into an AST
 */
ASTNode* parse(TokenList* tokens) {
    int pos = 0;
    ASTNode* root = NULL;

    /*
     * e.g. let x = 5 + 3; print(x);
     * first iteration: parses "let x = 5 + 3;"
     * second iteration: parses "print(x);"
     */
    while (tokens->tokens[pos].type != T_EOF) {
        /*
         * 'stmt' points to the AST node representing the current statement.
         * For example, with the code: let x = 5 + 3;
         *      stmt -> AST_ASSIGN(x)
         *                └── AST_BINARY_OP(+)
         *                     ├── AST_NUMBER(5)
         *                     └── AST_NUMBER(3)
         *  
         * If there are multiple statements (e.g. let x = 5 + 3; print(x);), 
         * each iteration of the while loop will parse the next one, and 'stmt' 
         * will be updated to point to the root node of that new statement's AST.
         * 
         * The variable 'pos' is updated inside parse_statement() to keep track 
         * of the current position in the token list, so the loop knows where 
         * each statement starts and ends.
         */
        ASTNode* stmt = parse_statement(tokens, &pos);

        if (root == NULL) {
            root = stmt;
        } else {
            // append statements in a right-skewed list
            ASTNode* temp = root;
            // the while loop runs through the nodes on the right until it finds the last node (the one with right == NULL).
            while (temp->right != NULL) temp = temp->right;
            // add the new statement to the end of the list
            temp->right = stmt; 
        }
    }

    return root;
}

/* 
 * Recursively prints the AST
 */
void print_ast(ASTNode* node, int indent) {
    if (node == NULL) return;

    for (int i = 0; i < indent; i++) printf("  ");

    switch (node->type) {
        case AST_NUMBER:
            printf("AST_NUMBER(%d)\n", node->value);
            break;
        case AST_VAR:
            printf("AST_VAR(%s)\n", node->name);
            break;
        case AST_BINARY_OP:
            printf("AST_BINARY_OP(%c)\n", node->value);
            print_ast(node->left, indent + 1);
            print_ast(node->right, indent + 1);
            break;
        case AST_ASSIGN:
            printf("AST_ASSIGN(%s)\n", node->name);
            print_ast(node->left, indent + 1);
            break;
        case AST_PRINT:
            printf("AST_PRINT\n");
            print_ast(node->left, indent + 1);
            break;
        default:
            printf("Unknown AST node\n");
    }
}
