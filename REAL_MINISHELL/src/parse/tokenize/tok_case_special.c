/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_case_one.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 20:07:55 by joushin           #+#    #+#             */
/*   Updated: 2022/11/24 17:33:04 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/node.h"
#include "../../../include/node.h"
#include "../../../include/just_for_test.h"
#include "../../../include/utils.h"
#include "../../libft/libft.h"

t_token	*create_space_tok(t_readline *src)
{
	t_token	*tok;

	tok = malloc(sizeof(t_token));
	if (!tok)
		print_error(0, NULL);
	ft_memset(tok, 0, sizeof(t_token));
	while (token_case(see_char(src)) == SPACE_B && see_char(src) != ENDOF)
		move_char(src);
	tok->text = "SPACE";
	tok->tok_type = SPACE_TOK;
	return (tok);
}

t_token	*create_pipe_tok(t_readline *src)
{
	t_token	*tok;

	tok = malloc(sizeof(t_token));
	if (!tok)
		print_error(0, NULL);
	ft_memset(tok, 0, sizeof(t_token));
	move_char(src);
	tok->text = ft_mstrdup("PIPE'|'");
	tok->tok_type = PIPE_TOK;
	return (tok);
}

t_token	*create_direct_tok(t_readline *src)
{
	t_token	*tok;

	tok = malloc(sizeof(t_token));
	if (!tok)
		print_error(0, NULL);
	ft_memset(tok, 0, sizeof(t_token));
	move_char(src);
	if (token_case(see_char(src)) == DIRECT)
	{
		move_char(src);
		tok->text = ft_mstrdup("<<");
	}
	else
		tok->text = ft_mstrdup("<");
	tok->tok_type = IO_TOK;
	return (tok);
}

t_token	*create_redirect_tok(t_readline *src)
{
	t_token	*tok;

	tok = malloc(sizeof(t_token));
	if (!tok)
		print_error(0, NULL);
	ft_memset(tok, 0, sizeof(t_token));
	move_char(src);
	if (token_case(see_char(src)) == RE_DIRECT)
	{
		move_char(src);
		tok->text = ft_mstrdup(">>");
	}
	else
		tok->text = ft_mstrdup(">");
	tok->tok_type = IO_TOK;
	return (tok);
}
