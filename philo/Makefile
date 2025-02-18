CC = cc
CFLAGS = -Wall -Wextra -Werror
SRCS = main.c \
	   helpers.c
OBJS = $(SRCS:.c=.o)
HEADER = philo.h
NAME = philo

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
