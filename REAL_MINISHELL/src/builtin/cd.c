/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 16:23:04 by tson              #+#    #+#             */
/*   Updated: 2022/11/25 22:06:53 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/node.h"
#include "../../include/just_for_test.h"
#include "../../include/utils.h"
#include "../libft/libft.h"

int	cmd_len(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
		i++;
	return (i);
}

void	ft_cd(char **cmd, int flag)
{
	if (cmd_len(cmd) == 1)
	{
		chdir(get_env("HOME"));
		return ;
	}
	if (chdir(cmd[1]) == -1)
	{
		if (flag)
		{
			ft_eprintf("minishell: cd: %s: No such file or directory\n", cmd[1]);
			g_state.exit_code = -1;
		}
		else
		{
			ft_eprintf("minishell: cd: %s: No such file or directory\n", cmd[1]);
			exit (1);
		}
	}
}
