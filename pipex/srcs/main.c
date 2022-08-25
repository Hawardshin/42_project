/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 15:06:23 by joushin           #+#    #+#             */
/*   Updated: 2022/08/25 16:57:11 by joushin          ###   ########.fr       */
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
char	*mft_strdup(const char *s1)
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
		perror(s);
		exit(1);
	}
	else if (Flag == 3)
	{
		ft_eprintf("no such file or directory: %s\n",s);
		exit(1);
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

void	parse_input(t_data *px, char **argv, char **envp)
{
	char	*tmp_path;

	px->infile = mft_strdup(argv[1]);
	px->outfile = mft_strdup(argv[4]);
	px->ev = mft_strdup(envp);
	//if argc 갯수가 5일 때
	px->pipe_num = 2;
	node_init(px, argv);
	while (ft_strncmp(*envp, "PATH", 4) != 0 && envp)
		envp++;
	if (!envp)
		print_error(2, "Not exist path!\n");
	px -> path = ft_msplit(mft_strdup(*envp + 5), ':');
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
//만약 경로상에 존재하지 않는다면 현재 디렉토리에서도 탐색하는걸 추가할까?
void	cmd_init(t_data *px)
{
	char	*pathname;
	int		idx;
	int		i;
	char	*cmdtmp;
	t_px	*node;

	idx = -1;
	while (++idx < 2)//맨대토리라 명령어 2개
	{
		node = mlst_find(idx, px);
		node ->cmd_path[0] = 0;
		node ->cmd_path[1] = 0;
		cmdtmp = ft_strjoin("/",node->cmd[0]);
		// my_free(pipex->cmd[idx][0]);//이건 나중에 프리해주는걸로 하자.
		i = -1;
		while (px -> path[++i])
		{
			pathname = ft_strjoin(px-> path[i], cmdtmp);
			if (!pathname)
				print_error(0, NULL);
			if (access(pathname, R_OK | X_OK) == 0)
				node->cmd_path[0] = mft_strdup(pathname);
			my_free(&pathname);
		}
		// printf("ak: %s\n",pipex->cmd_path[idx][0]);
		my_free(&cmdtmp);
	}
}

void	level_fuc(t_px *pipex)
{
	int		idx;
	pid_t	pid;
	int		size;
	int		fds;
	int		fds2;

	idx = 0;
	size = 1;

	pid = fork();
	if (pid == -1)
	{
		perror("fork error ");
		exit(1);
	}//자식 프로세스
	else if (pid == 0)
	{


	}
	else
	{//부모프로세스
		fds2 = open(pipex->outfile, O_WRONLY);
		if (fds2 == -1)
		{
			perror("open error : ");
			exit(1);
		}
		sleep(2);
		idx++;
		close(pipex->pipefd[1]);
		if (dup2(pipex->pipefd[0], 0) == -1)
			exit(1);
		if (dup2(fds2, 1) == -1)
			exit(1);
		close(pipex->pipefd[0]);
		close(fds2);
		ft_error_check(idx, pipex);
		if (pipex->cmd_path[idx][0] != NULL)
			execve(pipex->cmd_path[idx][0], (pipex->cmd[idx]), pipex->ev);
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

void	exec_child(int idx, t_data *px)
{
	int	o_fd;

	if (idx == 0)
	{
		o_fd = open(px->infile, O_RDONLY);
		if (o_fd == -1)
			print_error(3, px->infile);
		if (dup2(o_fd, 0) == -1)
			print_error(2, NULL);
		if (dup2(px->pipefd[1], 1) == -1)
			print_error(2, NULL);
		close(o_fd);
		close(px->pipefd[1]);
	}
	if (px->cmd_path[idx][0] != NULL)
		execve(pipex->cmd_path[idx][0], (pipex->cmd[idx]), pipex->ev);
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
			exec_child(i, px);
	}
}
int	main(int argc, char **argv, char **envp)
{
	t_data	px;
	if (argc == 5)
	{
		ft_memset(&px, 0, sizeof(t_px));
		px.ev = envp;
		parse_input(&px, argv, envp);//파싱하기
		cmd_init(&px);//명령어 체크해서 있으면 제대로 없으면 NULL로 채워주기]
		fork_child(&px);

		if (pipe(pipex.pipefd) == -1)
		{
			perror("pipe error ");
			exit(1);
		}
		level_fuc(&pipex);//파이프라인 작동시키기
	}
	else
		return (1);
	return (0);
}
