/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 17:14:16 by joushin           #+#    #+#             */
/*   Updated: 2022/11/26 19:34:55 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/node.h"
#include "../../include/utils.h"
#include "../../include/exec.h"
#include "../../include/builtin.h"

static void	exec_pipe_wfd(int idx, t_main_node *px, int w_fd, t_node *node)
{
	if (node->outfile_node == NULL && px->cmd_num != 1)
		w_fd = px->pipefd[idx][1];
	if ((w_fd != 1) && dup2(w_fd, 1) == -1)
		print_error(2, NULL);
	close(px->pipefd[idx][1]);
}

static void	exec_pipe_ofd(int idx, t_main_node *px, int o_fd)
{
	ft_all_close(px, idx, idx - 1);
	close(px->pipefd[idx - 1][1]);
	close(px->pipefd[idx][0]);
	if (o_fd == 0)
		o_fd = px->pipefd[idx - 1][0];
	if (dup2(o_fd, 0) == -1)
		print_error(2, NULL);
	close(px->pipefd[idx - 1][0]);
	if (o_fd != px->pipefd[idx - 1][0])
		close(o_fd);
}

void	exec_pipe(int idx, t_main_node *px)
{
	int		o_fd;
	int		w_fd;
	t_node	*node;

	node = mlst_find(idx + 1, px);
	if (node == NULL)
		return ;
	infile_init(node, &o_fd);
	outfile_init(node, &w_fd);
	exec_pipe_wfd(idx, px, o_fd, node);
	exec_pipe_ofd(idx, px, o_fd);
	signal(SIGQUIT, SIG_DFL);
	if (node ->cmd && ft_built_check(node->cmd[0]))
	{
		ft_in_built(node, 0);
		exit(0);
	}
	else if (node->cmd_path[0] != NULL)
		execve(node->cmd_path[0], node->cmd, ret_env_char());
	if (node != NULL && node->cmd != NULL)
		print_error(1, node->cmd[0]);
	exit(0);
}
