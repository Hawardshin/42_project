/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 16:52:48 by joushin           #+#    #+#             */
/*   Updated: 2022/08/29 20:26:44 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "./libft/libft.h"

static int	check_in(char a, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == a)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_mstrtrim(char **s1, char const *set)
{
	int		start;
	int		end;
	int		i;
	char	*ret;

	start = 0;
	i = 0;
	if (!(*s1))
		return (0);
	if (!set)
		return ((char *)(*s1));
	end = ft_strlen(*s1) - 1;
	while ((*s1)[start] && check_in((*s1)[start], set))
		start++;
	while ((*s1)[end] && check_in((*s1)[end], set) && start <= end)
		end--;
	ret = (char *)malloc(sizeof(char) * (end - start + 2));
	if (!ret)
		print_error(0, NULL);
	while (start <= end)
		ret[i++] = (*s1)[start++];
	ret[i] = '\0';
	my_free(s1);
	return (ret);
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
		if (!ft_strncmp(argv[i + 2], "awk ", 4) || \
			!ft_strncmp(argv[i + 2], "sed ", 4))
		{
			node->cmd = ft_split(argv[i + 2], '\'');
			node -> cmd[0] = ft_mstrtrim(&(node->cmd[0]), " ");
		}
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
	px->ev = envp;
	px->pipe_num = argc - 3;//파이프 갯수
	node_init(px, argv);
	while (ft_strncmp(*envp, "PATH", 4) != 0 && envp)
		envp++;
	if (!envp)
		print_error(2, "Not exist path!\n");
	px->path = ft_msplit(ft_mstrdup(*envp + 5), ':');
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
				pathname = ft_mstrdup(node->cmd[0]);
			if (access(pathname, R_OK | X_OK) == 0)
				node->cmd_path[0] = ft_mstrdup(pathname);
			my_free(&pathname);
		}
	}
}
