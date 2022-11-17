#include "./include/node.h"

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

void	print_all_io(t_node *node)
{
	t_infile_node *hnode = node->heardoc_node;
	t_infile_node *inode = node->infile_node;
	t_outfile_node *onode = node->outfile_node;
	for (int i=0; hnode!=NULL;i++)
	{
		printf("idx :: %d hear_doc_node(<<) :: %s;\n",i,hnode->file);
		hnode = hnode->hnext;
	}
	for (int i=0; inode!=NULL;i++)
	{
		if (inode->is_heardoc == 0)
		printf("idx :: %d infile_node(<) :: %s;\n",i,inode->file);
		else if  (inode->is_heardoc == 1)
			printf("idx :: %d infile_node(<<) :: %s;\n",i,inode->file);
		inode = inode->next;
	}
	for (int i=0; onode!= NULL;i++)
	{
		if (onode->type == APPEND_TYPE)
			printf("outfile_node(>>)");
		else if (onode->type == WRITE_TYPE)
			printf("outfile_node(>)");
		printf("idx :: %d outfile_node :: %s;\n",i,onode->file);
		onode = onode->next;
	}
}
void	print_all_node(t_main_node *node)
{
	t_node *tmp;

	tmp = node->node_head;
	printf("------PRINT_ALL_NODE-------\n");
	for (int i=0; tmp != NULL; i++)
	{
		printf("------------node---------------\n");
		printf("node idx : %d\n", i);
		for (int j=0; tmp->cmd && tmp->cmd[j]!= NULL ;j++)
				printf("cmd[%d] : %s;\n", j, tmp->cmd[j]);
		printf("cmd path: %s;\n",tmp->cmd_path[0]);
		print_all_io(tmp);
		tmp = tmp->next;
		printf("------------node---------------\n");
	}
	printf("------PRINT_ALL_NODE-------\n");
}
