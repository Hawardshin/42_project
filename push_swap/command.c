/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 10:47:46 by joushin           #+#    #+#             */
/*   Updated: 2022/08/08 13:49:04 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "./libft/libft.h"

void	stack_push(t_stack *s, t_node *new)
{
	// if (!s)
	// 	return ;
	if (s->count == 0)
	{
		s -> head = new;
		s -> tail = new;
	}
	else
	{
		s->head->bef = new;
		new->next = s->head;
		s->head = new;
	}
	s->count++;
}

t_node	*stack_pop(t_stack *s)
{
	// if (!s || s -> count != 0)
	// 	return (0);
	t_node	*tmp;

	tmp = s-> head;
	s->head = s->head->next;
	tmp ->next = 0;
	if (s->count == 1)
		s->tail = 0;
	else
		s->head->bef = 0;
	s->count--;
	return (tmp);
}

void	push_stack(t_stack *a, t_stack *b, char s)
{
	t_node	*tmp;

	if (s == 'a')//pa
	{
	if (b -> count == 0)
		return ;
	tmp = stack_pop(b);
	stack_push(a,tmp);
	write(1, "pa\n",3);
	}//s == b
	else//pb
	{
		if (a -> count == 0)
			return ;
		tmp = stack_pop(a);
		printf("kk : %d",tmp->num);
		stack_push(b,tmp);
		write(1, "pb\n",3);
	}
}
