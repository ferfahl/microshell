NAME = microshell

CC = cc
FLAGS = -Wall -Wextra -Werror

SOURCES =	microshell.c		\

OBJS = $(SOURCES:%.c=%.o)

HEADER = microshell.h

all: $(NAME)

$(NAME): $(HEADER) $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -o $(NAME)

%.o:%.c
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

val: $(NAME)
	valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes ./$(NAME) /bin/ls 

make re: fclean all

