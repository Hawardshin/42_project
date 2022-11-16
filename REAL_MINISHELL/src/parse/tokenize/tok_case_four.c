/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_case_four.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 21:19:45 by joushin           #+#    #+#             */
/*   Updated: 2022/11/16 21:20:07 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/node.h"
#include "../../../include/node.h"
#include "../../../include/just_for_test.h"
#include "../../../include/utils.h"
#include "../../libft/libft.h"

int	ft_quote_len(t_readline *src)
{
	int		len;
	int		i;
	char	*tmp;

	tmp = src->buffer;
	len = 0;
	i = src->now_pos;
	if (i == -2)
		i = 0;
	while (token_case(see_char(src)) != QUOTES && see_char(src) != ENDOF)
	{
		move_char(src);
		len++;
	}
	src->now_pos = i;
	return (len);
}

t_token	*create_quotes(t_readline *src)
{
	t_token	*tok;
	int		len;
	int		i;

	i = 0;
	move_char(src);
	tok = malloc(sizeof(t_token));
	len = ft_quote_len(src);
	tok->text = malloc(sizeof(char) * (len + 1));
	tok->text_len = len;
	while (token_case(see_char(src)) != QUOTES && see_char(src) != ENDOF)
	{
		tok->text[i] = move_char(src);
		i++;
	}
	tok->text[i] = '\0';
	if (see_char(src) == ENDOF)
		g_state.exit_code = 258;
	else
		move_char(src);
	tok->tok_type = ARGV_TOK;
	return (tok);
}
