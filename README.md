# msh: Maini Shell

A modular command-line interpreter developed in C. This project implements the core mechanics of the Unix Sh-family architecture, focusing on robust process lifecycle management, strict memory hygiene, and environment-aware execution.

---

## Technical Features

* **Advanced Process Management:** Orchestrates command execution via fork(), execvp(), and synchronized waitpid() logic with status boundary checks.
* **Struct-Mapped Builtins:** High-extensibility architecture using a t_builtin dispatch table for efficient command resolution and modularity.
    * **cd:** Optimized with $HOME defaults and OLDPWD tracking for 'cd -' support.
    * **help:** Dynamic discovery of available shell internal commands.
    * **exit:** Clean termination of the REPL session with proper exit status.
* **Signal Resilience:** Custom signal masking. SIGINT (Ctrl+C) and SIGQUIT (Ctrl+\) are ignored by the parent shell but restored to default behavior in child processes to ensure terminal stability.
* **Systems Integration:**
    * **Dynamic Prompt:** Real-time $PWD resolution with ANSI color-coding for enhanced navigation.
    * **Environment Sync:** Automatic updates to PWD and OLDPWD environment variables during directory transitions.
* **Memory Hygiene:** Engineered for zero-leak sessions using getline for dynamic buffer management and structured free() cycles in the REPL loop.

---

## Architecture Overview

The shell operates on a refined Read-Eval-Print Loop (REPL) with a modular dependency chain:

1. **Lexical Analysis:** Tokenizes raw input strings into discrete command components and operators.
2. **Dispatch Engine:** A centralized msh_execute layer that differentiates between internal built-ins and external binaries located in the system PATH.
3. **Execution Layer:**
    * Manages the fork-join model for external binaries.
    * Restores signal defaults in the child context to maintain standard terminal interactivity.
4. **Header-Driven Modularity:** Strict separation of concerns across parser, executor, and builtins modules.

---

## Project Structure

.
├── include/           # Modular headers (msh.h, executor.h, builtins.h, parser.h)
├── src/               # Implementation logic
│   ├── main.c         # Entry point & REPL loop
│   ├── executor.c     # Forking & process execution logic
│   ├── builtins.c     # Internal shell command implementations
│   └── parser.c       # String tokenization & I/O handling
└── Makefile           # Automated build system with -Wall -Wextra flags

---

## Getting Started

### Prerequisites
* GCC or Clang compiler
* GNU Make
* Standard C Library (libc)

### Installation
1. **Clone the repository:**
   git clone https://github.com/phantekzy/msh.git
   cd msh

2. **Compile the executable:**
   make

3. **Initialize the shell:**
   ./msh

---

## Development & Testing

The project is validated against the following criteria:
* **Valgrind:** Comprehensive heap analysis to ensure zero memory leaks.
* **Signal Stressing:** Verification of parent/child signal isolation.
* **POSIX Compliance:** Adherence to standard Unix process behavior.

---

## License
This project is intended for educational purposes within the scope of systems programming and Unix architecture studies.
