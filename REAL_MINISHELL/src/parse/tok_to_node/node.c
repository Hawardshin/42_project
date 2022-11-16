/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 09:18:42 by joushin           #+#    #+#             */
/*   Updated: 2022/11/16 23:05:08 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/node.h"
#include "../../../include/just_for_test.h"
#include "../../../include/utils.h"
#include "../../libft/libft.h"

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
//이렇게 생각을 했었는데 구조를 바꿨습니다.
//각 노드 즉 파이프가 나오기 전까지는 새로운 노드를 생성하지 않습니다.
//각각의 io_token에 대해서 3개의 구조체에 링크드 리스트로 연결해서 들고갈 것입니다.

//cmd 최소 1개
//명령어로 1개
void	make_argv_node(t_node *node, t_token **tmp_tok, t_main_node *main_node)
{
	int		i;
	t_token	*ttmp;

	i = 0;
	node->cmd_path[0] = find_path((*tmp_tok)->text, main_node);
	ttmp = (*tmp_tok);
	while (ttmp && ttmp->tok_type == ARGV_TOK)
	{
		i++;
		ttmp = ttmp->next;
	}
	node ->cmd = malloc(sizeof (char *) * (i + 1));
	i = 0;
	while ((*tmp_tok) && (*tmp_tok)->tok_type == ARGV_TOK)
	{
		node->cmd[i] = ft_strdup((*tmp_tok)->text);
		i++;
		(*tmp_tok) = (*tmp_tok)->next;
	}
	node->cmd[i] = NULL;
}

void	io_noding(t_token **tmp_tok, t_node *node)
{
	if (ft_strncmp((*tmp_tok)->text, "<<", 2) == 0)
		make_hdoc_node(node, tmp_tok);
	else if (ft_strncmp((*tmp_tok)->text, "<", 1) == 0)
		make_ifile_node(node, tmp_tok);
	else if (ft_strncmp((*tmp_tok)->text, ">", 1) == 0)
		make_ofile_node(node, tmp_tok);
	else if (ft_strncmp((*tmp_tok)->text, ">>", 2) == 0)
		make_rfile_node(node, tmp_tok);
	(*tmp_tok) = (*tmp_tok)->next;
}

t_main_node	*make_tok_to_node(t_main_token *tok)
{
	t_main_node	*main_node;
	t_token		*tmp_tok;
	t_node		*node;

	main_node = main_init(&tok, &tmp_tok, &node);
	while (tmp_tok)
	{
		if (tmp_tok-> tok_type == ARGV_TOK)
			make_argv_node(node, &tmp_tok, main_node);
		else if (tmp_tok-> tok_type == IO_TOK)
			io_noding(&tmp_tok, node);
		else if (tmp_tok->tok_type == PIPE_TOK)
			node = make_pipe_node(&tmp_tok, main_node);
		else
			tmp_tok = tmp_tok->next;
	}
	pipe_init(main_node);
	return (main_node);
}
