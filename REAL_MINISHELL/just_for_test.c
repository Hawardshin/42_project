

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
	for (int i=0; (tmp != NULL); i++)
	{
		printf("------------tok---------------\n");
		printf("idx :%d|\ntext_len :%d\ntext :%s;\ntok_type: ",i,tmp->text_len,tmp->text);
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

void	print_node_type(int a)
{
	printf("node type :: ");
	if (a == HERE_DOC_NODE)
		printf("HERE_DOC_NODE\n");
	if (a == APPEND_NODE)
		printf("APPEND_NODE\n");
	if (a == OPEN_NODE)
		printf("OPEN_NODE\n");
	if (a == WRITE_NODE)
		printf("WRITE_NODE\n");
	if (a == 0)
		printf("CMD_NODE\n");
}

void	print_all_node(t_main_node *node)
{
	t_node *tmp;

	tmp = node->node_head;
	printf("------PRINT_ALL_NODE-------\n");
	for (int i=0; (tmp != NULL); i++)
	{
		printf("------------node---------------\n");
		printf("node idx : %d\n", i);
		if (tmp->node_type == 0)
		{
			print_node_type(tmp->node_type);
			for (int j=0; tmp->cmd[j]!= NULL ;j++)
				printf("cmd[%d] : %s;\n", j, tmp->cmd[j]);
			printf("cmd path: %s;\n",tmp->cmd_path[0]);
		}
		else
		{
			print_node_type(tmp->node_type);
			printf("file:: %s;\n",tmp->file);
		}
		tmp = tmp->next;
		printf("------------node---------------\n");
	}
	printf("------PRINT_ALL_NODE-------\n");
}
