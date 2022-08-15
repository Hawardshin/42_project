/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 12:42:34 by joushin           #+#    #+#             */
/*   Updated: 2022/08/15 19:21:47 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "./libft/libft.h"
//중복 체크해주기, int_max넘는지 확인, 문제 없으면 데이터 넣어주기.

//한꺼번에 다 넣어버리고 에러 핸들링 해주기 위한 함수.
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

void	add_node(int data, t_stack *stack_a)
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
		stack_a -> head = new_node;
	stack_a -> tail = new_node;
}


//atoi에서 - 하나 받거나 + 하나 받는거 터트려? 일단 난 잡자.
int	ft_atoi_c(const char *str)
{
	int					sign;
	unsigned long long	result;

	sign = 1;
	result = 0;
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
	if (result > 2147483648 && sign == -1)
		ft_error();
	else if (sign == 1 && result > 2147483647)
		ft_error();
	return ((int)sign * result);
}

void	ft_mlstclear(t_node **node)
{
	t_node	*tmp;

	while ((*node) != NULL)
	{
		tmp = *node;
		*node = (*node) -> next;
		free(tmp);
		tmp = NULL;
	}
	*node = NULL;
}
//이걸 리스트 클리어 해주고 하는게 맞는걸까? 어차피 다 exit 할꺼라면 필요 없지 않나

int	chk_dup(int in, t_stack *stack_a)
{
	t_node	*now;

	now = stack_a ->head;
	while (now != NULL)
	{
		if (now -> num == in)
			ft_error();
		else
			now = now -> next;
	}
	return (in);
}
