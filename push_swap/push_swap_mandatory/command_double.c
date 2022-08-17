/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_double.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 18:55:59 by joushin           #+#    #+#             */
/*   Updated: 2022/08/17 15:43:11 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	rrr_stack(t_stack *a, t_stack *b)
{
	if (a -> count == 0)
		return (rreverse_stack(a, b, 'b'));
	else if (b -> count == 0)
		return (rreverse_stack(a, b, 'a'));
	write(1, "rrr\n", 4);
	rreverse_stack(a, b, 'A');
	rreverse_stack(a, b, 'B');
}

void	rr_stack(t_stack *a, t_stack *b)
{
	if (a -> count == 0)
		return (reverse_stack(a, b, 'b'));
	else if (b -> count == 0)
		return (reverse_stack(a, b, 'a'));
	write(1, "rr\n", 3);
	reverse_stack(a, b, 'A');
	reverse_stack(a, b, 'B');
}

void	ss_stack(t_stack *a, t_stack *b)
{
	if (a -> count == 0)
		return (swap_stack(a, b, 'b'));
	else if (b -> count == 0)
		return (swap_stack(a, b, 'a'));
	write(1, "ss\n", 3);
	swap_stack(a, b, 'A');
	swap_stack(a, b, 'B');
}

void	command_optimize(t_stack *a, t_stack *b, t_node **node)
{
	int	idx;

	if ((*node)->bscore > b->count / 2 && (*node)->ascore > a->count / 2)
	{
		idx = b->count - (*node)->bscore;
		if (b->count - (*node)->bscore > a-> count - (*node)->ascore)
			idx = a-> count - (*node)->ascore;
		(*node)->bscore = (*node)->bscore + idx;
		(*node)->ascore = (*node)->ascore + idx;
		idx++;
		while (--idx)
			rrr_stack(a, b);
	}
	else if ((*node)->bscore <= b->count / 2 && (*node)->ascore <= a->count / 2)
	{
		idx = (*node)->ascore;
		if ((*node)->bscore < (*node)->ascore)
			idx = (*node)->bscore;
		(*node)->ascore = (*node)->ascore - idx;
		(*node)->bscore = (*node)->bscore - idx;
		idx++;
		while (--idx)
			rr_stack(a, b);
	}
}
