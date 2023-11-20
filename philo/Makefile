NAME = philo

SRC := 	utils.c \
		time.c \
		init.c \
		philo.c


OBJ := $(SRC:.c=.o)

#CCFLAGS := -Wall -Wextra -Werror
CCFLAGS := -g -fsanitize=address

.PHONY: all bonus clean fclean re

all:$(NAME)

#bonus:$(BNS_OBJ) $(OBJ)
#	ar rc $(NAME) $(BNS_OBJ) $(OBJ)

#$(BNS_OBJ):
#	cc -c $(BNS_SRC) $(CCFLAGS)

$(NAME): $(OBJ)
	cc $(CCFLAGS) $(OBJ) -o $(NAME)
$(OBJ):
	cc -c $(CCFLAGS) $(SRC)
clean:
	rm -f $(OBJ)
fclean: clean
	rm -f $(NAME) 
re: fclean all