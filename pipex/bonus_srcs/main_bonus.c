/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 15:06:23 by joushin           #+#    #+#             */
/*   Updated: 2022/08/31 16:31:20 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include "../srcs/libft/libft.h"

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

void	ft_all_close(t_data *px, int idx, int bef)
{
	int	i;

	i = 0;
	while (i < px->cmd_num - 1)
	{
		if (i != idx && i != bef)
		{
			close(px->pipefd[i][0]);
			close(px->pipefd[i][1]);
		}
		i++;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_data	px;

	if (argc >= 5)
	{
		ft_memset(&px, 0, sizeof(t_data));
		px.ev = envp;
		if (ft_strncmp(argv[1], "here_doc", 8) == 0)
		{
			parse_input(&px, argc - 1, argv + 1, envp);
			px.flag = 1;
		}
		else
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
