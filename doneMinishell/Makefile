# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: joushin <joushin@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/02 16:21:23 by joushin           #+#    #+#              #
#    Updated: 2022/11/26 22:04:55 by joushin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc
CFLAGS = -Wall -Werror -Wextra
DEBUG_FLAGS = -g3 -fsanitize=address
INCLUDE = -I./include -I/Users/joushin/.brew/opt/readline/include -I./src/libft/

LIBRARY = -L/Users/joushin/.brew/opt/readline/lib -lreadline -L$(LIBFT_DIR) -lft

LIBFT_DIR = ./$(SRC_DIR)/libft/
PARSE_DIR = ./$(SRC_DIR)/parse/
UTILS_DIR = ./$(SRC_DIR)/utils/
EXECVE_DIR = ./$(SRC_DIR)/execve/
INIT_DIR = $(PARSE_DIR)init/
TOK_TO_NODE_DIR = $(PARSE_DIR)tok_to_node/
TOKEN_DIR = $(PARSE_DIR)tokenize/
BUILTIN_DIR = ./$(SRC_DIR)/builtin/
SRC_DIR = src

SRCS =	$(SRC_DIR)/main.c					\
		$(SRC_DIR)/main_utils.c				\
		$(INIT_DIR)env.c					\
		$(INIT_DIR)merge_env.c				\
		$(INIT_DIR)env_utils.c				\
		$(INIT_DIR)merge_env_utils.c		\
		$(TOK_TO_NODE_DIR)check_syntax.c	\
		$(TOK_TO_NODE_DIR)node.c			\
		$(TOK_TO_NODE_DIR)node_case.c		\
		$(TOK_TO_NODE_DIR)node_utils.c		\
		$(TOK_TO_NODE_DIR)main_node_init.c	\
		$(TOKEN_DIR)tok_case_char_dollar.c	\
		$(TOKEN_DIR)tok_case_double_quotes.c\
		$(TOKEN_DIR)tok_case_quotes.c		\
		$(TOKEN_DIR)tok_case_special.c		\
		$(TOKEN_DIR)tok_optimize.c			\
		$(TOKEN_DIR)tok_utils.c				\
		$(TOKEN_DIR)token.c					\
		$(TOKEN_DIR)tok_case_env_utils.c	\
		$(UTILS_DIR)m_split.c				\
		$(UTILS_DIR)error.c 				\
		$(UTILS_DIR)utils.c					\
		$(UTILS_DIR)get_next_line_utils.c	\
		$(UTILS_DIR)get_next_line.c			\
		$(UTILS_DIR)memory_free.c			\
		$(EXECVE_DIR)exec_main.c			\
		$(EXECVE_DIR)exec_utils.c			\
		$(EXECVE_DIR)exec_first.c			\
		$(EXECVE_DIR)exec_init_and_heardoc.c\
		$(EXECVE_DIR)exec_last.c			\
		$(EXECVE_DIR)exec_pipe.c			\
		$(BUILTIN_DIR)builtin_main.c		\
		$(BUILTIN_DIR)cd.c					\
		$(BUILTIN_DIR)echo.c				\
		$(BUILTIN_DIR)env.c					\
		$(BUILTIN_DIR)exit.c				\
		$(BUILTIN_DIR)export.c				\
		$(BUILTIN_DIR)pwd.c					\
		$(BUILTIN_DIR)unset.c				\

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
