/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joushin <joushin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 13:19:47 by joushin           #+#    #+#             */
/*   Updated: 2022/11/26 20:20:59 by joushin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H
# define BUFFER_SIZE 42

# include "node.h"

int		ft_strcmp(char *str1, char *str2);
void	my_free(void **to_free);
char	*ft_mstrdup(const char *s1);
char	*ft_mstrjoin(char const *s1, char const *s2);
pid_t	mfork(void);
char	**ft_msplit(char *str, char c);
void	syntax_error(void);
void	print_error(int Flag, char *s);
char	*get_next_line(int fd);
char	**ft_msplit(char *str, char c);
size_t	ft__strlen(const char *str);
void	*ft__memmove(void *dst, const void *src, size_t len);
size_t	ft__strlcpy(char *dst, const char *src, size_t dstsize);
char	*ft__strdup(const char *s1);
char	*ft__strjoin(char *s1, char *s2);

char	**ret_env_char(void);
void	tok_clean(t_main_token	*mtok);
void	pipe_init(t_main_node *main_node);
void	ft_end_free(t_main_node *px);

void	ft_tc_on(void);
void	ft_tc(void);

#endif
