/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 16:52:48 by joushin           #+#    #+#             */
/*   Updated: 2022/08/29 12:02:33 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include "../srcs/libft/libft.h"

static char	**all_free(int i, char **result)
{
	while (--i >= 0)
	{
		free(result[i]);
		result[i] = NULL;
	}
	free(result);
	result = NULL;
	return (0);
}

void	pase_sed_awk(t_data *px, )
{
	char	*tmp;
	if (ft_strncmp(node->cmd[0], "awk", 3) == 0 || ft_strncmp(node->cmd[0], "sed") == 0)//awk sed 처리
		{
			tmp = ft_mstrdup(node->cmd[0]);
			int	idx = 0;
			while (node->cmd[idx])
			{
				free(node->cmd[idx]);
				node->cmd[idx] =NULL;
				idx++;
			}
			free(node->cmd);
			node->cmd = NULL;
			node->cmd = (char **)malloc (sizeof (char *) * 3);
			if (!(node->cmd))
				print_error(0,NULL);
			node->cmd[0] = tmp;// 이렇게 해도 될까? free하고 듑해야하는건 아닐까?
			idx = 0;
			while (argv[i + 2][idx] == *tmp)
				idx++;
			int	len = ft_strlen(argv[i + 2] + idx);
			node->cmd[1] = (char *)malloc(sizeof(char) * (len + 1));
			if (!(node ->cmd[1]))
				print_error(0, NULL);
			idx += 3;
			int j = 0;
			while (argv[i + 2][idx])
			{
				if (argv[i+2][idx] == '\'')
					idx++;
				node->cmd[1][j] = argv[i + 2][idx];
				idx++;
				j++;
			}
			node->cmd[1][j] = 0;
			node->cmd[2] = 0;
		}
}

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
		while (*argv[i + 2] == ' ')
			argv[i + 2]++;
		node ->cmd = ft_msplit(argv[i + 2],' ');//argv[0] : 실행파일 argv[1] : 파일1번
		parse_sed_awk(px, argv[i + 2], node);
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
