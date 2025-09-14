#include <stdio.h>
#include "../include/lexer.h"
#include "../include/parser.h"
#include "../include/interpreter.h"

/*
 * Main entry point of the Mini C Compiler.
 * This program demonstrates the compiler pipeline:
 * 1. Lexical analysis (convert source code into tokens)
 * 2. Parsing (build an Abstract Syntax Tree from tokens)
 * 3. Interpretation (execute the AST) - to be implemented later
 */

int main() {
    // Sample source code to process
    const char* source_code = "let x = 5 + 3; let y = 1 + 1; print(x + y);";

    printf("Source code:\n%s\n\n", source_code);

    // Step 1: Lexer - convert text into a list of tokens
    TokenList tokens = lex(source_code);
    printf("Tokens:\n");
    print_tokens(&tokens);

    // Step 2: Parser - convert tokens into an AST
    ASTNode* ast = parse(&tokens);
    printf("\nAST:\n");
    print_ast(ast, 0);

    // Step 3: Interpreter - will execute the AST
    printf("\nProgram output:\n");
    interpret(ast);

    return 0;
}
