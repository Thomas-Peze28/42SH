##
## EPITECH PROJECT, 2025
## fozzbazz
## File description:
## Makefile
##

NAME	= 42sh

SRC	=	src/mysh.c\
		src/lib/my_str_to_word_array.c\
		src/builtin/my_env.c\
		src/builtin/my_exit.c\
		src/builtin/my_getenv.c\
		src/lib/my_strcat.c\
		src/my_split.c\
		src/my_free.c\
		src/builtin/my_cd.c\
		src/builtin/my_setenv.c\
		src/my_clist.c\
		src/lib/my_strcpy.c\
		src/my_list_to_clist.c\
		src/my_clist_get_value.c\
		src/execute_commands.c\
		src/my_clist_len.c\
		src/shell_loop.c\
		src/my_print_dir.c\
		src/my_commands.c\
		src/lib/my_strcmp.c\
		src/search_commands.c\
		src/file_reader.c\
		src/clist_delete.c\
		src/builtin/my_unsetenv.c\
		src/my_stdfd.c\
		src/lib/my_strsplit.c\
		src/commands_scanner.c\
		src/redirection.c\
		src/my_42.c \
		src/init_ncurse.c \
		src/ncurse.c \
		src/eof.c \

OBJ	= $(SRC:.c=.o)

CC	= gcc

INCLUDE_DIR = include

CFLAGS  = -I$(INCLUDE_DIR) -Wall -Wextra -lncurses

LFLAGS	= -I include

all: $(NAME)

$(NAME):	$(OBJ)
	gcc -o $(NAME) $(OBJ) $(CFLAGS)

debug:
	$(CC) -c $(SRC) $(CFLAGS) -g
	@mv $(notdir $(OBJ)) src
	$(CC) -o $(NAME)_debug $(OBJ) $(CFLAGS) -g

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)
	@rm -f $(NAME)_debug

re: fclean all

run: all
	./$(NAME)
