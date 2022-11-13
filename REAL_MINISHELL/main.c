/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 16:29:05 by joushin           #+#    #+#             */
/*   Updated: 2022/11/13 19:54:10 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "./libft/libft.h"
#include "./include/node.h"
#include "./include/token.h"
#include "./include/just_for_test.h"
// #include "./include/token.h"
// #include "./include/m_utils.h"
// #include "./include/parse_utils.h"
// #include "./include/parse_cmd.h"
// #include "./include/m_split.h"



// t_main_node	*set_main_node(char **envp)
// {
// 	t_main_node *main_node;

// 	main_node = malloc(sizeof(t_main_node));
// 	if (!main_node)
// 		return(NULL) ;//이것도 나중에 바꾸기.
// 	ft_memset(main_node, 0, sizeof(t_main_node));
// 	main_node->ev = envp;
// 	while (envp != NULL && *envp != NULL && ft_strncmp(*envp, "PATH", 4) != 0)
// 		envp++;
// 	if (envp == NULL || *envp == NULL)
// 		print_error(3, "Not exist path!\n");
// 	main_node -> path = ft_msplit(*envp + 5, ':');
// 	return (main_node);
// }

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

int	main(int argc, char **argv, char **envp)
{
	// int		ret;
	char	*rd_line;
	if (argc != 1)
		return 0;
	(void) argv;
	signal(SIGINT, handler);
	// t_main_node	*main_node;
	t_readline	src;
	(void) envp;
	// main_node = set_main_node(envp);
	printf("\n-------------------------------------------start--------------------------------------------------\n");
	while (1)
	{
		rd_line = readline("jshell$ ");
		if(!rd_line)
		{
			printf("exit\n");
			exit(EXIT_SUCCESS); //널인경우 성공
		}
		if(rd_line[0] == '\0' || ft_strncmp(rd_line, "\n",1) == 0)
		{
			free(rd_line);
			continue;
		}
		if(ft_strncmp(rd_line, "exit",5) == 0)
		{
			free(rd_line);
			printf("exit\n");
			break;
		}
		printf("\n-------------------------------------------input--------------------------------------------------\n");
		src.buffer = rd_line;
		src.bufsize = ft_strlen(rd_line);
		src.now_pos = -2;

		t_main_token * tok =tokenize(&src);
		// Print_all_token(tok->start_token);
		// check_syntax(tok);
		// make_node(tok);
		(void)tok;
		add_history(rd_line);
		free(rd_line);
		rd_line = NULL;
		printf("\n-------------------------------------------end--------------------------------------------------\n");
	}
	return (0);
}
