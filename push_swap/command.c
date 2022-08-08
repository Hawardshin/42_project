/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 10:47:46 by joushin           #+#    #+#             */
/*   Updated: 2022/08/08 15:58:06 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "./libft/libft.h"

void	push_front(t_stack *s, t_node *new)
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

void	push_back(t_stack *s, t_node *new)
{
	if (s -> count ==0)
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
	// if (!s || s -> count != 0)
	// 	return (0);
	t_node	*tmp;

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

t_node	*pop_back(t_stack *s)//검증 필요
{
	// if (!s || s -> count != 0)
	// 	return (0);
	t_node	*tmp;

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

void	push_stack(t_stack *a, t_stack *b, char s)
{
	t_node	*tmp;

	if (s == 'a')//pa
	{
	if (b -> count == 0)
		return ;
	tmp = pop_front(b);
	push_front(a,tmp);
	write(1, "pa\n",3);
	}//s == b
	else//pb
	{
		if (a -> count == 0)
			return ;
		tmp = pop_front(a);
		//printf("kk : %d",tmp->num);
		push_front(b,tmp);
		write(1, "pb\n", 3);
	}
}


//비어있을 때 생각해야하는가?? 아직 안 함
void	swap_stack(t_stack *a, t_stack *b, char s)
{
	t_node	*tmp1;
	t_node	*tmp2;

	if (s == 'a' || s == 'A')//sa
	{
		if (s == 'a')
			write(1, "sa\n", 3);
		if (a->count < 2)
			return ;
		tmp1 = pop_front(a);
		tmp2 = pop_front(a);
		push_front(a, tmp1);
		push_front(a, tmp2);
	}
	else if (s == 'b'|| s == 'B')//sb
	{

		if (s == 'b')
			write(1, "sb\n", 3);
		if (b->count < 2)
			return ;
		tmp1 = pop_front(b);
		tmp2 = pop_front(b);
		push_front(b, tmp1);
		push_front(b, tmp2);
	}
	else//ss
	{
		write(1, "ss\n", 3);
		swap_stack(a, b, 'A');
		swap_stack(a, b, 'B');
	}
}

void	reverse_stack(t_stack *a, t_stack *b, char s)
{
	t_node	*tmp;

	if (s == 'a' || s == 'A')//ra
	{
		if (s == 'a')
			write(1, "ra\n", 3);
		tmp = pop_front(a);
		push_back(a, tmp);
	}
	else if (s == 'b'|| s == 'B')//rb
	{
		if (s == 'b')
			write(1, "ra\n", 3);
		tmp = pop_front(b);
		push_back(b, tmp);
	}
	else//rr
	{
		write(1, "rr\n", 3);
		reverse_stack(a, b, 'A');
		reverse_stack(a, b, 'B');
	}
}

void	rreverse_stack(t_stack *a, t_stack *b, char s)
{
	t_node	*tmp;

	if (s == 'a' || s == 'A')//ra
	{
		if (s == 'a')
			write(1, "rra\n", 4);
		tmp = pop_back(a);
		push_front(a, tmp);
	}
	else if (s == 'b'|| s == 'B')//rb
	{
		if (s == 'b')
			write(1, "rrb\n", 4);
		tmp = pop_back(b);
		push_front(b, tmp);
	}
	else//rr
	{
		write(1, "rrr\n", 4);
		rreverse_stack(a, b, 'A');
		rreverse_stack(a, b, 'B');
	}


}
