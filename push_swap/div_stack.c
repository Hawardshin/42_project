/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   div_stack.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 12:46:42 by joushin           #+#    #+#             */
/*   Updated: 2022/08/12 17:11:57 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	go_head(t_stack	*a, t_stack *b, int idx)// 두 함수 합치는거(나중에 하기)
{
	while (idx)
	{
		reverse_stack(a, b, 'a');
		idx--;
	}
}

void	go_tail(t_stack *a, t_stack *b, int idx)
{
	while (idx)
	{
		rreverse_stack(a, b, 'a');
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
	while (i < len)
	{
		swap_stack(a, b, c);
		if (i != len - 1)
			rreverse_stack(a, b, c);
		i++;
	}
	i = 1;
	while (i < len)
	{
		reverse_stack(a, b, c);
		i++;
	}
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
	while (i < len)
	{
		rreverse_stack(a, b, c);
		i++;
	}
}


void	sorting(t_stack *a ,t_stack *b, char c)
{
	t_node	*node;
	t_stack	*stack;
	int		len;

	stack = b;
	if (c == 'a')
		stack = a;
	node = stack -> head;
	len = is_sorted(stack, node ->num);//본인보다 작은 수들의 숫자
	if (len == 0)
		return ;
	if (len < (stack -> count) / 2)
		swap_for(len, a, b, c);
	else
		swap_rev(len, a, b, c);
}

void	div_stack(t_stack *a, t_stack *b)
{
	int	pivot1;
	int	pivot2;
	int	pivot3;
	int	num;
	int	head_move;
	int	tail_move;

	pivot1 = a->count / 3;
	pivot2 = (a->count / 3) * 2;
	pivot3 = a -> count;
	num = 1;
	while (num <= pivot1)//1부터 피봇까지 쭉 넘긴다.
	{
		head_move = list_head_find(a, 1, pivot1);
		tail_move = list_tail_find(a, 1, pivot1);
		// printf("h_m%d\n",head_move);
		// printf("t_m%d\n",tail_move);
		// if (head_move == -1 || tail_move == -1)//디버깅용으로 만들어 놓은 보험
		// {
		// 	printf("ERRRORROROROROR\n\n");
		// 	return ;
		// }
		if (head_move <= tail_move)
			go_head(a, b, head_move);
		else
			go_tail(a, b, tail_move);
		push_stack(a, b, 'b');
		sorting(a, b, 'b');
		num++;
	}
	// printf("pivot1 :%d\n",pivot1);
	// printf("pivot2 :%d\n",pivot2);
	// printf("\n-----------pivot2--------------\n");
	while (num <= pivot2)//1부터 피봇까지 쭉 넘긴다.
	{
		head_move = list_head_find(a, pivot1 + 1, pivot2);
		tail_move = list_tail_find(a, pivot1 + 1, pivot2);
		// printf("h_m%d\n",head_move);
		// printf("t_m%d\n",tail_move);
		// if (head_move == -1 || tail_move == -1)//디버깅용으로 만들어 놓은 보험
		// {
		// 	printf("ERRRORROROROROR\n\n");
		// 	return ;
		// }
		if (head_move <= tail_move)
			go_head(a, b, head_move);
		else
			go_tail(a, b, tail_move);
		push_stack(a, b, 'b');
		sorting(a, b, 'b');
		num++;
	}
	while (num <= pivot3)
	{
		head_move = list_head_find(a, pivot1 + 1, pivot3);
		tail_move = list_tail_find(a, pivot1 + 1, pivot3);
		// printf("h_m%d\n",head_move);
		// printf("t_m%d\n",tail_move);
		// if (head_move == -1 || tail_move == -1)//디버깅용으로 만들어 놓은 보험
		// {
		// 	printf("ERRRORROROROROR\n\n");
		// 	return ;
		// }
		if (head_move <= tail_move)
			go_head(a, b, head_move);
		else
			go_tail(a, b, tail_move);
		push_stack(a, b, 'b');
		sorting(a, b, 'b');
		num++;
	}
	num = 0;
	while (num < pivot3)
	{
		push_stack(a, b, 'a');
		num++;
	}
}
