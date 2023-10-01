NAME = tokenizer
SRCS = ft_tokenizer.c
OBJS = $(SRCS:.c=.o)
AR = ar rcs
CC = cc -Wall -Wextra -Werror -I.

all: $(NAME)

$(NAME): $(OBJS)
	$(AR) lib$(NAME).a $(OBJS)
	ranlib lib$(NAME).a

%.o: %.c
	$(CC) -c $< -o $@

test: all
	./$(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f lib$(NAME).a

re: fclean all
