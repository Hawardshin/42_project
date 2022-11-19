/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 16:29:05 by joushin           #+#    #+#             */
/*   Updated: 2022/11/19 18:04:29 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft/libft.h"
#include "../include/node.h"
#include "../include/utils.h"
#include "../include/just_for_test.h"//이건 테스트용

void	handler(int signum)
{
	if (signum != SIGINT)
		return ;
	write(1, "\n", 1);
	if (rl_on_new_line() == -1)
		exit(1);
	rl_replace_line("", 1);
	rl_redisplay();
}

void	init_rd_line(t_readline *src, char *rd_line)
{
	g_state.exit_code = 0;
	src->buffer = rd_line;
	src->bufsize = ft_strlen(rd_line);
	src->now_pos = -2;
}

int	main(int argc, char **argv, char **envp)
{
	char			*rd_line;
	t_readline		src;
	t_main_token	*tok;
	t_main_node		*node;

	if (argc != 1)
		return (0);
	(void) argv;
	signal(SIGINT, handler);
	init_g_state(envp);
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
	while (1)
	{
		rd_line = readline("jshell$ ");
		if (!rd_line)
		{
			printf("exit\n");
			exit (EXIT_SUCCESS);
		}
		if (rd_line[0] == '\0' || ft_strncmp(rd_line, "\n",  1) == 0)
		{
			my_free((void **)&rd_line);
			continue ;
		}
		if (ft_strncmp(rd_line, "exit", 5) == 0)
		{
			my_free((void **)&rd_line);
			printf("exit\n");
			break ;
		}
		init_rd_line(&src, rd_line);
		tok = tokenize(&src);
		// Print_all_token(tok->start_token);
		if (check_syntax(tok->start_token) || g_state.exit_code)
		{
			my_free((void **)&rd_line);
			rd_line = NULL;
			syntax_error();
			//tok_clean()
			continue ;
		}
		if (tok->start_token != NULL)
		{
			node = make_tok_to_node(tok);
			node->ev = envp;
			g_state.exit_code = fork_child(node);
		}
		//tok_clean();
		add_history(rd_line);
	}
	return (0);
}
