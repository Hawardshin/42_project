/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 20:35:18 by joushin           #+#    #+#             */
/*   Updated: 2022/11/26 15:27:39 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/node.h"
#include "../../include/just_for_test.h"
#include "../../include/utils.h"
#include "../libft/libft.h"
#include "../../include/exec.h"
#include "../../include/builtin.h"

/*
기존 파이프 엑스와 다른점. 오픈 파일이 1개가 아니므로 open도 여러개 가능 + 생성도 여러개 가능하다.
즉 1. 오픈하는 파일을 전부다 오픈해본다. 하나라도 open을 실패하는경우 뒤에거는 오픈하지 않고 에러를 띄운다.
	이건 자식 프로세스에서 띄우는 것이므로 그냥 exit을 해줘도 된다 와 초개꿀. 그리고 마지막 open파일이 open이 된다.]
	2. outfile은 하나씩 생성을 하는데 > 인지 >> 인지 플래그에 따라서 다르게 생성을 해야만 한다. 즉 그 파일을 만드는 옵션을 다르게 준다.
	그렇게 outfile이 지정되면 pipe에는 아무것도 넘어가지 않게된다.
	즉 outfile이 없을 때만 파이프로 넘겨주는 것이다.
	3. 두번째 파이프 부터는 기본 open파일이 input pipe이지만 만약 inputfile이 존재하면 그 녀석을 최선 open으로 진행한다.
쭉 찾아다 hear_doc찾으면 tmp 만들고 또 만들고 또 만들어서 마지막 tmp 파일을 여는 느낌.
하지만 실행은 그게 아니라는 것..  결극 hdoc노드가 몇번째 위치에 있는지를 찾으면 된다.
음 결국 heardoc 노드를 따로 만드는게 맞는듯.. hear_doc이 가장 마지막 open인 경우에만 그 fd로 open을 하면 되지만,
만약 아닌경우 모든 명령을 돌면 된다.
여기서 가장 마지막 hear_doc이 맞는경우 어떻게 돌아야하는가? 이 경우는 open을 해보긴 하지만 순서대로 실패하는지만 검사를 해보면 된다.
*/

int	fork_child(t_main_node *px)
{
	int		i;
	pid_t	pid;
	int		status;

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
		if (i == 0)
			waitpid(pid, &status, 0);
	}
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
