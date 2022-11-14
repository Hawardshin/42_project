# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: joushin <joushin@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/02 16:21:23 by joushin           #+#    #+#              #
#    Updated: 2022/11/14 15:36:10 by joushin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc
CFLAGS = -Wall -Werror -Wextra
DEBUG_FLAGS = -g3 -fsanitize=address
INCLUDE = -I./includes -I/Users/joushin/.brew/opt/readline/include

LIBRARY = -L/Users/joushin/.brew/opt/readline/lib -lreadline -L$(LIBFT_DIR) -lft
LIBFT_DIR = ./libft/

SRCS =	main.c \
		token.c \
		just_for_test.c \
		error.c \
		env.c	\

OBJS = $(SRCS:.c=.o)


all : $(NAME)

$(NAME)	:  $(OBJS)
	$(MAKE) -C $(LIBFT_DIR)
	$(CC) $(CFLAGS) $(DEBUG_FLAGS) -o $@ $^ $(LIBRARY)

%.o : %.c
	$(CC) $(CFLAGS) $(DEBUG_FLAGS) $(INCLUDE) -c -o $@ $^

clean	:
	$(MAKE) clean -C $(LIBFT_DIR)
	rm -f $(OBJS)

fclean	: clean
	$(MAKE) fclean -C $(LIBFT_DIR)
	rm -f $(NAME)

re		:
	$(MAKE) fclean
	$(MAKE) all

.PHONY: all clean fclean re
