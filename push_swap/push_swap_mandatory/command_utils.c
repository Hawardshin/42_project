/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 18:50:15 by joushin           #+#    #+#             */
/*   Updated: 2022/08/19 12:19:22 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	push_front(t_stack *s, t_node *new)
{
	if (!s || !new)
		return ;
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

void	push_back(t_stack *s, t_node *new)
{
	if (!s || !new)
		return ;
	if (s -> count == 0)
	{
		s->head = new;
		s->tail = new;
	}
	else
	{
		s->tail->next = new;
		new -> next = NULL;
		new -> bef = s->tail;
		s->tail = new;
	}
	s->count++;
}

t_node	*pop_front(t_stack *s)
{
	t_node	*tmp;

	if (!s || s -> count == 0)
		return (0);
	tmp = s-> head;
	s->head = s->head->next;
	tmp ->next = 0;
	tmp -> bef = 0;
	if (s->count == 1)
		s->tail = 0;
	else
		s->head->bef = 0;
	s->count--;
	return (tmp);
}

t_node	*pop_back(t_stack *s)
{
	t_node	*tmp;

	if (!s || s -> count == 0)
		return (0);
	tmp = s-> tail;
	s->tail = s->tail->bef;
	tmp ->bef = 0;
	tmp -> next = 0;
	if (s->count == 1)
	{
		s->head = 0;
		s->tail = 0;
	}
	else
		s->tail->next = 0;
	s->count--;
	return (tmp);
}

int	ft_is_sorted(t_stack *a, t_stack *b)
{
	t_node	*node;

	node = a->head;
	if (b->count != 0 || a->count == 0)
		return (0);
	if (a->count == 1)
		return (1);
	while (node -> next)
	{
		if (node -> num > node -> next -> num)
			return (0);
		node = node -> next;
	}
	return (1);
}
