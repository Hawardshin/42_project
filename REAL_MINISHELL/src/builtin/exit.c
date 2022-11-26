/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 16:21:52 by tson              #+#    #+#             */
/*   Updated: 2022/11/25 20:13:02 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/node.h"
#include "../../include/just_for_test.h"
#include "../../include/utils.h"
#include "../libft/libft.h"
#include "../../include/builtin.h"

unsigned char	char_atoi(char *str)
{
	unsigned char	ret;
	int				i;
	int				minus;

	ret = 0;
	i = 0;
	minus = 1;
	if (str[0] == '-')
	{
		i = 1;
		minus = -1;
	}
	while (str[i])
	{
		ret *= 10;
		ret += (str[i] - '0') * minus;
		i++;
	}
	return (ret);
}

int	exist_not_numeric(char *str)
{
	int	i;

	i = 0;
	if (ft_strlen(str) > 0 && str[0] == '-')
		i++;
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (1);
		i++;
	}
	return (0);
}

void	ft_exit(char **cmd)
{
	if (cmd_len(cmd) == 1)
		exit(0);
	if (exist_not_numeric(cmd[1]))
	{
		printf("minishell: exit: %s: numeric argument required", cmd[1]);
		exit(255);
		return ;
	}
	if (cmd_len(cmd) > 2)
	{
		printf("minishell: exit: too many arguments\n");
		return ;
	}
	exit(char_atoi(cmd[1]));
}
