# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: joushin <joushin@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/03 13:06:03 by joushin           #+#    #+#              #
#    Updated: 2022/09/06 20:47:10 by joushin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror
INC = -I include

NAME = so_long

SRCS_DIR = srcs

SRCS_BONUS_DIR = bsrcs

RM= rm -rf

SRCS =	$(SRCS_DIR)/main.c \
		$(SRCS_DIR)/key_hook.c \
		$(SRCS_DIR)/parse.c \
		$(SRCS_DIR)/so_long_utils.c \
		$(SRCS_DIR)/move.c

SRCS_BONUS = $(SRCS_BONUS_DIR)/main.c \

OBJS = $(SRCS:.c=.o)
OBJS_BONUS = $(SRCS_BONUS:.c=.o)

ifdef WITH_BONUS
	OBJECTS = $(OBJS_BONUS)
else
	OBJECTS = $(OBJS)
endif

all : $(NAME)

$(NAME) : $(OBJECTS)
	@make -C ./$(SRCS_DIR)/libft all
	@make -C ./mlx all
	$(CC) $(CFLAGS) -o $@ $^ -L ./$(SRCS_DIR)/libft -lft \
	-L ./mlx -lmlx -framework OpenGL -framework AppKit

%.o : %.c
	$(CC) $(CFLAGS) -o $@ -c $^ $(INC)

bonus :
	@make WITH_BONUS=1

clean:
	@make -C ./$(SRCS_DIR)/libft clean
	@make -C ./mlx clean
	$(RM) $(OBJS) $(OBJS_BONUS)

fclean: clean
	@make -C ./$(SRCS_DIR)/libft fclean
	$(RM) $(NAME)

re:
	make fclean
	make all

.PHONY: all clean fclean re bonus
