/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_case_three.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 20:12:35 by joushin           #+#    #+#             */
/*   Updated: 2022/11/19 18:05:46 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/node.h"
#include "../../../include/node.h"
#include "../../../include/just_for_test.h"
#include "../../../include/utils.h"
#include "../../libft/libft.h"

int	ft_env_len(t_readline *src)
{
	int	len;
	int	tmp;

	len = 0;
	tmp = src->now_pos;
	while (token_case(see_char(src)) == DOLLAR)
	{
		move_char(src);
		len++;
	}
	while (token_case(see_char(src)) == CHAR)
	{
		move_char(src);
		len++;
	}
	src->now_pos = tmp;
	return (len);
}

int	ft_all_len(t_readline *src)
{
	char	*env_buff;
	int		len;
	int		i;
	int		tmp;

	len = 0;
	tmp = src->now_pos;
	while ((token_case(see_char(src)) != D_QUOTES) && (see_char(src) != ENDOF))
	{
		if (token_case(move_char(src)) == DOLLAR)
		{
			i = 0;
			env_buff = malloc (ft_env_len(src) + 1);
			while (token_case(see_char(src)) == DOLLAR)
				env_buff[i++] = move_char(src);
			while (token_case(see_char(src)) == CHAR)
				env_buff[i++] = move_char(src);
			env_buff[i] = '\0';
			len += ft_strlen(get_env(env_buff));
			my_free((void **) &env_buff);
		}
		len++;
	}
	src->now_pos = tmp;
	return (len);
}

char	*make_env_text(t_readline *src)
{
	char	*env_buff;
	int		k;
	char	*env_text;

	k = 0;
	env_buff = malloc (ft_env_len(src) + 1);
	move_char(src);
	k = 0;
	env_buff = malloc (ft_env_len(src) + 1);
	k = 0;
	while (token_case(see_char(src)) == DOLLAR)
		env_buff[k++] = move_char(src);
	while (token_case(see_char(src)) == CHAR)
		env_buff[k++] = move_char(src);
	env_buff[k] = '\0';
	env_text = get_env(env_buff);
	my_free((void **) &env_buff);
	if (k == 0)
		env_text = "$";
	return (env_text);
}

char	*make_double_tok(t_readline *src)
{
	char	*tok_buff;
	int		i;
	char	*env_text;

	i = 0;
	tok_buff = malloc(ft_all_len(src) + 1);
	while ((token_case(see_char(src)) != D_QUOTES) && (see_char(src) != ENDOF))
	{
		if (token_case(see_char(src)) == DOLLAR)
		{
			env_text = make_env_text(src);
			while (env_text && *env_text)
				tok_buff[i++] = *env_text++;
			tok_buff[i] = '\0';
		}
		else
			tok_buff[i++] = move_char(src);
	}
	tok_buff[i] = '\0';
	return (tok_buff);
}

t_token	*create_d_quotes(t_readline *src)
{
	t_token	*tok;

	move_char(src);
	tok = malloc(sizeof(t_token));
	ft_memset(tok, 0, sizeof(t_token));
	tok->text = make_double_tok(src);
	if (token_case(see_char(src)) != D_QUOTES)
		g_state.exit_code = 258;
	else
		move_char(src);
	tok->text_len = ft_strlen(tok->text);
	tok->tok_type = ARGV_TOK;
	return (tok);
}
