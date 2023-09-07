/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 09:18:42 by joushin           #+#    #+#             */
/*   Updated: 2022/11/26 22:14:51 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "node.h"
#include "utils.h"
#include "libft.h"

static void	make_argv_node(t_node *node, t_token **tmp_tok, \
									t_main_node *main_node)
{
	int		i;
	t_token	*ttmp;

	i = 0;
	ttmp = (*tmp_tok);
	node->cmd_path[0] = find_path((*tmp_tok)->text, main_node);
	ttmp = (*tmp_tok);
	while (ttmp && ttmp->tok_type == ARGV_TOK)
	{
		i++;
		ttmp = ttmp->next;
	}
	node ->cmd = malloc(sizeof (char *) * (i + 1));
	if (!(node->cmd))
		print_error(0, NULL);
	i = 0;
	while ((*tmp_tok) && (*tmp_tok)->tok_type == ARGV_TOK)
	{
		node->cmd[i] = ft_mstrdup((*tmp_tok)->text);
		i++;
		(*tmp_tok) = (*tmp_tok)->next;
	}
	node->cmd[i] = NULL;
}

static void	io_noding(t_token **tmp_tok, t_node *node)
{
	if (ft_strncmp((*tmp_tok)->text, "<<", 2) == 0)
		make_hdoc_node(node, tmp_tok);
	else if (ft_strncmp((*tmp_tok)->text, "<", 1) == 0)
		make_ifile_node(node, tmp_tok);
	else if (ft_strncmp((*tmp_tok)->text, ">", 1) == 0)
		make_ofile_node(node, tmp_tok);
	else if (ft_strncmp((*tmp_tok)->text, ">>", 2) == 0)
		make_rfile_node(node, tmp_tok);
	(*tmp_tok) = (*tmp_tok)->next;
}

t_main_node	*make_tok_to_node(t_main_token *tok)
{
	t_main_node	*main_node;
	t_token		*tmp_tok;
	t_node		*node;

	main_node = main_init(&tok, &tmp_tok, &node);
	while (tmp_tok)
	{
		if (tmp_tok-> tok_type == ARGV_TOK && (tmp_tok->tok_type) != DELETE_TOK)
			make_argv_node(node, &tmp_tok, main_node);
		else if (tmp_tok-> tok_type == IO_TOK)
			io_noding(&tmp_tok, node);
		else if (tmp_tok->tok_type == PIPE_TOK)
			node = make_pipe_node(&tmp_tok, main_node);
		else
			tmp_tok = tmp_tok->next;
	}
	pipe_init(main_node);
	return (main_node);
}
