/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 13:33:43 by joushin           #+#    #+#             */
/*   Updated: 2022/08/15 21:49:04 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	ft_a_score(t_stack *stack, int n)//a스택의 위치 찾기
{
	int		idx;
	t_node	*node;

	node = stack -> head;
	idx = 1;
	while (node->next)
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
//a에서 움직여야 하는 횟수와 b에서 움직여야 하는 횟수를 구조체에 담아준다.
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

t_node	*find_least_node(t_stack *a, t_stack *b)
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

void	a_sort(t_stack *a, t_stack *b)
{
	t_node	*node;

	node = a->head;
	if (node->ascore > (a->count - 1) / 2)
		swap_rev(a-> count - node->ascore - 1, a, b, 'a');
	else
		swap_for(node ->ascore, a, b, 'a');
}

void	forwarding(t_stack *a, t_stack *b)
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

void	move_btoa(t_stack *a, t_stack *b)
{
	t_node	*node;

	node = find_least_node(a, b);
	if (node->bscore > b->count / 2)
		go_tail(a, b, b->count - node -> bscore, 'b');
	else
		go_head(a, b, node ->bscore, 'b');
	push_stack(a, b, 'a');
	a_sort(a, b);
}

// void	print_all_score(t_stack *a)//테스트용 함수
// {
// 	t_node	*node;
// 	if (a == NULL)
// 	{
// 		printf("NULL");
// 		return ;
// 	}
// 	node = a->head;
// 	while (node)
// 	{
// 		printf("num :%d ascore:%d bscore:%d\n",node->num,node->ascore,node->bscore);
// 		node = node->next;
// 	}
// }
void	sort_start(t_stack *a, t_stack *b)
{
	while (b->count != 0)
	{
		score_b(a, b);
		move_btoa(a, b);
	}
	forwarding(a, b);
	// printf("\n-----a :%d-----\n",a->count);
	// print_all_score(a);
	// printf("\n-----b :%d-----\n",b->count);
	// print_all_score(b);
}
