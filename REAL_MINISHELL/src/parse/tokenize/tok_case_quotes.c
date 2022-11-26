/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_case_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 21:19:45 by joushin           #+#    #+#             */
/*   Updated: 2022/11/25 21:54:11 by joushin          ###   ########.fr       */
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
	if (!tok)
		print_error(0, NULL);
	len = ft_quote_len(src);
	tok->text = malloc(sizeof(char) * (len + 1));
	if (!(tok->text))
		print_error(0, NULL);
	tok->text_len = len;
	while (token_case(see_char(src)) != QUOTES && see_char(src) != ENDOF)
		tok->text[i++] = move_char(src);
	tok->text[i] = '\0';
	tok->tok_type = ARGV_TOK;
	if (see_char(src) == ENDOF)
		tok->tok_type = ERROR_TOK;
	else
		move_char(src);
	return (tok);
}
