#ifndef MICROSHELL_H
# define MICROSHELL_H

# include <stdlib.h> // malloc, free
# include <unistd.h> // fork, execve, pipe, dup, dup2, chdir, exit, write, close
# include <string.h> // strcmp, strncmp
# include <signal.h> // signal
# include <sys/types.h> // waitpid, kill
# include <sys/wait.h> // waitpid

#include <stdio.h> //debug

# define STDIN 0
# define STDOUT 1
# define STDERR 2

# define TRUE 1
# define FALSE 0

#endif