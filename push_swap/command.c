/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 12:42:34 by joushin           #+#    #+#             */
/*   Updated: 2022/08/06 14:09:25 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_node	*new_node(char a)
{
	t_node	*new_lst;

	new_lst = (t_node *)malloc(sizeof(t_node));
	if (!new_lst)
		return (new_lst);
	new_lst -> num;
}
//노드 만드는데.
