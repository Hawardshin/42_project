/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 13:33:43 by joushin           #+#    #+#             */
/*   Updated: 2022/08/16 19:16:53 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static t_node	*find_least_node(t_stack *a, t_stack *b)
{
	t_node	*node;
	t_node	*least_node;
	int		acnt;
	int		bcnt;
	int		l_score;

	node = b->head;
	l_score = 2147483647;
	while (node)
	{
		acnt = node->ascore;
		bcnt = node->bscore;
		if (node->ascore > a->count / 2)
			acnt = a-> count - node->ascore;
		if (node->bscore > b->count / 2)
			bcnt = b->count - node -> bscore;
		if (l_score > acnt + bcnt)
		{
			least_node = node;
			l_score = acnt + bcnt;
		}
		node = node->next;
	}
	return (least_node);
}

static void	a_sort(t_stack *a, t_stack *b)
{
	t_node	*node;

	node = b->head;
	if (node->ascore > a->count / 2)
		go_tail(a, b , a-> count - node->ascore, 'a');
	else
		go_head(a, b, node ->ascore, 'a');
}

static void	forwarding(t_stack *a, t_stack *b)
{
	t_node	*node;
	int		cnt;

	node = a->head;
	cnt = 0;
	while (node)
	{
		if (a->count - 1 == node_rank(a, node->num))
		{
			if (cnt > (a->count) / 2)
				go_tail(a, b, a->count - cnt, 'a');
			else
				go_head(a, b, cnt, 'a');
			return ;
		}
		node = node ->next;
		cnt++;
	}
}

static void	move_btoa(t_stack *a, t_stack *b)
{
	t_node	*node;

	node = find_least_node(a, b);
	command_optimize(a, b, &node);
	if (node->bscore > b->count / 2)
		go_tail(a, b, b->count - node -> bscore, 'b');
	else
		go_head(a, b, node ->bscore, 'b');
	a_sort(a, b);
	push_stack(a, b, 'a');
}

void	sort_start(t_stack *a, t_stack *b)
{
	while (b->count != 0)
	{
		score_b(a, b);
		move_btoa(a, b);
	}
	forwarding(a, b);
}
