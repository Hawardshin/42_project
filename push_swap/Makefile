# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: joushin <joushin@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/06 19:02:02 by joushin           #+#    #+#              #
#    Updated: 2022/08/17 13:46:04 by joushin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror

DIR = ./push_swap_mandatory

SRCS = 	$(DIR)/push_swap_utils.c \
		$(DIR)/main.c \
		$(DIR)/command.c \
		$(DIR)/command_double.c\
		$(DIR)/command_utils.c \
		$(DIR)/div_stack.c \
		$(DIR)/list.c \
		$(DIR)/three_argv.c \
		$(DIR)/sort.c \
		$(DIR)/sort_utils.c\

OBJS= $(SRCS:.c=.o)

NAME = push_swap

RM= rm -rf

%.o : %.c
	@$(CC) $(CFLAGS) -o $@ -c $^

all : $(NAME)

ifdef BONUS
	make -C ./push_swap_bonus/ all
else
endif

$(NAME) : $(OBJS)
	make -C ./libft all
	$(CC) $(CFLAGS) -o $@ $^ -L ./libft -lft

bonus :
	make BONUS=1

clean:
	make -C ./libft clean
	make -C ./push_swap_bonus clean
	$(RM) $(OBJS)

fclean: clean
	make -C ./libft fclean
	make -C ./push_swap_bonus fclean
	$(RM) $(NAME)

re:
	make fclean
	make all

.PHONY: all clean fclean re bonus
