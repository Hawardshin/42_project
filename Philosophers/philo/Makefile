# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: joushin <joushin@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/19 11:05:58 by joushin           #+#    #+#              #
#    Updated: 2022/12/24 22:48:17 by joushin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror
INC = -I include

NAME = philo

RM= rm -rf

SRCS =	main.c \
		message.c \
		monitoring.c \
		philo_act.c \
		utils.c \

OBJS = $(SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o : %.c
	$(CC) $(CFLAGS) -o $@ -c $^ $(INC)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re:
	make fclean
	make all

.PHONY: all clean fclean re bonus

