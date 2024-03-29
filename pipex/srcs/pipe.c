/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 17:32:39 by joushin           #+#    #+#             */
/*   Updated: 2022/09/01 15:27:20 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "./libft/libft.h"

static void	exec_first(t_data *px)
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

static void	exec_last(t_data *px)
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

static void	ft_end_free(t_data *px)
{
	t_px	*node;
	t_px	*tmp;
	int		i;

	node = px->cmd_node_head;
	while (node)
	{
		i = 0;
		tmp = node;
		node = node->next;
		while (tmp->cmd[i])
			my_free(&(tmp ->cmd[i++]));
		free(tmp->cmd);
		if (tmp->cmd_path[0])
			my_free(&(tmp->cmd_path[0]));
		free(tmp);
	}
	i = 0;
	while (px->path[i])
	{
		my_free(&(px->path[i++]));
	}
	free(px->path);
}

int	fork_child(t_data *px)
{
	int		i;
	pid_t	pid;
	int		status;

	i = -1;
	while (++i < px->cmd_num)
	{
		pid = mfork();
		if (pid == 0)
		{
			if (i == 0)
				exec_first(px);
			else
				exec_last(px);
		}
	}
	close(px->pipefd[1]);
	close(px->pipefd[0]);
	waitpid(pid, &status, 0);
	ft_end_free(px);
	if (0 == (status & 0xff))
		return (status >> 8);
	return (status);
}
