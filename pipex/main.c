/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 15:06:23 by joushin           #+#    #+#             */
/*   Updated: 2022/08/23 21:53:45 by joushin          ###   ########.fr       */
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
	my_free(tmp_path);
}

//만약 경로상에 존재하지 않는다면 현재 디렉토리에서도 탐색하는걸 추가할까?
void	check_cmd(t_px *pipex, char **argv, char **envp)
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
			my_free(pathname);
		}
		if(!(pipex->cmd_path[idx][0]))//
			pipex->cmd_path[idx][0] = NULL;
		// printf("ak: %s\n",pipex->cmd_path[idx][0]);
		my_free(cmdtmp);
	}
}

void	level_fuc(t_px *pipex)
{
	int		idx;
	pid_t	pid;
	int		size = 1;
	int fd1[2];//fd1은 자식에서 부모로 보내는 파이프 용도로 사용

	idx = 0;
	if (pipe(fd1) == -1 )//파이프 생성 실패시
	{
		printf("vb\n");
		exit(1);
	}
	pid = fork();
	if (pid == -1)
	{//프로세싱 실패
		printf("nopro\n");
		exit(1);
	}
	else if (pid == 0)
	{
		int fds = open(pipex->infile,O_RDONLY);
		//자식 프로세스
		// write(fd1[1],,BUFFER_SIZE);
		if (dup2(fds, 0) == -1)//여기서 표준 입력을 이 fd값으로 바꿔주게 되면
		{
			printf("not fd\n");
			exit(1);
		}
		close(fds);
		if (dup2(fd1[1], 1) == -1)//여기서 표준 입력을 이 fd값으로 바꿔주게 되면
		{
			printf("not fd\n");
			exit(1);
		}
		close(fd1[1]);
		if (pipex->cmd_path[idx][0] != NULL)
			execve(pipex->cmd_path[idx][0], (pipex->cmd[idx]), pipex->ev);
	}
	else
	{//부모프로세스
		int fds2 = open(pipex->outfile, O_WRONLY);
		if (fds2 == -1)
		{
			// open 실패시 출력하는 에러노 값을 출력해주자.
			// 궁금한점 : open을 실패한 경우 그냥 표준 출력으로 찍어주기만 하면 되는 걸까?
			printf("open no\n");
			exit(1);
		}
		sleep(2);
		idx++;
		close(fd1[1]);
		if (dup2(fd1[0], 0) == -1)//여기서 표준 입력을 이 fd값으로 바꿔주게 되면
		{
			printf("not fd\n");
			exit(1);
		}
		close(fd1[0]);
		if (dup2(fds2, 1) == -1)//여기서 표준 출력을 이 fd값으로 바꿔주게 되면
		{
			printf("not fd\n");
			exit(1);
		}
		close(fds2);
		if (pipex->cmd_path[idx][0] != NULL)
			execve(pipex->cmd_path[idx][0], (pipex->cmd[idx]), pipex->ev);//즉 그 다음경로부터 본다.
	}
	// while (idx < 3)
	// {
	// 	if (pipex->cmd_path[idx][0] != NULL)
	// 		execve(pipex->cmd_path[idx][0], &(pipex->cmd_path[idx][0]), pipex->ev);//이렇게 해주면 현재 환경변수가 없는 것
	// 	idx++;
	// }
	// printf("명령어 수행 실패\n");
}



int	main(int argc, char **argv, char **envp)
{
	t_px	pipex;
	if (argc == 5)
	{
		// pipex.cmd = (char ***)malloc (sizeof(char **) * 3);
		// if (!pipex.cmd)
		// 	return (0);
		// pipex.cmd[3] = NULL;
		ft_memset(&pipex, 0, sizeof(t_px));
		pipex.ev = envp;
		parse_input(&pipex, argv, envp);//파싱하기
		check_cmd(&pipex, argv, envp);//명령어 체크해서 있으면 제대로 없으면 NULL로 채워주기
		level_fuc(&pipex);//파이프라인 작동시키기
	}
	else
		return (1);
	return (0);
}
