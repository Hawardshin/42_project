/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 17:32:39 by joushin           #+#    #+#             */
/*   Updated: 2022/08/29 15:56:07 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include "../srcs/libft/libft.h"

void	exec_first(t_data *px)//함수 분리 필요 unlink(".tmp"); 삭제 하기 -> 이 함수 나가서
{
	int		o_fd;
	t_px	*node;
	char	*tmp;

	node = px->cmd_node_head;
	if (px->flag == 1)//새로운 파일 만들어서 하는거
	{
		o_fd = open (".tmp", O_RDWR | O_CREAT | O_TRUNC, 0644);
		if (o_fd == -1)
			print_error(3, px->infile);
		tmp = get_next_line(0);
		while (ft_strncmp(tmp, px->infile, ft_strlen(px->infile)))
		{
			write (o_fd, tmp, ft_strlen(tmp));
			my_free(&tmp);
			tmp = get_next_line(0);
			if (tmp == NULL)
			{
				ft_eprintf("warning: here-document \
			at line 58 delimited by end-of-file (wanted `%s')", px->infile);
				//exit(0);//이거 확인
				break;
			}
		}
		if (tmp)
			my_free(&tmp);
	}
	else
	{
		o_fd = open(px->infile, O_RDONLY);
		if (o_fd == -1)
			print_error(3, px->infile);
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

//만약 명령어 갯수가 1일 때 2번 실행가능성 있다.
void	exec_last(t_data *px)
{
	int		o_fd;
	t_px	*node;

	node = px->cmd_node_tail;
	close(px->pipefd[1]);
	if (px->flag == 1)
		o_fd = open(px->outfile, O_APPEND | O_WRONLY | O_CREAT, 0666 );//O_WRONLY하는게 맞나.
	else
		o_fd = open(px->outfile, O_TRUNC | O_WRONLY | O_CREAT, 0666);
	if (o_fd == -1)
		print_error(3, px->outfile);
	if (dup2(px->pipefd[0], 0) == -1)
		print_error(2, NULL);
	if (dup2(o_fd, 1) == -1)
		print_error(2, NULL);
	close(px->pipefd[0]);
	close(o_fd);//
	if (node->cmd_path[0] != NULL)
		execve(node->cmd_path[0], (node->cmd), px->ev);
	print_error(1, node->cmd[0]);
}

void	exec_pipe(int idx, t_data *px)
{
	t_px	*node;

	node = mlst_find(idx, px);
	if (dup2(px->pipefd[1], 0) == -1)
		print_error(2, NULL);//
	if (dup2(px->pipefd[0], 1) == -1)
		print_error(2, NULL);
	close(px->pipefd[1]);
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
				exec_pipe(i, px);
		}
	}
	waitpid(pid, &status, WUNTRACED);
	return (status >> 8 & 0x000000ff);
}
