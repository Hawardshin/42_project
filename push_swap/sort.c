/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 13:33:43 by joushin           #+#    #+#             */
/*   Updated: 2022/08/16 19:02:50 by joushin          ###   ########.fr       */
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
	// if (node->ascore > (a->count - 1) / 2)
	// 	swap_rev(a-> count - node->ascore - 1, a, b, 'a');
	// else
	// 	swap_for(node ->ascore, a, b, 'a');
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

void	command_optimize(t_stack *a, t_stack *b, t_node **node)
{
	int	idx;

	if ((*node)->bscore > b->count / 2 && (*node)->ascore > a->count / 2)
	{
		idx = b->count - (*node)->bscore;
		if (b->count - (*node)->bscore > a-> count - (*node)->ascore)
			idx = a-> count - (*node)->ascore;
		(*node)->bscore = (*node)->bscore + idx;
		(*node)->ascore = (*node)->ascore + idx;
		idx++;
		while (--idx)
			rrr_stack(a, b);
	}
	else if ((*node)->bscore <= b->count / 2 && (*node)->ascore <= a->count / 2)
	{
		idx = (*node)->ascore;
		if ((*node)->bscore < (*node)->ascore)
			idx = (*node)->bscore;
		(*node)->ascore = (*node)->ascore - idx;
		(*node)->bscore = (*node)->bscore - idx;
		idx++;
		while (--idx)
			rr_stack(a, b);
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
#include <stdio.h>
void	print_all_score(t_stack *a)//테스트용 함수
{
	t_node	*node;
	if (a == NULL)
	{
		printf("NULL");
		return ;
	}
	node = a->head;
	while (node)
	{
		printf("num :%d ascore:%d bscore:%d\n",node->num,node->ascore,node->bscore);
		node = node->next;
	}
}

void	sort_start(t_stack *a, t_stack *b)
{
	while (b->count != 0)
	{
	// for (int i=0; i < 15; i++)
	// {
		score_b(a, b);
		move_btoa(a, b);
		// printf("\n-----a :%d-----\n",a->count);
		// print_all_score(a);
		// printf("\n-----b :%d-----\n",b->count);
		// print_all_score(b);
	}
		// printf("\n-----a :%d-----\n",a->count);
		// print_all_score(a);
		// printf("\n-----b :%d-----\n",b->count);
		// print_all_score(b);

	// }
	forwarding(a, b);
// printf("\n-----a :%d-----\n",a->count);
// 	print_all_score(a);
// 	printf("\n-----b :%d-----\n",b->count);
// 	print_all_score(b);
}
