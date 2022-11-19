# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: joushin <joushin@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/02 16:21:23 by joushin           #+#    #+#              #
#    Updated: 2022/11/19 13:19:09 by joushin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc
CFLAGS = -Wall -Werror -Wextra
DEBUG_FLAGS = -g3 -fsanitize=address
INCLUDE = -I./includes -I/Users/joushin/.brew/opt/readline/include

LIBRARY = -L/Users/joushin/.brew/opt/readline/lib -lreadline -L$(LIBFT_DIR) -lft

LIBFT_DIR = ./$(SRC_DIR)/libft/
PARSE_DIR = ./$(SRC_DIR)/parse/
UTILS_DIR = ./$(SRC_DIR)/utils/
EXECVE_DIR = ./$(SRC_DIR)/execve/
INIT_DIR = $(PARSE_DIR)init/
TOK_TO_NODE_DIR = $(PARSE_DIR)tok_to_node/
TOKEN_DIR = $(PARSE_DIR)tokenize/
SRC_DIR = src

SRCS =	$(SRC_DIR)/main.c					\
		just_for_test.c						\
		$(INIT_DIR)env.c					\
		$(TOK_TO_NODE_DIR)check_syntax.c	\
		$(TOK_TO_NODE_DIR)node.c			\
		$(TOK_TO_NODE_DIR)node_case.c		\
		$(TOK_TO_NODE_DIR)node_utils.c		\
		$(TOK_TO_NODE_DIR)main_node_init.c	\
		$(TOKEN_DIR)tok_case_one.c			\
		$(TOKEN_DIR)tok_case_two.c			\
		$(TOKEN_DIR)tok_case_three.c		\
		$(TOKEN_DIR)tok_case_four.c			\
		$(TOKEN_DIR)tok_optimize.c			\
		$(TOKEN_DIR)tok_utils.c				\
		$(TOKEN_DIR)token.c					\
		$(UTILS_DIR)m_split.c				\
		$(UTILS_DIR)error.c 				\
		$(UTILS_DIR)utils.c					\
		$(UTILS_DIR)get_next_line_utils.c	\
		$(UTILS_DIR)get_next_line.c			\
		$(EXECVE_DIR)exec.c					\
		$(EXECVE_DIR)exec_utils.c			\

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
