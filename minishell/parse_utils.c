/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 16:27:24 by joushin           #+#    #+#             */
/*   Updated: 2022/11/09 20:27:07 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include "./include/node.h"

// # define EOF -1

char	move_char(t_readline *src)//움직이기까지 함.
{
	char	c1;

	if (!src || !src->buffer)
	{
		errno = ENODATA;
		return (0);
	}
	c1 = 0;
	if (src->now_pos == -2)
		src->now_pos = -1;
	else
		c1 = src->buffer[src->now_pos];
	if (++src->now_pos >= src->bufsize)
	{
		src->now_pos = src->bufsize;
		return (-1);
	}
	return (src->buffer[src->now_pos]);
}

char	see_char(t_readline *src)//보기만 함.
{
	int	pos;

	if (!src || !(src->buffer))
	{
		errno = ENODATA;
		return (0);
	}
	pos = src->now_pos;
	if (pos == -2)
		pos++;
	pos++;
	if (pos >= src->bufsize)
		return (-1);
	return (src->buffer[pos]);
}

void	skip_white_spaces(t_readline *src)
{
	char	c;

	if (!src || !src->buffer)
		return ;
	c = see_char(src);
	while (c != -1 && (c == ' ' || c == '\t'))
	{
		c = see_char(src);
		if (c != -1)
			move_char(src);
	}
	if (src->now_pos > 0)
		src->done_pos = src->now_pos;
}
