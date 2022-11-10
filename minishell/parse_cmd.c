/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 21:05:25 by joushin           #+#    #+#             */
/*   Updated: 2022/11/10 16:38:51 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/node.h"
#include "./include/m_utils.h"
#include "./libft/libft.h"
#include <sys/stat.h>

static char	*ft_make_cmd_path(t_main_node *px, t_token *tok, int i)
{
	char	*tmp;
	char	*ptmp;

	tmp = ft_mstrjoin("/", tok->text);
	ptmp = ft_mstrjoin(px->path[i], tmp);
	my_free(&tmp);
	return (ptmp);
}

t_node	*cmd_init(t_main_node *px, t_token *tok)
{
	t_node		*node;
	struct stat	st;
	char		*ptmp;
	int			idx;
	int			i;

	node = malloc(sizeof(t_node));// 널가드
	idx = -1;
	node->cmd_path[0] = NULL;
	node->cmd_path[1] = NULL;
	i = -1;
	while (px -> path[++i])
	{
		if (ft_strncmp(tok->text, "/", 1) != 0)
			ptmp = ft_make_cmd_path(px, tok, i);
		else
			ptmp = ft_mstrdup(tok->text);
		if (stat(ptmp, &st) == 0)
			node->cmd_path[0] = ft_mstrdup(ptmp);
		my_free(&ptmp);
	}
	return (node);
}


void	make_new_node(t_main_node *cmd_node, t_token *tok)
{
	t_node	*node;

	//file 과 cmd구분하는 부분이 필요해요..
	//만약 명령이라면?
	node = cmd_init(cmd_node, tok);
	printf("cmd path :%s\n",node->cmd_path[0]);
	if (cmd_node->node_head == NULL)
	{
		// printf("goo\n");
		cmd_node->node_head = node;
		node->next = NULL;
		cmd_node->node_tail = node;
	}
	else
	{
		cmd_node->node_tail->next = node;
		cmd_node->node_tail = node;
		node->next = NULL;
	}
}
