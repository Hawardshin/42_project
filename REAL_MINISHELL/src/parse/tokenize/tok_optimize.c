/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_optimize.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 20:50:00 by joushin           #+#    #+#             */
/*   Updated: 2022/11/26 20:02:28 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/node.h"
#include "../../../include/utils.h"
#include "../../libft/libft.h"

static char	*merge_tok_utils(t_token *front, t_token *back)
{
	char	*buff;
	int		i;
	int		j;

	i = 0;
	j = 0;
	buff = malloc (front->text_len + back->text_len + 1);
	if (!buff)
		print_error(0, NULL);
	while (front -> text[i])
	{
		buff[i] = front -> text[i];
		i++;
	}
	while (back && back->text[j])
		buff[i++] = back->text[j++];
	buff[i] = '\0';
	my_free((void **)&front->text);
	if (i == 0)
		i++;
	front->text_len = i;
	return (buff);

}

static void	merge_two_tok(t_token *front, t_token *back)
{
	front->text = merge_tok_utils(front, back);

	front->next = back->next;
	my_free((void **)&back->text);
	my_free((void **)&back);
	back = NULL;
}

void	merge_argv_tok(t_main_token *tok)
{
	t_token	*tmp;

	tmp = tok->start_token;
	while (tmp->next != NULL)
	{
		if ((tmp->tok_type == ARGV_TOK) && ((tmp->next->tok_type) == ARGV_TOK))
			merge_two_tok(tmp, tmp->next);
		else
			tmp = tmp->next;
	}
}

void	delete_all_space_tok(t_main_token *tok)
{
	t_token	*tmp;
	t_token	*ntmp;

	tmp = tok->start_token;
	while (tmp)
	{
		ntmp = tmp->next;
		if (ntmp)
			ntmp->bef = tmp->bef;
		if (tmp->tok_type == SPACE_TOK)
		{
			if (tmp->bef == NULL)
				tok->start_token = ntmp;
			else
				tmp->bef->next = ntmp;
			my_free((void **)&tmp);
		}
		else if (ntmp)
			ntmp->bef = tmp;
		tmp = ntmp;
	}
}
