/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pase.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 16:52:48 by joushin           #+#    #+#             */
/*   Updated: 2022/08/26 16:54:47 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "./libft/libft.h"

void	node_init(t_data *px, char **argv)
{
	int		i;
	t_px	*node;

	i = -1;
	while (++i < px->pipe_num)
	{
		node = (t_px *)malloc(sizeof (t_px));
		if (!node)
			print_error(0,NULL);
		node->next = NULL;
		node->idx = i;
		node ->cmd = ft_msplit(argv[i + 2],' ');//argv[0] : 실행파일 argv[1] : 파일1번
		if (px->cmd_node_head != NULL)
		{
			node->bef = px->cmd_node_tail;
			px->cmd_node_tail->next = node;
		}
		else
		{
			px->cmd_node_head = node;
			node->bef = NULL;
		}
		px->cmd_node_tail = node;
	}
}

void	parse_input(t_data *px, int argc, char **argv, char **envp)
{
	px->infile = argv[1];
	px->outfile = argv[4];
	px->ev = envp;
	px->pipe_num = argc - 3;//파이프 갯수
	node_init(px, argv);
	while (ft_strncmp(*envp, "PATH", 4) != 0 && envp)
		envp++;
	if (!envp)
		print_error(2, "Not exist path!\n");
	px -> path = ft_msplit(ft_mstrdup(*envp + 5), ':');
	if (pipe(px->pipefd) == -1)
		print_error(2, "pipe error\n");
}

//명령어에 이미 /가 있다면 그냥 그대로 실행해보고 아니면 /붙혀서 해본다.
//명령어를 찾아서 각 노드별로 명령어를 적어주는 방식사용
void	cmd_init(t_data *px)
{
	char	*pathname;
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
				pathname = ft_mstrjoin(px->path[i], ft_mstrjoin("/", node->cmd[0]));
			else
				pathname = ft_mstrdup(px->path[i]);
			if (access(pathname, R_OK | X_OK) == 0)
				node->cmd_path[0] = ft_mstrdup(pathname);
			my_free(&pathname);
		}
	}
}
