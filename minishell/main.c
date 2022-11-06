/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 16:29:05 by joushin           #+#    #+#             */
/*   Updated: 2022/11/06 21:31:27 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <stdlib.h>
#include "./libft/libft.h"
#include "./include/source.h" 
#include "./include/parser.h" 
#include "./include/executor.h"

int		exit_code;

void	handler(int signum)
{
	if (signum != SIGINT)// 시그널에 해당하는게 아니면
		return ;
	write(1, "\n", 1);
	if (rl_on_new_line() == -1)
		exit(1);
	rl_replace_line("", 1);
	rl_redisplay();
}

int	parse_and_execute(struct source_s *src)
{
    skip_white_spaces(src);
    struct token_s *tok = tokenize(src);
    if(tok == &eof_token)
    {
        return 0;
    }
    while(tok && tok != &eof_token)
    {
        struct node_s *cmd = parse_simple_command(tok);
        if(!cmd)
        {
            break;
        }
        do_simple_command(cmd);
        free_node_tree(cmd);
        tok = tokenize(src);
    }
    return 1;
}

int	main(int argc, char **argv, char **envp)
{
	// int		ret;
	char	*cmd;
	(void) argc; (void) argv; (void) envp ;
	signal(SIGINT, handler);
	
	while (1)
	{
		cmd = readline("jshell$ ");
		if(!cmd)
        {
			printf("exit\n");
            exit(EXIT_SUCCESS); //널인경우 성공
        }
		if(cmd[0] == '\0' || ft_strncmp(cmd, "\n",1) == 0)
        {
            free(cmd);
            continue;
        }
		if(ft_strncmp(cmd, "exit",5) == 0)
        {
            free(cmd);
			printf("exit\n");
			// exit(1);
            break;
        }
		struct source_s src;
    	src.buffer = cmd;
    	src.bufsize = strlen(cmd);
    	src.curpos = INIT_SRC_POS;
    	parse_and_execute(&src);
		// printf("output : %s\n", cmd);
		//나중에 이부분에 명령을 처리하면 된다.
		//처리하고 exit 코드를 저장해주자.
		add_history(cmd);
		free(cmd);
		cmd = NULL;
	}
	return (0);
}
