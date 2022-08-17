/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 11:52:42 by joushin           #+#    #+#             */
/*   Updated: 2022/08/15 19:25:44 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	list_head_find(t_stack *a, int start, int end)
{
	int		cnt;
	t_node	*node;

	node = a->head;
	cnt = 0;
	while (node)
	{
		if (start <= node-> num && node -> num <= end)
			return (cnt);
		else
			node = node -> next;
		cnt++;
	}
	return (-1);
}

int	list_tail_find(t_stack *a, int start, int end)
{
	int		cnt;
	t_node	*node;

	node = a->tail;
	cnt = 1;
	while (node)
	{
		if (start <= node-> num && node -> num <= end)
			return (cnt);
		else
			node = node -> bef;
		cnt++;
	}
	return (-1);
}
