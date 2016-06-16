# OSC_project_1
project 1 for Operating Systems Concepts class

Objectives:
1. use fork system call
2. use execve system call
3. use pipe system call
4. use wait/waitpid system call

part 1: copy-on-write:
using fork and pipe calls, spawn a child process and have them talk to eachother

Once you have a parent process and a child process (created using fork), you will use the child process to demonstrate
the effects of copy-on-write fork semantics.

You will initialize a variable called cow to a value of 10. Please
make sure that this is done before calling fork().

This is because whatever is present in a processs address space before
fork will be considered by fork.

part 2: execve
use fork to spawn child process, ensure the parent process does not terminate before children using wait

one of child processes will call execve to run the ls command