/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 12:33:29 by joushin           #+#    #+#             */
/*   Updated: 2022/11/15 20:30:06 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/node.h"
// 1. pipe_tok는 앞 뒤에 argv_tok가 있는지 확인
// 2. io_tok 같은 경우 뒤에 argv_tok가 있는지 확인
int	check_syntax(t_token *start_tok)
{
	t_token	*tok;

	tok = start_tok;
	while (tok)
	{
		if (tok->tok_type == PIPE_TOK)
		{
			if (tok->bef == NULL || tok->next == NULL \
				|| tok->bef->tok_type != ARGV_TOK || tok->next->tok_type != ARGV_TOK)
			{
				g_state.exit_code = 258;
				return (1);
			}
		}
		else if (tok->tok_type == IO_TOK)
		{
			if (tok->next == NULL || tok->next->tok_type != ARGV_TOK)
			{
				g_state.exit_code = 258;
				return (1);
			}
		}
		tok = tok->next;
	}
	return (0);
}
