CC = cc
CFLAGS = -Wall -Wextra -Werror -fsanitize=thread -g
SRCS = main.c \
	   helpers.c \
	   helpers2.c \
	   philo_helpers.c \
	   routine_helpers.c \
	   routine.c \
	   utils.c
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
