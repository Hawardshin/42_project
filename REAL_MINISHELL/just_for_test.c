

#include "./include/node.h"
#include "./include/token.h"

void	print_tok_type(int a)
{
	if (a == IO_TOK)
		printf("IO_TOK\n");
	if (a == ARGV_TOK)
		printf("ARGV_TOK\n");
	if (a == PIPE_TOK)
		printf("PIPE_TOK\n");
	if (a == SPACE_TOK)
		printf("SPACE_TOK\n");
	if (a == EOF_TOK)
		printf("EOF_TOK\n");
}

void	Print_a_token(t_token *tok)
{
	t_token *tmp;
	tmp = tok;
	printf("------PRINT_A_TOK-------\n");
	printf("text :%s;\ntok_type: ",tmp->text);
	print_tok_type(tmp->tok_type);
	printf("------PRINT_A_TOK-------\n");
}

void	Print_all_token(t_token	*tok)
{
	t_token *tmp;
	tmp = tok;
	printf("------PRINT_ALL_TOK-------\n");
	for (int i=0; (tmp != NULL) && (tmp->tok_type != EOF_TOK); i++)
	{
		printf("------------tok---------------\n");
		printf("idx :%d|\ntext :%s;\ntok_type: ",i,tmp->text);
		print_tok_type(tmp->tok_type);
		tmp = tmp->next;
		printf("------------tok---------------\n");
	}
	printf("------PRINT_ALL_TOK-------\n");
}

void	print_src_char(t_readline *src)
{
	printf("src->char ::::: %c;\n",see_char(src));
}
