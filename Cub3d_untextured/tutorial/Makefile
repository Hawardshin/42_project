# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: joushin <joushin@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/16 12:44:37 by joushin           #+#    #+#              #
#    Updated: 2023/01/16 19:30:03 by joushin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror -g3
INC = -I include

NAME = cub3d

SRCS_DIR = srcs

RM= rm -rf

SRCS =  rex1.c
		#ex6.c
		#ex5.c
		#ex4.c
		# ex3.c
		# ex2.c
		# ex1.c

OBJS = $(SRCS:.c=.o)

%.o : %.c
	$(CC) $(CFLAGS) -o $@ -c $^ $(INC)

all : $(NAME)

$(NAME) : $(OBJS)
	# @make -C ./$(SRCS_DIR)/libft all
	@make -C ../mlx all
	# $(CC) $(CFLAGS) -o $@ $^ -L ./$(SRCS_DIR)/libft -lft \
	# -L ../mlx -lmlx -framework OpenGL -framework AppKit
	$(CC) $(CFLAGS) -o $@ $^ -L ../mlx -lmlx -framework OpenGL -framework AppKit

clean:
	# @make -C ./$(SRCS_DIR)/libft clean
	@make -C ../mlx clean
	$(RM) $(OBJS)

fclean: clean
	# @make -C ./$(SRCS_DIR)/libft fclean
	$(RM) $(NAME)

re:
	make fclean
	make all

.PHONY: all clean fclean re
