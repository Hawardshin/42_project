/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 12:10:01 by joushin           #+#    #+#             */
/*   Updated: 2022/08/13 17:12:45 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdlib.h>
# include <unistd.h>
#include <stdio.h>/////

typedef struct s_node
{
	int				num;
	int				ascore;
	int				bscore;
	struct s_node	*next;
	struct s_node	*bef;
}t_node;

typedef struct s_stack
{
	int		count;
	t_node	*head;
	t_node	*tail;
}t_stack;
void printstack(t_stack *stack_a);/////
//push_swap_utils.c
char	*ft_all_join(int argc, char **argv);
void	add_node(int data, t_stack *stack_a);
int		ft_atoi_c(const char *str);
void	ft_mlstclear(t_node **node);
int		chk_dup(int in, t_stack *stack_a);

//command.c
void	push_front(t_stack *s, t_node *new);
void	push_back(t_stack *s, t_node *new);
t_node	*pop_front(t_stack *s);
t_node	*pop_back(t_stack *s);
void	push_stack(t_stack *a, t_stack *b, char s);
void	swap_stack(t_stack *a, t_stack *b, char s);
void	reverse_stack(t_stack *a, t_stack *b, char s);
void	rreverse_stack(t_stack *a, t_stack *b, char s);
//main.c
void	ft_error(void);
void	data_init(t_stack *stack_a, int argc, char **argv);

//list.c
int	list_head_find(t_stack *a, int start, int end);
int	list_tail_find(t_stack *a, int start, int end);

//div_stack.c
void	div_stack(t_stack *a, t_stack *b);
void	go_head(t_stack	*a, t_stack *b, int idx, char c);
void	go_tail(t_stack *a, t_stack *b, int idx, char c);

//chk.c
void	two_argv(t_stack *a, t_stack *b);
void	three_argv(t_stack *a, t_stack *b);

//sort.c
void	sort_start(t_stack *a, t_stack *b);

#endif
