#ifndef LEXER_H
#define LEXER_H

/*
 * Token types for the Mini C Compiler
 * Each token represents a meaningful element of the source code
 */
typedef enum {
    T_NUMBER,      // numeric literal
    T_PLUS,        // '+'
    T_MINUS,       // '-'
    T_MULT,        // '*'
    T_DIV,         // '/'
    T_LET,         // 'let' keyword
    T_IDENTIFIER,  // variable name
    T_EQUAL,       // '='
    T_PRINT,       // 'print' keyword
    T_SEMICOLON,   // ';'
    T_EOF          // end of file/input
} TokenType;

/*
 * Token structure
 * Holds type and value or name (depending on token)
 */
typedef struct {
    TokenType type;
    int value;         // used if token is a number
    char name[32];     // used if token is a variable
} Token;

/*
 * Token list structure
 * Contains an array of tokens and a count
 */
typedef struct {
    Token* tokens;
    int count;
} TokenList;

/* Function declarations */

/*
 *   Takes a string containing source code and converts it into a list of tokens.
 *   Each token represents a meaningful element of the language (number, operator, keyword, identifier, etc.).
 */
TokenList lex(const char* source);

/*
 *   Prints all tokens in a TokenList to the console, for debugging and verification purposes.
 */
void print_tokens(TokenList* list);

#endif
