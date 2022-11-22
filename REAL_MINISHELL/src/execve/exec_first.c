/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_first.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 17:13:07 by joushin           #+#    #+#             */
/*   Updated: 2022/11/19 17:21:14 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/node.h"
#include "../../include/utils.h"
#include "../../include/exec.h"

static void	exec_first_fd(t_main_node *px, int o_fd, int w_fd, t_node *node)
{
	ft_all_close(px, 0, -1);
	close(px->pipefd[0][0]);
	if ((o_fd != 0) && dup2(o_fd, 0) == -1)
		print_error(2, NULL);
	if (o_fd != 0)
		close(o_fd);
	if (node->outfile_node == NULL && px->cmd_num != 1)
		w_fd = px->pipefd[0][1];
	if ((w_fd != 1) && dup2(w_fd, 1) == -1)
		print_error(2, NULL);
	close(px->pipefd[0][1]);
}

void	exec_first(t_main_node *px)
{
	int		o_fd;
	int		w_fd;
	t_node	*node;

	node = px->node_head;
	infile_init(node, &o_fd);
	outfile_init(node, &w_fd);
	exec_first_fd(px, o_fd, w_fd, node);
	if (node->cmd_path[0] != NULL)
		execve(node->cmd_path[0], node->cmd, px->ev);
	if (node != NULL && node->cmd != NULL)
		print_error(1, node->cmd[0]);
}