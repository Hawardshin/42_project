/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 17:22:52 by tson              #+#    #+#             */
/*   Updated: 2022/11/26 15:49:32 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/node.h"
#include "../../include/just_for_test.h"
#include "../../include/utils.h"
#include "../libft/libft.h"

void	ft_unset(char **cmd)
{
	int	i;
	int	eflag;

	i = 1;
	eflag = 0;
	while (cmd[i])
	{
		if (ft_strchr(cmd[i], '=') || ft_strchr(cmd[i], '-'))
		{
			ft_eprintf("minishell: unset: `%s': \
			not a valid identifier", cmd[i]);
			i++;
			eflag = 1;
			continue ;
		}
		env_lst_delete(cmd[i]);
		i++;
	}
	if (eflag)
		exit(1);
}
