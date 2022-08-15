/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   div_stack.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 12:46:42 by joushin           #+#    #+#             */
/*   Updated: 2022/08/15 21:48:25 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	swap_rev(int len, t_stack *a, t_stack *b, char c)
{
	int	i;

	i = 0;
	while (i < len)
	{
		rreverse_stack(a, b, c);
		swap_stack(a, b, c);
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
}

int	div_pivot(int start, int end, t_stack *a, t_stack *b)
{
	int	head_move;
	int	tail_move;
	int	num;

	num = start;
	while (num <= end)
	{
		if (a->count == 3)
		{
			three_argv(a, b);
			return (1);
		}
		head_move = list_head_find(a, start, end);
		tail_move = list_tail_find(a, start, end);
		if (head_move <= tail_move)
			go_head(a, b, head_move, 'a');
		else
			go_tail(a, b, tail_move, 'a');
		push_stack(a, b, 'b');
		num++;
	}
	return (0);
}

void	div_stack(t_stack *a, t_stack *b)
{
	int	pivot;

	pivot = a->count / 3;
	if (div_pivot(1, pivot, a, b))
		return ;
	if (div_pivot(pivot + 1, pivot * 2, a, b))
		return ;
	while (a->count > 3)
		push_stack(a, b, 'b');
	three_argv(a, b);
}
