/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 20:35:18 by joushin           #+#    #+#             */
/*   Updated: 2022/11/19 14:37:36 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/node.h"
#include "../../include/just_for_test.h"
#include "../../include/utils.h"
#include "../libft/libft.h"

/* 기존 파이프 엑스와 다른점. 오픈 파일이 1개가 아니므로 open도 여러개 가능 + 생성도 여러개 가능하다.
즉 1. 오픈하는 파일을 전부다 오픈해본다. 하나라도 open을 실패하는경우 뒤에거는 오픈하지 않고 에러를 띄운다.
	이건 자식 프로세스에서 띄우는 것이므로 그냥 exit을 해줘도 된다 와 초개꿀. 그리고 마지막 open파일이 open이 된다.]
	2. outfile은 하나씩 생성을 하는데 > 인지 >> 인지 플래그에 따라서 다르게 생성을 해야만 한다. 즉 그 파일을 만드는 옵션을 다르게 준다.
	그렇게 outfile이 지정되면 pipe에는 아무것도 넘어가지 않게된다.
	즉 outfile이 없을 때만 파이프로 넘겨주는 것이다.
	3. 두번째 파이프 부터는 기본 open파일이 input pipe이지만 만약 inputfile이 존재하면 그 녀석을 최선 open으로 진행한다.
*/
/*
쭉 찾아다 hear_doc찾으면 tmp 만들고 또 만들고 또 만들어서 마지막 tmp 파일을 여는 느낌.
하지만 실행은 그게 아니라는 것..  결극 hdoc노드가 몇번째 위치에 있는지를 찾으면 된다.
음 결국 heardoc 노드를 따로 만드는게 맞는듯.. hear_doc이 가장 마지막 open인 경우에만 그 fd로 open을 하면 되지만,
만약 아닌경우 모든 명령을 돌면 된다.
여기서 가장 마지막 hear_doc이 맞는경우 어떻게 돌아야하는가? 이 경우는 open을 해보긴 하지만 순서대로 실패하는지만 검사를 해보면 된다.
*/

