/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 12:10:01 by joushin           #+#    #+#             */
/*   Updated: 2022/08/06 16:49:24 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdlib.h>
# include <unistd.h>

typedef struct s_node
{
	int				num;
	struct s_node	*next;
	struct s_node	*bef;
}t_node;

typedef struct s_stack
{
	t_node	*head;
	t_node	*tail;
}t_stack;

#endif
