##
## EPITECH PROJECT, 2024
## makefile for 42ch
## File description:
## makefile for 42ch
##

TEST	=	unit_tests
NAME	=	mysh
OBJ_DIR	=	obj
SRC	=	\
		src/builtins/builtins.c \
		src/builtins/func_cd.c \
		src/builtins/func_env.c \
		src/builtins/func_setenv_unsetenv.c \
		src/builtins/handle_exit.c \
		src/builtins/my_which.c \
		src/pipe_n_redirect/child_exec_process.c \
		src/pipe_n_redirect/pip_utils.c \
		src/pipe_n_redirect/pipe_handling.c \
		src/pipe_n_redirect/redirection.c \
		src/pipe_n_redirect/run_commands_pipe.c \
		src/utils/change_dir.c \
		src/utils/check_empty_commands.c \
		src/utils/div_path.c \
		src/utils/easter.c \
		src/utils/free.c \
		src/utils/search_command.c \
		src/ncurse.c \

MAIN	=	src/main.c
OBJ	=	$(SRC:src/%.c=$(OBJ_DIR)/%.o)
MAIN_OBJ=	$(MAIN:src/%.c=$(OBJ_DIR)/%.o)
CFLAGS	=	-Wall -Wextra -L$(LIB_DIR) -l:$(LIB_NAME).a -I./include -lncurses
ILFLAGS	=	-I./lib
LIB_DIR	=	lib
LIB_NAME	=	libmy
LIB_PATH	=	$(LIB_DIR)/lib$(LIB_NAME).a

all: $(LIB_PATH) create_dirs $(NAME)

create_dirs:
	@mkdir -p $(OBJ_DIR)/builtins
	@mkdir -p $(OBJ_DIR)/pipe_n_redirect
	@mkdir -p $(OBJ_DIR)/utils

$(NAME): $(LIB_PATH) $(OBJ) $(MAIN_OBJ)
	gcc -o $(NAME) $(OBJ) $(MAIN_OBJ) $(CFLAGS) $(ILFLAGS)

$(OBJ_DIR)/%.o: src/%.c
	gcc $(CFLAGS) $(ILFLAGS) -c $< -o $@

$(LIB_PATH):
	$(MAKE) -C $(LIB_DIR)

clean:
	$(MAKE) -C $(LIB_DIR) clean
	rm -rf $(OBJ_DIR)
	rm -f *.gcno
	rm -f *.gcda

fclean: clean
	$(MAKE) -C $(LIB_DIR) fclean
	rm -f $(NAME)
	rm -f $(TEST)

re: fclean all

debug: $(LIB_PATH) create_dirs $(OBJ) $(MAIN_OBJ)
	gcc -o $(NAME) -g $(OBJ) $(MAIN_OBJ) $(CFLAGS) $(ILFLAGS)
	valgrind --leak-check=full --show-leak-kinds=all ./mysh
