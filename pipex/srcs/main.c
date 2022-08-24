/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 15:06:23 by joushin           #+#    #+#             */
/*   Updated: 2022/08/24 18:51:17 by joushin          ###   ########.fr       */
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
		exit(1);
	ft_strlcpy(result, s1, len + 1);
	return (result);
}

void	parse_input(t_px *pipex, char **argv, char **envp)
{
	char	*tmp_path;

	pipex->infile = mft_strdup(argv[1]);
	pipex->cmd[0] = ft_split(argv[2], ' ');//char ** cmd[3];
	pipex->cmd[1] = ft_split(argv[3], ' ');
	pipex->outfile = mft_strdup(argv[4]);
	pipex->cmd[2] = 0;//필요?
	while (ft_strncmp(*envp,"PATH",4) != 0 && envp)
		envp++;
	tmp_path = mft_strdup(*envp + 5);
	pipex -> path = ft_split(tmp_path, ':');
	my_free(&tmp_path);
}

//만약 경로상에 존재하지 않는다면 현재 디렉토리에서도 탐색하는걸 추가할까?
void	check_cmd(t_px *pipex)
{
	char	*pathname;
	int		idx;
	int		i;
	char	*cmdtmp;

	idx = -1;
	while (++idx < 2)//맨대토리라 명령어 2개
	{
		cmdtmp = ft_strjoin("/",pipex->cmd[idx][0]);
		// my_free(pipex->cmd[idx][0]);//이건 나중에 프리해주는걸로 하자.
		i = -1;
		while (pipex -> path[++i])
		{
			pathname = ft_strjoin(pipex-> path[i], cmdtmp);
			if (!pathname)
				return ;
			if (access(pathname, R_OK | X_OK) == 0)
				pipex->cmd_path[idx][0] = mft_strdup(pathname);
			my_free(&pathname);
		}
		if(!(pipex->cmd_path[idx][0]))//
			pipex->cmd_path[idx][0] = NULL;
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
		fds = open(pipex->infile, O_RDONLY);
		if (fds == -1)
		{
			perror("open error : ");
			exit(1);
		}
		if (dup2(fds, 0) == -1)
			exit(1);
		if (dup2(pipex->pipefd[1], 1) == -1)
			exit(1);
		close(fds);
		close(pipex->pipefd[1]);
		ft_error_check(idx, pipex);
		if (pipex->cmd_path[idx][0] != NULL)
			execve(pipex->cmd_path[idx][0], (pipex->cmd[idx]), pipex->ev);
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

int	main(int argc, char **argv, char **envp)
{
	t_px	pipex;
	if (argc == 5)
	{
		ft_memset(&pipex, 0, sizeof(t_px));
		pipex.ev = envp;
		parse_input(&pipex, argv, envp);//파싱하기
		check_cmd(&pipex);//명령어 체크해서 있으면 제대로 없으면 NULL로 채워주기]
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
