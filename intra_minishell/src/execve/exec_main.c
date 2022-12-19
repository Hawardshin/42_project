/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 20:35:18 by joushin           #+#    #+#             */
/*   Updated: 2022/11/27 13:28:36 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "node.h"
#include "utils.h"
#include "exec.h"
#include "builtin.h"

static int	exec_done(t_main_node *px, pid_t pid, int status)
{
	if (px->cmd_num == 1)
	{
		if (px->node_head->cmd && ft_built_first_check(px->node_head->cmd[0]))
			ft_in_built(px->node_head, 1);
	}
	ft_all_close(px, -1, -1);
	waitpid(pid, &status, 0);
	ft_end_free(px);
	if (g_state.exit_code == -1)
		return (1);
	if (0 == (status & 0xff))
		return (status >> 8);
	return (status);
}

int	fork_child(t_main_node *px)
{
	int		i;
	pid_t	pid;
	int		status;
	t_node	*node;

	i = -1;
	while (++i < px->cmd_num)
	{
		pid = mfork();
		if (pid == 0)
		{
			signal(SIGINT, SIG_DFL);
			if (i == 0)
				exec_first(px);
			else if (i + 1 == px->cmd_num)
				exec_last(px);
			else
				exec_pipe(i, px);
		}
		node = mlst_find(i + 1, px);
		if (node && node->heardoc_node && node->heardoc_node != NULL)
			waitpid(pid, &status, 0);
	}
	return (exec_done(px, pid, status));
}
