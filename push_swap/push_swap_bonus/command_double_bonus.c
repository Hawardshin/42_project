/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_double_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 18:55:59 by joushin           #+#    #+#             */
/*   Updated: 2022/08/17 17:10:49 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap_bonus.h"

void	rrr_stack(t_stack *a, t_stack *b)
{
	if (a -> count == 0)
		return (rreverse_stack(a, b, 'b'));
	else if (b -> count == 0)
		return (rreverse_stack(a, b, 'a'));
	rreverse_stack(a, b, 'A');
	rreverse_stack(a, b, 'B');
}

void	rr_stack(t_stack *a, t_stack *b)
{
	if (a -> count == 0)
		return (reverse_stack(a, b, 'b'));
	else if (b -> count == 0)
		return (reverse_stack(a, b, 'a'));
	reverse_stack(a, b, 'A');
	reverse_stack(a, b, 'B');
}

void	ss_stack(t_stack *a, t_stack *b)
{
	if (a -> count == 0)
		return (swap_stack(a, b, 'b'));
	else if (b -> count == 0)
		return (swap_stack(a, b, 'a'));
	swap_stack(a, b, 'A');
	swap_stack(a, b, 'B');
}
