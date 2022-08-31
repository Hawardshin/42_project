/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 15:06:23 by joushin           #+#    #+#             */
/*   Updated: 2022/08/31 16:20:14 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "./libft/libft.h"

void	print_error(int Flag, char *s)
{
	ft_putstr_fd("pipex: ", 2);
	if (Flag == 0)
	{
		ft_putstr_fd("Memory allocation fails.\n", 2);
		exit(1);
	}
	else if (Flag == 1)
	{
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
		ft_eprintf("%s", s);
		exit(1);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_data	px;

	if (argc == 5)
	{
		ft_memset(&px, 0, sizeof(t_data));
		px.ev = envp;
		parse_input(&px, argc, argv, envp);
		cmd_init(&px);
		return (fork_child(&px));
	}
	else
	{
		ft_eprintf("argv error\n");
		return (1);
	}
	return (0);
}
