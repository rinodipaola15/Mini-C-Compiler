#include <stdio.h>
#include <stdlib.h>
#include "../include/lexer.h"
#include "../include/parser.h"
#include "../include/interpreter.h"
#include "../include/utils.h"

/*
 * Main entry point of the Mini C Compiler.
 * This program demonstrates the compiler pipeline:
 * 1. Lexical analysis (convert source code into tokens)
 * 2. Parsing (build an Abstract Syntax Tree from tokens)
 * 3. Interpretation (execute the AST) - to be implemented later
 */

int main(int argc, char* argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Error: No source file specified.\n");
        fprintf(stderr, "Please provide the path to the source code file when running the program.\n");
        fprintf(stderr, "Example usage: %s examples/test.txt\n", argv[0]);
        return EXIT_FAILURE;
    }

    // Step 0: Read source code from the provided file
    char* source_code = read_file(argv[1]);
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

    free(source_code);
    return 0;
}
