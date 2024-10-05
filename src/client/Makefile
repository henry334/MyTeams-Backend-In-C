##
## EPITECH PROJECT, 2022
## myftp
## File description:
## Makefile
##

CC	=	gcc

SRC	=	client.c \
		get_command.c \
		commands/help.c \
		commands/login.c \
		commands/users.c \
		commands/sub_unsub.c \
		commands/use.c \
		commands/list.c \
		commands/send_msg.c \
		commands/info.c \
		commands/subscribed.c \
		commands/create.c \
		help_error.c \
		main.c \
		wait_int.c \
		command_sec.c \
		../shared/my_split.c	\
		../shared/my_concate.c	\
		../shared/my_pop_twod.c \
		../shared/my_revstr.c \
		../shared/my_strip.c	\
		../shared/my_str_to_word_array.c	\
		../shared/my_twod_size.c

OBJ	=	$(SRC:.c=.o)

CFLAGS	=	-Wall -Wextra -Werror -g3

CPPFLAGS	=	-I./includes -I../shared \
				-I../../libs/myteams -L ../../libs/myteams/ -lmyteams

NAME	=	myteams_cli

all:	$(NAME)

$(NAME):	$(OBJ)
	$(CC) -g3 -o $(NAME) $(OBJ) $(CFLAGS) $(CPPFLAGS)
	mv $(NAME) ../../
	make clean

clean:
	$(RM) $(OBJ)

fclean: clean
	cd ../.. && $(RM) $(NAME)

re: fclean all

.PHONY:	all clean fclean re
