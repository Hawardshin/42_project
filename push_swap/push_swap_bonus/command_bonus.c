/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 10:47:46 by joushin           #+#    #+#             */
/*   Updated: 2022/08/17 14:42:11 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap_bonus.h"
#include "../libft/libft.h"

void	push_stack(t_stack *a, t_stack *b, char s)
{
	t_node	*tmp;

	if (s == 'a')
	{
		if (b -> count == 0)
			return ;
		tmp = pop_front(b);
		push_front(a, tmp);
	}
	else
	{
		if (a -> count == 0)
			return ;
		tmp = pop_front(a);
		push_front(b, tmp);
	}
}

void	swap_b(t_stack *b)
{
	t_node	*tmp1;
	t_node	*tmp2;

	if (b -> count == 0 || b -> count == 1)
		return ;
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
		if (a->count < 2)
			return ;
		tmp1 = pop_front(a);
		tmp2 = pop_front(a);
		push_front(a, tmp1);
		return (push_front(a, tmp2));
	}
	swap_b(b);
}

void	reverse_stack(t_stack *a, t_stack *b, char s)
{
	t_node	*tmp;

	if (s == 'a' || s == 'A')
	{
		if (a -> count == 0 || a-> count == 1)
			return ;
		tmp = pop_front(a);
		push_back(a, tmp);
	}
	else if (s == 'b' || s == 'B')
	{
		if (b -> count == 0 || b -> count == 1)
			return ;
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
		tmp = pop_back(a);
		push_front(a, tmp);
	}
	else if (s == 'b' || s == 'B')
	{
		if (b -> count == 0 || b -> count == 1)
			return ;
		tmp = pop_back(b);
		push_front(b, tmp);
	}
}
