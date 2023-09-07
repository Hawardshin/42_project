/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_case.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 22:52:43 by joushin           #+#    #+#             */
/*   Updated: 2022/11/26 22:14:51 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "node.h"
#include "utils.h"
#include "libft.h"

void	make_ifile_node(t_node *node, t_token **tmp_tok)
{
	t_infile_node	*infile;
	t_infile_node	*itmp;

	infile = malloc(sizeof (t_infile_node));
	if (!infile)
		print_error(0, NULL);
	ft_memset(infile, 0, sizeof(t_infile_node));
	if ((node->infile_node) == NULL)
		node->infile_node = infile;
	else
	{
		itmp = node->infile_node;
		while (itmp->next != NULL)
			itmp = itmp->next;
		itmp->next = infile;
		infile->prev = itmp;
	}
	(*tmp_tok) = (*tmp_tok)->next;
	infile->file = ft_mstrdup((*tmp_tok)->text);
}

void	make_ofile_node(t_node *node, t_token **tmp_tok)
{
	t_outfile_node	*outfile;
	t_outfile_node	*otmp;

	outfile = malloc(sizeof (t_outfile_node));
	if (!outfile)
		print_error(0, NULL);
	ft_memset(outfile, 0, sizeof(t_outfile_node));
	if ((node->outfile_node) == NULL)
		node->outfile_node = outfile;
	else
	{
		otmp = node->outfile_node;
		while (otmp->next != NULL)
			otmp = otmp->next;
		otmp->next = outfile;
		outfile->prev = otmp;
	}
	(*tmp_tok) = (*tmp_tok)->next;
	outfile->file = ft_mstrdup((*tmp_tok)->text);
	outfile->type = WRITE_TYPE;
}

void	make_rfile_node(t_node *node, t_token **tmp_tok)
{
	t_outfile_node	*outfile;
	t_outfile_node	*otmp;

	outfile = malloc(sizeof(t_outfile_node));
	if (!outfile)
		print_error(0, NULL);
	ft_memset(outfile, 0, sizeof(t_outfile_node));
	if ((node->outfile_node) == NULL)
		node->outfile_node = outfile;
	else
	{
		otmp = node->outfile_node;
		while (otmp->next != NULL)
			otmp = otmp->next;
		otmp->next = outfile;
		outfile->prev = otmp;
	}
	(*tmp_tok) = (*tmp_tok)->next;
	outfile->file = ft_mstrdup((*tmp_tok)->text);
	outfile->type = APPEND_TYPE;
}

t_node	*make_pipe_node(t_token **tmp_tok, t_main_node *main_node)
{
	t_node	*node;

	main_node->cmd_num++;
	node = malloc(sizeof(t_node));
	if (!node)
		print_error(0, NULL);
	node = ft_memset(node, 0, sizeof(t_node));
	node->idx = main_node->cmd_num;
	main_node->node_tail->next = node;
	node->prev = main_node->node_tail;
	main_node->node_tail = node;
	(*tmp_tok) = (*tmp_tok)->next;
	return (node);
}
