<<<<<<< HEAD
# simple_shell
# simple_shell
# monty
# monty
=======
Simple Shell Project by Anthony Muli and Mutiso Muli, Software Engineering students at ALX-SE Programme.

Overview

This is a simple shell project that provides both interactive and non-interactive modes for executing shell commands. The shell is designed to mimic the basic functionality of popular Unix/Linux shells, such as Bash.

Features

Interactive shell mode: Allows users to enter and execute commands interactively.
Non-interactive shell mode: Executes commands from a script or file.
Basic command execution: Supports running common shell commands and programs.
Command history: Keeps a history of previously executed commands in interactive mode.
Exit command: Allows users to exit the shell gracefully.

Prerequisites

This project requires a Unix-like operating system (Linux, macOS, or WSL on Windows).
You should have a C compiler (e.g., GCC) installed on your system.

Compilation

To compile the shell, use the following command:gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh

RUNNING THE SHELL

Interactive Mode

To start the shell in interactive mode, simply run the executable:./hsh
You will be presented with a prompt where you can enter commands interactively.

Non-Interactive Mode

To run the shell in non-interactive mode and execute commands from a script or file, use the following command:echo "/bin/ls" | ./hsh

Usage

Interactive Mode

In interactive mode, you can enter commands one at a time. The shell will execute the command and display the output.
You can use the "exit" command to exit the shell.

Non-Interactive Mode

In non-interactive mode, you can execute a series of commands from a script or file. The shell will execute the commands sequentially.

Command History

The shell keeps a history of the commands executed in interactive mode. You can use the up and down arrow keys to navigate through the command history.

Acknowledgments

This project is inspired by the simplicity of Unix/Linux shells.
Thanks to the open-source community for providing valuable resources and documentation on shell scripting and system programming.
>>>>>>> aaf892024b5292aa1031190815cab585f194868e
