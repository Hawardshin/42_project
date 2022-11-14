/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 14:58:39 by joushin           #+#    #+#             */
/*   Updated: 2022/11/14 17:14:34 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

#include "node.h"

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
	struct s_env	*prev;
}	t_env;

typedef struct s_env_main_node
{
	t_env	*head;
	t_env	*tail;
}	t_env_main_node;

typedef struct s_state
{
	t_env_main_node	env_main_node;
	pid_t			pid;
	int				exit_code;
	// int				is_fork;
}	t_state;

t_state	g_state;



void	init_g_state(char **envp);
char	*get_env(char *key);

#endif
