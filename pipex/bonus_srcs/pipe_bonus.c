/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 17:32:39 by joushin           #+#    #+#             */
/*   Updated: 2022/09/02 11:29:25 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include "../srcs/libft/libft.h"

static void	exec_bonus(int *o_fd, t_data *px)
{
	char	*tmp;
	int		len;

	*o_fd = open (".tmp", O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (*o_fd == -1)
		print_error(2, px->infile);
	write(1, "heredoc> ", 9);
	tmp = get_next_line(0);
	while (ft_strncmp(tmp, px->infile, ft_strlen(px->infile)))
	{
		len = (int)ft_strlen(tmp);
		write (*o_fd, tmp, len);
		my_free (&tmp);
		write(1, "heredoc> ", 9);
		tmp = get_next_line(0);
	}
	if (tmp)
		my_free(&tmp);
	close(*o_fd);
}

static void	exec_first(t_data *px)
{
	int		o_fd;
	t_px	*node;

	node = px->cmd_node_head;
	if (px->flag == 1)
	{
		exec_bonus(&o_fd, px);
		o_fd = open(".tmp", O_RDONLY);
	}
	else
		o_fd = open(px->infile, O_RDONLY);
	if (o_fd == -1)
		print_error(2, px->infile);
	ft_all_close(px, 0, -1);
	close(px->pipefd[0][0]);
	if (dup2(o_fd, 0) == -1)
		print_error(2, NULL);
	close(o_fd);
	if (dup2(px->pipefd[0][1], 1) == -1)
		print_error(2, NULL);
	close(px->pipefd[0][1]);
	if (node->cmd_path[0] != NULL)
		execve(node->cmd_path[0], node->cmd, px->ev);
	print_error(1, node->cmd[0]);
}

static void	exec_last(t_data *px)
{
	int		o_fd;
	t_px	*node;

	node = px->cmd_node_tail;
	ft_all_close(px, (px->cmd_num) - 2, -1);
	close(px->pipefd[(px->cmd_num) - 2][1]);
	if (px->flag == 1)
	{
		o_fd = open(px->outfile, O_APPEND | O_WRONLY | O_CREAT, 0644);
		unlink(".tmp");
	}
	else
		o_fd = open(px->outfile, O_TRUNC | O_WRONLY | O_CREAT, 0644);
	if (o_fd == -1)
		print_error(2, px->outfile);
	if (dup2(px->pipefd[px->cmd_num - 2][0], 0) == -1)
		print_error(2, NULL);
	close(px->pipefd[px->cmd_num -2][0]);
	if (dup2(o_fd, 1) == -1)
		print_error(2, NULL);
	close(o_fd);
	if (node->cmd_path[0] != NULL)
		execve(node->cmd_path[0], (node->cmd), px->ev);
	print_error(1, node->cmd[0]);
}

static void	exec_pipe(int idx, t_data *px)
{
	t_px	*node;

	node = mlst_find(idx, px);
	ft_all_close(px, idx, idx - 1);
	close(px->pipefd[idx - 1][1]);
	close(px->pipefd[idx][0]);
	if (dup2(px->pipefd[idx - 1][0], 0) == -1)
		print_error(2, NULL);
	close(px->pipefd[idx - 1][0]);
	if (dup2(px->pipefd[idx][1], 1) == -1)
		print_error(2, NULL);
	close(px->pipefd[idx][1]);
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
	while (++i < px->cmd_num)
	{
		pid = mfork();
		if (pid == 0)
		{
			if (i == 0)
				exec_first(px);
			else if (i + 1 == px->cmd_num)
				exec_last(px);
			exec_pipe(i, px);
		}
		if (px->flag && i == 0)
			waitpid(pid, &status, 0);
	}
	ft_all_close(px, -1, -1);
	waitpid(pid, &status, 0);
	ft_end_free(px);
	if (0 == (status & 0xff))
		return (status >> 8);
	return (status);
}
