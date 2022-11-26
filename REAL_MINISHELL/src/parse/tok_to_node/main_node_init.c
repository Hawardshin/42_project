/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_node_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 22:45:21 by joushin           #+#    #+#             */
/*   Updated: 2022/11/26 19:42:25 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/node.h"
#include "../../../include/utils.h"
#include "../../libft/libft.h"

t_main_node	*main_init(t_main_token **tok, t_token **tmp_tok, t_node **node)
{
	t_main_node	*main_node;

	main_node = malloc(sizeof (t_main_node));
	if (!main_node)
		print_error(0, NULL);
	ft_memset(main_node, 0, sizeof(t_main_node));
	(*tmp_tok) = (*tok)->start_token;
	if (!(*tmp_tok))
		return (NULL);
	main_node->cmd_num++;
	(*node) = malloc(sizeof(t_node));
	if (!(*node))
		print_error(0, NULL);
	(*node) = ft_memset((*node), 0, sizeof(t_node));
	(*node)->idx = main_node->cmd_num;
	main_node->node_head = (*node);
	main_node->node_tail = (*node);
	if (get_env("PATH"))
		main_node -> path = ft_msplit(ft_mstrdup(get_env("PATH")), ':');
	else
		main_node->path = NULL;
	return (main_node);
}

void	pipe_init(t_main_node *main_node)
{
	int	i;

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
}
