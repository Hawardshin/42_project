/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 15:22:45 by joushin           #+#    #+#             */
/*   Updated: 2022/11/26 22:14:51 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "node.h"
#include "utils.h"
#include "libft.h"

static t_env	*make_new_env(char *key, char *value)
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

static void	lst_add_back_main_node(t_env_main_node *main_node, t_env *new_env)
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
