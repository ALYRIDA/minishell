# Minishell

> A minimalistic, POSIX-compliant shell implementation built in C.

**Project**: 42 Beirut — Curriculum Milestone 4  
**Status**: Complete  

---

## Overview

Minishell is a lightweight Unix shell implementation designed from scratch. It recreates essential Bash functionality, demonstrating core concepts of system programming, process creation, file descriptor manipulation, and memory management.

This project parses user input, builds an Abstract Syntax Tree (AST), handles environment variable expansions, and executes commands safely without memory leaks.

## Features

- **Prompt & History**: Interactive prompt with GNU Readline support and command history.
- **Execution**: Runs executables from absolute, relative, or environment `PATH`.
- **Pipelines (`|`)**: Seamlessly connects multiple commands, executing them concurrently.
- **Redirections (`>`, `>>`, `<`, `<<`)**: Full support for input, output, append, and heredoc.
- **Expansions**: Handles environment variables (`$VAR`) and exit status (`$?`).
- **Quotes**: Accurate interpretation of single (`'`) and double (`"`) quotes.
- **Signals**: Accurate handling of `Ctrl+C`, `Ctrl+D`, and `Ctrl+\` identical to Bash.

## Built-in Commands

| Command | Description |
|---------|-------------|
| `echo`  | Prints arguments (supports `-n` flag). |
| `cd`    | Changes the current directory. |
| `pwd`   | Prints the current working directory. |
| `export`| Sets or updates environment variables. |
| `unset` | Removes environment variables. |
| `env`   | Displays the current environment variables. |
| `exit`  | Exits the shell, with an optional exit code. |

## Getting Started

### Prerequisites

- A POSIX-compliant operating system (Linux, macOS)
- `gcc` or `clang` compiler
- `make`
- GNU `readline` library

### Installation

1. **Clone the repository:**
   ```bash
   git clone <your_repository_url>
   cd minishell
   ```

2. **Compile the project:**
   ```bash
   make
   ```

3. **Run the shell:**
   ```bash
   ./minishell
   ```

## Architecture Overview

The shell operates in a structured pipeline:

1. **Lexer / Tokenizer**: Reads the raw input string and divides it into a linked list of tokens (commands, arguments, pipes, redirections).
2. **Parser**: Analyzes the tokens and constructs an Abstract Syntax Tree (AST), ensuring syntactic correctness.
3. **Expander**: Replaces environment variables (`$USER`, `$?`) with their actual values, respecting quote rules.
4. **Executor**: Traverses the AST recursively, setting up pipes, managing file descriptors, forking child processes, and executing commands via `execve` or built-in functions.

## 42 Curriculum Standards

This project strictly adheres to the 42 School guidelines:
- Written in **C**.
- Complies with the **Norminette** standard.
- **Zero memory leaks** (strictly verified via Valgrind).
- No undefined behavior.
- Efficient memory allocation and robust error handling.

---
*Developed for the 42 Beirut core curriculum.*
