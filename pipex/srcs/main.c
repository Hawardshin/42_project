/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 15:06:23 by joushin           #+#    #+#             */
/*   Updated: 2022/08/26 16:53:37 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "./libft/libft.h"
# define BUFFER_SIZE 400
//옵션으로 들어온 녀석 까지 같이 검사해주면 될까? ls -c 는 실행되는데 cat -c는 실행이 안됨..

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