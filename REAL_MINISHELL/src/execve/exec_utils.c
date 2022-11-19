/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 12:42:42 by joushin           #+#    #+#             */
/*   Updated: 2022/11/19 13:18:05 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/node.h"
#include "../../include/just_for_test.h"
#include "../../include/utils.h"
#include "../libft/libft.h"

void	ft_all_close(t_main_node *px, int idx, int bef)
{
	int	i;

	i = 0;
	while (i + 1 < px->cmd_num)
	{
		if (i != idx && i != bef)
		{
			close(px->pipefd[i][0]);
			close(px->pipefd[i][1]);
		}
		i++;
	}
}

t_node	*mlst_find(int idx, t_main_node *data)
{
	t_node	*node;

	node = data->node_head;
	while (node)
	{
		if (node->idx == idx)
			return (node);
		node = node ->next;
	}
	return (NULL);
}
