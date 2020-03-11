NAME= ft_minishell

TEST= test

SRC := $(addsuffix .c, src/glob_init src/process src/startshell src/expand_tilde src/expand_dollar src/expand_path src/shell_history src/builtins src/start_utils src/mini_environ)

INC := $(addsuffix .h, includes/ft_minishell includes/libft)

FLAGS= -Wall -Werror -Wextra -Wunused-value -fsanitize=address -Wno-unused-variable

$(NAME):
	@make -C libft/ re
	@cp libft/libft.a .
	@gcc $(FLAGS) $(SRC) libft.a src/main.c -o $(NAME)

$(TEST): fc
	@make -C libft/ re
	@gcc -g $(FLAGS) src/builtins.c src/expand_dollar.c src/expand_path.c src/expand_tilde.c src/glob_init.c src/process.c src/shell_history.c src/start_utils.c src/mini_environ.c test.c libft/libft.a -o shelltesting

all: $(NAME)

clean:
	@rm $(NAME) 2>/dev/null | echo "No binary to remove"
	@make -C libft/ clean

fclean: clean
	@rm shelltesting | echo "testing binary removed"
	@rm -r shelltesting.dSYM | echo "testing data removed"
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
