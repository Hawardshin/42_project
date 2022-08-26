/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 15:06:23 by joushin           #+#    #+#             */
/*   Updated: 2022/08/26 15:56:12 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "./libft/libft.h"
# define BUFFER_SIZE 400
//옵션으로 들어온 녀석 까지 같이 검사해주면 될까? ls -c 는 실행되는데 cat -c는 실행이 안됨..

void	my_free(char **to_free)
{
	free(*to_free);
	*to_free = NULL;
}
char	*ft_mstrdup(const char *s1)
{
	char	*result;
	size_t	len;

	len = ft_strlen(s1);
	result = (char *)malloc(sizeof(char) * (len + 1));
	if (!result)
		print_error(0,NULL);
	ft_strlcpy(result, s1, len + 1);
	return (result);
}

void	print_error(int	Flag, char *s)
{
	if (Flag == 0)
	{
		ft_putstr_fd("Memory allocation fails.\n", 2);
		exit(1);
	}
	else if (Flag == 1)
	{
		ft_eprintf("command not found: %s\n", s);
		exit(127);
	}
	else if (Flag == 2)
	{
		// perror(s);
		exit(1);
	}
	else if (Flag == 3)
	{
		ft_eprintf("no such file or directory: %s\n",s);
		exit(1);
	}
}
char	*ft_mstrjoin(char const *s1, char const *s2)
{
	char	*retstr;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (0);
	i = 0;
	retstr = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!retstr)
		print_error(0, NULL);
	while (s1[i])
	{
		retstr[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		retstr[i + j] = s2[j];
		j++;
	}
	retstr[i + j] = '\0';
	return (retstr);
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

t_px	*mlst_find(int idx, t_data *data)
{
	t_px	*node;

	node = data->cmd_node_head;
	while (node)
	{
		if (node->idx == idx)
			return (node);
		node = node ->next;
	}
	return (NULL);
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
			if (ft_strncmp(px->path[i], "/", 1) != 0)
				pathname = ft_mstrjoin(px->path[i], ft_mstrjoin("/", node->cmd[0]));
			else
				pathname = ft_mstrdup(px->path[i]);
			if (access(pathname, R_OK | X_OK) == 0)
				node->cmd_path[0] = ft_mstrdup(pathname);
			my_free(&pathname);
		}
	}
}

pid_t	mfork(void)//fork를 실패하면 프로세스를 종료하는 게 맞는걸까?
{
	pid_t	rpid;

	rpid = fork();
	if (rpid == -1)
	{
		perror("fork error ");
		exit(1);
	}
	return (rpid);
}

void	exec_pipe(int idx, t_data *px)
{
	t_px	*node;
	int	status;

	wait(&status);
	node = mlst_find(idx, px);
	if (dup2(px->pipefd[1], 0) == -1)
		print_error(2, NULL);
	if (dup2(px->pipefd[0], 1) == -1)
		print_error(2, NULL);
	close(px->pipefd[1]);
	close(px->pipefd[0]);
	if (node->cmd_path[0] != NULL)
		execve(node->cmd_path[0], node->cmd, px->ev);
	print_error(1, node->cmd[0]);
}

void	exec_first(t_data *px)
{
	int		o_fd;
	t_px	*node;

	node = px->cmd_node_head;
	o_fd = open(px->infile, O_RDONLY);
	close(px->pipefd[0]);
	if (o_fd == -1)
		print_error(3, px->infile);
	if (dup2(o_fd, 0) == -1)
		print_error(2, NULL);
	if (dup2(px->pipefd[1], 1) == -1)
		print_error(2, NULL);
	close(o_fd);
	close(px->pipefd[1]);
	if (node->cmd_path[0] != NULL)
		execve(node->cmd_path[0], node->cmd, px->ev);
	print_error(1, node->cmd[0]);
}
//만약 명령어 갯수가 1일 때 2번 실행가능성 있다.
void	exec_last(t_data *px)
{
	int		o_fd;
	int		status;
	t_px	*node;

	node = px->cmd_node_tail;
	wait(&status);
	close(px->pipefd[1]);
	o_fd = open(px->outfile, O_WRONLY);
	if (o_fd == -1)
		print_error(3, px->infile);
	if (dup2(px->pipefd[0], 0) == -1)
		print_error(2, NULL);
	if (dup2(o_fd, 1) == -1)
		print_error(2, NULL);
	close(px->pipefd[0]);
	close(o_fd);
	if (node->cmd_path[(px->pipe_num) - 1] != NULL)
		execve(node->cmd_path[(px->pipe_num) - 1], (node->cmd), px->ev);
	print_error(1, node->cmd[0]);
}

void	fork_child(t_data *px)
{
	int		i;
	pid_t	pid;

	i = -1;
	while (++i < px->pipe_num)
	{
		pid = mfork();
		if (pid == 0)
		{
			if (i == 0)
				exec_first(px);
			else if (i + 1 == px->pipe_num)
				exec_last(px);
			else
				exec_pipe(i, px);
		}
	}
}
int	main(int argc, char **argv, char **envp)
{
	t_data	px;
	if (argc == 5)
	{
		ft_memset(&px, 0, sizeof(t_px));
		px.ev = envp;
		parse_input(&px, argc, argv, envp);//파싱하기
		cmd_init(&px);//명령어 체크해서 있으면 제대로 없으면 NULL로 채워주기]
		fork_child(&px);
	}
	else
		return (1);
	return (0);
}
