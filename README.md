<p align="center">
  <img src="https://github.com/pibouill/42-project-badges/blob/main/badges/minishelle.png" alt="minishell-badge"/>
</p>

<p align="center">
	<img alt="GitHub code size in bytes" src="https://img.shields.io/github/languages/code-size/natttttttttttttt/minishell">
</p>

# Minishell

> This project is about creating a simple shell. Yes, your own little bash. You will learn a lot about processes and file descriptors.

## Overview

A minimal bash-like shell written in C, built as a pair project at 42 school by
[@natttttttttttttt](https://github.com/natttttttttttttt) and [@pibouill](https://github.com/pibouill).

## Features

- Interactive prompt with working history (readline)
- Command execution via `PATH`, relative or absolute paths
- Pipes (`|`)
- Redirections: `<`, `>`, `>>` (append) and `<<` (heredoc)
- Environment variable expansion (`$VAR`, `$?`)
- Single and double quote handling
- Signal handling (`ctrl-C`, `ctrl-D`, `ctrl-\`)

## Builtins

| Command | Description |
|---------|-------------|
| `echo` | With option `-n` |
| `cd` | With relative or absolute path |
| `pwd` | Print current working directory |
| `export` | Set environment variables |
| `unset` | Remove environment variables |
| `env` | Print the environment |
| `exit` | Exit the shell with a status |

## Usage

```bash
make
./minishell
```

## Concepts Covered

- Lexing, tokenization, and parsing
- Processes: `fork`, `execve`, `wait`
- File descriptors, pipes, and redirections
- Signals and terminal behavior
- Environment management
