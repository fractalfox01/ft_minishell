NAME= ft_minishell

TEST= test

LIB= libft.a

BUILTINS := $(addsuffix .c, builtins/ft_mini_exit builtins/ft_mini_clear \
	builtins/ft_mini_unset_env builtins/ft_mini_print_history \
	builtins/ft_mini_echo builtins/ft_mini_set_env builtins/ft_mini_print_env \
	builtins/ft_mini_change_dir)

SRC := $(addsuffix .c, src/glob_init src/process src/startshell src/expand_tilde \
	src/expand_dollar src/expand_path src/shell_history src/builtins src/mini_environ)

TEST_SRC := $(addsuffix .c, src/builtins src/expand_dollar src/expand_path \
	src/expand_tilde src/glob_init src/process src/shell_history src/mini_environ)

UTILS := $(addsuffix .c, utils/start_utils utils/ft_mini_utils utils/mini_env_utils)

INC := $(addsuffix .h, includes/ft_minishell includes/libft)

FLAGS= -Wall -Werror -Wextra -Wunused-value -Wno-unused-variable

$(NAME):
	@make -C libft/ re
	@cp libft/libft.a .
	@gcc $(FLAGS) $(SRC) $(BUILTINS) $(UTILS) $(LIB) src/main.c -o $(NAME)

$(TEST): fc
	@make -C libft/ re
	@cp libft/libft.a .
	@gcc -g $(FLAGS) $(TEST_SRC) $(BUILTINS) $(UTILS) tests/test.c $(LIB) -o shelltesting

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
