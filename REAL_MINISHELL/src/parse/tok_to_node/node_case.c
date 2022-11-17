/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_case.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 22:52:43 by joushin           #+#    #+#             */
/*   Updated: 2022/11/17 13:30:13 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/node.h"
#include "../../../include/just_for_test.h"
#include "../../../include/utils.h"
#include "../../libft/libft.h"

void	make_hdoc_node(t_node *node, t_token **tmp_tok)
{
	t_infile_node	*infile;
	t_infile_node	*itmp;

	infile = malloc(sizeof (t_infile_node));
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
	infile->file = ft_strdup((*tmp_tok)->text);
	infile->is_heardoc = 1;
	if ((node->heardoc_node) == NULL)
		node->heardoc_node = infile;
	else
	{
		itmp = node->heardoc_node;
		while (itmp->hnext != NULL)
			itmp = itmp->hnext;
		itmp->hnext = infile;
		infile->hprev = itmp;
	}
}

void	make_ifile_node(t_node *node, t_token **tmp_tok)
{
	t_infile_node	*infile;
	t_infile_node	*itmp;

	infile = malloc(sizeof (t_infile_node));
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
	infile->file = ft_strdup((*tmp_tok)->text);
}

void	make_ofile_node(t_node *node, t_token **tmp_tok)
{
	t_outfile_node	*outfile;
	t_outfile_node	*otmp;

	outfile = malloc(sizeof (t_outfile_node));
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
	outfile->file = ft_strdup((*tmp_tok)->text);
	outfile->type = WRITE_TYPE;
}

void	make_rfile_node(t_node *node, t_token **tmp_tok)
{
	t_outfile_node	*outfile;
	t_outfile_node	*otmp;

	outfile = malloc(sizeof(t_outfile_node));
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
	outfile->file = ft_strdup((*tmp_tok)->text);
	outfile->type = APPEND_TYPE;
}

t_node	*make_pipe_node(t_token **tmp_tok, t_main_node *main_node)
{
	t_node	*node;

	main_node->cmd_num++;
	node = malloc(sizeof(t_node));
	node = ft_memset(node, 0, sizeof(t_node));
	node->idx = main_node->cmd_num;
	main_node->node_tail->next = node;
	node->prev = main_node->node_tail;
	main_node->node_tail = node;
	(*tmp_tok) = (*tmp_tok)->next;
	return (node);
}
