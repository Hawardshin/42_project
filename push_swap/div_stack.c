/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   div_stack.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 12:46:42 by joushin           #+#    #+#             */
/*   Updated: 2022/08/15 17:07:41 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

//정방향
void	go_head(t_stack	*a, t_stack *b, int idx, char c)// 두 함수 합치는거(나중에 하기)
{
	while (idx)
	{
		reverse_stack(a, b, c);
		idx--;
	}
}
//역방향
void	go_tail(t_stack *a, t_stack *b, int idx, char c)
{
	while (idx)
	{
		rreverse_stack(a, b, c);
		idx--;
	}
}

int	is_sorted(t_stack *stack, int n)//스택의 현재 이 값보다 몇개가 더 작은지
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

void	swap_rev(int len, t_stack *a, t_stack *b, char c)
{
	int	i;

	i = 0;
	// if (a->head->ascore == a->count - 1)
	// {
	// 	rreverse_stack(a, b, c);
	// 	swap_stack(a, b, c);
	// 	return ;
	// }
	while (i < len)
	{
		rreverse_stack(a, b, c);
		// if (i != len - 1)
			swap_stack(a, b, c);
		i++;
	}
	i = 1;
// 	while (i < len)
// 	{
// 		reverse_stack(a, b, c);
// 		i++;
// 	}
}

void	swap_for(int len, t_stack *a, t_stack *b, char c)
{
	int	i;

	i = 0;
	while (i < len)
	{
		swap_stack(a, b, c);
		if (i != len - 1)
			reverse_stack(a, b, c);
		i++;
	}
	i = 1;
	// while (i < len)
	// {
	// 	rreverse_stack(a, b, c);
	// 	i++;
	// }
}

// void	sorting(t_stack *a ,t_stack *b, char c)
// {
// 	t_node	*node;
// 	t_stack	*stack;
// 	int		len;

// 	stack = b;
// 	if (c == 'a')
// 		stack = a;
// 	node = stack -> head;
// 	len = is_sorted(stack, node ->num);//본인보다 작은 수들의 숫자
// 	if (len == 0)
// 		return ;
// //	if (len <= (stack -> count) / 2)
// 		swap_for(len, a, b, c);
// 	//else
// 	//	swap_rev(len, a, b, c);
// }

void	div_stack(t_stack *a, t_stack *b)
{
	int	pivot;
	int	num;
	int	head_move;
	int	tail_move;

	pivot = a->count / 3;
	num = 1;
	while (num <= pivot)//1부터 피봇까지 쭉 넘긴다.
	{
		if (a->count == 3)
			return (three_argv(a, b));
		head_move = list_head_find(a, 1, pivot);
		tail_move = list_tail_find(a, 1, pivot);
		if (head_move <= tail_move)
			go_head(a, b, head_move, 'a');
		else
			go_tail(a, b, tail_move, 'a');
		push_stack(a, b, 'b');
		num++;
	}
	while (num <= pivot * 2)//1부터 피봇까지 쭉 넘긴다.
	{
		if (a->count == 3)
			return (three_argv(a, b));
		head_move = list_head_find(a, pivot + 1, pivot * 2);
		tail_move = list_tail_find(a, pivot + 1, pivot * 2);
		if (head_move <= tail_move)
			go_head(a, b, head_move, 'a');
		else
			go_tail(a, b, tail_move, 'a');
		push_stack(a, b, 'b');
		num++;
	}
	while (a->count > 3)
		push_stack(a, b, 'b');
	three_argv(a, b);
}
