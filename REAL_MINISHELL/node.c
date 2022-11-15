/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 09:18:42 by joushin           #+#    #+#             */
/*   Updated: 2022/11/15 15:15:28 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/node.h"
#include "./include/token.h"
#include "./libft/libft.h"
#include "./include/env.h"
#include "./include/utils.h"
#include "./include/error.h"
#include "./include/env.h"

//만든 토큰을 노드에 넣을 건데, 파이프를 기준으로 새로운 노드를 생성할 계획.
//-- 새로운 노드 만들때마다 구현해야하는 것.
// 1. 메인노드의 cmd_num++,
// 2. 노드에 인덱스 채워주고 노드 동적할당 후 memset해주기.
//1. 토큰을 쭉 돌면서 ARGV_TOK 같은경우
	//처음 만나면 cmd에 넣고 경로 찾아서 넣어주고
	//두번째 만나면 ARGV는 경로는 찾지 않고 뒤에 2차원 배열로 넣어주고
//2. PIPE_TOK 만나면 노드 인덱스 하나 늘려주면서 새로운 노드로 넘어간다. + 메인노드의 명령어 숫자도 늘려준다.
//3. IO_TOK를 만나면 이게 어떤 IO_TOK인지 검사해서 4개의 IO_type을 저장해주고 노드 위에 파일은 바로 뒤에 오는 ARGV_TOK로 채워준다.
	// 이 IO_TOK 같은 경우 명령이 아니니까 cmd랑 cmd_path가 모두 널이다.

// 토큰을 여기서 free해주는 것도 나쁘지 않겠다.

static char	*ft_make_cmd_path(t_main_node *px, char *text, int i)
{
	char	*tmp;
	char	*ptmp;

	tmp = ft_mstrjoin("/", text);
	ptmp = ft_mstrjoin(px->path[i], tmp);
	my_free((void**)&tmp);
	return (ptmp);
}

char	*find_path(char *text, t_main_node *main_node)
{
	int		i;
	char	*ptmp;
	struct stat st;

	i = -1;
	while (main_node -> path[++i])
	{
		if (ft_strncmp(text ,"/", 1) != 0)
			ptmp = ft_make_cmd_path(main_node, text, i);
		else
			ptmp = ft_mstrdup(text);
		if (stat(ptmp, &st) == 0)
			return(ptmp);
		my_free((void**)&ptmp);
	}
	return (NULL);
}

t_main_node * make_tok_to_node(t_main_token *tok)
{
	t_main_node	*main_node;
	t_token *tmp_tok;
	t_node	*node;
	int		i;

	i = 0;
	main_node = malloc(sizeof (t_main_node));
	ft_memset(main_node, 0, sizeof(t_main_node));
	tmp_tok = tok->start_token;
	if (!tmp_tok)
		return (NULL);
	main_node->cmd_num++;
	node = malloc(sizeof(t_node));
	node = ft_memset(node, 0, sizeof(t_node));
	node->idx = main_node->cmd_num;
	main_node->node_head = node;
	main_node->node_tail = node;
	char *path = get_env("PATH");
	if (path)
		main_node -> path = ft_msplit(ft_mstrdup(path), ':');
	while (tmp_tok)
	{
		if (tmp_tok-> tok_type == ARGV_TOK)
		{
			node->cmd_path[0] = find_path(tmp_tok->text, main_node);
			t_token *ttmp = tmp_tok;//cmd 최소 1개
			while (ttmp && ttmp->tok_type == ARGV_TOK)//명령어로 1개
			{
				i++;
				ttmp = ttmp->next;
			}
			node ->cmd = malloc(sizeof (char *) * (i + 1));
			i = 0;
			while(tmp_tok && tmp_tok->tok_type == ARGV_TOK)
			{
				node->cmd[i] = ft_strdup(tmp_tok->text);
				i++;
				tmp_tok = tmp_tok->next;
			}
			node->cmd[i] = NULL;
		}
		else if (tmp_tok-> tok_type == IO_TOK)
		{
			if (ft_strncmp(tmp_tok->text ,"<<", 2) == 0)
				node->node_type =HERE_DOC_NODE;
			else if (ft_strncmp(tmp_tok->text, "<", 1) == 0)
				node->node_type =OPEN_NODE;
			else if (ft_strncmp(tmp_tok->text, ">", 1) == 0)
				node->node_type =WRITE_NODE;
			else if (ft_strncmp(tmp_tok->text , ">>", 2) == 0)
				node->node_type =APPEND_NODE;
			else
			{
				printf("WHAT THE ?\n");
				exit(1000);
			}
			tmp_tok= tmp_tok->next;
			node->file = ft_strdup(tmp_tok->text);
			tmp_tok = tmp_tok->next;
			// free((void**)tmp_tok->bef);
		}
		else if (tmp_tok->tok_type == PIPE_TOK)
		{
			main_node->cmd_num++;
			// if (node)
			// 	my_free((void**)&node);
			node = malloc(sizeof(t_node));
			node = ft_memset(node, 0, sizeof(t_node));
			node->idx = main_node->cmd_num;
			main_node->node_tail->next = node;
			node->prev = main_node->node_tail;
			main_node->node_tail = node;
			tmp_tok = tmp_tok->next;
		}
		else
			tmp_tok = tmp_tok->next;
	}
	//파이프 init
	i = -1;
	main_node->pipefd = (int **)malloc(sizeof(int *) * (main_node->cmd_num));
	if (!(main_node->pipefd))
		print_error(0, NULL);
	while (++i < main_node->cmd_num)
	{
		main_node->pipefd[i] = (int *)malloc(sizeof (int) * 2);
		if (!(main_node->pipefd[i]))
			print_error(0, NULL);
		if (pipe(main_node->pipefd[i]) == -1)
			print_error(3, NULL);
	}
	return (main_node);
}
