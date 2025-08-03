NAME = minishell
LIBFT_A = libft/libft.a
SRC = minishell.c lexing.c lexing1.c lexing2.c utils.c expansion.c
OBJ = $(SRC:.c=.o)
CFLAGS += -g -Ilibft #-Wall -Wextra -Werror 

all: $(NAME)

$(NAME): $(LIBFT_A) $(OBJ)
	cc $(CFLAGS) $(OBJ) $(LIBFT_A) -lreadline -o $(NAME)

$(LIBFT_A):
	$(MAKE) bonus -C libft

%.o: %.c
	cc $(CFLAGS) -c $< -o $@

clean:
	rm  -f $(OBJ)
	$(MAKE) clean -C libft

fclean: clean
	rm -f $(NAME)
	$(MAKE) fclean -C libft

re: fclean all