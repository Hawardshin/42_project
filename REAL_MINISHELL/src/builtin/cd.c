/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 16:23:04 by tson              #+#    #+#             */
/*   Updated: 2022/11/26 20:05:52 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/node.h"
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

void	translate_minus(char **cmd)
{
	free(cmd[1]);
	cmd[1] = ft_mstrdup(get_env("OLDPWD"));
}

void	ft_cd(char **cmd, int flag)
{
	char	*pwd;

	if (cmd_len(cmd) == 1)
	{
		chdir(get_env("HOME"));
		return ;
	}
	if (ft_strcmp(cmd[1], "-") == 0)
		translate_minus(cmd);
	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
		print_error(0, NULL);
	if (chdir(cmd[1]) == -1)
	{
		ft_eprintf("minishell: cd: %s: No such file or directory\n", cmd[1]);
		if (flag)
			g_state.exit_code = -1;
		else
			exit (1);
		return ;
	}
	env_lst_add_back(ft_mstrdup("OLDPWD"), pwd);
}
