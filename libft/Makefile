CC = gcc
CFLAGS = -Wall -Werorr -Wextra

AR = ar
ARFLAGS = -rcs

NAME = libft.a

OBJECT=main.o

all : $(NAME)

$(NAME) : $(OBJS)
	    $(AR) $(ARFLAGS) $@ $^

%.o : %.c
	$(CC) $(CFLAGS) -c $^ -o $@ -I $(HEAD_DIR)

clean :
	rm -rf $(OBJS)

fclean : clean
	rm -rf $(NAME)

re : fclean all

.PHONY : all clean fclean re
