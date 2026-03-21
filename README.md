# msh: Maini Shell

A modular command line interpreter developed in C. This project implements the core mechanics of the Unix Sh-family architecture, focusing on robust process lifecycle management, strict memory hygiene, and environment-aware execution.

---

## Technical Features

* **Advanced Process Management:** Orchestrates command execution via fork(), execvp(), and synchronized waitpid() logic with status boundary checks.
* **Multi-Stage Pipeline (Piping):** Supports command chaining using pipe() and dup2(), allowing data to flow between multiple processes (e.g., ls | grep msh).
* **Environment Variable Expansion:** Dynamic resolution of system variables (e.g., $USER, $PATH) performed before the parsing stage for native shell behavior.
* **Struct-Mapped Builtins:** High-extensibility architecture using a t_builtin dispatch table for efficient command resolution and modularity.
    * **cd:** Optimized with $HOME defaults and OLDPWD tracking for 'cd -' support.
    * **help:** Dynamic discovery of available shell internal commands.
    * **exit:** Clean termination of the REPL session with proper exit status.
* **Signal Resilience:** Custom signal masking. SIGINT (Ctrl+C) and SIGQUIT (Ctrl+\) are ignored by the parent shell but restored to default behavior in child processes.
* **Automated Build System:** Pro-tier Makefile featuring wildcard discovery, header dependency tracking (-MMD -MP), and debug symbol integration.

---

## Architecture Overview

The shell operates on a refined **Read-Expand-Parse-Execute** pipeline:

1. **Lexical Analysis:** Tokenizes raw input strings into discrete command components and operators.
2. **Expansion Engine:** A pre-parsing layer in src/env.c that scans for $ tokens and replaces them with system environment values using getenv().
3. **Dispatch Engine:** A centralized msh_execute layer that differentiates between internal built-ins, piped commands, and external binaries.
4. **Execution Layer:**
    * Manages the fork-join model for external binaries.
    * Implements pipe-line synchronization for concurrent process execution.
    * Restores signal defaults in the child context to maintain standard terminal interactivity.

---

## Project Structure

```text
.
├── include/           # Modular headers (msh.h, executor.h, builtins.h, parser.h)
├── src/               # Implementation logic
│   ├── main.c         # Entry point & REPL loop
│   ├── env.c          # Environment variable expansion logic ($VAR)
│   ├── executor.c     # Forking, pipe handling & process execution
│   ├── builtins.c     # Internal shell command implementations
│   └── parser.c       # String tokenization & I/O handling
├── obj/               # Generated object files (automatically managed)
└── Makefile           # Automated build system with dependency tracking
```

---

## Roadmap

* [ ] **I/O Redirection:** Implement `>`, `>>`, and `<` using open() and dup2().
* [ ] **Command History:** Persistent history tracking across sessions.
* [ ] **Logical Operators:** Support for `&&` and `||` conditional execution.

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
* **Header Integrity:** Automatic recompilation on header changes via Makefile dependency tracking.

---

## License
The project is intended for educational purposes within the scope of systems programming and Unix architecture studies.
