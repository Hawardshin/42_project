/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 12:09:57 by joushin           #+#    #+#             */
/*   Updated: 2022/08/18 10:22:35 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "../libft/libft.h"

void	ft_error(void)
{
	write(2, "Error\n", 6);
	exit(1);
}

static void	count_num(t_stack *a, int *tmp)
{
	int		cnt;
	t_node	*tnode;
	t_node	*node;
	int		i;

	node = a->head;
	i = 0;
	while (node != NULL)
	{
		cnt = 1;
		tnode = a -> head;
		while (tnode != NULL)
		{
			if (node ->num > tnode ->num)
				cnt++;
			tnode = tnode -> next;
		}
		tmp[i++] = cnt;
		node = node -> next;
	}
}

static void	node_indexing(t_stack *a)
{
	int		i;
	t_node	*node;
	int		*tmp;

	node = a -> head;
	tmp = malloc(sizeof(int) * (a->count + 1));
	if (!tmp)
		exit(1);
	i = 0;
	count_num(a, tmp);
	i = 0;
	node = a->head;
	while (node != NULL)
	{
		node -> num = tmp[i++];
		node = node -> next;
	}
	free(tmp);
}

static void	data_init(t_stack *stack_a, int argc, char **argv)
{
	char	**splited;
	char	*tmp;
	int		i;

	i = 0;
	stack_a -> head = NULL;
	stack_a -> tail = NULL;
	stack_a -> count = 0;
	tmp = ft_all_join(argc, argv);
	if (!tmp)
		exit(1);
	splited = ft_split(tmp, ' ');
	free(tmp);
	if (!splited)
		exit(1);
	i = 0;
	while (splited[i])
	{
		add_node(chk_dup(ft_atoi_c(splited[i]), stack_a), stack_a);
		stack_a -> count++;
		free(splited[i]);
		i++;
	}
	free(splited);
	node_indexing(stack_a);
}

int	main(int argc, char **argv)
{
	t_stack	*stack_a;
	t_stack	*stack_b;

	if (argc < 2)
		return (0);
	stack_a = (t_stack *)malloc(sizeof(t_stack));
	stack_b = (t_stack *)malloc(sizeof(t_stack));
	if (!stack_a || !stack_b)
		exit(1);
	stack_b -> head = NULL;
	stack_b -> tail = NULL;
	stack_b -> count = 0;
	data_init(stack_a, argc, argv);
	if (ft_is_sorted(stack_a, stack_b) == 0)
	{
		div_stack(stack_a, stack_b);
		sort_start(stack_a, stack_b);
	}
	ft_mlstclear(&stack_a->head);
	ft_mlstclear(&stack_b->head);
	free(stack_a);
	free(stack_b);
}
