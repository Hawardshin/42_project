# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: joushin <joushin@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/24 14:07:52 by tson              #+#    #+#              #
#    Updated: 2023/01/22 18:11:01 by joushin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
CC = cc
CFLAGS = -Wall -Werror -Wextra
SRCS = srcs/main.c\
	   srcs/keyboard.c\
	   srcs/check_file.c\
	   srcs/setting_map.c\
	   srcs/setting_tex_color.c\
	   srcs/setting_tex_color_utils.c\
	   srcs/init.c\
	   srcs/rendering.c\
	   srcs/rendering_utils.c\
	   srcs/calculate.c\
	   srcs/utils.c \
	   srcs/setting_map_init.c \
	   srcs/setting_map_utils.c \

OBJS = ${SRCS:.c=.o}

all : $(NAME)

$(NAME) : $(OBJS)
	@make -C ./srcs/libft all
	@make -C ./mlx all
	$(CC) $(CFLAGS) -o $@ $^ -L ./mlx -lmlx -framework OpenGL -framework AppKit srcs/libft/libft.a

%.o : %.c
	$(CC) $(CFLAGS) -o $@ -c $^

clean :
	@make -C ./srcs/libft clean
	@make -C ./mlx clean
	rm -f $(OBJS)

fclean : clean
	@make -C ./srcs/libft fclean
	rm -f $(OBJS) $(NAME)

re : fclean all

.PHONY : all clean fclean re
