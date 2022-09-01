/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 09:57:04 by joushin           #+#    #+#             */
/*   Updated: 2022/09/01 15:49:41 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/wait.h>
# define BUFFER_SIZE 42

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
	int		**pipefd;
	int		cmd_num;
	int		flag;
	t_px	*cmd_node_head;
	t_px	*cmd_node_tail;
}t_data;

void	print_error(int Flag, char *s);
void	ft_all_close(t_data *px, int idx, int bef);
void	ft_end_free(t_data *px);

void	parse_input(t_data *px, int argc, char **argv, char **envp);
void	cmd_init(t_data *px);

int		fork_child(t_data *px);

void	my_free(char **to_free);
char	*ft_mstrdup(const char *s1);
char	*ft_mstrjoin(char const *s1, char const *s2);
t_px	*mlst_find(int idx, t_data *data);
pid_t	mfork(void);

char	**ft_msplit(char const *str, char c);

size_t	ft__strlen(const char *str);
void	*ft__memmove(void *dst, const void *src, size_t len);
size_t	ft__strlcpy(char *dst, const char *src, size_t dstsize);
char	*ft__strdup(const char *s1);
char	*ft__strjoin(char *s1, char *s2);

char	*get_next_line(int fd);

#endif
