/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 15:13:50 by joushin           #+#    #+#             */
/*   Updated: 2022/11/25 22:17:42 by joushin          ###   ########.fr       */
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

	if (key == NULL)
	{
		ft_eprintf("minishell: export: `=%s': not a valid identifier\n", value);
		g_state.exit_code = -1;
		return ;
	}
	if (search_env(key) != NULL)
	{
		free(search_env(key)->value);
		search_env(key)->value = value;
		free(key);
		return ;
	}
	node = malloc(sizeof(t_env));
	g_state.env_main_node.count++;
	if (!node)
		print_error(0, NULL);
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

t_env	*search_env(char *key)
{
	t_env	*ret;

	ret = g_state.env_main_node.head;
	while (ret)
	{
		if (ft_strcmp(key, ret->key) == 0)
			break ;
		ret = ret->next;
	}
	return (ret);
}

void	connect_two_node(t_env *front, t_env *back)
{
	if (front == NULL && back == NULL)
		return ;
	if (front == NULL)
	{
		back->prev = NULL;
		return ;
	}
	if (back == NULL)
	{
		front->next = NULL;
		return ;
	}
	front->next = back;
	back->prev = front;
}

void	env_lst_delete(char *key)
{
	t_env	*del;

	del = search_env(key);
	connect_two_node(del->prev, del->next);
	free(del->key);
	free(del->value);
	free(del);
	g_state.env_main_node.count--;
}

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
