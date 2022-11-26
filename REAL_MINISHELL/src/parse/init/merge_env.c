/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 15:22:45 by joushin           #+#    #+#             */
/*   Updated: 2022/11/25 20:12:19 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/node.h"
#include "../../../include/node.h"
#include "../../../include/just_for_test.h"
#include "../../../include/utils.h"
#include "../../libft/libft.h"

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

t_env	*make_new_env(char *key, char *value)
{
	t_env	*ret;

	ret = malloc(sizeof(t_env));
	if (ret == NULL)
		print_error(0, NULL);
	ft_memset(ret, 0, sizeof(t_env));
	ret->key = ft_strdup(key);
	if (ret->key == NULL)
		print_error(0, NULL);
	if (value == NULL)
	{
		ret->value = NULL;
		return (ret);
	}
	ret->value = ft_strdup(value);
	if (ret->value == NULL)
		print_error(0, NULL);
	return (ret);
}

void	lst_add_back_main_node(t_env_main_node *main_node, t_env *new_env)
{
	t_env	*last_env;

	(main_node->count)++;
	last_env = main_node->tail;
	if (last_env == NULL)
	{
		main_node->head = new_env;
		main_node->tail = new_env;
		return ;
	}
	last_env->next = new_env;
	new_env->prev = last_env;
	main_node->tail = new_env;
}

t_env_main_node	env_dup(t_env_main_node env)
{
	t_env			*new_env;
	t_env			*p;
	t_env_main_node	ret;

	p = env.head;
	ft_memset(&ret, 0, sizeof(t_env_main_node));
	while (p)
	{
		new_env = make_new_env(p->key, p->value);
		lst_add_back_main_node(&ret, new_env);
		p = p->next;
	}
	return (ret);
}

char	**ret_env_char(void)
{
	char	**ret_env;
	char	*tmp;
	int		i;
	t_env	*e_node;

	i = 0;
	ret_env = malloc(sizeof(char *) * (g_state.env_main_node.count + 1));
	if (!ret_env)
		print_error(0, NULL);
	e_node = g_state.env_main_node.head;
	while (e_node)
	{
		tmp = ft_mstrjoin(e_node->key, "=");
		ret_env[i] = ft_mstrjoin(tmp, e_node->value);
		free(tmp);
		e_node = e_node->next;
		i++;
	}
	ret_env[i] = NULL;
	return (ret_env);
}
