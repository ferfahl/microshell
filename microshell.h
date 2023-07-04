#ifndef MICROSHELL_H
# define MICROSHELL_H

# include <stdlib.h> // malloc, free
# include <unistd.h> // fork, execve, pipe, dup, dup2, chdir, exit, write, close
# include <string.h> // strcmp, strncmp
# include <signal.h> // signal
# include <sys/types.h> // waitpid, kill
# include <sys/wait.h> // waitpid

# define STDIN 0
# define STDOUT 1
# define STDERR 2

# define TRUE 1
# define FALSE 0

typedef struct s_cmd
{
	char			*cmd;
	char			*path[];
	struct s_cmd	*next;
}				t_cmd;

typedef struct s_piped
{
	struct s_cmd	*head_c;
	struct s_piped	*next;
}				t_piped;

typedef struct s_semicolon
{
	struct s_piped		*head_p;
	struct s_semicolon	*next;
}				t_semicolon;

typedef struct s_micro
{
	char				*envp[];
	struct s_semicolon	*head_s;
}			t_micro;

#endif