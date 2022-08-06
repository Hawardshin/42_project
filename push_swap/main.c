/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 12:09:57 by joushin           #+#    #+#             */
/*   Updated: 2022/08/06 18:55:57 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "./libft/libft.h"
#include<stdio.h>///////
void	ft_error(void)
{
	write(2, "Error\n", 6);
	exit(1);
}

//넣으면서 0부터 데이터 넣어주기.
//atoi변경 실패시 프로세스 종료 이렇게 해도 될까?
void	data_init(t_stack *stack_a, int argc, char **argv)
{
	char	**splited;
	char	*tmp;
	int		i;

	i = 0;
	tmp = ft_all_join(argc, argv);
	//printf("%s",tmp);
	splited = ft_split(tmp, ' ');
	if (!splited)
		ft_error();
	free(tmp);
	while (splited[i])
	{

		add_node(chk_dup(ft_atoi_c(splited[i]), stack_a), stack_a);
		//printf("%d",(*stack_a) ->head ->num);
		free(splited[i]);
		i++;
	}
	free(splited);
}

#include<stdio.h>
int	main(int argc, char **argv)
{
	t_stack	*stack_a;
	stack_a = (t_stack *)malloc(sizeof(t_stack));
	if (!stack_a || argc  < 2)
		return (0);
	stack_a -> head = NULL;
	stack_a -> tail = NULL;
	data_init(stack_a, argc, argv);
	//
	//printf("%d",stack_a ->head ->num);
	t_node *tmp = (stack_a ->head);
	while (tmp -> next != NULL)
	{
		printf("%d", tmp->num);
		tmp = tmp -> next;
	}
	printf("%d", tmp->num);
}
