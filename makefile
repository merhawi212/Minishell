NAME        = minishell

SRCDIR      = ./src
LEXDIR		= ./src/lexer
PARSDIR		= ./src/parser
EXPANDDIR	= ./src/expander
EXECUTDIR	= ./src/executor
BUILTINDIR	= ./src/builtin

LIBFT       = ./libft/libft.a 

FILES = $(SRCDIR)/minishell.c $(LEXDIR)/lexer.c $(LEXDIR)/remove_extra_space.c $(LEXDIR)/join_quote.c \
		$(LEXDIR)/separate_characters.c $(LEXDIR)/split_input.c $(LEXDIR)/syntax_error.c $(LEXDIR)/tokenize.c \
		$(LEXDIR)/check_file_presence.c $(PARSDIR)/markers.c $(PARSDIR)/parser.c $(PARSDIR)/parsing_utils.c  \
		$(PARSDIR)/redirections.c $(PARSDIR)/check_command.c $(PARSDIR)/full_path_handler.c\
		$(EXECUTDIR)/open_fd.c \
		$(EXECUTDIR)/exec_multiple_cmds.c $(EXECUTDIR)/exec_single_cmd.c  $(EXECUTDIR)/here_doc.c \
		$(EXECUTDIR)/exec_utils1.c $(EXECUTDIR)/executor.c $(EXECUTDIR)/exec_utils2.c $(EXECUTDIR)/free.c \
		$(EXECUTDIR)/sig_handler.c $(EXPANDDIR)/expand_utils.c $(EXPANDDIR)/expander.c \
		$(BUILTINDIR)/builtin.c $(BUILTINDIR)/exit.c $(BUILTINDIR)/export_utils.c \
		$(BUILTINDIR)/export.c $(BUILTINDIR)/ft_cd.c $(BUILTINDIR)/ft_echo.c $(BUILTINDIR)/unset.c

CC          = cc

CFLAGS      = -Wall -Wextra -Werror -g
readline		= -lreadline -L /usr/local/Cellar/readline/8.1/lib -L /usr/local/Cellar/readline/8.1/include
sanitize    = -fsanitize=address -fno-omit-frame-pointer -fno-optimize-sibling-calls

RM          = rm -f

OBJS		= $(FILES:.c=.o)

all: $(NAME)

%.o : %.c
	@cc $(CFLAGS) -c $< -o $@
	 @echo "\033[1;32m.\c\033[35m"

$(NAME): $(LIBFT) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)  $(readline)
	@echo "\n"
	@echo "\033[1;36m _    _   ___    _  _   ___    ___    _  _   ___   _      _\033[0m"
	@echo "\033[1;36m|  \/  | |_ _|  | \| | |_ _|  / __|  | || | | __| | |    | | \033[0m"
	@echo "\033[1;36m| |\/| |  | |   | .\` |  | |   \__ \  | __ | | _|  | |__  | |__\033[0m"
	@echo "\033[1;36m|_|  |_| |___|  |_|\_| |___|  |___/  |_||_| |___| |____| |____|\033[0m"
                                                         
$(LIBFT) :
	@echo "Creating \033[0;33mminishell\033[0m"
	@make -sC ./libft

clean:
	@$(RM) $(OBJS)
	@make clean -sC ./libft

fclean: clean
	@$(RM) $(NAME)
	@make fclean -sC ./libft

re: fclean all

leaks:
	make && valgrind --suppressions=suppresser.txt \
	--leak-check=full --trace-children=yes \
	--show-leak-kinds=all --track-origins=yes \
	--track-fds=yes ./minishell

push: fclean
	git add .
	git commit -m "Updated on $(shell date +'%Y-%m-%d %H:%M:%S') by $(shell whoami) final"
	git push -u origin master

.PHONY: all clean fclean re
