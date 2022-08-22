/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 15:06:23 by joushin           #+#    #+#             */
/*   Updated: 2022/08/22 17:40:54 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "./libft/libft.h"

void	parse_cmd(t_px *pipex, char **argv, char **envp)
{
	char	*tmp_path;
	int		cmd_size;
	int		idx;

	cmd_size = 2;//명령어 갯수 맨대토리는 2개 설정.
	idx = 0;
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
	char *pathname;
	int mode = R_OK | X_OK; //검증필요
	//경로에 명령이 있는지 확인하는 부분 문자열에서 /명령어를 붙혀서 access를 해준다.
	int	i;
	char *cmdtmp;

	while (idx < cmd_size)
	{
		cmdtmp = ft_strjoin("/",pipex->cmd[idx][0]);//이것도 0 0 변경하기
		i = 0;
		while (pipex -> path[i])//현재 디렉토리 탐색> 좀이따
		{
			pathname = ft_strjoin(pipex-> path[i], cmdtmp);
			if (!pathname) //exit으로 수정하기
				return ;
			if (access(pathname, mode) == 0)
			{//그 명령이 실행이 가능한 명령어인 경우에 명령어를 잠시 저장해둔다.
				pipex->cmd_path[idx] = ft_strdup(pathname);
				// printf("pathname : %s\n",pathname);
			}
			i++;
			free(pathname);
		}
		// if(!(pipex->cmd_path[idx]))
		// 	pipex->cmd_path[idx] = NULL;//명령이 아에 없다는 것이기 때문에 에러노값 받아서 그 에러출력 해줘야함.
		//일단 널을 넣어줬지만 나중에 탐색에서 문제가 발생하거나 총 명령어의 갯수를 인자로 넘겨주지 않게된다면 다른걸로 넣어준다.
		printf("ak: %s\n",pipex->cmd_path[idx]);
		idx++;
		free(cmdtmp);
	}
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
		// check_cmd(&pipex, argv, envp);
		//1. 파싱하기
		//2. 파싱한 거 경로에 있는 명령어 인지 체크하기
		//3. 주요기능 작동함수
	}
	else
		return (1);
	return (0);
}
