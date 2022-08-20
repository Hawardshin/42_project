/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 15:06:23 by joushin           #+#    #+#             */
/*   Updated: 2022/08/20 22:00:35 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "./libft/libft.h"

int	parse_cmd(t_px *pipex, char **argv, char **envp)
{
	char	*tmp_path;

	pipex->infile = ft_strdup(argv[1]);
	pipex->cmd[0] = ft_split(argv[2], ' ');
	check_slash();


}


int	main(int argc, char **argv, char **envp)
{
	t_px	pipex;
	if (argc == 5)
	{
		pipex.cmd = (char ***)malloc (sizeof(char **) * 3);
		if (!pipex.cmd)
			return (0);
		pipex.cmd[3] = NULL;
		ft_memset(&pipex, 0, sizeof(t_px));
		pipex.ev = envp;
		parse_cmd(&pipex, argv, envp);
		//1. 파싱하기
		//2. 파싱한 거 경로에 있는 명령어 인지 체크하기
		//3. 주요기능 작동함수
	}
	else
		return (1);
	return (0);
}
