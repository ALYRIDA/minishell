🐚 Minishell

A minimal Bash-like shell implemented in C
42 Beirut — Milestone 3

📖 Overview

Minishell is a small Unix shell that recreates essential features of Bash, including:

Tokenizing user input

Parsing and building an Abstract Syntax Tree (AST)

Environment variable expansion

Executing commands with pipes and redirections

Handling built-ins

Managing signals

Supporting heredocs

This project offers deep insights into how real shells work internally.

✨ Features
🔹 Core Shell Capabilities

🖥️ Interactive colored prompt using Readline

📝 Command history

⚙️ Execution of binaries (PATH or absolute)

⚡ Pipelines (cmd1 | cmd2 | ...)

📥 Redirections (<, >, >>, <<)

🔄 Environment variable expansion ($VAR, $?)

🧩 Proper quote handling

🛑 Bash-like signal behavior (Ctrl+C, Ctrl+D, Ctrl+\)

🧹 Full memory-safe implementation (no leaks)

🔹 Built-in Commands
Built-in	Description
echo	Print text (-n supported)
cd	Change directory
pwd	Print working directory
export	Add/update environment variables
unset	Remove environment variables
env	Display environment variables
exit	Exit the shell
🧠 Internal Architecture

Here’s how Minishell processes a command from input → output.

1️⃣ Tokenization

The tokenizer splits user input into tokens while respecting:

Quotes

Special operators

Whitespace

Environment variables

Example

Input:

echo "hello world" | grep hello > out.txt


Tokenizer output:

[ECHO] ["hello world"] [|] [GREP] [hello] [>] [out.txt]


The tokenizer:

Detects operators

Handles quoting

Expands simple tokens

Produces a linked-list of tokens

2️⃣ Parsing → AST (Abstract Syntax Tree)

Tokens are transformed into a syntax tree representing:

Commands

Pipelines

Redirections

Example AST

          PIPE
         /    \
   COMMAND     REDIR_OUT
  (ls -l)       \
                 COMMAND
                (grep .c)


The AST makes execution deterministic and structured.

3️⃣ Expansion

Before execution, Minishell expands:

$VAR environment variables

$? exit status

Double-quoted strings

Removes quotes correctly

Example:

echo "$USER lives here"


Expands to:

echo ["aly lives here"]

4️⃣ Execution

The executor walks the AST to run:

Pipelines

Commands

Built-ins

Redirections

Execution steps:

Build pipes

Fork processes

Duplicate FDs with dup2

Run built-ins directly or call execve for external programs

5️⃣ Built-ins

Built-ins run without forking when needed, so they can modify shell state.

Examples:

cd changes the current directory

export updates environment variables

exit terminates the shell

6️⃣ Redirections

Minishell supports:

🔸 Output
cmd > file

🔸 Append
cmd >> file

🔸 Input
cmd < file

🔸 Heredoc
cmd << EOF


The heredoc:

Reads lines until the delimiter

Stores content in a pipe or temp file

Feeds it to the command’s STDIN

7️⃣ Pipelines

Example:

a | b | c


Execution:

Connects a stdout → b stdin

Connects b stdout → c stdin

Processes run sequentially but execute concurrently

🧪 Usage Examples
minishell$ ls -la
minishell$ ls | grep ".c"
minishell$ echo hello > x.txt
minishell$ cat < x.txt | wc -l
minishell$ cat << EOF
> hi
> EOF

🧱 Project Structure
minishell/
├── minishell.c
├── minishell.h
├── Makefile
│
├── tokenizer/
│   ├── tokenizer.c
│   ├── extract_*.c
│   ├── syntax_checker.c
│   └── cleanup_tokens*.c
│
├── parser/
│   ├── parser.c
│   ├── parse_command.c
│   ├── parse_pipeline.c
│   └── parse_redirection.c
│
├── expander/
│   ├── expand_tokens.c
│   ├── expand_variables.c
│   ├── expand_exit_code.c
│   └── handle_dollar.c
│
├── executor/
│   ├── ast_executor.c
│   ├── cmd_executor.c
│   ├── builtin_executor.c
│   ├── pipeline_executor.c
│   ├── redir_executor.c
│   ├── heredoc_*.c
│   └── cmd_path_resolver.c
│
└── utils/
    ├── string_utils.c
    ├── env_*.c
    ├── char_*.c
    └── banner.c

📚 What We Learned

Shell architecture

Lexing & tokenization

AST parsing

File descriptors & IO

Pipe creation and management

Signals in interactive programs

Environment storage & manipulation

Memory-safe C design

👥 Authors

Sirine & Aly Rida
42 Beirut Students

GitHub: @ALYRIDA

🙏 Acknowledgments

42 Beirut

The original Unix shell developers

GNU Bash for inspiration

❤️ Made with love at 42 Beirut
If you like the project, consider starring ⭐ the repo!
