# Minishell

Minishell is a simple UNIX command-line shell developed as part of the curriculum at 42 Abu Dhabi. It provides a basic shell environment with support for various built-in commands, as well as the ability to execute external commands, handle pipes, and perform input/output redirection.

## Table of Contents
- [Features](#features)
- [Getting Started](#getting-started)
  - [Prerequisites](#prerequisites)
  - [Installation](#installation)
- [Usage](#usage)
- [Built-in Commands](#built-in-commands)
- [External Commands](#external-commands)
- [Pipes and Redirection](#pipes-and-redirection)
- [Signals](#signals)
- [Contributors](#contributors)

## Features

- Supports a variety of built-in shell commands.
- Ability to execute external commands.
- Handles input and output redirection.
- Supports piping of commands.
- Implements signal handling for Ctrl+C (SIGINT), Ctrl+\ (SIGQUIT) and Ctrl+D (EOF).
- User-friendly and interactive command-line interface.

## Getting Started

### Prerequisites

Before you begin, ensure you have met the following requirements:

- **Linux/Unix Environment**: Minishell is designed to run on Unix-like systems.

### Installation

1. Clone the repository:

   ```sh
   git clone https://github.com/your-username/minishell.git

2. Make
   ```sh
    cd minishell
    make

### Usage  
To start using Minishell, simply run the minishell executable:
     ```sh
      ./minishell
### Built-in Commands

Minishell supports several built-in commands:

- echo: Display messages.
- cd: Change the current directory.
- exit: Exit the shell.
- export: Set environment variables.
- unset: Unset environment variables.
- pwd: Print the current working directory.
- env: Display the environment variables.
  
### External Commands

You can also execute external commands by entering their names and argument if needed at the shell prompt.

### Pipes and Redirection

Minishell supports pipes and input/output redirection. You can use | for pipes, < for input redirection, and > for output redirection.

Example:
    ```sh
      ls -la | grep myfile.txt

## Signals

Minishell handles signals gracefully, including the following:

- Ctrl+C (SIGINT): Used to interrupt a running command.
- Ctrl+D (EOF): Signals the end of input.
- Ctrl+\ (SIGQUIT): Triggers a core dump and can be used to exit the shell with a core dump.

Feel free to explore these signals while using Minishell.
## Contributors 
This project was done by me (Degef) and Merhawi as part of our curriculum at 42 Abu Dhabi. 
... 
