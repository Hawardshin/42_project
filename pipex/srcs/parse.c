/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 16:52:48 by joushin           #+#    #+#             */
/*   Updated: 2022/08/30 16:11:00 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "./libft/libft.h"

void	awk_sed(char **argv, int i, t_px *node)
{
	int		j;
	int		tmp;
	char	**tmp_node;

	j = 0;
	node->cmd = ft_msplit(argv[i + 2], ' ');
	while (ft_strncmp(node->cmd[j], "\'", 1) != 0 && node->cmd[j])
		j++;
	tmp = j;
	if (node->cmd[j] == 0)
		return ;
	while (node->cmd[j])
		my_free(&(node->cmd[j++]));
	tmp_node = ft_msplit(argv[i + 2], '\'');
	node->cmd[tmp] = ft_mstrdup(tmp_node[1]);
	if (!tmp_node[1])
		node->cmd[tmp + 1] = ft_mstrdup(tmp_node[2]);
	tmp = 0;
	while (tmp_node[tmp])
	{
		my_free(&tmp_node[tmp]);
		tmp++;
	}
	free(tmp_node);
	tmp_node = NULL;
}

void	node_init(t_data *px, char **argv)
{
	int		i;
	t_px	*node;

	i = -1;
	while (++i < px->pipe_num)
	{
		node = (t_px *)malloc(sizeof(t_px));
		if (!node)
			print_error(0, NULL);
		node->next = NULL;
		node->idx = i;
		if (!ft_strncmp(argv[i + 2], "awk ", 4) && \
			!ft_strncmp(argv[i + 2], "sed ", 4))
			awk_sed(argv, i, node);
		else
			node ->cmd = ft_msplit(argv[i + 2], ' ');
		if (px->cmd_node_head != NULL)
			px->cmd_node_tail->next = node;
		else
			px->cmd_node_head = node;
		px->cmd_node_tail = node;
	}
}

void	parse_input(t_data *px, int argc, char **argv, char **envp)
{
	px->infile = argv[1];
	px->outfile = argv[4];
	px->pipe_num = argc - 3;
	node_init(px, argv);
	while (ft_strncmp(*envp, "PATH", 4) != 0 && envp)
		envp++;
	if (!envp)
		print_error(3, "Not exist path!\n");
	px->path = ft_msplit(ft_mstrdup(*envp + 5), ':');
	if (pipe(px->pipefd) == -1)
		print_error(3, "pipe error\n");
}

void	cmd_init(t_data *px)
{
	char	*ptmp;
	int		idx;
	int		i;
	t_px	*node;

	idx = -1;
	while (++idx < px->pipe_num)
	{
		node = mlst_find(idx, px);
		ft_memset(node->cmd_path, 0, 2);
		i = -1;
		while (px -> path[++i])
		{
			if (ft_strncmp(node->cmd[0], "/", 1) != 0)
				ptmp = ft_mstrjoin(px->path[i], ft_mstrjoin("/", node->cmd[0]));
			else
				ptmp = ft_mstrdup(node->cmd[0]);
			if (access(ptmp, R_OK | X_OK) == 0)
				node->cmd_path[0] = ft_mstrdup(ptmp);
			my_free(&ptmp);
		}
	}
}
