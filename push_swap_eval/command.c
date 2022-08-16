/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 10:47:46 by joushin           #+#    #+#             */
/*   Updated: 2022/08/15 18:55:12 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "./libft/libft.h"

void	push_stack(t_stack *a, t_stack *b, char s)
{
	t_node	*tmp;

	if (s == 'a')
	{
		if (b -> count == 0)
			return ;
		tmp = pop_front(b);
		push_front(a, tmp);
		write(1, "pa\n", 3);
	}
	else
	{
		if (a -> count == 0)
			return ;
		tmp = pop_front(a);
		push_front(b, tmp);
		write(1, "pb\n", 3);
	}
}

void	swap_b(t_stack *b, char s)
{
	t_node	*tmp1;
	t_node	*tmp2;

	if (b -> count == 0 || b -> count == 1)
		return ;
	if (s == 'b')
		write(1, "sb\n", 3);
	if (b->count < 2)
		return ;
	tmp1 = pop_front(b);
	tmp2 = pop_front(b);
	push_front(b, tmp1);
	push_front(b, tmp2);
}

void	swap_stack(t_stack *a, t_stack *b, char s)
{
	t_node	*tmp1;
	t_node	*tmp2;

	if (s == 'a' || s == 'A')
	{
		if (a -> count == 0 || a-> count == 1)
			return ;
		if (s == 'a')
			write(1, "sa\n", 3);
		if (a->count < 2)
			return ;
		tmp1 = pop_front(a);
		tmp2 = pop_front(a);
		push_front(a, tmp1);
		return (push_front(a, tmp2));
	}
	swap_b(b, s);
}

void	reverse_stack(t_stack *a, t_stack *b, char s)
{
	t_node	*tmp;

	if (s == 'a' || s == 'A')
	{
		if (a -> count == 0 || a-> count == 1)
			return ;
		if (s == 'a')
			write(1, "ra\n", 3);
		tmp = pop_front(a);
		push_back(a, tmp);
	}
	else if (s == 'b' || s == 'B')
	{
		if (b -> count == 0 || b -> count == 1)
			return ;
		if (s == 'b')
			write(1, "rb\n", 3);
		tmp = pop_front(b);
		push_back(b, tmp);
	}
}

void	rreverse_stack(t_stack *a, t_stack *b, char s)
{
	t_node	*tmp;

	if (s == 'a' || s == 'A')
	{
		if (a -> count == 0 || a-> count == 1)
			return ;
		if (s == 'a')
			write(1, "rra\n", 4);
		tmp = pop_back(a);
		push_front(a, tmp);
	}
	else if (s == 'b' || s == 'B')
	{
		if (b -> count == 0 || b -> count == 1)
			return ;
		if (s == 'b')
			write(1, "rrb\n", 4);
		tmp = pop_back(b);
		push_front(b, tmp);
	}
}
