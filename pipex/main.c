/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 15:06:23 by joushin           #+#    #+#             */
/*   Updated: 2022/08/23 17:44:01 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "./libft/libft.h"
# define BUFFER_SIZE 400
void	parse_cmd(t_px *pipex, char **argv, char **envp)
{
	char	*tmp_path;

	pipex->infile = ft_strdup(argv[1]);
	pipex->cmd[0] = ft_split(argv[2], ' ');//명령어가 옵션으로 들어올 수 있기 때문에 잘라줬다.
	pipex->cmd[1] = ft_split(argv[3], ' ');
	pipex->outfile = ft_strdup(argv[4]);
	pipex->cmd[2] = 0;
	while (ft_strncmp(*envp,"PATH",4) != 0 && envp)
		envp++;
	tmp_path = ft_strdup(*envp + 5);//tmp_path가 반드시 필요한걸까? PATH가 없을수도 있는가? 없다
	pipex -> path = ft_split(tmp_path, ':');
	free(tmp_path);
}

void	check_cmd(t_px *pipex, char **argv, char **envp)
{
	char 	*pathname;
	int		cmd_size;
	int		idx;
	int		mode;
	cmd_size = 2;//명령어 갯수 맨대토리는 2개 설정.
	idx = -1;

	mode = R_OK | X_OK; //검증필요
	//경로에 명령이 있는지 확인하는 부분 문자열에서 /명령어를 붙혀서 access를 해준다.
	int	i;
	char *cmdtmp;

	while (++idx < cmd_size)
	{
		cmdtmp = ft_strjoin("/",pipex->cmd[idx][0]);//이것도 0 0 변경하기
		i = -1;
		while (pipex -> path[++i])//현재 디렉토리 탐색> 좀이따
		{
			pathname = ft_strjoin(pipex-> path[i], cmdtmp);
			if (!pathname) //exit으로 수정하기
				return ;
			if (access(pathname, mode) == 0)
				pipex->cmd_path[idx][0] = ft_strdup(pathname);
			free(pathname);
		}
		if(!(pipex->cmd_path[idx][0]))
			pipex->cmd_path[idx][0] = NULL;//명령이 아에 없다는 것이기 때문에 에러노값 받아서 그 에러출력 해줘야함.
		//일단 널을 넣어줬지만 나중에 탐색에서 문제가 발생하거나 총 명령어의 갯수를 인자로 넘겨주지 않게된다면 다른걸로 넣어준다.
		printf("ak: %s\n",pipex->cmd_path[idx][0]);
		free(cmdtmp);
	}
}

void	level_fuc(t_px *pipex)
{
	int		idx;
	pid_t	pid;
	int		size = 1;
	int fd1[2];//fd1은 자식에서 부모로 보내는 파이프 용도로 사용
	char *buff[BUFFER_SIZE]; //읽기 위한 버퍼 (버퍼 값은 바꿀 수 있다.)
	idx = 0;
	if (pipe(fd1) == -1 )//파이프 생성 실패시
	{
		printf("vb\n");
		exit(1);
	}//입력 파일을 어떻게 명령을 수행하는지?
	// int fds = open(pipex->infile,O_RDONLY);
	int fds2 = open(pipex->outfile, O_WRONLY);
	if (fds2 == -1)
	{
		// open 실패시 출력하는 에러노 값을 출력해주자.
		// 궁금한점 : open을 실패한 경우 그냥 표준 출력으로 찍어주기만 하면 되는 걸까?
		printf("open no\n");
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
			execve(pipex->cmd_path[idx][0], &(pipex->cmd_path[idx][0]), pipex->ev);
	}
	else
	{//부모프로세스
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
		execve(pipex->cmd_path[idx][0], &(pipex->cmd_path[idx][0]), pipex->ev);
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
		parse_cmd(&pipex, argv, envp);
		check_cmd(&pipex, argv, envp);
		//1. 파싱하기
		//2. 파싱한 거 경로에 있는 명령어 인지 체크하기
		//3. 주요기능 작동함수
		level_fuc(&pipex);
	}
	else
		return (1);
	return (0);
}
