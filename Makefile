# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anavagya <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/22 12:16:28 by anavagya          #+#    #+#              #
#    Updated: 2025/03/22 12:53:39 by anavagya         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

SRCS = ./sources/*.c

OBJS = $(SRCS:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror

all : $(NAME)

$(NAME) : $(LIBFT) $(OBJS)
	$(CC) $(LIBFT) $(OBJS) -o $(NAME)

$(LIBFT) :
	make -C ./libft/ all

%.o: %.c $(NAME).h
	@$(CC) $(FLAGS) -c -o $@ $<

clean :
	make -C ./libft/ clean
	rm -f $(OBJS)

fclean : clean
	make -C ./libft/ fclean
	rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re
