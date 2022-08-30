/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 17:32:39 by joushin           #+#    #+#             */
/*   Updated: 2022/08/30 17:46:16 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include "../srcs/libft/libft.h"

void	exec_bonus(int *o_fd, t_data *px)
{
	char	*tmp;
	int		len;

	*o_fd = open (".tmp", O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (*o_fd == -1)
		print_error(2, px->infile);
	tmp = get_next_line(0);
	while (ft_strncmp(tmp, px->infile, ft_strlen(px->infile)))
	{
		len = (int)ft_strlen(tmp);
		write (*o_fd, tmp, len);
		my_free (&tmp);
		tmp = get_next_line(0);
	}
	if (tmp)
		my_free(&tmp);
	close(*o_fd);
}

void	exec_first(t_data *px)
{
	int		o_fd;
	t_px	*node;

	node = px->cmd_node_head;
	ft_putstr_fd(node->cmd_path[0], 2);///
	ft_putstr_fd(":: first \n",2);
	if (px->flag == 1)
	{
		exec_bonus(&o_fd, px);
		o_fd = open (".tmp", O_RDONLY);
	}
	else
	{
		o_fd = open(px->infile, O_RDONLY);
		if (o_fd == -1)
			print_error(2, px->infile);
	}
	if (dup2(o_fd, 0) == -1)
		print_error(2, NULL);
	close(o_fd);
	close(px->pipefd[0]);
	if (dup2(px->pipefd[1], 1) == -1)
		print_error(2, NULL);
	close(px->pipefd[1]);
	if (node->cmd_path[0] != NULL)
		execve(node->cmd_path[0], node->cmd, px->ev);
	print_error(1, node->cmd[0]);
}

void	exec_last(t_data *px)
{
	int		o_fd;
	t_px	*node;

	node = px->cmd_node_tail;
	ft_putstr_fd(node->cmd_path[0], 2);//
	ft_putstr_fd(":: last \n", 2);
	close(px->pipefd[px->pipe_num][1]);
	if (px->flag == 1)
	{
		o_fd = open(px->outfile, O_APPEND | O_WRONLY | O_CREAT, 0644);
		unlink(".tmp");
	}
	else
		o_fd = open(px->outfile, O_TRUNC | O_WRONLY | O_CREAT, 0644);
	if (o_fd == -1)
		print_error(2, px->outfile);
	if (dup2(px->pipefd[0][0], 0) == -1)
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
	ft_putstr_fd(node->cmd_path[0], 2);///
	ft_eprintf("%d \n", idx);
	ft_putstr_fd(":: mid\n", 2);
	if (dup2(px->pipefd[idx][1], 0) == -1)
		print_error(2, NULL);
	close(px->pipefd[1]);
	if (dup2(px->pipefd[idx][0], 1) == -1)
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
		if (px->flag && i == 0)
			waitpid(pid, &status, 0);
		else
			waitpid(pid, &status, WNOHANG);
	}
	close(px->pipefd[1]);
	close(px->pipefd[0]);
	waitpid(pid, &status, 0);
	if (0 == (status & 0xff))
		return (status >> 8);
	return (status);
}
