/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 21:12:18 by joushin           #+#    #+#             */
/*   Updated: 2022/11/25 21:12:51 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/node.h"
#include "../../include/just_for_test.h"
#include "../../include/utils.h"
#include "../../include/builtin.h"
#include "../libft/libft.h"

int	ft_built_check(char *str)
{
	if (str == NULL)
		return (0);
	if (!ft_strncmp(str, "cd", 3) || \
			!ft_strncmp(str, "echo", 5) || \
			!ft_strncmp(str, "pwd", 4) || \
			!ft_strncmp(str, "export", 7) || \
			!ft_strncmp(str, "unset", 6) || \
			!ft_strncmp(str, "env", 4) || \
			!ft_strncmp(str, "exit", 5))
		return (1);
	return (0);
}

int	ft_built_first_check(char *str)//하나라도 명령어에 해당하는게 있으면 1반환
{
	if (str == NULL)
		return (0);
	if (!ft_strncmp(str, "cd", 3) || \
			!ft_strncmp(str, "export", 7) || \
			!ft_strncmp(str, "unset", 6) ||\
			!ft_strncmp(str, "exit", 5))
		return (1);
	return (0);
}

int	ft_in_built(t_node *val, int flag)
{
	if (val->cmd[0] == NULL)
		ft_eprintf("이딴건 코드가 아니야\n");
	if (!ft_strncmp(val->cmd[0], "cd", 3))
		ft_cd(val->cmd, flag);
	else if (!ft_strncmp(val->cmd[0], "echo", 5))
		ft_echo(val->cmd);
	else if (!ft_strncmp(val->cmd[0], "pwd", 4))
		ft_pwd();
	else if (!ft_strncmp(val->cmd[0], "export", 7))
		ft_export(val->cmd);
	else if (!ft_strncmp(val->cmd[0], "unset", 6))
		ft_unset(val->cmd);
	else if (!ft_strncmp(val->cmd[0], "env", 4))
		ft_env(0, "");
	else if (!ft_strncmp(val->cmd[0], "exit", 5))
		ft_exit(val->cmd);
	return (0);
}
