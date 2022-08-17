/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 14:57:12 by joushin           #+#    #+#             */
/*   Updated: 2022/08/17 15:36:40 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap_bonus.h"

static int	ft_strcmp(char *s, char *com)
{
	while (*s && *com)
	{
		if (*s != *com)
			return (0);
		s++;
		com++;
	}
	if (*s == 0 && *com == 0)
		return (1);
	else
		return (0);
}

static void	check_fuc(char *s, t_stack*a, t_stack*b)
{
	if (ft_strcmp(s, "pa\n"))
		push_stack(a, b, 'a');
	else if (ft_strcmp(s, "pb\n"))
		push_stack(a, b, 'b');
	else if (ft_strcmp(s, "sa\n"))
		swap_stack(a, b, 'a');
	else if (ft_strcmp(s, "sb\n"))
		swap_stack(a, b, 'b');
	else if (ft_strcmp(s, "rra\n"))
		rreverse_stack(a, b, 'a');
	else if (ft_strcmp(s, "rrb\n"))
		rreverse_stack(a, b, 'b');
	else if (ft_strcmp(s, "ra\n"))
		reverse_stack(a, b, 'a');
	else if (ft_strcmp(s, "rb\n"))
		reverse_stack(a, b, 'b');
	else if (ft_strcmp(s, "rrr\n"))
		rrr_stack(a, b);
	else if (ft_strcmp(s, "rr\n"))
		rr_stack(a, b);
	else if (ft_strcmp(s, "ss\n"))
		ss_stack(a, b);
	else
		ft_error();
}

static int	ft_is_sorted(t_stack *a, t_stack *b)
{
	t_node	*node;

	node = a->head;
	if (b->count != 0)
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

void	sort_check(t_stack *a, t_stack *b)
{
	char	*s;

	while (1)
	{
		s = get_next_line(0);
		if (s == NULL)
			break ;
		check_fuc(s, a, b);
		free(s);
		s = NULL;
	}
	if (ft_is_sorted (a, b))
		write(1, "OK\n", 3);
	else
		write(1, "KO\n", 3);
}
