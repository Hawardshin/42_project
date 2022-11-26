/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_case_double_quotes.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 20:12:35 by joushin           #+#    #+#             */
/*   Updated: 2022/11/26 19:46:43 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/node.h"
#include "../../../include/utils.h"
#include "../../libft/libft.h"

static void	tok_buff_init(t_readline *src, char **tok_buff, t_token *tok)
{
	char	*env_text;
	int		flag;
	int		i;

	flag = 0;
	i = 0;
	while ((token_case(see_char(src)) != D_QUOTES) && (see_char(src) != ENDOF))
	{
		if (token_case(see_char(src)) == DOLLAR)
		{
			src->now_pos--;
			env_text = make_env_text(src);
			while (env_text && *env_text)
				(*tok_buff)[i++] = *env_text++;
			flag = 1;
		}
		else
			(*tok_buff)[i++] = move_char(src);
	}
	(*tok_buff)[i] = '\0';
	tok->tok_type = ARGV_TOK;
	if (flag == 1 && i == 0)
		tok->tok_type = DELETE_TOK;
}

static char	*make_double_tok(t_readline *src, t_token *tok)
{
	char	*tok_buff;

	tok_buff = malloc(ft_all_len(src) + 1);
	if (!tok_buff)
		print_error(0, NULL);
	tok_buff_init(src, &tok_buff, tok);
	return (tok_buff);
}

t_token	*create_d_quotes(t_readline *src)
{
	t_token	*tok;

	move_char(src);
	tok = malloc(sizeof(t_token));
	if (!tok)
		print_error(0, NULL);
	ft_memset(tok, 0, sizeof(t_token));
	tok->text = make_double_tok(src, tok);
	if (token_case(see_char(src)) == ENDOF)
		tok->tok_type = ERROR_TOK;
	else
		move_char(src);
	tok->text_len = ft_strlen(tok->text);
	return (tok);
}
