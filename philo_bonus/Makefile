CC = cc
CFLAGS = -Wall -Wextra -Werror
SRCS = bonus_helpers.c \
       bonus_helpers2.c \
       init_helpers.c \
       main.c \
       routine.c \
       routine_helpers.c 
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