static void	exec_bonus(int *o_fd, t_infile_node *px, int idx)
{
	char	*tmp;
	int		len;

	*o_fd = open (".tmp", O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (*o_fd == -1)
		print_error(2, px->file);
	while (idx)
	{
		write(1, "pipe ", 5);
		idx--;
	}
	write(1, "heredoc> ", 9);
	tmp = get_next_line(0);
	while (ft_strncmp(tmp, px->file, ft_strlen(px->file)))
	{
		write(1, "heredoc> ", 9);
		len = (int)ft_strlen(tmp);
		write (*o_fd, tmp, len);
		my_free ((void **)&tmp);
		tmp = get_next_line(0);
	}
	if (tmp)
		my_free((void **)&tmp);
	close(*o_fd);
}
/* 첫번째 경우
open 하기 i */
static void	exec_first(t_main_node *px)
{
	int				o_fd;
	t_node			*node;
	t_infile_node	*inode;
	int				flag;
	int				w_fd;
	t_outfile_node	*onode;

	node = px->node_head;
	flag = 0;
	inode = node->heardoc_node;
	o_fd = 0;
	w_fd = 1;
	while (inode != NULL)
	{
		exec_bonus(&o_fd, inode, 0);
		if (inode ->hnext == NULL)
			break ;
		inode = inode->hnext;
	}
	if (inode != NULL && inode->next == NULL)
		flag = 1;
	inode = node->infile_node;
	while (inode != NULL)
	{
		if (inode->is_heardoc == 0)
		{
			if (o_fd != 0)
				close(o_fd);
			o_fd = open(inode->file, O_RDONLY);
			if (o_fd == -1)
				print_error(2, inode->file);
		}
		inode = inode->next;
	}
	if (flag)
	{
		if (o_fd != 0)
			close(o_fd);
		o_fd = open(".tmp", O_RDONLY);
	}
	onode = node->outfile_node;
	while (onode)
	{
		if (onode->type == APPEND_TYPE)
			w_fd = open(onode->file, O_APPEND | O_WRONLY | O_CREAT, 0644);
		else if (onode ->type == WRITE_TYPE)
			w_fd = open(onode->file, O_TRUNC | O_WRONLY | O_CREAT, 0644);
		if (w_fd == -1)
			print_error(2, onode->file);
		onode = onode->next;
	}
	ft_all_close(px, 0, -1);
	close(px->pipefd[0][0]);
	printf("ooooooooooooo%d\n",o_fd);
	if ((o_fd != 0) && dup2(o_fd, 0) == -1)
		print_error(2, NULL);
	if (o_fd != 0)
		close(o_fd);
	// printf("ooooooooooooo%d\n",o_fd);
	if (node->outfile_node != NULL || px->cmd_num == 1)
		close(px->pipefd[0][1]);
	else
		w_fd = px->pipefd[0][1];
	if ((w_fd != 1) && dup2(w_fd, 1) == -1)
		print_error(2, NULL);
	// printf("w_fd :: %d o_fd :: %d\n",w_fd, o_fd);
	if (node->cmd_path[0] != NULL)
		execve(node->cmd_path[0], node->cmd, px->ev);
	// print_error(1, node->cmd[0]);
}

// static void	exec_last(t_main_node *px)
// {
// 	int		o_fd;
// 	t_node	*node;

// 	node = px->cmd_node_tail;
// 	ft_all_close(px, (px->cmd_num) - 2, -1);
// 	close(px->pipefd[(px->cmd_num) - 2][1]);
// 	if (px->flag == 1)
// 	{
// 		o_fd = open(px->outfile, O_APPEND | O_WRONLY | O_CREAT, 0644);
// 		unlink(".tmp");
// 	}
// 	else
// 		o_fd = open(px->outfile, O_TRUNC | O_WRONLY | O_CREAT, 0644);
// 	if (o_fd == -1)
// 		print_error(2, px->outfile);
// 	if (dup2(px->pipefd[px->cmd_num - 2][0], 0) == -1)
// 		print_error(2, NULL);
// 	close(px->pipefd[px->cmd_num -2][0]);
// 	if (dup2(o_fd, 1) == -1)
// 		print_error(2, NULL);
// 	close(o_fd);
// 	if (node->cmd_path[0] != NULL)
// 		execve(node->cmd_path[0], (node->cmd), px->ev);
// 	print_error(1, node->cmd[0]);
// }

// static void	exec_pipe(int idx, t_main_node *px)
// {
// 	int				o_fd;
// 	t_node			*node;
// 	t_infile_node	*inode;
// 	int				flag;
// 	int				w_fd;
// 	t_outfile_node	*onode;

// 	node = mlst_find(idx, px);
// 	flag = 0;
// 	inode = node->heardoc_node;
// 	o_fd = 0;
// 	while (inode != NULL)
// 	{
// 		exec_bonus(&o_fd, inode, 0);
// 		inode = inode->hnext;
// 	}
// 	ft_all_close(px, idx, idx - 1);
// 	close(px->pipefd[idx - 1][1]);
// 	close(px->pipefd[idx][0]);
// 	if (dup2(px->pipefd[idx - 1][0], 0) == -1)
// 		print_error(2, NULL);
// 	close(px->pipefd[idx - 1][0]);
// 	if (dup2(px->pipefd[idx][1], 1) == -1)
// 		print_error(2, NULL);
// 	close(px->pipefd[idx][1]);
// 	if (node->cmd_path[0] != NULL)
// 		execve(node->cmd_path[0], node->cmd, px->ev);
// 	print_error(1, node->cmd[0]);
// }

int	fork_child(t_main_node *px)
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
			// else if (i + 1 == px->cmd_num)
			// 	exec_last(px);
			// exec_pipe(i, px);
		}
		// if (px->flag && i == 0)
		// 	waitpid(pid, &status, 0);
	}
	ft_all_close(px, -1, -1);
	waitpid(pid, &status, 0);
	// ft_end_free(px);
	if (0 == (status & 0xff))
		return (status >> 8);
	return (status);
}
