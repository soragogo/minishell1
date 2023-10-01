NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror -Iincludes

SRC = src/main.c \
      src/ft_system.c \
      src/ft_chdir.c \
	  src/signal_handler.c

OBJS = $(SRC:.c=.o)
OBJS := $(OBJS:src/%=obj/%)
RLDIR = $(shell brew --prefix readline)

LIBFTDIR = libft
LIBFT = $(LIBFTDIR)/libft.a
LIBFT_INCLUDE = -I$(LIBFTDIR)
LIBFT_LINK = -L$(LIBFTDIR) -lft 


all: $(NAME)

$(NAME): $(OBJS)
	@echo "set echo-control-characters off" > ~/.inputrc
	@make -C $(LIBFTDIR)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT_LINK) -lreadline -L $(RLDIR)/lib

obj/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@ -I $(RLDIR)/include $(LIBFT_INCLUDE)

$(OBJS): $(SRC)

$(LIBFT):
	make -C $(LIBFTDIR)

clean:
	rm -rf $(OBJS)
	make -C $(LIBFTDIR) clean

fclean: clean
	rm -rf $(NAME)
	make -C $(LIBFTDIR) fclean

re: fclean all

