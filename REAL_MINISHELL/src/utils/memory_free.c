/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 20:47:46 by joushin           #+#    #+#             */
/*   Updated: 2022/11/26 20:14:49 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/utils.h"
#include "../../include/node.h"

static void	path_pipe_free(t_main_node *px)
{
	int	i;

	i = 0;
	while (px->path && px->path[i])
		my_free((void **)&(px->path[i++]));
	my_free((void **)&(px->path));
	i = 0;
	while (i < px->cmd_num - 1)
		free((void **)px->pipefd[i++]);
}

void	ft_end_free(t_main_node *px)
{
	t_node	*node;
	t_node	*tmp;
	int		i;

	unlink(".tmp");
	node = px->node_head;
	while (node)
	{
		i = 0;
		tmp = node;
		node = node->next;
		while (tmp->cmd && tmp->cmd[i])
			my_free((void **)&(tmp ->cmd[i++]));
		if (tmp->cmd)
			my_free((void **)tmp->cmd);
		if (tmp->cmd_path[0])
			my_free((void **)&(tmp->cmd_path[0]));
		if (tmp)
			my_free((void **)&tmp);
	}
	path_pipe_free(px);
}

void	tok_clean(t_main_token	*mtok)
{
	t_token	*tok;
	t_token	*tmp;
	int		i;

	tok = mtok->start_token;
	while (tok)
	{
		i = 0;
		tmp = tok->next;
		if (tok && tok->tok_type != SPACE_TOK && tok->text && *(tok->text))
			my_free((void **) &tok->text);
		if (tok)
			my_free((void **) &tok);
		tok = tmp;
	}
	my_free((void **)&mtok);
}
