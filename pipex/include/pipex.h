/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 15:07:21 by joushin           #+#    #+#             */
/*   Updated: 2022/09/01 15:27:36 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/wait.h>

typedef struct s_px
{
	char		**cmd;
	char		*cmd_path[2];
	int			idx;
	struct s_px	*next;
}t_px;

typedef struct s_data
{
	char	*infile;
	char	*outfile;
	char	**ev;
	char	**path;
	int		pipefd[2];
	int		cmd_num;
	t_px	*cmd_node_head;
	t_px	*cmd_node_tail;
}t_data;

char	**ft_msplit(char const *str, char c);

void	print_error(int Flag, char *s);

void	parse_input(t_data *px, int argc, char **argv, char **envp);
void	cmd_init(t_data *px);

int		fork_child(t_data *px);

void	my_free(char **to_free);
char	*ft_mstrdup(const char *s1);
char	*ft_mstrjoin(char const *s1, char *s2);
t_px	*mlst_find(int idx, t_data *data);
pid_t	mfork(void);


#endif
