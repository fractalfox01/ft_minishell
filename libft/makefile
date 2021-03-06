NAME= libft.a

FLAGS= -Wall -Wextra -Werror -Wunused-variable

SRC := $(addsuffix .c, ft_strrev \
	ft_ustoh ft_ustoa ft_ultoa ft_ulltoa ft_uitoa ft_uctoa ft_stoa ft_lltoo ft_lltoh ft_itob ft_lftoa ft_atoll \
	ft_lltoa ft_ctoh ft_itoh ft_ftoa ft_otoi ft_itoo ft_ltoo ft_ltoh \
	ft_ltoa ft_numlen ft_create_queue ft_destroy_queue ft_queue_front ft_queue_is_full \
	ft_dequeue ft_enqueue ft_queue_is_empty ft_queue_rear ft_hex_to_int ft_strsplit_int ft_isspace \
	ft_get_lst_len ft_abs ft_strpbrk ft_iscntrl ft_isgraph ft_realloc \
	ft_lstmap ft_lstadd ft_lstiter ft_lstdel ft_lstdelone ft_lstnew ft_strbuild ft_power \
	ft_putnbr_fd ft_putendl_fd ft_putstr_fd ft_putchar_fd ft_putendl ft_itoa ft_strxlen ft_wordcount ft_strsplit \
	ft_whitespace ft_strtrim ft_strjoin ft_strsub ft_strnequ ft_strequ ft_strmapi ft_strmap ft_striteri ft_striter \
	ft_strclr ft_strdel ft_strnew ft_memdel ft_memalloc ft_strnlen ft_strnstr ft_strlcat ft_strncat ft_strncpy ft_atoi \
	ft_isascii ft_memchr ft_memset ft_strcat ft_strdup ft_strrchr ft_bzero ft_isdigit ft_memcmp ft_putchar ft_strchr \
	ft_strlcat ft_strstr ft_isalnum ft_isprint ft_memcpy ft_putnbr ft_strcmp ft_strlen ft_tolower ft_isalpha ft_memccpy \
	ft_memmove ft_putstr ft_strcpy ft_strncmp ft_toupper ft_putlong get_next_line)

OBJ := $(addsuffix .o, ft_strrev ft_ustoh ft_ustoa ft_ultoa ft_ulltoa ft_uitoa ft_uctoa ft_stoa ft_lltoo ft_lltoh ft_itob ft_lftoa ft_atoll \
	ft_lltoa ft_ctoh ft_itoh ft_ftoa ft_otoi ft_itoo ft_ltoo ft_ltoh \
	ft_ltoa ft_numlen ft_create_queue ft_destroy_queue ft_queue_front ft_queue_is_full \
	ft_dequeue ft_enqueue ft_queue_is_empty ft_queue_rear ft_hex_to_int ft_strsplit_int ft_isspace \
	ft_get_lst_len ft_abs ft_strpbrk ft_iscntrl ft_isgraph ft_realloc \
	ft_lstmap ft_lstadd ft_lstiter ft_lstdel ft_lstdelone ft_lstnew ft_strbuild ft_power \
	ft_putnbr_fd ft_putendl_fd ft_putstr_fd ft_putchar_fd ft_putendl ft_itoa ft_strxlen ft_wordcount ft_strsplit \
	ft_whitespace ft_strtrim ft_strjoin ft_strsub ft_strnequ ft_strequ ft_strmapi ft_strmap ft_striteri ft_striter \
	ft_strclr ft_strdel ft_strnew ft_memdel ft_memalloc ft_strnlen ft_strnstr ft_strlcat ft_strncat ft_strncpy ft_atoi \
	ft_isascii ft_memchr ft_memset ft_strcat ft_strdup ft_strrchr ft_bzero ft_isdigit ft_memcmp ft_putchar ft_strchr \
	ft_strlcat ft_strstr ft_isalnum ft_isprint ft_memcpy ft_putnbr ft_strcmp ft_strlen ft_tolower ft_isalpha ft_memccpy \
	ft_memmove ft_putstr ft_strcpy ft_strncmp ft_toupper ft_putlong get_next_line)

$(NAME):
	@echo "\033[1;32mBuilding Libft..."
	@cp src/*.c .
	@gcc -c $(FLAGS) $(SRC)
	@rm *.c
	@ar rc libft.a $(OBJ)
	@mv *.o objs

all: $(NAME)

clean: 
	@echo "\033[1;36mCleaning Up Library, removing all object files.\033[0;31m"
	@for f in $(OBJ) ; do \
		rm objs/$$f 2>/dev/null || 2>/dev/null; \
	done

fclean: clean
	@echo "\033[1;32mremoving libft.a"
	@rm libft.a 2>/dev/null || echo "You've Already Removed libft.a"

fc: fclean

re: fclean all

test_start: $(NAME) clean
	@gcc -g -Wall -Werror -Wextra main.c -L. -lft -o temp_testing 2>/dev/null

test_rm: fc
	rm temp_testing
	rm -rf temp_testing.dSYM

test_re: test_rm test_start

test_hide:
	mv main.c main.txt

test_unhide:
	mv main.txt main.c

.PHONY: fclean testall libft all clean
