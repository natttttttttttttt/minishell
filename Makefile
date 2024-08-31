NAME = minishell
CC = cc 
CFLAGS = -g 
LDFLAGS = -lreadline -lncurses  
RM = rm -rf

SRCS = main.c lst_utils.c utils.c parsing.c

OBJS = $(SRCS:.c=.o)

$(NAME): $(OBJS) 
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LDFLAGS) 

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

fclean: clean
	$(RM) $(NAME)

clean:
	$(RM) $(OBJS)

re: fclean all

.PHONY: all clean fclean re