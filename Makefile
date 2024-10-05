##
## EPITECH PROJECT, 2022
## myftp
## File description:
## Makefile
##

all:
		cd src/server/ && make
		cd src/client/ && make

clean:
		cd src/server/ && make clean
		cd src/client/ && make clean

fclean:
		cd src/server/ && make fclean
		cd src/client/ && make fclean

re:
		cd src/server/ && make re
		cd src/client/ && make re

exp:
	export LD_LIBRARY_PATH=$PWD/libs/myteams/libmyteams.so:$PWD/libs/myteams
	source ~/.bashrc

.PHONY:	all clean fclean re
