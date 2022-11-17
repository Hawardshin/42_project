/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 15:13:50 by joushin           #+#    #+#             */
/*   Updated: 2022/11/17 12:14:05 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/node.h"
#include "../../../include/node.h"
#include "../../../include/just_for_test.h"
#include "../../../include/utils.h"
#include "../../libft/libft.h"

// 문자열을 동적할당해서 들어온다고 가정.
void	env_lst_add_back(char *key, char *value)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	ft_memset(node, 0, sizeof (t_env));
	node->key = key;
	node->value = value;
	if (g_state.env_main_node.head)
	{
		g_state.env_main_node.tail->next = node;
		node->prev = g_state.env_main_node.tail;
		node->next = NULL;
	}
	else
		g_state.env_main_node.head = node;
	g_state.env_main_node.tail = node;
}

// 전역변수의 환경변수 주소값을 리턴해준다.
char	*get_env(char *key)
{
	t_env	*e_node;

	e_node = g_state.env_main_node.head;
	while (e_node)
	{
		if (ft_strncmp(e_node->key, key, ft_strlen(key)) == 0)
			return (e_node->value);
		else
			e_node = e_node->next;
	}
	return (NULL);
}

void	make_key_value(int i, char **envp)
{
	char	*key;
	char	*value;

	key = malloc(i + 1);
	key[0] = '\0';
	ft_strlcpy(key, *envp, i + 1);
	key[i] = '\0';
	i++;
	value = malloc(ft_strlen((*envp) + i) + 1);
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
