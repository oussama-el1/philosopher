CC = cc
CFLAGS = -Wall -Wextra -Werror
SRCS = death.c \
       forks.c \
	   ft_atoi.c \
	   ft_itoa.c \
	   ft_strjoin.c \
	   init.c \
	   main.c \
	   process.c \
	   utils.c
OBJS = $(SRCS:.c=.o)
HEADER = philo_bonus.h
NAME = philo_bonus

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
