/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_bonus.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 12:10:01 by joushin           #+#    #+#             */
/*   Updated: 2022/08/17 17:06:18 by joushin          ###   ########.fr       */
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

void	sort_check(t_stack *a, t_stack *b);

char	*get_next_line(int fd);
char	*ft__strjoin(char *s1, char *s2);
char	*ft__strdup(const char *s1);
void	*ft__memmove(void *dst, const void *src, size_t len);
size_t	ft__strlen(const char *str);

char	*ft_all_join(int argc, char **argv);
void	add_node(int data, t_stack *stack_a);
int		ft_atoi_c(const char *str);
void	ft_mlstclear(t_node **node);
int		chk_dup(int in, t_stack *stack_a);

char	*get_next_line(int fd);

void	push_front(t_stack *s, t_node *new);
void	push_back(t_stack *s, t_node *new);
t_node	*pop_front(t_stack *s);
t_node	*pop_back(t_stack *s);

void	push_stack(t_stack *a, t_stack *b, char s);
void	swap_stack(t_stack *a, t_stack *b, char s);
void	reverse_stack(t_stack *a, t_stack *b, char s);
void	rreverse_stack(t_stack *a, t_stack *b, char s);

void	rrr_stack(t_stack *a, t_stack *b);
void	rr_stack(t_stack *a, t_stack *b);
void	ss_stack(t_stack *a, t_stack *b);

void	ft_error(void);

#endif
