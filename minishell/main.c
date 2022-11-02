/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 16:29:05 by joushin           #+#    #+#             */
/*   Updated: 2022/11/02 19:32:20 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <stdlib.h>

int		exit_code;

void	handler(int signum)
{
	if (signum != SIGINT)// 시그널에 해당하는게 아니면
		return ;
	printf("\n");
	if (rl_on_new_line() == -1)
		exit(1);
	rl_replace_line("", 1);
	rl_redisplay();
}

int	main(int argc, char **argv, char **envp)
{
	// int		ret;
	char	*line;
	(void) argc; (void) argv; (void) envp ;
	signal(SIGINT, handler);
	while (1)
	{
		line = readline("jshell$ ");
		if (!line)
		{
            printf(" exit\n");
            exit(exit_code);
		}
		else if (*line == '\0')
		{
            free(line);
		}
		else
		{
			printf("output : %s\n", line);
			//나중에 이부분에 명령을 처리하면 된다.
			//처리하고 exit 코드를 저장해주자.
			add_history(line);
			free(line);
			line = NULL;
		}
	}
	return (0);
}
