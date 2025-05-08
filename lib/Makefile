##
## EPITECH PROJECT, 2025
## lib
## File description:
## Makefile
##

CFLAGS	=	-Wall -Werror -I.

SRC	=	math_func.c \
		my_iota.c \
		my_isprintable.c \
		my_putnbr.c \
		my_putstr.c \
		my_revstr.c \
		my_strlen.c \
		compare.c \
		my_atoi.c \
		my_str_to_warray.c \
		my_strstr.c \
		my_strs.c \
		my_count_words.c \
		my_is_in_str.c \
		my_is_alphanum.c \

OBJ	=	$(SRC:.c=.o)
LIB_NAME	=	libmy

all: $(LIB_NAME)

$(LIB_NAME): $(OBJ)
	ar rc $(LIB_NAME).a $(OBJ)

clean:
	-rm -f $(OBJ)

fclean: clean
	-rm -f $(LIB_NAME).a

re: fclean all
