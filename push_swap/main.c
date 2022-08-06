/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 12:09:57 by joushin           #+#    #+#             */
/*   Updated: 2022/08/06 18:04:39 by joushin          ###   ########.fr       */
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
//중복 체크해주기, int_max넘는지 확인, 문제 없으면 데이터 넣어주기.
//넣으면서 0부터 데이터 넣어주기.

char	*ft_all_join(int argc, char **argv)
{
	int		i;
	int		len;
	char	*str;
	int		idx;
	int		j;

	i = 0;
	idx = 0;
	len = 0;
	while (++i < argc)
		len += ft_strlen(argv[i]);
	i = 0;
	str = (char *)malloc(sizeof(char) * (len + argc));
	if (!str)
		return (NULL);
	while (++i < argc)
	{
		j = 0;
		while (argv[i][j])
			str[idx++] = argv[i][j++];
		if (i != argc - 1)
			str[idx++] = ' ';
	}
	return (str);
}

//head와 tail이 같은 상황에 대한 고려가 필요
//new_node 동적 할당 실패했을 경우?
void	add_new_node(int data, t_stack *stack_a)
{
	t_node	*new_node;

	new_node = (t_node *)malloc(sizeof(t_node));
	if (!new_node)
		return ;
	new_node -> num = data;
	new_node -> bef = stack_a ->tail;
	if (stack_a -> tail != NULL)
		stack_a -> tail -> next = new_node;
	new_node -> next = NULL;
	if (((stack_a) -> head) == NULL)
	{
	//	printf("Aas");
		stack_a -> head = new_node;
	}
	//printf("b");
	stack_a -> tail = new_node;
}
//atoi에서 - 하나 받거나 + 하나 받는거 터트려? 일단 난 잡자.
int	ft_atoi_c(const char *str)
{
	int					sign;
	unsigned long long	result;

	sign = 1;
	result = 0;
	// while ((*str >= 9 && *str <= 13) || *str == ' ')
	// 	str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	if (!*str)
		ft_error();
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + *str - '0';
		str++;
	}
	if (*str)
		ft_error();
	if (result > 2147364748 && sign == -1)
		ft_error();
	else if (sign == 1 && result > 2147364747)
		ft_error();
	return ((int)sign * result);
}

//atoi변경 해서 바로 실패시 바로 프로세스 종료 이렇게 해도 될까?
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
		add_new_node(ft_atoi_c(splited[i]), stack_a);
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
