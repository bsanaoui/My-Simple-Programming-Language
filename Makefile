NAME = hello
CC = gcc
FLAGS = -Werror -Wextra -Wall

SRC= $(wildcard src/*.c) src/libft/libft.a

all : $(NAME)

$(NAME):
	@$(CC) $(SRC) -I $(FLAGS) -o $(NAME)
	
fclean: clean
	@rm -f $(NAME)

clean:
	@rm -f *.o

re: fclean all