/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 12:09:57 by joushin           #+#    #+#             */
/*   Updated: 2022/08/08 15:58:05 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "./libft/libft.h"

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
		stack_a -> count++;
		//printf("%d",(*stack_a) ->head ->num);
		free(splited[i]);
		i++;
	}
	free(splited);
}

//테스트용 함수
void printstack(t_stack *stack_a)
{
	if (stack_a -> count == 0)
	{
		printf("NULL\ns");
		return ;
	}
	printf("count :: %d\n",stack_a -> count);
	t_node *tmp = (stack_a ->head);
	while (tmp -> next != NULL)
	{
	 	printf("%d\n", tmp->num);
		tmp = tmp -> next;
	}
	printf("%d", tmp->num);
}

int	main(int argc, char **argv)
{
	setvbuf(stdout, NULL, _IONBF, 0);/////printf write순서 맞추기
	t_stack	*stack_a;
	t_stack	*stack_b;//나중에 최적화 하기

	stack_a = (t_stack *)malloc(sizeof(t_stack));
	if (!stack_a)
		return (0);
	stack_b = (t_stack *)malloc(sizeof(t_stack));
	if (!stack_b)
		return (0);
	if (argc  < 2)
		return (0);
	stack_a -> head = NULL;
	stack_a -> tail = NULL;
	stack_a -> count = 0;
	stack_b -> head = NULL;
	stack_b -> tail = NULL;
	stack_b -> count = 0;
	data_init(stack_a, argc, argv);
	////

	printstack(stack_a);
	printstack(stack_b);
	push_stack(stack_a, stack_b, 'b');
	push_stack(stack_a, stack_b, 'b');
	push_stack(stack_a, stack_b, 'b');
	printf("\n::::a::::\n");
	printstack(stack_a);
	printf("\n::::b::::\n");
	printstack(stack_b);
	swap_stack(stack_a, stack_b, 'C');
	printf("\nafter swap\n::::a::::\n");
	printstack(stack_a);
	printf("\n::::b::::\n");
	printstack(stack_b);
	reverse_stack(stack_a, stack_b, 'C');
	printf("\nafter reverse\n::::a::::\n");
	printstack(stack_a);
	printf("\n::::b::::\n");
	printstack(stack_b);
	rreverse_stack(stack_a, stack_b, 'C');
	printf("\nafter rreverse\n::::a::::\n");
	printstack(stack_a);
	printf("\n::::b::::\n");
	printstack(stack_b);
}
