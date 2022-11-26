/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 17:14:16 by joushin           #+#    #+#             */
/*   Updated: 2022/11/25 19:59:31 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/node.h"
#include "../../include/utils.h"
#include "../../include/exec.h"
#include "../../include/builtin.h"
#include "../libft/libft.h"

//0이 read 1이 write
// 전 파이프 0 1 다음 파이프 0 1
// 전파이프 0 은 현재 input 다음파이프 1 output
static void	exec_pipe_fd(int idx, t_main_node *px, int o_fd, int w_fd, t_node *node)
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
	if (node->outfile_node == NULL && px->cmd_num != 1)
		w_fd = px->pipefd[idx][1];
	if ((w_fd != 1) && dup2(w_fd, 1) == -1)
		print_error(2, NULL);
	close(px->pipefd[idx][1]);
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
	exec_pipe_fd(idx, px, o_fd, w_fd, node);
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
