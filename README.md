# Lexical Analyzer in C

## Introduction

A Lexical Analyzer is the first phase of a compiler. It reads source code and converts it into meaningful tokens.

This project is implemented in C language. It identifies different types of tokens such as keywords, identifiers, operators, symbols, numbers, strings, character constants and preprocessor directives. It also detects some basic errors in the source code.

## Features

- **Keyword Detection:** Identifies the 32 C language keywords.
- **Identifier Detection:** Identifies variable names and other identifiers.
- **Preprocessor Detection:** Identifies predefined header files such as stdio.h, stdlib.h, string.h and others.
- **String Detection:** Identifies strings enclosed in double quotes.
- **Character Detection:** Identifies single character constants.
- **Number Detection:** Identifies integer and floating-point numbers.
- **Operator Detection:** Identifies arithmetic, relational, logical and assignment operators.
- **Symbol Detection:** Identifies parentheses, curly brackets, square brackets, commas, semicolons and other symbols.
- **Error Detection:** Detects some basic errors such as invalid parentheses, curly brackets and statement-related errors.
- **Output Table:** Displays the detected tokens in a formatted table.

## Technologies Used

- C Programming Language
- File Handling
- String Handling
- Conditional Statements
- Loops
- Functions
- Pointers

## Project Files

- `main.c` – Contains the main program and lexical analysis logic.
- `lexical_analyzer.h` – Contains function declarations.
- `sample.txt` – Contains the sample C source code for testing.
- `document.txt` – Contains project documentation.
- `README.md` – Contains project information.

## How to Compile and Run

**Step 1: Compile the program**

```bash
gcc main.c -o lexical_analyzer
```

**Step 2: Run the program**

```bash
./lexical_analyzer
```

Note: Make sure `sample.txt` is available in the current working directory.

## Working Process

1. Start the program.
2. Open the sample.txt file.
3. Check whether the file is opened successfully.
4. Read the source code character by character.
5. Identify preprocessor directives.
6. Identify strings.
7. Check keywords and identifiers.
8. Identify numbers.
9. Identify character constants.
10. Identify operators.
11. Identify symbols.
12. Display tokens in the output table.
13. Check basic errors.
14. Continue reading until EOF.
15. Display the final output.

## Limitations

- Supports only predefined preprocessor directives.
- Character constant detection currently handles single-character constants.
- Number detection supports basic integer and floating-point patterns.
- Error detection is limited to selected basic conditions.
- It does not implement the complete C language lexical specification.

## Author

**Sagar**

## Project Purpose

The main purpose of this project is to understand the working of the lexical analysis phase of a compiler using the C programming language.
