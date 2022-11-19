/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_last.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 17:15:04 by joushin           #+#    #+#             */
/*   Updated: 2022/11/19 17:57:27 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/node.h"
#include "../../include/utils.h"
#include "../../include/exec.h"

//cmd->num -2에서 0만을 사용.
static void	exec_last_fd(t_main_node *px, int o_fd, int w_fd)
{
	ft_all_close(px, (px->cmd_num) - 2, -1);
	close(px->pipefd[(px->cmd_num) - 2][1]);
	if (o_fd == 0)
		o_fd = px->pipefd[(px->cmd_num) - 2][0];
	if (dup2(o_fd, 0) == -1)
		print_error(2, NULL);
	close(px->pipefd[px->cmd_num -2][0]);
	if (o_fd != px->pipefd[(px->cmd_num) - 2][0])
		close(o_fd);
	if ((w_fd != 1) && dup2(w_fd, 1) == -1)
		print_error(2, NULL);
}

void	exec_last(t_main_node *px)
{
	int		o_fd;
	t_node	*node;
	int		w_fd;

	node = px->node_tail;
	infile_init(node, &o_fd);
	outfile_init(node, &w_fd);
	exec_last_fd(px, o_fd, w_fd);
	if (node->cmd_path[0] != NULL)
		execve(node->cmd_path[0], (node->cmd), px->ev);
	print_error(1, node->cmd[0]);
}
