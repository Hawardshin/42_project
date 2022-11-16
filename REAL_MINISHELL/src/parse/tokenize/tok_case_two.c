/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_case_two.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 20:10:49 by joushin           #+#    #+#             */
/*   Updated: 2022/11/16 22:40:59 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/node.h"
#include "../../../include/node.h"
#include "../../../include/just_for_test.h"
#include "../../../include/utils.h"
#include "../../libft/libft.h"

int	ft_dollar_len(t_readline *src)
{
	char	*env_buff;
	int		len;
	int		tmp;
	int		i;

	len = 0;
	tmp = src->now_pos;
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
	src->now_pos = tmp;
	return (len);
}

t_token	*create_dollar_tok(t_readline *src)
{
	t_token	*tok;
	char	*env_text;
	char	*tok_buff;
	int		i;

	i = 0;
	tok = malloc(sizeof(t_token));
	ft_memset(tok, 0, sizeof(t_token));
	tok_buff = malloc(ft_dollar_len(src) + 1);
	env_text = make_env_text(src);
	while (env_text && *env_text)
		tok_buff[i++] = *env_text++;
	tok_buff[i] = '\0';
	while (env_text && *env_text)
		tok_buff[i++] = *env_text++;
	tok_buff[i] = '\0';
	i++;
	tok->text = tok_buff;
	tok->text_len = i;
	tok->tok_type = ARGV_TOK;
	return (tok);
}

int	char_tok_len(t_readline *src)
{
	int		len;
	int		i;

	len = 0;
	i = src->now_pos;
	while (token_case(see_char(src)) == CHAR)
	{
		move_char(src);
		len++;
	}
	src->now_pos = i;
	return (len);
}

t_token	*create_char_tok(t_readline *src)
{
	t_token	*tok;
	int		len;
	int		i;

	i = 0;
	tok = malloc(sizeof(t_token));
	len = char_tok_len(src);
	tok->text = malloc (len + 1);
	tok->text_len = len;
	while (token_case(see_char(src)) == CHAR)
	{
		tok->text[i] = move_char(src);
		i++;
	}
	tok->text[i] = '\0';
	tok->tok_type = ARGV_TOK;
	return (tok);
}
