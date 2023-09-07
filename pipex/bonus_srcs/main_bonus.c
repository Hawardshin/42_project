/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 15:06:23 by joushin           #+#    #+#             */
/*   Updated: 2022/09/02 11:38:13 by joushin          ###   ########.fr       */
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

void	ft_end_free(t_data *px)
{
	t_px	*node;
	t_px	*tmp;
	int		i;

	node = px->cmd_node_head;
	while (node)
	{
		i = 0;
		tmp = node;
		node = node->next;
		while (tmp->cmd[i])
			my_free(&(tmp ->cmd[i++]));
		free(tmp->cmd);
		if (tmp->cmd_path[0])
			my_free(&(tmp->cmd_path[0]));
		free(tmp);
	}
	i = 0;
	while (px->path[i])
		my_free(&(px->path[i++]));
	free(px->path);
	i = 0;
	while (i < px->cmd_num - 1)
		free(px->pipefd[i++]);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	px;

	if (argc >= 5)
	{
		ft_memset(&px, 0, sizeof(t_data));
		if (ft_strncmp(argv[1], "here_doc", 8) == 0)
		{
			if (argc == 5)
				return (ft_eprintf("argv error\n"));
			px.flag = 1;
			parse_input(&px, argc - 1, argv + 1, envp);
		}
		else
			parse_input(&px, argc, argv, envp);
		cmd_init(&px);
		return (fork_child(&px));
	}
	else
		return (ft_eprintf("argv error\n"));
	return (0);
}
