# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: joushin <joushin@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/19 21:08:50 by joushin           #+#    #+#              #
#    Updated: 2022/09/01 17:41:33 by joushin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


CC = cc
CFLAGS = -Wall -Wextra -Werror
INC = -I include

NAME = pipex

RM= rm -rf

SRCS =	srcs/main.c \
		srcs/parse.c \
		srcs/m_split.c \
		srcs/pipe_utils.c \
		srcs/pipe.c \


SRCS_BONUS =	bonus_srcs/main_bonus.c \
				bonus_srcs/parse_bonus.c \
				bonus_srcs/m_split_bonus.c \
				bonus_srcs/pipe_utils_bonus.c \
				bonus_srcs/pipe_bonus.c \
				bonus_srcs/get_next_line.c \
				bonus_srcs/get_next_line_utils.c \


OBJS = $(SRCS:.c=.o)
OBJS_BONUS = $(SRCS_BONUS:.c=.o)

ifdef WITH_BONUS
	OBJECTS = $(OBJS_BONUS)
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
	$(RM) $(OBJS) $(OBJS_BONUS)

fclean: clean
	@make -C ./srcs/libft fclean
	$(RM) $(NAME)

re:
	make fclean
	make all

.PHONY: all clean fclean re bonus
