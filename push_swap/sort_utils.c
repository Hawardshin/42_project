/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 21:43:40 by joushin           #+#    #+#             */
/*   Updated: 2022/08/15 21:48:31 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	node_rank(t_stack *stack, int n)
{
	int		idx;
	t_node	*node;

	node = stack -> head;
	idx = 0;
	while (node)
	{
		if (node->num > n)
			idx++;
		node = node->next;
	}
	return (idx);
}

void	go_head(t_stack	*a, t_stack *b, int idx, char c)
{
	while (idx)
	{
		reverse_stack(a, b, c);
		idx--;
	}
}

void	go_tail(t_stack *a, t_stack *b, int idx, char c)
{
	while (idx)
	{
		rreverse_stack(a, b, c);
		idx--;
	}
}
