# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: joushin <joushin@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/17 12:36:05 by joushin           #+#    #+#              #
#    Updated: 2022/08/17 15:05:08 by joushin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror

B_SRCS = 	push_swap_utils_bonus.c \
			main_bonus.c \
			command_bonus.c \
			command_double_bonus.c\
			command_utils_bonus.c \
			list_bonus.c \
			get_next_line.c \
			get_next_line_utils.c\
			checker.c

B_OBJS= $(B_SRCS:.c=.o)

NAME = ../checker

RM= rm -rf

%.o : %.c
	@$(CC) $(CFLAGS) -o $@ -c $^
all : $(NAME)

$(NAME) : $(B_OBJS)
	$(CC) $(CFLAGS) -o $@ $^ -L ../libft -lft

clean:
	$(RM) $(B_OBJS)

fclean: clean
	$(RM) $(NAME)

re:
	make fclean
	make all

.PHONY: all clean fclean re
