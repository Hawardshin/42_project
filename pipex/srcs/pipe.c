/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 17:32:39 by joushin           #+#    #+#             */
/*   Updated: 2022/08/30 14:54:42 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "./libft/libft.h"

void	exec_first(t_data *px)
{
	int		o_fd;
	t_px	*node;

	node = px->cmd_node_head;
	close(px->pipefd[0]);
	if (dup2(px->pipefd[1], 1) == -1)
		print_error(2, NULL);
	close(px->pipefd[1]);
	o_fd = open(px->infile, O_RDONLY);
	if (o_fd == -1)
		print_error(2, px->infile);
	if (dup2(o_fd, 0) == -1)
		print_error(2, NULL);
	close(o_fd);
	if (node->cmd_path[0] != NULL)
		execve(node->cmd_path[0], node->cmd, px->ev);
	print_error(1, node->cmd[0]);
}

//만약 명령어 갯수가 1일 때 2번 실행가능성 있다.
void	exec_last(t_data *px)
{
	int		o_fd;
	t_px	*node;

	node = px->cmd_node_tail;
	close(px->pipefd[1]);
	o_fd = open(px->outfile, O_TRUNC | O_WRONLY | O_CREAT, 0644);
	if (o_fd == -1)
		print_error(2, px->outfile);
	if (dup2(px->pipefd[0], 0) == -1)
		print_error(2, NULL);
	close(px->pipefd[0]);
	if (dup2(o_fd, 1) == -1)
		print_error(2, NULL);
	close(o_fd);
	if (node->cmd_path[0] != NULL)
		execve(node->cmd_path[0], (node->cmd), px->ev);
	print_error(1, node->cmd[0]);
}

void	exec_pipe(int idx, t_data *px)
{
	t_px	*node;

	node = mlst_find(idx, px);
	if (dup2(px->pipefd[1], 0) == -1)
		print_error(2, NULL);
	close(px->pipefd[1]);
	if (dup2(px->pipefd[0], 1) == -1)
		print_error(2, NULL);
	close(px->pipefd[0]);
	if (node->cmd_path[0] != NULL)
		execve(node->cmd_path[0], node->cmd, px->ev);
	print_error(1, node->cmd[0]);
}

int	fork_child(t_data *px)
{
	int		i;
	pid_t	pid;
	int		status;

	i = -1;
	while (++i < px->pipe_num)
	{
		pid = mfork();
		if (pid == 0)
		{
			if (i == 0)
				exec_first(px);
			else if (i + 1 == px->pipe_num)
				exec_last(px);
			else
				exec_pipe(i + 1, px);
		}
		waitpid(pid, &status, WNOHANG);
	}
	close(px->pipefd[1]);
	close(px->pipefd[0]);
	waitpid(pid, &status, 0);
	if (0 == (status & 0xff))
		return (status >> 8);
	return (status);
}
