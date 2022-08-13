/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 13:33:43 by joushin           #+#    #+#             */
/*   Updated: 2022/08/13 18:01:37 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	ft_a_score(t_stack *stack, int n)//a스택의 위치 찾기
{
	int		idx;
	t_node	*node;

	node = stack -> head;
	if (stack->tail -> num < n && n < node->num)
		return (0);
	idx = 1;
	while (node->next)
	{
		if (node->num < n && n < node->next->num)
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
	// t_node	*least_node;

	bnode = b->head;
	bi = 0;
	l_score = -1;
	while (bnode)
	{
		bnode->ascore = ft_a_score(a, bnode->num);
		// if (bnode->ascore > a->count / 2)
		// 	bnode->ascore = a-> count - bnode->ascore;
		bnode->bscore = bi;
		// if (bi > b->count / 2)
		// 	bnode -> bscore = b->count - bi;
		// if (l_score == -1 || l_score > bnode->ascore + bnode->bscore)
		// {
		// 	least_node = bnode;
		// 	l_score = bnode->ascore + bnode->bscore;
		// }
		bi++;
		bnode = bnode->next;
	}
	// return (least_node);
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

void	a_sort(t_stack *a,t_stack *b)
{
	t_node	*node;

	node = a->head;
	if (node ->ascore < (a->count - 1) / 2 )//애매해 count -1이 맞는걸까
		go_head(a, b, a-> count - node->ascore - 2, 'a');
	else
		go_tail(a, b, node ->ascore - 1, 'a');
	swap_stack(a, b, 'a');

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

void	print_all_score(t_stack *a)//테스트용 함수
{
	t_node	*node;

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
		score_b(a, b);
	// printf("\n-----a-----\n");
	// printstack(a);
	// printf("\n-----b-----\n");
	// printstack(b);
	// printf("\n-----a-----\n");
	// print_all_score(a);
	// printf("\n-----b-----\n");
	// print_all_score(b);
	// printf("\n-----a-----\n");
	// printstack(a);
	// printf("\n-----b-----\n");
	// printstack(b);
	// printf("\n-----a-----\n");
	// print_all_score(a);
	// printf("\n-----b-----\n");
	// print_all_score(b);
		move_btoa(a, b);
	}
	// printf("\n-----a-----\n");
	// printstack(a);
	// printf("\n-----b-----\n");
	// printstack(b);
	// printf("\n-----a-----\n");
	// print_all_score(a);
	// printf("\n-----b-----\n");
	// print_all_score(b);
}
