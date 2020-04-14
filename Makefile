NAME = corewar
CC = gcc
FLAGS = -Wall -Wextra -Werror
HEAD_DIR = include
SRC_DIR = src
OBJ_DIR = obj
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
LIBFT_HEAD = $(LIBFT_DIR)/include
HEAD_FILES = corewar.h op.h
SRC_FILES = main.c error.c input.c arena.c battle.c delete.c op1.c op2.c op3.c op4.c output.c players.c process.c table.c
SRC = $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJ = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))

all: $(NAME)

-include $(OBJ:.o=.d)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(FLAGS) -o $(NAME) $(OBJ) $(LIBFT)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(FLAGS) -I$(HEAD_DIR) -I$(LIBFT_HEAD) -o $@ -c $< -MMD

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(LIBFT): FAKE
	make -C $(LIBFT_DIR)

clean:
	rm -rf $(OBJ_DIR)
	make clean -C $(LIBFT_DIR)

fclean: clean
	rm -f $(NAME)
	rm -f $(LIBFT)

re: fclean all

.PHONY: all clean fclean re FAKE