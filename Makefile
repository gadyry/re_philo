NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread
SRC_MAN = mandatory/philo.c	mandatory/parse_args.c mandatory/initialization.c mandatory/death_detection.c
OBJ_MAN = $(SRC_MAN:.c=.o)


all : $(NAME)

$(NAME) : $(OBJ_MAN)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ_MAN)

mandatory/%.o : mandatory/%.c mandatory/philosophers.h
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	rm -rf $(OBJ_MAN) $(OBJ_BON)

fclean : clean
	rm -rf $(NAME) $(NAME_BONUS)

re : fclean all

.PHONY: clean