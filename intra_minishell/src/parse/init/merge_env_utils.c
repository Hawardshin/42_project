/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_env_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 15:59:11 by joushin           #+#    #+#             */
/*   Updated: 2022/11/26 22:14:30 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "node.h"
#include "libft.h"

void	free_all_env_main_node(t_env_main_node *main_node)
{
	t_env	*del;
	t_env	*p;

	del = main_node->head;
	if (del == NULL)
		return ;
	p = del->next;
	while (1)
	{
		free(del);
		del = p;
		if (del == NULL)
			break ;
		p = del->next;
	}
	ft_memset(main_node, 0, sizeof(t_env_main_node));
}

t_env	*env_of_idx(t_env_main_node main_node, int idx)
{
	int		i;
	t_env	*ret;

	i = 0;
	ret = main_node.head;
	while (!(ret == NULL || i >= idx))
	{
		i++;
		ret = ret->next;
	}
	return (ret);
}

void	swap_env(t_env_main_node main_node, int idx1, int idx2)
{
	char	*tmp;
	t_env	*env1;
	t_env	*env2;

	env1 = env_of_idx(main_node, idx1);
	env2 = env_of_idx(main_node, idx2);
	if (env1 == NULL || env2 == NULL)
		return ;
	tmp = env1->key;
	env1->key = env2->key;
	env2->key = tmp;
	tmp = env1->value;
	env1->value = env2->value;
	env2->value = tmp;
}
