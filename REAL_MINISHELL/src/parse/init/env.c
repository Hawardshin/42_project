/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 15:13:50 by joushin           #+#    #+#             */
/*   Updated: 2022/11/26 17:21:43 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/node.h"
#include "../../../include/just_for_test.h"
#include "../../../include/utils.h"
#include "../../libft/libft.h"

// 전역변수의 환경변수 주소값을 리턴해준다.
char	*get_env(char *key)
{
	t_env	*e_node;

	e_node = g_state.env_main_node.head;
	while (e_node)
	{
		if (ft_strcmp(e_node->key, key) == 0)
			return (e_node->value);
		else
			e_node = e_node->next;
	}
	return (NULL);
}

t_env	*get_env_of_idx(int idx)
{
	t_env	*ret;
	int		i;

	ret = g_state.env_main_node.head;
	i = 0;
	while (ret)
	{
		if (i == idx)
			break ;
		ret = ret->next;
		i++;
	}
	return (ret);
}

void	make_key_value(int i, char **envp)
{
	char	*key;
	char	*value;

	key = malloc(i + 1);
	if (!key)
		print_error(0, NULL);
	key[0] = '\0';
	ft_strlcpy(key, *envp, i + 1);
	key[i] = '\0';
	i++;
	value = malloc(ft_strlen((*envp) + i) + 1);
	if (!value)
		print_error(0, NULL);
	ft_strlcpy (value, (*envp) + i, ft_strlen((*envp) + i) + 1);
	value[ft_strlen((*envp) + i)] = '\0';
	env_lst_add_back(key, value);
}

void	init_g_state(char **envp)
{
	t_env	*env_node;
	int		i;

	while (*envp)
	{
		env_node = malloc(sizeof(t_env));
		if (!env_node)
			print_error(0, NULL);
		ft_memset(env_node, 0, sizeof(t_env));
		i = -1;
		while ((*envp)[++i])
		{
			if ((*envp)[i] == '=')
			{
				make_key_value(i, envp);
				break ;
			}
		}
		envp++;
	}
}
