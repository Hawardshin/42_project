/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 15:13:50 by joushin           #+#    #+#             */
/*   Updated: 2022/11/15 14:12:30 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/node.h"
#include "./include/env.h"
#include "./libft/libft.h"

void	env_lst_add_back(char *key, char *value)// 문자열을 동적할당해서 들어온다고 가정.
{
	t_env *node;

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

char	*get_env(char *key) // 전역변수의 환경변수 주소값을 리턴해준다.
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

void	init_g_state(char **envp)
{
	t_env	*env_node;
	int		i;
	char	*key;
	char	*value;

	while (*envp)
	{
 		env_node = malloc(sizeof(t_env));
		ft_memset(env_node, 0, sizeof(t_env));
		i = 0;
		while ((*envp)[i])
		{
			if ((*envp)[i] == '=')
			{
				key = malloc(i + 1);
				key[0] = '\0';
				ft_strlcpy(key, *envp, i + 1);
				key[i] = '\0';
				i++;
				value = malloc(ft_strlen((*envp) + i) + 1);
				ft_strlcpy (value, (*envp) + i ,ft_strlen((*envp) + i) + 1);
				value[ft_strlen((*envp) + i)] = '\0';
				env_lst_add_back(key, value);
				break ;
			}
			i++;
		}
		envp++;
	}
}
