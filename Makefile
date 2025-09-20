PINK = \033[3;35m
MAGENTA = \033[1;95m
RED = \033[1;31m
GREEN = \033[1;32m
BLUE = \033[1;34m
WHITE = \033[1;37m
BOLD = \033[1m
RESET = \033[0m

NAME = computor
CC = cc
CFLAGS = -Wall -Wextra -Werror -std=c99 -pedantic
OBJ_DIR = objs
SRCS_DIR = src
SRCS = $(wildcard $(SRCS_DIR)/*.c)
OBJS = $(addprefix $(OBJ_DIR)/, $(notdir $(SRCS:.c=.o)))

all: $(NAME)
	@echo "$(PINK)$(NAME)$(GREEN) compiled successfully!$(RESET)"
	@echo "$(BLUE)Usage: $(PINK)./$(NAME)$(BLUE) \"<polynomial>\""

$(NAME): $(OBJ_DIR) $(OBJS)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

$(OBJ_DIR)/%.o: $(SRCS_DIR)/%.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

clean:
	@rm -rf $(OBJ_DIR)
	@echo "$(RED)Object files removed!$(RESET)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(PINK)$(NAME) $(RED)executable removed!$(RESET)"

re: fclean all

.PHONY: all clean fclean re