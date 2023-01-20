# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: joushin <joushin@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/16 12:44:37 by joushin           #+#    #+#              #
#    Updated: 2023/01/20 13:46:29 by joushin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror -g3 -fsanitize=address
INC = -I include

NAME = cub3d

SRCS_DIR = srcs

RM= rm -rf

SRCS =  $(SRCS_DIR)/main.c \
		$(SRCS_DIR)/utils.c \
		$(SRCS_DIR)/raycasting.c\
		$(SRCS_DIR)/key_hook.c\
		$(SRCS_DIR)/parse.c\
		# $(SRCS_DIR)/draw_map.c

OBJS = $(SRCS:.c=.o)

%.o : %.c
	$(CC) $(CFLAGS) -o $@ -c $^ $(INC)

all : $(NAME)

$(NAME) : $(OBJS)
	@make -C ./$(SRCS_DIR)/libft all
	@make -C ./mlx all
	$(CC) $(CFLAGS) -o $@ $^ -L ./$(SRCS_DIR)/libft -lft \
	-L ./mlx -lmlx -framework OpenGL -framework AppKit

clean:
	@make -C ./$(SRCS_DIR)/libft clean
	@make -C ./mlx clean
	$(RM) $(OBJS)

fclean: clean
	@make -C ./$(SRCS_DIR)/libft fclean
	$(RM) $(NAME)

re:
	make fclean
	make all

.PHONY: all clean fclean re
