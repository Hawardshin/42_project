/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_bonus.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 12:10:01 by joushin           #+#    #+#             */
/*   Updated: 2022/08/17 12:55:07 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_BONUS_H
# define PUSH_SWAP_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif
# include <stdlib.h>
# include <unistd.h>

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

//get_next_line_bonus.c
char	*get_next_line(int fd);
char	*ft__strjoin(char *s1, char *s2);
char	*ft__strdup(const char *s1);
void	*ft__memmove(void *dst, const void *src, size_t len);
size_t	ft__strlen(const char *str);

//push_swap_utils_bonus.c
char	*ft_all_join(int argc, char **argv);
void	add_node(int data, t_stack *stack_a);
int		ft_atoi_c(const char *str);
void	ft_mlstclear(t_node **node);
int		chk_dup(int in, t_stack *stack_a);

//command_utils_bonus.c
void	push_front(t_stack *s, t_node *new);
void	push_back(t_stack *s, t_node *new);
t_node	*pop_front(t_stack *s);
t_node	*pop_back(t_stack *s);

//command_bonus.c
void	push_stack(t_stack *a, t_stack *b, char s);
void	swap_stack(t_stack *a, t_stack *b, char s);
void	reverse_stack(t_stack *a, t_stack *b, char s);
void	rreverse_stack(t_stack *a, t_stack *b, char s);

//command_double_bonus.c
void	rrr_stack(t_stack *a, t_stack *b);
void	rr_stack(t_stack *a, t_stack *b);
void	ss_stack(t_stack *a, t_stack *b);
void	command_optimize(t_stack *a, t_stack *b, t_node **node);

//main_bonus.c
void	ft_error(void);
void	data_init(t_stack *stack_a, int argc, char **argv);

//list_bonus.c
int		list_head_find(t_stack *a, int start, int end);
int		list_tail_find(t_stack *a, int start, int end);

//div_stack_bonus.c
void	div_stack(t_stack *a, t_stack *b);
void	swap_rev(int len, t_stack *a, t_stack *b, char c);
void	swap_for(int len, t_stack *a, t_stack *b, char c);
int		div_pivot(int start, int end, t_stack *a, t_stack *b);

//three_argv_bonus.c
void	three_argv(t_stack *a, t_stack *b);

//sort_bonus.c
void	sort_start(t_stack *a, t_stack *b);

// sort_utils_bonus.c
int		node_rank(t_stack *stack, int n);
void	go_head(t_stack	*a, t_stack *b, int idx, char c);
void	go_tail(t_stack *a, t_stack *b, int idx, char c);
int		ft_a_score(t_stack *stack, int n);
void	score_b(t_stack *a, t_stack *b);

#endif
