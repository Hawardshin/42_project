

#include "./include/node.h"
#include "./include/token.h"

void	Print_all_token(t_token	*tok)
{
	t_token *tmp;
	tmp = tok;
	for (int i=0; tok->next != NULL; i++)
	{
		printf("all_token : i:::::: %d\n text %s",i,tmp->text);
		tmp = tmp->next;
	}
}

void	print_src_char(t_readline *src)
{
	printf("char ::::: %c\n",see_char(src));
}
