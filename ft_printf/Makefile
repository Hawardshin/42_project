# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: joushin <joushin@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/18 17:25:08 by joushin           #+#    #+#              #
#    Updated: 2022/07/19 14:34:39 by joushin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror -c

AR =ar
ARFLAGS = -rcs

NAME = libftprintf.a

SRCS = ft_printf.c

OBJS = $(SRCS:.c=.o)

INCLUDE = ./includes


all : $(NAME)

$(NAME) : $(OBJS)
		$(MAKE) -C ./libft all
		$(AR) $(ARFLAGS) $(NAME) $(OBJS)

%.o : %.c
		$(CC) $(CFLAGS) $< -o $@ -I $(INCLUDE)

clean :
		$(MAKE) -C ./libft clean
		rm -f $(OBJS)

fclean : clean
		$(MAKE) -C ./libft fclean
		rm -f $(NAME)

re :
	make fclean
	make all

.PHONY : all clean fclean re
