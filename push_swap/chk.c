/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chk.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 11:51:03 by joushin           #+#    #+#             */
/*   Updated: 2022/08/13 16:25:44 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	two_argv(t_stack *a, t_stack *b)
{
	t_node	*node;

	node = a-> head;
	if (node->num < node -> next ->num)
		return ;
	else
		swap_stack(a, b, 'a');
}

static int	get_flag_three(int val1, int val2, int val3)
{
	if ((val1 > val2) && (val2 > val3))
		return (1);
	else if ((val1 > val2) && (val2 < val3) && (val1 > val3))
		return (2);
	else if ((val1 < val2) && (val2 > val3) && (val1 > val3))
		return (3);
	else if ((val1 > val2) && (val2 < val3) && (val1 < val3))
		return (4);
	else if ((val1 < val2) && (val2 > val3) && (val1 < val3))
		return (5);
	else
		return (0);
}

static void	three_sort(t_stack *a, t_stack *b, int flag, char c)//c 는 무조건 a
{
	if (flag == 1)
	{
		swap_stack(a, b, c);
		rreverse_stack(a, b, c);
	}
	if (flag == 2)
		reverse_stack(a, b, c);
	if (flag == 3)
		rreverse_stack(a, b, c);
	if (flag == 4)
		swap_stack(a, b, c);
	if (flag == 5)
	{
		swap_stack(a, b, c);
		reverse_stack(a, b, c);
	}
}

void	three_argv(t_stack *a, t_stack *b)//char c 넣어서 둘다?
{
	int		count;
	int		flag;
	t_node	*node;

	node = a->head;
	// if (is_sorted(a))
	// 	return ;
	count = a ->count;
	// while (count > 3)
	// {
	// 	push_stack(a, b, 'b');
	// 	count--;
	// }
	flag = get_flag_three(node->num, node->next->num, node->next->next->num);
	three_sort(a, b, flag, 'a');
}
