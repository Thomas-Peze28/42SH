##
## EPITECH PROJECT, 2024
## makefile for ## to_file
## File description:
## makefile for ## to_file
##

TEST	=	unit_tests
NAME	=	mysh
SRC	=	free.c \
		func_cd.c \
		func_env.c \
		div_path.c \
		search_command.c \
		func_setenv_unsetenv.c \
		change_dir.c \
		handle_exit.c \
		pipe_handling.c \
		pip_utils.c \
		check_empty_commands.c \
		child_exec_process.c \
		run_commands_pipe.c \
		redirection.c \
		ncurse.c \
		my_which.c \
		easter.c \
		builtins.c \

MAIN	=	main.c
OBJ	=	$(SRC:.c=.o)
MAIN_OBJ=	$(MAIN:.c=.o)
CFLAGS	=	-Wall -Wextra -L$(LIB_DIR) -l:$(LIB_NAME).a -I./include -lncurses
ILFLAGS	=	-I./lib
LIB_DIR	=	lib
LIB_NAME	=	libmy
LIB_PATH	=	$(LIB_DIR)/lib$(LIB_NAME).a

all: $(LIB_PATH) $(NAME)

$(NAME): $(LIB_PATH) $(OBJ) $(MAIN_OBJ)
	gcc -o $(NAME) $(OBJ) $(MAIN_OBJ) $(CFLAGS) $(ILFLAGS)

$(LIB_PATH):
	$(MAKE) -C $(LIB_DIR)

clean:
	$(MAKE) -C $(LIB_DIR) clean
	rm -f $(OBJ) $(MAIN_OBJ)
	rm -f *.gcno
	rm -f *.gcda

fclean: clean
	$(MAKE) -C $(LIB_DIR) fclean
	rm -f $(NAME)
	rm -f $(TEST)

re: fclean all

debug: $(LIB_PATH) $(OBJ) $(MAIN_OBJ)
	gcc -o $(NAME) -g $(OBJ) $(MAIN_OBJ) $(CFLAGS) $(ILFLAGS)
	valgrind --leak-check=full --show-leak-kinds=all ./mysh
