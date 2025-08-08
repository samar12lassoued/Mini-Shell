## Mini Shell

A minimal command-line shell written in c. It can execute basic commnds like `ls`, `pwd`, etc.


## Features
- Read user input in a REPL (Read_Eval_Print Loop)
- Tokenize input using space as delimiter
- Execute commands via `execvp()`
- Graceful exit ith the `exit` command 

## Project Structure
```bash
.
├── include
│   ├── executor.h         # Declaration of command execution functions
│   └── parser.h           # Declaration of input parsing functions
├── Makefile               # Build instructions
├── README.md              # Project documentation
└── src
    ├── executor.c         # Implementation of command execution
    ├── main.c             # Shell entry point and REPL loop
    └── parser.c           # Input tokenization logic

```
## Getting Started

### Build & Run

- [x] Clone the repository
- [x] Run `make` to build the project
- [x] Launch the shell: `./mini-shell`



### Example Usage
```bash
mini-shell> ls
mini-shell> pwd
mini-shell> echo Welcome to mini-shell !
mini-shell> exit

```


## Feature Roadmap && TODO

| Feature | Status |
|--------|--------|
| ➕ Input redirection (`<`) | ⬜ Planned |
| ➕ Output redirection (`>`, `>>`) | ⬜ Planned |
| ➕ Pipelines  | ⬜ Planned |
| ➕ Command history (arrow keys) via GNU Readline | ⬜ Planned |
| ➕ Background process execution (`sleep 5 &`) | ⬜ Planned |
| ➕ Environment variable expansion (`echo $HOME`) | ⬜ Planned |
