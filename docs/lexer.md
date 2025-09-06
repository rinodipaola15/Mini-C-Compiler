# Lexer Module

## Purpose
The lexer reads the source code string and converts it into a list of tokens.
Each token represents a meaningful element of the language (number, operator, keyword, identifier, etc.).

## Usage
```c
TokenList tokens = lex("let x = 5 + 3; print(x);");
print_tokens(&tokens);
```

## Supported Tokens

- **Numbers** (e.g., `123`)
- **Operators**: `+`, `-`, `*`, `/`
- **Keywords**: `let`, `print`
- **Identifiers** (variable names)
- **Semicolons** `;`
- **End-of-file (EOF)**

## Notes

- Whitespace is ignored.
- Unrecognized characters will terminate the program with an error message.
