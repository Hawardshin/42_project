/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 16:29:05 by joushin           #+#    #+#             */
/*   Updated: 2022/11/09 22:53:06 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "./libft/libft.h"
#include "./include/node.h"
#include "./include/token.h"
#include "./include/m_utils.h"
#include "./include/parse_utils.h"
#include "./include/parse_cmd.h"
#include "./include/m_split.h"

void	print_error(int Flag, char *s)
{
	ft_putstr_fd("minishell: ", 2);
	if (Flag == 0)
	{
		ft_putstr_fd("Memory allocation fails.\n", 2);
		exit(1);
	}
	else if (Flag == 1)
	{
		ft_eprintf("%s: command not found\n", s);
		exit(127);
	}
	else if (Flag == 2)
	{
		perror(s);
		exit(1);
	}
	else if (Flag == 3)
	{
		ft_eprintf("%s", s);
		exit(1);
	}
}
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

void	print_token(t_token	*tok)
{
	printf("%s\n",tok->text);
}


t_main_node *	set_main_node(char **envp)
{
	t_main_node *main_node;

	main_node = malloc(sizeof(t_main_node));
	if (!main_node)
		return(NULL) ;//이것도 나중에 바꾸기.
	ft_memset(main_node, 0, sizeof(t_main_node));
	main_node->ev = envp;
	while (envp != NULL && *envp != NULL && ft_strncmp(*envp, "PATH", 4) != 0)
		envp++;
	if (envp == NULL || *envp == NULL)
		print_error(3, "Not exist path!\n");
	main_node -> path = ft_msplit(*envp + 5, ':');
	return (main_node);
}

int	parse_and_execute(t_readline *src, char **envp)
{
	t_token		*tok;
	// t_node		*mnode;
	t_main_node	*main_node;
	if (src->now_pos == src->bufsize -1)
		return 0;
    skip_white_spaces(src);//일단 시작하면서 화이트 스페이스를 전부 다 넘겨준다. 검증완료
	// printf("%d",src->done_pos);
	// printf("%s\n", src->buffer + src->done_pos);
    tok = tokenize(src);
	if (!tok->eof)
		printf("%s\n",tok->text);
	else
	{
		// printf("eof\n");
		return (0);//리턴 값 바꾸기.
	}
	main_node = set_main_node(envp);
	// printf("%s\n",main_node->path[0]);
	while(tok && !tok->eof)
	{
		//토큰을 쭉 돌면서 하나의 리스트로 묶어준다.
		make_new_node(main_node, tok);
		// if(!mnode)
		// {
		// 	break;
		// }
		tok = tokenize(src);
		if (tok->eof)
			break;
		// print_token(tok);
	}
	printf("out\n");
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
		t_readline	src;
    	src.buffer = cmd;
    	src.bufsize = ft_strlen(cmd);
    	src.now_pos = -2;
		src.done_pos = 0;

    	parse_and_execute(&src,envp);
		// printf("output : %s\n", cmd);
		//나중에 이부분에 명령을 처리하면 된다.
		//처리하고 exit 코드를 저장해주자.
		add_history(cmd);
		free(cmd);
		cmd = NULL;
	}
	return (0);
}
