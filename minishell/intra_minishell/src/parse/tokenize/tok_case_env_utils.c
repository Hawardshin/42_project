/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_case_env_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 16:37:38 by joushin           #+#    #+#             */
/*   Updated: 2022/11/26 22:14:51 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "node.h"
#include "utils.h"
#include "libft.h"

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
	int		len;
	int		tmp;

	len = 3;
	tmp = src->now_pos;
	while ((token_case(see_char(src)) != D_QUOTES) && (see_char(src) != ENDOF))
	{
		if (token_case(move_char(src)) == DOLLAR)
			len += ft_dallar_len_utils(src);
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
	move_char(src);
	if (see_char(src) == '?')
		return (this_is_question(src, &env_buff));
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
