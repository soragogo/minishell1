LIBFTDIR = libft
LIBFT = $(LIBFTDIR)/libft.a
LIBFT_INCLUDE = -I$(LIBFTDIR)
LIBFT_LINK = -L$(LIBFTDIR) -lft

# TOKENDIR = tokenizer
# TOKEN = $(TOKENDIR)/libtokenizer.a
# TOKEN_INCLUDE = -I$(TOKENDIR)
# TOKEN_LINK = -L$(TOKENDIR) -ltokenizer


NAME	=	minishell

SRC_DIR			=	src
TOKENIZER_DIR	=	tokenizer
BUILTIN_DIR		=	builtin
EXEC_DIR 		=	exec
UTIL_DIR		=	utils
OBJ_DIR			=	obj

SRCS =	main.c

E_SRCS		=		exec.c \
					readline.c \
					redir.c \
					search_path.c

T_SRCS		=		ft_parser.c \
					ft_redirection.c \
					ft_tests.c \
					ft_tokenizer.c \
					getpath.c \
					syntax_error_handling.c \
					utils.c

B_SRCS		=		builtin_chdir.c \
					builtin_echo.c \
					builtin_env.c \
					builtin_exit.c \
					builtin_export.c \
					builtin_pwd.c \
					builtin_unset.c

U_SRCS		=	env.c \
				error.c \
				expand_env.c \
				ft_system.c \
				quote.c \
				signal_handler.c \
				utils.c

# LIBFT_DIR	=	./libft
# LIBFT		=	$(LIBFTDIR)/libft.a

OBJS		=	$(addprefix $(OBJ_DIR)/,$(SRCS:.c=.o)) \
				$(addprefix $(OBJ_DIR)/,$(E_SRCS:.c=.o)) \
				$(addprefix $(OBJ_DIR)/,$(T_SRCS:.c=.o)) \
				$(addprefix $(OBJ_DIR)/,$(B_SRCS:.c=.o)) \
				$(addprefix $(OBJ_DIR)/,$(U_SRCS:.c=.o))

RLDIR = $(shell brew --prefix readline)
CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror -I./readline

all: $(NAME)

$(NAME): $(OBJS)
	@echo "set echo-control-characters off" > ~/.inputrc
	@mkdir -p $(OBJ_DIR)
	@make -C $(LIBFTDIR)
	@make -C $(TOKENDIR)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT_LINK) -lreadline -L$(RLDIR)/lib

obj/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@ -I $(RLDIR)/includes $(LIBFT_INCLUDE) $(TOKEN_INCLUDE)


$(OBJ_DIR)/%.o: $(TOKENIZER_DIR)/%.c
	@ $(CC) $(CFLAGS) -c -o $@ $<

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@ -I $(RLDIR)/includes $(LIBFT_INCLUDE) $(TOKEN_INCLUDE)


$(OBJ_DIR)/%.o: $(EXEC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@ -I $(RLDIR)/includes $(LIBFT_INCLUDE) $(TOKEN_INCLUDE)

$(OBJ_DIR)/%.o: $(BUILTIN_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@ -I $(RLDIR)/includes $(LIBFT_INCLUDE) $(TOKEN_INCLUDE)

$(OBJ_DIR)/%.o: $(UTIL_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@ -I $(RLDIR)/includes $(LIBFT_INCLUDE) $(TOKEN_INCLUDE)

$(OBJ_DIR)/%.o: $(TOKENIZER_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@ -I $(RLDIR)/includes $(LIBFT_INCLUDE) $(TOKEN_INCLUDE)

$(LIBFT):
	make -C $(LIBFTDIR)
$(TOKEN):
	make -C $(TOKENDIR)

clean:
	rm -rf $(OBJS)
	make -C $(LIBFTDIR) clean
	make -C $(TOKENDIR) clean

fclean: clean
	rm -rf $(NAME)
	make -C $(LIBFTDIR) fclean
	make -C $(TOKENDIR) fclean

re: fclean all

# all: $(NAME)

# $(NAME): $(OBJS) $(LIBFT)
# 	@ $(CC) $(CFLAGS) -o minishell $(OBJS) -lreadline

# $(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
# 	@ mkdir -p $(OBJ_DIR)
# 	@ $(CC) $(CFLAGS) -c -o $@ $<

# $(OBJ_DIR)/%.o: $(TOKENIZER_DIR)/%.c
# 	@ $(CC) $(CFLAGS) -c -o $@ $<

# $(LIBFT):
# 	$(MAKE) -C $(LIBFT_DIR)


# re: fclean all
