NAME = libft.a
CC = gcc
FLAGS = -c -Wall -Wextra -Werror -MMD
HEAD_DIR = include
SRC_DIR = src
OBJ_DIR = obj
PRINTF_DIR = ft_printf
HEAD_FILES = libft.h ft_printf.h ft_bigint.h get_next_line.h
PRINTF_FILES = ft_printf.c ft_printf_b.c ft_printf_e.c ft_printf_efg.c ft_printf_f.c ft_printf_float.c ft_printf_int.c ft_printf_n.c ft_printf_otoa.c ft_printf_ptr.c ft_printf_r.c \
	ft_printf_string.c ft_printf_uint.c ft_printf_utoa.c ft_printf_wchar.c ft_printf_xtoa.c ft_setformat.c ft_bigint.c ft_bigint_exp.c
SRC_FILES = ft_memset.c ft_bzero.c ft_memcpy.c ft_memccpy.c ft_memmove.c ft_memchr.c ft_memcmp.c ft_strlen.c ft_strdup.c ft_strcpy.c ft_strncpy.c ft_strcat.c ft_strncat.c ft_strlcat.c \
	ft_strchr.c ft_strrchr.c ft_strstr.c ft_strnstr.c ft_strcmp.c ft_strncmp.c ft_atoi.c ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_toupper.c ft_tolower.c \
	ft_memalloc.c ft_memdel.c ft_strnew.c ft_strdel.c ft_strclr.c ft_striter.c ft_striteri.c ft_strmap.c ft_strmapi.c ft_strequ.c ft_strnequ.c ft_strsub.c ft_strjoin.c ft_strtrim.c \
	ft_strsplit.c ft_itoa.c ft_putchar.c ft_putstr.c ft_putendl.c ft_putnbr.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_lstnew.c ft_lstdelone.c ft_lstdel.c \
	ft_lstadd.c ft_lstiter.c ft_lstmap.c ft_isspace.c ft_isupper.c ft_islower.c ft_strtol.c ft_atol.c ft_realloc.c ft_memswap.c ft_isort.c ft_qsort.c ft_lstadd_sorted.c ft_lstsort.c \
	ft_isqrt.c ft_lltoa.c ft_ulltoa.c ft_wcslen.c ft_abs.c get_next_line.c
SRC = $(addprefix $(SRC_DIR)/, $(SRC_FILES))
SRC_PRINTF = $(addprefix $(SRC_DIR)/$(PRINTF_DIR)/, $(PRINTF_FILES))
OBJ = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC)) $(patsubst $(SRC_DIR)/$(PRINTF_DIR)/%.c, $(OBJ_DIR)/$(PRINTF_DIR)/%.o, $(SRC_PRINTF))

all: $(NAME)

-include $(OBJ:.o=.d)

$(NAME): $(OBJ)
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(FLAGS) -I$(HEAD_DIR) -o $@ $<

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)
	mkdir -p $(OBJ_DIR)/$(PRINTF_DIR)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
