/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_init_and_heardoc.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 17:10:03 by joushin           #+#    #+#             */
/*   Updated: 2022/11/19 17:21:46 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/node.h"
#include "../../include/utils.h"
#include "../../include/exec.h"
#include "../libft/libft.h"

static void	exec_heardoc(int *o_fd, t_infile_node *px, int idx)
{
	char	*tmp;
	int		len;
	int		i;

	i = 0;
	*o_fd = open (".tmp", O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (*o_fd == -1)
		print_error(2, px->file);
	while (i < idx)
	{
		write(1, "pipe ", 5);
		i++;
	}
	write(1, "heredoc> ", 9);
	tmp = get_next_line(0);
	while (1)
	{
		if (ft_strncmp(tmp, px->file, ft_strlen(px->file)) == 0 \
		&& ft_strlen(px->file) + 1 == ft_strlen(tmp))
			break ;
		i = 0;
		while (i < idx)
		{
			write(1, "pipe ", 5);
			i++;
		}
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

static void	chk_infile_hear_doc(t_infile_node *inode, int *o_fd, int flag)
{
	while (inode != NULL)
	{
		if (inode->is_heardoc == 0)
		{
			if ((*o_fd) != 0)
				close((*o_fd));
			(*o_fd) = open(inode->file, O_RDONLY);
			if ((*o_fd) == -1)
				print_error(2, inode->file);
		}
		inode = inode->next;
	}
	if (flag)
	{
		if ((*o_fd) != 0)
			close((*o_fd));
		(*o_fd) = open(".tmp", O_RDONLY);
	}
}

void	infile_init(t_node *node, int *o_fd)
{
	int				flag;
	t_infile_node	*inode;

	unlink(".tmp");
	inode = node->heardoc_node;
	(*o_fd) = 0;
	flag = 0;
	while (inode != NULL)
	{
		exec_heardoc(o_fd, inode, 0);
		if (inode ->hnext == NULL)
			break ;
		inode = inode->hnext;
	}
	if (inode != NULL && inode->next == NULL)
		flag = 1;
	inode = node->infile_node;
	chk_infile_hear_doc(inode, o_fd, flag);
}

void	outfile_init(t_node *node, int *w_fd)
{
	t_outfile_node	*onode;

	(*w_fd) = 1;
	onode = node->outfile_node;
	while (onode)
	{
		if (onode->type == APPEND_TYPE)
			(*w_fd) = open(onode->file, O_APPEND | O_WRONLY | O_CREAT, 0644);
		else if (onode ->type == WRITE_TYPE)
			(*w_fd) = open(onode->file, O_TRUNC | O_WRONLY | O_CREAT, 0644);
		if ((*w_fd) == -1)
			print_error(2, onode->file);
		onode = onode->next;
	}
}
