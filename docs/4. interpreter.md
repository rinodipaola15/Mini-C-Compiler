# Interpreter Module

## Purpose
The interpreter takes an Abstract Syntax Tree (AST) produced by the parser and executes it.  
It evaluates expressions, manages variable storage in a **symbol table**, and performs actions like printing values.

## Usage
```c
ASTNode* root = parse(&tokens);
interpret(root);
```

## Symbol Table

- The symbol table stores variable names and their values during execution.

```c
typedef struct {
    char name[32];
    int value;
} Symbol;

typedef struct {
    Symbol symbols[128];
    int count;
} SymbolTable;
```

- `set_symbol()` inserts or updates a variable.
- `lookup_symbol()` retrieves the value of a variable or throws a runtime error if undefined.

## AST Node Execution

- **AST_NUMBER**: returns its numeric value.
- **AST_VAR**: retrieves the value from the symbol table.
- **AST_BINARY_OP**: recursively evaluates the left and right expressions and applies the operator (+, -, *, /).
- **AST_ASSIGN**: evaluates the expression on the right-hand side and stores the value in the symbol table under the variable name.
- **AST_PRINT**: evaluates the expression and prints the result.

## Example: Binary Operation Evaluation

```c
int left_val = eval_expression(node->left, table);
int right_val = eval_expression(node->right, table);
switch(node->value) {
    case '+': return left_val + right_val;
    case '-': return left_val - right_val;
    case '*': return left_val * right_val;
    case '/': return left_val / right_val;
}
```

- `eval_expression()` is **recursive**, allowing nested expressions like **(2 + 3) * 4**.
- The left and right subtrees of **AST_BINARY_OP** are evaluated before applying the operator.

## Notes

- The interpreter traverses the AST **top-down**, executing statements in the order they appear.
- Statements are linked using the **right** pointer of each AST node, forming a right-skewed list.
- Division by zero or access to undefined variables will terminate execution with a runtime error.
- Printing is handled immediately when an **AST_PRINT** node is encountered.

## Example

Given the AST for the source code:

```c
let x = 5 + 3;
print(x);
```

Execution proceeds as follows:

```c
AST_LET(x)
  AST_BINARY_OP(+)
    AST_NUMBER(5)
    AST_NUMBER(3)

AST_PRINT
  AST_IDENTIFIER(x)
```

Output:

```plaintext
8
```

## Runtime Errors

- **Undefined variable**: Accessing a variable that hasn't been declared.
- **Division by zero**: Attempting to divide by zero.
- **Invalid expression node**: Encountering a malformed or unsupported AST node.

Each runtime error prints a descriptive message and terminates the program.