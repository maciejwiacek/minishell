NAME = minishell
CC = cc
FLAGS = -Wall -Wextra -Werror
RM = rm -f

SRCS = minishell.c init_shell.c parse/parse_input.c parse/fill_commands.c parse/fill_commands_utils.c \
		parse/parse_commands.c utils/exit_program.c utils/inlines.c utils/skip_spaces.c utils/safe_malloc.c utils/search_var.c \
		builtins/mini_cd.c builtins/mini_echo.c builtins/mini_env.c builtins/mini_exec.c builtins/mini_pwd.c builtins/mini_unset.c \
		utils/envp_add_back.c builtins/mini_export.c exec/exec.c

OBJS = $(SRCS:.c=.o)

LIBFT = libft/libft.a

all: $(LIBFT) $(NAME)

$(LIBFT):
	make -C libft

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(FLAGS) $(OBJS) -Llibft -lft -lreadline -o $@

clean:
	$(RM) $(OBJS)
	make fclean -C libft

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
