# Tokenizer for Simple Programming Language

## Overview

This project is a tokenizer for a simple programming language designed to process and categorize tokens from a source file. It recognizes various elements such as keywords, identifiers, numbers, operators, delimiters, strings, and comments. The tokenizer processes the input file and prints a table of tokens with their types and values.

## Features

- **Keywords Recognition**: Identifies predefined keywords in the programming language.
- **Identifier Handling**: Distinguishes between identifiers and keywords, assigning a unique token value to each identifier.
- **Number Detection**: Extracts integer literals from the input.
- **String Processing**: Handles string literals enclosed in double quotes.
- **Comments Handling**: Ignores comments starting with `//` and `/*...*/`.
- **Operator Identification**: Detects various operators, including unary and binary operators, with special handling for compound operators.
- **Delimiter Identification**: Recognizes common delimiters used in programming languages.
- **Error Handling**: Reports unexpected characters as errors.

## How It Works

The tokenizer reads from an input file, processes each character to classify it, and outputs a formatted table with token details. The main components of the tokenizer include:

1. **Key Functions**:
   - `getIndex(char key[])`: Finds the index of a key in the internal storage.
   - `insert(char key[], int value)`: Inserts or updates a key-value pair.
   - `get(char key[])`: Retrieves the value associated with a key.
   - `isOperator(char c)`: Checks if a character is an operator.
   - `isKeyword(char word[])`: Checks if a word is a keyword.
   - `isDelimiter(char c)`: Checks if a character is a delimiter.
   - `getToken(FILE *fp)`: Main function that processes the input file and categorizes tokens.

2. **Token Types**:
   - **Keywords**: Predefined words in the language (e.g., `if`, `while`, `return`).
   - **Identifiers**: Variable names and function names.
   - **Numbers**: Integer literals.
   - **Strings**: Text enclosed in double quotes.
   - **Operators**: Mathematical and logical operators (e.g., `+`, `-`, `&&`).
   - **Delimiters**: Symbols used for separating code elements (e.g., `;`, `,`).
   - **Comments**: Lines or blocks of text meant for documentation.

## Example

Given an `input.txt` file with the following content:

```c
int main() {
    int x = 10;
    if (x > 5) {
        print("x is greater than 5");
    }
}
```

The output will be:

```
 token                token_type      token_value
------------------------------------------------------------------------
 int                  Keywords        int
 main                 ID              100
 (                    DELIMITER       (
 )                    DELIMITER       )
 {                    DELIMITER       {
 int                  Keywords        int
 x                    ID              101
 =                    OPERATOR        =
 10                   Number          10
 ;                    DELIMITER       ;
 if                   Keywords        if
 (                    DELIMITER       (
 x                    ID              101
 >                    OPERATOR        >
 5                    Number          5
 )                    DELIMITER       )
 {                    DELIMITER       {
 print                ID              102
 (                    DELIMITER       (
 "x is greater than 5" STRING        "x is greater than 5"
 )                    DELIMITER       )
 ;                    DELIMITER       ;
 }                    DELIMITER       }
 }                    DELIMITER       }
```
