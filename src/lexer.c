#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "lexer.h"

/*
 * Simple lexer for the Mini C Compiler
 * Converts source code string into a list of tokens.
 * Supports numbers, basic operators, 'let' and 'print' keywords, identifiers, and semicolons.
 */

// Helper function to create a new token
Token create_token(TokenType type, int value, const char* name) {
    Token token;
    token.type = type;
    token.value = value;
    if (name)
        strncpy(token.name, name, sizeof(token.name) - 1);
    else
        token.name[0] = '\0';
    return token;
}

// Lexical analysis function
TokenList lex(const char* source) {
    TokenList list;
    list.tokens = malloc(128 * sizeof(Token)); // initial size, can grow
    list.count = 0;

    int i = 0;
    while (source[i] != '\0') {
        char c = source[i];

        // Skip whitespace
        if (isspace(c)) {
            i++;
            continue;
        }

        // Numbers
        if (isdigit(c)) {
            int value = 0; // value will contain the complete integer once the entire numeric token has been read
            /* Cycles until consecutive numeric characters are found
             * This is used to read numbers with multiple digits (e.g., 12345)
             */
            while (isdigit(source[i])) { 
                /*
                 * Converts the numeric character into an integer value
                 * (source[i] - ‘0’) → transforms the character ‘5’ into the number 5
                 * value = value * 10 + digit → builds the complete number:
                 * e.g. we read “123”:
                 * first cycle: value = 0*10 + 1 = 1
                 * second cycle: value = 1*10 + 2 = 12
                 * third cycle: value = 12*10 + 3 = 123
                 */
                value = value * 10 + (source[i] - '0');
                // Move to the next character
                i++;
            }
            /*
             * Once the number is read, creates a token of type T_NUMBER with the integer value just calculated
             * Adds it to the list of tokens (list.tokens)
             * list.count++ → updates the total token count
            */
            list.tokens[list.count++] = create_token(T_NUMBER, value, NULL);
            continue;
        }

        // Identifiers and keywords
        if (isalpha(c)) { // checks if c is a letter (a-z or A-Z)
            /*
             * Defines a temporary array where the characters of the word/identifier are stored
             * j is the current index in the array
             */
            char buffer[32];
            int j = 0;
            /*
             * Cycles until the character is a letter or number → so it reads identifiers such as x1, var2, etc.
             * j < 31 → prevents buffer overflow
             */
            while (isalnum(source[i]) && j < 31) {
                // Copies the character into the buffer and increments both i (-> advancing the source) and j (-> advancing the array)
                buffer[j++] = source[i++];
            }
            buffer[j] = '\0';

            /*
             * strcmp compares the word read with the language keywords
             * If it matches → creates a special token (T_LET, T_PRINT)
             * Otherwise → the word is a generic identifier (e.g., variable name) → creates a T_IDENTIFIER token with the name copied to the token's name field
             */
            if (strcmp(buffer, "let") == 0)
                list.tokens[list.count++] = create_token(T_LET, 0, NULL);
            else if (strcmp(buffer, "print") == 0)
                list.tokens[list.count++] = create_token(T_PRINT, 0, NULL);
            else
                list.tokens[list.count++] = create_token(T_IDENTIFIER, 0, buffer);

            continue;
        }

        // Operators and punctuation
        switch (c) {
            case '+': list.tokens[list.count++] = create_token(T_PLUS, 0, NULL); break;
            case '-': list.tokens[list.count++] = create_token(T_MINUS, 0, NULL); break;
            case '*': list.tokens[list.count++] = create_token(T_MULT, 0, NULL); break;
            case '/': list.tokens[list.count++] = create_token(T_DIV, 0, NULL); break;
            case '=': list.tokens[list.count++] = create_token(T_EQUAL, 0, NULL); break;
            case ';': list.tokens[list.count++] = create_token(T_SEMICOLON, 0, NULL); break;
            default:
                printf("Unknown character: %c\n", c);
                exit(1);
        }
        i++;
    }

    // End-of-file token
    list.tokens[list.count++] = create_token(T_EOF, 0, NULL);

    return list;
}

// Print all tokens in a TokenList
void print_tokens(TokenList* list) {
    for (int i = 0; i < list->count; i++) {
        Token t = list->tokens[i];
        switch (t.type) {
            case T_NUMBER: printf("NUMBER(%d)\n", t.value); break;
            case T_PLUS: printf("PLUS\n"); break;
            case T_MINUS: printf("MINUS\n"); break;
            case T_MULT: printf("MULT\n"); break;
            case T_DIV: printf("DIV\n"); break;
            case T_LET: printf("LET\n"); break;
            case T_IDENTIFIER: printf("IDENT(%s)\n", t.name); break;
            case T_EQUAL: printf("EQUAL\n"); break;
            case T_PRINT: printf("PRINT\n"); break;
            case T_SEMICOLON: printf("SEMICOLON\n"); break;
            case T_EOF: printf("EOF\n"); break;
        }
    }
}
