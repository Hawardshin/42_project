/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 20:47:56 by joushin           #+#    #+#             */
/*   Updated: 2022/11/26 22:12:56 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "node.h"
#include "utils.h"
#include "libft.h"

void	print_error(int Flag, char *s)
{
	unlink(".tmp");
	g_state.exit_code = 1;
	ft_putstr_fd("minishell: ", 2);
	if (Flag == 0)
	{
		ft_putstr_fd("Memory allocation fails.\n", 2);
		exit(1);
	}
	else if (Flag == 1)
	{
		g_state.exit_code = 127;
		ft_eprintf("%s: command not found\n", s);
		exit(127);
	}
	else if (Flag == 2)
	{
		perror(s);
		exit(1);
	}
	else if (Flag == 3)
	{
		ft_eprintf("%s\n", s);
		exit(1);
	}
}

void	syntax_error(void)
{
	ft_eprintf("minishell: syntax error near unexpected token\n");
	g_state.exit_code = 258;
}
