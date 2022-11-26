/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_case_double_quotes.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 20:12:35 by joushin           #+#    #+#             */
/*   Updated: 2022/11/26 13:29:56 by joushin          ###   ########.fr       */
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

	len = 3;
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

	len = 3;
	tmp = src->now_pos;
	while ((token_case(see_char(src)) != D_QUOTES) && (see_char(src) != ENDOF))
	{
		if (token_case(move_char(src)) == DOLLAR)
		{
			i = 0;
			env_buff = malloc (ft_env_len(src) + 1);
			if (!env_buff)
				print_error(0, NULL);
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

char	*this_is_question(t_readline *src, char **env_buff)
{
	move_char(src);
	my_free((void **) env_buff);
	return (ft_itoa(g_state.exit_code));
}

char	*make_env_text(t_readline *src)
{
	char	*env_buff;
	int		k;
	char	*env_text;

	k = 0;
	env_buff = malloc (ft_env_len(src) + 1);
	if (!env_buff)
		print_error(0, NULL);
	if (see_char(src) == '?')
		return (this_is_question(src, &env_buff));
	move_char(src);
	while (token_case(see_char(src)) == DOLLAR)
	{
		env_buff[k++] = move_char(src);
		if (see_char(src) == '?')
			return (this_is_question(src, &env_buff));
	}
	while (token_case(see_char(src)) == CHAR)
		env_buff[k++] = move_char(src);
	env_buff[k] = '\0';
	env_text = ft_mstrdup(get_env(env_buff));
	my_free((void **) &env_buff);
	if (k == 0)
		env_text = ft_mstrdup("$");
	return (env_text);
}

char	*make_double_tok(t_readline *src, t_token *tok)
{
	char	*tok_buff;
	int		i;
	char	*env_text;
	int		flag;

	i = 0;
	flag = 0;
	tok_buff = malloc(ft_all_len(src) + 1);
	if (!tok_buff)
		print_error(0, NULL);
	while ((token_case(see_char(src)) != D_QUOTES) && (see_char(src) != ENDOF))
	{
		if (token_case(see_char(src)) == DOLLAR)
		{
			src->now_pos--;
			env_text = make_env_text(src);
			while (env_text && *env_text)
				tok_buff[i++] = *env_text++;
			flag = 1;
		}
		else
			tok_buff[i++] = move_char(src);
	}
	tok_buff[i] = '\0';
	tok->tok_type = ARGV_TOK;
	if (flag == 1 && i == 0)
		tok->tok_type = DELETE_TOK;
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
