##
## EPITECH PROJECT, 2022
## myftp
## File description:
## Makefile
##

CC	=	gcc

SRC	=	myteams.c		\
		error.c			\
		print.c			\
		get_command.c	\
		tools.c			\
		handle_client.c \
		handle_client_sec.c \
		./commands/users.c \
		./commands/list.c \
		./commands/infos.c \
		./commands/subscribed.c \
		./commands/unsubsub.c \
		./commands/use.c \
		./commands/basic_cmd.c \
		./commands/create.c \
		./commands/create_sec.c \
		./commands/message.c \
		./database/database.c \
		./database/open_write.c \
		../shared/my_str_to_word_array.c	\
		../shared/my_split.c	\
		../shared/my_twod_size.c	\
		../shared/my_strip.c	\
		../shared/my_concate.c	\
		../shared/my_pop_twod.c \
		../shared/my_revstr.c \
		main.c

OBJ	=	$(SRC:.c=.o)

CFLAGS	=	-Wall -Wextra -Werror -g3

CPPFLAGS	=	-I./includes -I../shared \
				-I../../libs/myteams -L ../../libs/myteams/ -lmyteams -luuid

NAME	=	myteams_server


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
