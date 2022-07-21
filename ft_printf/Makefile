# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: joushin <joushin@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/18 17:25:08 by joushin           #+#    #+#              #
#    Updated: 2022/07/21 16:44:45 by joushin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC=cc
CFLAGS= -Wall -Werror -Wextra

SRCS = ft_printf.c ft_printf_utils1.c ft_printf_utils2.c
OBJS= $(SRCS:.c=.o)

INC = ./includes

NAME=libftprintf.a

AR = ar
ARFLAGS = -rcs

RM= rm -rf

%c : %o
	$(CC) $(CFLAGS) $^ -o $@ -I $(INC)
all: $(NAME)

$(NAME): $(OBJS)
	make -C ./libft all
	cp libft/libft.a $(NAME)
	$(AR) $(ARFLAGS) $(NAME) $(OBJS)

clean:
	make -C ./libft clean
	$(RM) $(OBJS)

fclean: clean
	make -C ./libft fclean
	$(RM) $(NAME)

re:
	make fclean
	make all

.PHONY: all clean fclean re
