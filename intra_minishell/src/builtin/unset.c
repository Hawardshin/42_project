/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 17:22:52 by tson              #+#    #+#             */
/*   Updated: 2022/11/26 22:12:28 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "node.h"
#include "libft.h"

int	ft_unset(char **cmd)
{
	int	i;
	int	eflag;

	i = 1;
	eflag = 0;
	while (cmd[i])
	{
		if (ft_strchr(cmd[i], '=') || ft_strchr(cmd[i], '-'))
		{
			ft_eprintf \
			("minishell: unset: `%s': not a valid identifier\n", cmd[i]);
			i++;
			eflag = 1;
			continue ;
		}
		env_lst_delete(cmd[i]);
		i++;
	}
	if (eflag)
	{
		g_state.exit_code = -1;
		return (1);
	}
	return (0);
}
