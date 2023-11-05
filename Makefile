
NAME	=	minishell

SRC_DIR			=	src
TOKENIZER_DIR	=	tokenizer
BUILTIN_DIR		=	builtin
EXEC_DIR 		=	exec
UTIL_DIR		=	utils
OBJ_DIR			=	obj
ENV_DIR			=	env

LIBFTDIR = libft
LIBFT = $(LIBFTDIR)/libft.a
LIBFT_INCLUDE = -I$(LIBFTDIR)
LIBFT_LINK = -L$(LIBFTDIR) -lft

SRCS =	main.c

ENV_SRCS	=		create_map.c \
					env_command.c \
					env_utils.c \
					env.c

E_SRCS		=		exec_builtin.c \
					exec.c \
					heredoc.c \
					pipe.c \
					readline.c \
					redir_utils.c \
					redir.c \
					search_path.c

T_SRCS		=		bracket_error.c \
					categorize_tokens.c \
					create_commandset.c \
					free_commandset.c \
					import_command.c \
					parser.c \
					redirection.c \
					syntax_error_handling.c \
					token_utils.c \
					tokenizer.c \
					clean_tokenlist.c

B_SRCS		=		builtin_chdir.c \
					builtin_echo.c \
					builtin_env.c \
					builtin_exit.c \
					builtin_export.c \
					builtin_pwd.c \
					builtin_unset.c \
					chdir_utils.c

U_SRCS		=	error.c \
				expand_env.c \
				expand_env_utils.c \
				quote.c \
				signal_handler.c

OBJS		=	$(addprefix $(OBJ_DIR)/,$(SRCS:.c=.o)) \
				$(addprefix $(OBJ_DIR)/,$(E_SRCS:.c=.o)) \
				$(addprefix $(OBJ_DIR)/,$(T_SRCS:.c=.o)) \
				$(addprefix $(OBJ_DIR)/,$(B_SRCS:.c=.o)) \
				$(addprefix $(OBJ_DIR)/,$(U_SRCS:.c=.o)) \
				$(addprefix $(OBJ_DIR)/,$(ENV_SRCS:.c=.o))

RLDIR = $(shell brew --prefix readline)
CC		=	cc

ifeq ($(MAKECMDGOAL), debug)
	CC += -g -fsanitize=address
endif

CFLAGS	=	-Wall -Wextra -Werror -I./readline
ifeq ($(MAKECMDGOALS), debug)
	CFLAGS += -g -fsanitize=thread
endif
all: $(NAME)

$(NAME): $(OBJS)
	@echo "set echo-control-characters off" > ~/.inputrc
	@echo "set enable-bracketed-paste off" >> ~/.inputrc
	@mkdir -p $(OBJ_DIR)
	@make -C $(LIBFTDIR)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT_LINK) -lreadline -L$(RLDIR)/lib -Iincludes -I $(RLDIR)/include

obj/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@ -I $(RLDIR)/include $(LIBFT_INCLUDE)

$(OBJ_DIR)/%.o: $(TOKENIZER_DIR)/%.c
	@ $(CC) $(CFLAGS) -c -o $@ $<

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@ -I $(RLDIR)/include $(LIBFT_INCLUDE)


$(OBJ_DIR)/%.o: $(EXEC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@ -I $(RLDIR)/include $(LIBFT_INCLUDE)

$(OBJ_DIR)/%.o: $(BUILTIN_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@ -I $(RLDIR)/include $(LIBFT_INCLUDE)

$(OBJ_DIR)/%.o: $(UTIL_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@ -I $(RLDIR)/include $(LIBFT_INCLUDE)

$(OBJ_DIR)/%.o: $(TOKENIZER_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@ -I $(RLDIR)/include $(LIBFT_INCLUDE)

$(OBJ_DIR)/%.o: $(ENV_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@ -I $(RLDIR)/include $(LIBFT_INCLUDE)

$(LIBFT):
	make -C $(LIBFTDIR)

clean:
	rm -rf $(OBJS)
	make -C $(LIBFTDIR) clean

fclean: clean
	rm -rf $(NAME)
	make -C $(LIBFTDIR) fclean

re: fclean all

debug: re

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
