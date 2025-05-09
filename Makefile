##
## EPITECH PROJECT, 2024
## makefile for 42ch
## File description:
## makefile for 42ch
##

TEST	=	unit_tests
NAME	=	42sh
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
		src/history/manage_history.c \
		src/alias/manage_alias.c \
		src/alias/alias_commands.c \
		src/alias/free_aliases.c \
		src/alias/create_alias.c \
		src/alias/handle_alias.c \
		src/ncurse_keys.c \
		src/ncurse_keys_left_right.c \

MAIN	=	src/main.c
OBJ	=	$(SRC:src/%.c=$(OBJ_DIR)/%.o)
MAIN_OBJ=	$(MAIN:src/%.c=$(OBJ_DIR)/%.o)
CFLAGS	=	-Wall -Wextra -L$(LIB_DIR) -l:$(LIB_NAME).a -I./include -lncurses
ILFLAGS	=	-I./lib
LIB_DIR	=	lib
LIB_NAME	=	libmy
LIB_PATH	=	$(LIB_DIR)/lib$(LIB_NAME).a

CC      ?= gcc

GREEN	=	\033[0;32m
YELLOW	=	\033[1;33m
RED	=	\033[0;31m
BLUE	=	\033[1;34m
NC	=	\033[0m

all: $(LIB_PATH) create_dirs $(NAME)
	@echo -e "$(GREEN)[OK] Compilation terminée.$(NC)"

create_dirs:
	@mkdir -p $(OBJ_DIR)/builtins
	@mkdir -p $(OBJ_DIR)/pipe_n_redirect
	@mkdir -p $(OBJ_DIR)/utils
	@mkdir -p $(OBJ_DIR)/history
	@mkdir -p $(OBJ_DIR)/alias

$(NAME): $(LIB_PATH) $(OBJ) $(MAIN_OBJ)
	@echo -e "$(BLUE)[INFO] Edition des liens...$(NC)"
	$(CC) -o $(NAME) $(OBJ) $(MAIN_OBJ) $(CFLAGS) $(ILFLAGS)

$(OBJ_DIR)/%.o: src/%.c
	@echo -e "$(YELLOW)[COMP] $<$(NC)"
	$(CC) $(CFLAGS) $(ILFLAGS) -c $< -o $@

$(LIB_PATH):
	@echo -e "$(BLUE)[INFO] Compilation de la librairie...$(NC)"
	$(MAKE) -C $(LIB_DIR)

clean:
	@echo -e "$(RED)[CLEAN] Suppression des fichiers objets...$(NC)"
	$(MAKE) -C $(LIB_DIR) clean
	rm -rf $(OBJ_DIR)
	rm -f *.gcno
	rm -f *.gcda

fclean: clean
	@echo -e "$(RED)[FCLEAN] Suppression des binaires...$(NC)"
	$(MAKE) -C $(LIB_DIR) fclean
	rm -f $(NAME)
	rm -f $(TEST)

re: fclean all

debug: $(LIB_PATH) create_dirs $(OBJ) $(MAIN_OBJ)
	@echo -e "$(BLUE)[DEBUG] Compilation avec debug...$(NC)"
	$(CC) -o $(NAME) -g $(OBJ) $(MAIN_OBJ) $(CFLAGS) $(ILFLAGS)
	valgrind --leak-check=full --show-leak-kinds=all ./mysh
