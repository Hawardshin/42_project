# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: joushin <joushin@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/19 21:08:50 by joushin           #+#    #+#              #
#    Updated: 2022/08/24 18:55:55 by joushin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


CC = cc
CFLAGS = -Wall -Wextra -Werror
INC = -I include

NAME = pipex
LIBFT = srcs/libft/libft.a

RM= rm -rf

SRCS =	srcs/main.c \
		srcs/check_error.c \

SRCS_BONUS = \


OBJS = $(SRCS:.c=.o)
OBJS_BONUS = $(SRCS_BONUS:.c=.o)

ifdef WITH_BONUS
	OBJECTS = $(OBJS) $(OBJS_BONUS)
else
	OBJECTS = $(OBJS)
endif

all : $(NAME)

$(NAME) : $(OBJECTS)
	@make -C ./srcs/libft all
	$(CC) $(CFLAGS) -o $@ $^ -L ./srcs/libft -lft

%.o : %.c
	$(CC) $(CFLAGS) -o $@ -c $^ $(INC)

bonus :
	@make WITH_BONUS=1

clean:
	@make -C ./srcs/libft clean
	$(RM) $(OBJS)

fclean: clean
	@make -C ./srcs/libft fclean
	$(RM) $(NAME)

re:
	make fclean
	make all

.PHONY: all clean fclean re bonus
