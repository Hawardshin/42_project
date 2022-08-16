# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: joushin <joushin@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/06 19:02:02 by joushin           #+#    #+#              #
#    Updated: 2022/08/16 16:42:52 by joushin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror

SRCS = 	push_swap_utils.c \
		main.c \
		command.c \
		command_double.c\
		command_utils.c \
		div_stack.c \
		list.c \
		three_argv.c \
		sort.c \
		sort_utils.c\


OBJS= $(SRCS:.c=.o)

NAME = push_swap

RM= rm -rf

%.o : %.c
	@$(CC) $(CFLAGS) -o $@ -c $^
all : $(NAME)

$(NAME) : $(OBJS)
	make -C ./libft all
	$(CC) $(CFLAGS) -o $@ $^ -L ./libft -lft

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
