NAME = philo

SRC := 	utils.c \
		time.c \
		init.c \
		philo.c \
		clean.c \
		setter.c \
		getter.c \
		print.c \
		input.c \
		dead.c


OBJ := $(SRC:.c=.o)

CCFLAGS := -Wall -Wextra -Werror
#CCFLAGS := -g -fsanitize=address
#CCFLAGS := -g -fsanitize=thread

.PHONY: all bonus clean fclean re

all:$(NAME)

$(NAME): $(OBJ)
	cc $(CCFLAGS) $(OBJ) -o $(NAME)
$(OBJ): $(SRC)
	cc -c $(CCFLAGS) $(SRC)
clean:
	rm -f $(OBJ)
fclean: clean
	rm -f $(NAME) 
re: fclean all