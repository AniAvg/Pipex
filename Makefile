NAME = pipex

SRCS = ./sources/main.c ./sources/helper_funct1.c ./sources/helper_funct2.c

OBJS = $(SRCS:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror #-g3 -fsanitize=address

LIBFT = ./libft/libft.a

all : $(NAME)

$(NAME) : $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) -I ./includes -I ./libft  $(OBJS) -L ./libft -lft -o $(NAME)

$(LIBFT) :
	make -C ./libft all

%.o: %.c
	$(CC) $(CFLAGS) -I./includes -I./libft -c -o $@ $<

clean :
	make -C ./libft clean
	rm -f $(OBJS)

fclean : clean
	make -C ./libft fclean
	rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re
