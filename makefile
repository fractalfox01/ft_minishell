NAME= ft_minishell

TEST= test

SRC := $(addsuffix .c, src/glob_init src/process src/startshell src/expand_tilde src/expand_dollar)

INC := $(addsuffix .h, includes/ft_minishell includes/libft)

FLAGS= -Wall -Werror -Wextra

$(NAME):
	@make -C libft/ re
	@cp libft/libft.a .
	@gcc $(FLAGS) $(SRC) libft.a src/main.c -o $(NAME)

$(TEST): fc
	@make -C libft/ re
	@cp libft/libft.a .
	@rm -rf ft_minishell.dSYM 2>/dev/null | echo deleted
	@gcc $(FLAGS) -g $(SRC) libft.a src/main.c -o $(NAME)

all: $(NAME)

clean:
	rm $(NAME) 2>/dev/null | echo "Gone"
	rm -rf $(NAME).dSYM/ 2>/dev/null | echo "Gone"
	rm test 2>/dev/null | echo "Gone"
	rm -rf test.dSYM/ 2>/dev/null | echo "Gone"
	@make -C libft/ clean

fclean: clean
	@rm libft.a | echo "libft.a gone"
	@make -C libft/ fc

fc: fclean

re: fclean all

add:
	git add makefile $(SRC) $(INC)
	git status

push:
	git commit -m "auto push"
	git push
