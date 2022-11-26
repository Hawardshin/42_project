/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 16:29:05 by joushin           #+#    #+#             */
/*   Updated: 2022/11/26 22:04:02 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "node.h"
#include "utils.h"

void	handler(int signum)
{
	if (signum != SIGINT)
		return ;
	write(STDOUT_FILENO, "\n", 1);
	if (rl_on_new_line() == -1)
		exit(1);
	rl_replace_line("", 1);
	rl_redisplay();
}

void	init_rd_line(t_readline *src, char *rd_line)
{
	src->buffer = rd_line;
	src->bufsize = ft_strlen(rd_line);
	src->now_pos = -2;
}

void	in_while(char *rd_line)
{
	t_readline		src;
	t_main_token	*tok;
	t_main_node		*node;

	init_rd_line(&src, rd_line);
	tok = tokenize(&src);
	if ((tok->is_error == 1) || check_syntax(tok->start_token))
	{
		my_free((void **)&rd_line);
		rd_line = NULL;
		syntax_error();
		tok_clean(tok);
	}
	else if (tok->start_token != NULL)
	{
		node = make_tok_to_node(tok);
		tok_clean(tok);
		node->ev = ret_env_char();
		g_state.exit_code = fork_child(node);
		add_history(rd_line);
	}
}

int	main(int argc, char **argv, char **envp)
{
	char			*rd_line;

	if (argc != 1)
		print_error(1, argv[0]);
	init_g_state(envp);
	printf("\n");
	while (1)
	{
		ft_tc();
		signal(SIGINT, handler);
		signal(SIGQUIT, SIG_IGN);
		rd_line = readline("jshell$ ");
		if (!rd_line)
		{
			printf("exit\n");
			exit (EXIT_SUCCESS);
		}
		if (rd_line[0] == '\0' || ft_strncmp(rd_line, "\n", 1) == 0)
		{
			my_free((void **)&rd_line);
			continue ;
		}
		in_while(rd_line);
	}
	return (0);
}
