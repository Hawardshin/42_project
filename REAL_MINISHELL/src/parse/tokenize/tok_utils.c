/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 19:58:45 by joushin           #+#    #+#             */
/*   Updated: 2022/11/16 20:13:03 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/node.h"
#include "../../../include/node.h"
#include "../../../include/just_for_test.h"
#include "../../../include/utils.h"
#include "../../libft/libft.h"

char	move_char(t_readline *src)
{

	if (!src || !src->buffer)
	{
		errno = ENODATA;
		return (0);
	}
	if (src->now_pos == -2)
		src->now_pos = -1;
	if (++src->now_pos >= src->bufsize)
	{
		src->now_pos = src->bufsize;
		return (ENDOF);
	}
	return (src->buffer[src->now_pos]);
}

char	see_char(t_readline *src)
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
		return (ENDOF);
	return (src->buffer[pos]);
}

int	token_case(char a)
{
	if (a == '|')
		return (PIPE);
	if (a == '\'')
		return (QUOTES);
	if (a == '\"')
		return (D_QUOTES);
	if (a == ' ')
		return (SPACE_B);
	if (a == '$')
		return (DOLLAR);
	if (a == '<')
		return (DIRECT);
	if (a == '>')
		return (RE_DIRECT);
	if (a == ENDOF)
		return (ENDOF);
	return (CHAR);
}
