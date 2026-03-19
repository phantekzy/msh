# msh: Maini Shell

A functional command-line interpreter developed in C. This project implements the fundamental mechanics of a Unix shell, focusing on process lifecycle management, environment handling, and inter-process communication.

---

## Technical Features

* **Process Management:** Implements command execution using fork(), execve(), and waitpid().
* **Built-in Commands:** Native implementations for core utilities:
    * cd: Supports absolute and relative path navigation.
    * echo: Handles the -n flag.
    * export / unset: Modifies the environment during runtime.
    * pwd, env, and exit.
* **Redirections:** Manages file descriptor manipulation for standard input/output redirection (>, >>, <).
* **Pipelines:** Facilitates sequential command execution with inter-process communication via pipe().
* **Signal Handling:** Custom handlers for SIGINT (Ctrl+C) and SIGQUIT (Ctrl+\) to ensure shell stability and standard terminal behavior.
* **Environment Management:** Dynamic management of environment variables through structured data pointers.

---

## Architecture Overview

The shell follows a standard Read-Eval-Print Loop (REPL) architecture:

1. Lexical Analysis: Tokenizes raw input strings into discrete command components and operators.
2. Parsing: Analyzes tokens to identify command hierarchies, redirections, and pipeline sequences.
3. Execution:
    * Identifies if a command is a shell built-in or an external binary.
    * Manages child process creation and piping.
    * Resolves binary paths through the PATH environment variable.
4. Memory Management: Strictly manages heap allocations to ensure a leak-free environment during long sessions.

---

## Getting Started

### Prerequisites
* GCC or Clang compiler
* GNU Make
* Standard C Library (libc)

### Installation
1. Clone the repository:
   git clone https://github.com/phantekzy/msh.git
   cd msh

2. Compile the executable:
   make

3. Initialize the shell:
   ./msh

---

## Usage Examples

Binary Execution with Arguments:
msh> ls -la /usr/bin

Piping and Redirection:
msh> cat file.txt | grep "pattern" > result.txt

Environment Control:
msh> export SESSION_ID=42
msh> env | grep SESSION_ID

---

## Project Structure

* src/: Core logic including the executor, parser, and signal handlers.
* include/: Header files defining data structures and function prototypes.
* libft/: Internal utility library for string manipulation and memory wrappers.

---

## License
This project is intended for educational purposes within the scope of systems programming and Unix architecture studies.
