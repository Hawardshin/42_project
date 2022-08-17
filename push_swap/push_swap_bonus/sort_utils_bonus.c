/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 21:43:40 by joushin           #+#    #+#             */
/*   Updated: 2022/08/17 12:47:38 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap_bonus.h"

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

int	ft_a_score(t_stack *stack, int n)
{
	int		idx;
	t_node	*node;

	node = stack -> head;
	if (node_rank(stack, n) == stack->count && \
		node_rank(stack, node->num) == stack ->count - 1)
		return (0);
	idx = 1;
	while (node-> next)
	{
		if (node->num < n && n < node->next->num)
			return (idx);
		if (node -> num > node->next->num && n < node -> next->num)
			return (idx);
		if (node -> num > node -> next->num && n > node ->num)
			return (idx);
		node = node->next;
		idx++;
	}
	return (idx);
}

void	score_b(t_stack *a, t_stack *b)
{
	t_node	*bnode;
	int		bi;
	int		l_score;

	bnode = b->head;
	bi = 0;
	l_score = -1;
	while (bnode)
	{
		bnode->ascore = ft_a_score(a, bnode->num);
		bnode->bscore = bi;
		bi++;
		bnode = bnode->next;
	}
}
